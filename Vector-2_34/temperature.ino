// Software de control para máquina de Vector
// Creado por Carlos Fiebig Cosmelli - cffiebigc@gmail.com
int counter = 1;
double sum1, sum2, sum3 = 0;
int prom = 8;

void readTemperatures(){
  sum1 += thermocoupleMotorE.readCelsius()-6;
  sum2 += thermocoupleMotorS.readCelsius()-6;
  sum3 += tCasa = dht.readTemperature();
  if (counter == prom){
    tcMotorE = (sum1/prom) - offset1;
    tcMotorS = (sum2/prom) - offset2;
    tCasa = (sum3/prom) - offset3;
    counter = 0;
    sum1 = sum2 = sum3 = 0;
    showTemp = true;
  }
  counter++;
}

void setTemperature() {
  String str;
  // Arriba a la IZQ
  char res2[5];
  str = String(tcMotorE);
  str.toCharArray(res2, 5);
  if(tcMotorE < 10){
    lc.setChar(0,7,0, false);
    lc.setChar(0,6,res2[0], true);
    lc.setChar(0,5,res2[2], false);
  }
  else {
    lc.setChar(0,7,res2[0], false);
    lc.setChar(0,6,res2[1], true);
    lc.setChar(0,5,res2[3], false);  
  }

  // Arriba a la DER
  char res1[5];
  str = String(tcMotorS);
  str.toCharArray(res1, 5);
  if(tcMotorS < 10){
    lc.setChar(0,3,0, false);
    lc.setChar(0,2,res1[0], true);
    lc.setChar(0,1,res1[2], false);
  }else {
    lc.setChar(0,3,res1[0], false);
    lc.setChar(0,2,res1[1], true);
    lc.setChar(0,1,res1[3], false);
  }

  // Abajo a la IZQ
  char res4[5];
  str = String(tCasa);
  str.toCharArray(res4, 5);
  if(tCasa < 10) {
    lc.setChar(1,7,0, false);
    lc.setChar(1,6,res4[0], true);
    lc.setChar(1,5,res4[2], false);
  }
  else {
    lc.setChar(1,7,res4[0], false);
    lc.setChar(1,6,res4[1], true);
    lc.setChar(1,5,res4[3], false);
  }
}
