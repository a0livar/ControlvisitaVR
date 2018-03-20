#include <Arduino.h>

/******

Definición de protocolo

AA01016400FF
AA = Inicio de paquete
01 = Tipo
01 = Canal
01 = Funcion
64 = Valor
00 = Tiempo
FF = Cierre de paquete

Tipo
1 = Dimmer corriente continua
2 = Dimmer corriente alterna
3 = Secuencia
4 = DMX

Valor
0 -> 100

*******/

//Pinout tipo 1
#define PIN_PWM_1 9
#define PIN_PWM_2 10
#define PIN_PWM_3 11


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

uint8_t tipo = 0, canal = 0, valor = 0, tiempo = 0;
uint8_t i = 0, j = 0;
uint8_t aa = 0x00;

//Variables buffer circular
byte chk_sum = 0;
int estado = 1;
//byte tipo = 0;
int escribe = 0;
int lee = 0;
int largoData = 0;
const unsigned int LARGO = 0xFF;
byte data[LARGO] = "\0";
byte resp[8] = "\0";
byte infoServidor[LARGO] = "\0";
int indiceInfo = 0;
unsigned long tiempoPing = 0;
boolean ackn_e = false;
byte dataFrame[20] = "\0";
byte dirFrame[6] = "\0";
uint32_t dirFrameMs_hx = 0x0013a200;
uint32_t dirFrameLs_hx = 0;


/*
 * FUNCIONES
 */
 int distancia(void);
 void incrementaLee(void);
 int determinaTipo(byte *);

 /*
  *  Esta funcion incremente el valor y mantiene su circularidad
  *
  */
void incrementaEscribe(){
    escribe++;
    escribe &= LARGO;
  }
/*
 * Función que llena el buffer circular que contiene las tramas
 * @author Andres Olivares
 */
void escribeFunction(){
    data[escribe] = (byte) Serial1.read();
    Serial.write(data[escribe]);
   incrementaEscribe();
}

void leeFunction(){
    if (distancia() != 0){
       switch (estado){
        case 1:{
            if (data[lee] == 0xAA){
              //Serial.println("Posible cabecera");
              Serial.println("Posible peticion de servidor");
              estado = 2;
              //data[lee] = '0';
            }
            else if(data[lee] == 0x45){
              //Error
              char kackn[6] = {0x45, 0x52, 0x52, 0x4F, 0x52};//Error
              char ackn[6] = "\0";
              int i = 0;
              int aux = lee;
              do {
                ackn[i] = data[aux];
                i++;
                aux++;
              } while(i < 5);
              if(strcmp(ackn,kackn) == 0){
                Serial.println("Error de socket, reiniciando GSM");
                //Levantar servicio
                levantarServicio();
                estado = 1;
              }
            }
            incrementaLee();
          }break;
        case 2:{

          int aux = lee;
          tipo = data[aux];
          //data[lee] = '0';
          aux++;
          largoData = data[aux] - 4;
          // Serial.print("Largo data: ");
          // Serial.println(largoData);
          //data[lee] = '0';
          aux++;
          chk_sum = 0;
          dirFrameLs_hx = 0;
          for(int i = 0; i < 4; i++){
            dirFrame[i] = data[aux];
            chk_sum += data[aux];
            //data[lee] = '0';
            aux++;
          }

          dirFrameLs_hx = dirFrame[0];
          dirFrameLs_hx = dirFrameLs_hx << 8;
          dirFrameLs_hx += dirFrame[1];
          dirFrameLs_hx = dirFrameLs_hx << 8;
          dirFrameLs_hx += dirFrame[2];
          dirFrameLs_hx = dirFrameLs_hx << 8;
          dirFrameLs_hx += dirFrame[3];

          // Serial.print("Direccion en hexa: ");
          // Serial.println(dirFrameLs_hx,HEX);

          for(int i = 0; i < largoData; i++){
            dataFrame[i] = data[aux];
            chk_sum += data[aux];
            //data[lee] = '0';
            aux++;
          }
          // Serial.print("Checksum: ");
          // Serial.write(chk_sum);
          // Serial.println("");
          if(chk_sum == data[aux] && chk_sum != 0){
            Serial.println("Checksum correcto");
            Serial.println("");
            Serial.println("Peticion valida entrante");
            estado = 3;
            lee = aux;
          }
          else{
            Serial.println("Checksum incorrecto");
            Serial.println("Paquete inválido");
            estado = 1;
          }
          }break;
        case 3:{

          switch (tipo){
           case 0x01:{
             //Caso de respuesta disponible {0x02}
             }break;
           case 0x05:{
             Serial.println("Redireccionando");
             Serial.print("");
            //  Serial.print("Direccion: ");
            //  for(int i = 0;i < 4; i++){
            //    Serial.write(dirFrame[i]);
            //  }
             //Serial.println(dirFrame_hx, HEX);
            //  Serial.println("");
            //  Serial.println("Data: ");
            //  for(int i = 0;i < largoData; i++){
            //    Serial.write(dataFrame[i]);
            //  }
            //  Serial.println("");

             Serial.print("Enviando a Nodo: ");
             Serial.print(dirFrameMs_hx,HEX);
             Serial.print("-");
             Serial.println(dirFrameLs_hx,HEX);


             Serial.print("Largo: ");
             Serial.println(largoData);

             Serial.println("Data: ");
             for(int i = 0; i < largoData;i++){
               Serial.print("Byte[");
               Serial.print(i);
               Serial.print("]: ");
               Serial.println(dataFrame[i],HEX);

             }
             Serial.println("");


             XBeeAddress64 addr64 = XBeeAddress64(dirFrameMs_hx, dirFrameLs_hx);
             ZBTxRequest zbTx = ZBTxRequest(addr64, dataFrame, largoData);
             ZBTxStatusResponse txStatus = ZBTxStatusResponse();

             xbee.send(zbTx);

             if (xbee.readPacket(500)) {
               // got a response!

               // should be a znet tx status
               if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
                 xbee.getResponse().getZBTxStatusResponse(txStatus);

               // get the delivery status, the fifth byte
               if (txStatus.getDeliveryStatus() == SUCCESS) {
                 //success.  time to celebrate
                 Serial.println("Enviado");
               } else {
                 //the remote XBee did not receive our packet. is it powered on?
                 Serial.println("No hubo respuesta de destinatario");
               }
             }

           } else if (xbee.getResponse().isError()) {
             Serial.println("LLego paquete pero con Error");
             //Serial.print("Error reading packet.  Error code: ");
             //Serial.println(xbee.getResponse().getErrorCode());
           } else {
             Serial.println("TimeOut en comunicacion");
             // local XBee did not provide a timely TX Status Response -- should not happen
             //Serial.println("local xBee no proporciona un tiempo para la respuesta Tx status");
           }

           estado = 1;
           //dataFrame[LARGO] = "\0";
           memset(dataFrame, 0, sizeof(dataFrame));
           memset(dirFrame, 0, sizeof(dirFrame));
           dirFrameLs_hx = 0x00;
           }break;
         default:{
           estado = 1;
           }break;
         }
        }break;
      }
  }
}

void incrementaLee(){
    lee++;
    lee &= LARGO;
}

/**
* Determina según los indices lee y escribe la distancia que existe entre los 2 punteros
*/
int distancia(){
  if (lee == escribe){
    return 0;
    }
  if (lee < escribe){
    return escribe - lee;
    }else{
      return (LARGO - lee) + escribe + 1;
    }
  }
void serialEvent1(){
  while(Serial1.available()>0)
  {
    escribeFunction();
  }
}


void setup() {
  Serial.begin(9600);

  pinMode(PIN_PWM_1, OUTPUT);
  pinMode(PIN_PWM_2, OUTPUT);
  pinMode(PIN_PWM_3, OUTPUT);

  previousMillis = currentMillis;
}

void loop() {

//1er Hilo
  if (distancia() > 5){
      leeFunction();
  }
  currentMillis = millis();

    // put your main code here, to run repeatedly:
}
