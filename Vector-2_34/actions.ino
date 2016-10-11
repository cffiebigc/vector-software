void heatWater(){
  // Enciende Máquina para calentar agua y recirculación solo con termo
  motor = wp1 = true;
  wp2 = false;
  digitalWrite(MAIN_MOTOR, HIGH);
  digitalWrite(W_PUMP1, HIGH);
  // Apaga recirculación CASA
  digitalWrite(W_PUMP2, LOW);
  if (stabilize){
    double sum1 = thermocoupleMotorE.readCelsius()-6;
    double sum2 = thermocoupleMotorS.readCelsius()-6;
    double sum3 = tCasa = dht.readTemperature();
    offset1 = prevTemp1 - sum1;
    offset2 = prevTemp2 - sum2;
    offset3 = prevTemp3 - sum3;
    stabilize = false;
  }
}

void recirculate(){
  // Apaga Máquina para calentar agua y recircula a Casa
  motor = wp1 = false;
  wp2 = true;
  digitalWrite(MAIN_MOTOR, LOW);
  digitalWrite(W_PUMP1, LOW);
  // Apaga recirculación CASA
  digitalWrite(W_PUMP2, HIGH);  
}

void turnOffEverything(){
  motor = wp1 = wp2 = false;
  digitalWrite(MAIN_MOTOR, LOW);
  digitalWrite(W_PUMP1, LOW);
  digitalWrite(W_PUMP2, LOW);
}

void initialSetup(){
  dht.begin();
  pinMode(MAIN_MOTOR, OUTPUT);
  pinMode(W_PUMP1, OUTPUT);
  pinMode(W_PUMP2, OUTPUT);
  pinMode(PWM, OUTPUT);
  keypad.addEventListener(keypadEvent);
  tft.initR(INITR_BLACKTAB);  // Fill black
  resetScreen(); // pantalla a negro con letras de incide en el final
  lc.shutdown(0, false);
  lc.setIntensity(0, 15); // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0); 
  lc.shutdown(1, false);
  lc.setIntensity(1, 15);
  lc.clearDisplay(1); 
  delay(500);
}

