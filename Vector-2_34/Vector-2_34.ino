// Software de control para máquina de Vector
// Creado por Carlos Fiebig Cosmelli - cffiebigc@gmail.com

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Keypad.h>
#include "max6675.h"
#include "LedControl.h"
#include "DHT.h"

#define TFT_CS      53  //10  // gris:      CS  53 (ss) 
#define TFT_RST     48  //9   // amarillo:  RST 48 
#define TFT_DC      49  //8   // verde:     A0  49
#define TFT_SCLK    52  //13  // lila:      SCK 52 (sck)
#define TFT_MOSI    51  //11  // azul:      SDA 51 (mosi)
#define MAIN_MOTOR  7       //digitalWrite(MAIN_MOTOR, HIGH);       Enciende motor principal
#define W_PUMP1     6       //digitalWrite(W_PUMP1, HIGH);          Enciende bomba de agua 1
#define W_PUMP2     5       //digitalWrite(W_PUMP2, HIGH);          Enciende bomba de agua 2
#define PWM         12      //analogWrite(PWM, 0); // Rango 0-255   PWM para control del variador de frecuencia
#define CURRENT     1
#define DHTPIN      8
#define DHTTYPE     DHT11

DHT dht(DHTPIN, DHTTYPE);

// display digitos en pines (2 CLK, 4 CS, 3 DIN , numero de dispositivos)
LedControl lc = LedControl(3, 2, 4, 2);

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {{'1', '2', '3', 'A'},{'4', '5', '6', 'B'},{'7', '8', '9', 'C'},{'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {23, 24, 25, 26};
byte colPins[COLS] = {27, 28, 29, 30}; 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

MAX6675 thermocoupleMotorE(41, 40, 39); // MAX6675 thermocouple1(thermoCLK, thermoCS1, thermoDO);
MAX6675 thermocoupleMotorS(37, 36, 35); // MAX6675 thermocoupleTermo(45, 44, 43); MAX6675 thermocouple4(33, 32, 31);

double tcMotorE, price, tcMotorS, Irms, tCasa = 0;
boolean showTemp, showPwr, setPrice, funcionando, motor, wp1, wp2 = false;
boolean calentar = true;
unsigned long refreshTime = 0;
double kwatt = 2.2;
double priceKWS = 162.19;
double prevTemp1, prevTemp2, prevTemp3 = 0;
double offset1, offset2, offset3 = 0;
boolean stabilize = false;

void setup(void) {
  initialSetup();
}

void loop() {
  // Pregunta de seguridad ¿las temperaturas se mantienen bajo los 70°C ?
  if(tcMotorS > 70 || tcMotorE > 70){ 
    turnOffEverything();
    resetScreen();
    alarmScreen();
  }
  // Modo automático
  if(funcionando){   
    if(calentar && tCasa < 24){
      heatWater();
    } else if(!calentar && tCasa < 20) {
      calentar = true;
    } else {
      calentar = false;
      recirculate();
    }
  }
  //lee del teclado
  char customKey = keypad.getKey();
  // lee las temperaturas de las termocuplas cada 180ms y acumula para entregar dato normado
  if(millis() > refreshTime){  
    readTemperatures();
    refreshTime = millis() + 180;
  }
  // muestra en pantalla las temperaturas y las refresca cada 2 segundos
  if (showTemp){   
    setTemperature();
    refreshTime = millis() + 1000;
    showTemp = false;
  }
  // muestra pantalla de consumo eléctrico y refresca cada 2 segundos
  if (millis() > refreshTime) {
    deleteIRMS();
    writeIRMS();
    refreshTime = millis() + 2000;
  }
  // pregunta de seguridad en el refresco, asegura que la tasa de refresco no sobrepase los 2,5 segundos
  if (refreshTime > millis() + 2500) {
    refreshTime = 0;
  }
}
