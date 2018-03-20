#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
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
    data[escribe] = (byte) Serial.read();
    //Serial.write(data[escribe]);
   incrementaEscribe();
}

void leeFunction(){
    if (distancia() != 0){
       switch (estado){
        case 1:
            if (data[lee] == 0xAA){
              //Serial.println("Posible cabecera");
              //Serial.println("Posible peticion de servidor");
              estado = 2;
              //data[lee] = '0';
            }
            else estado = 1;

            incrementaLee();
        break;

        case 2:

          tipo = data[lee];
          incrementaLee();

          switch (tipo) {
            case 1:   //Dimmer corriente continua
              canal = data[lee];
              incrementaLee();
              valor = data[lee];
              incrementaLee();

              analogWrite(canal, (valor*255)/100);

            break;

            case 2: //Dimmer de corriente alterna
              canal = data[lee];
              incrementaLee();
              valor = data[lee];
              incrementaLee();

              if (canal == 1) {
                if (valor<100) {
                  char buffer_valor[4] = " ";
                  sprintf(buffer_valor, "A0%d",valor);
                  Serial.print(buffer_valor);
                }
                else{
                  char buffer_valor[4] = " ";
                  sprintf(buffer_valor, "A%d",valor);
                  Serial.print(buffer_valor);
              }
              }
              if (canal == 2) {
                if (valor<100) {
                  char buffer_valor[4] = " ";
                  sprintf(buffer_valor, "B0%d",valor);
                  Serial.print(buffer_valor);
                }
                else{
                  char buffer_valor[4] = " ";
                  sprintf(buffer_valor, "B%d",valor);
                  Serial.print(buffer_valor);
              }
              }
            break;

            case 3: // Control de DMX
              /*****Pendiente de elaborar****/
            break;

            default:
              estado = 1;
            break;
          }
          break;

          default:
            estado = 1;
          break;
          }


           estado = 1;
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
void serialEvent(){
  while(Serial.available()>0)
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

    // put your main code here, to run repeatedly:
}
