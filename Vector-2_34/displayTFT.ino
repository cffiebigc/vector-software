// Software de control para máquina de Vector
// Creado por Carlos Fiebig Cosmelli - cffiebigc@gmail.com

void resetScreen() {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(20, 150);
  tft.setTextSize(0);
  tft.print("INCIDE Software");
  tft.setTextSize(1);
  tft.setCursor(0, 10);
}

void alarmScreen() {
  tft.setTextColor(ST7735_RED);
  tft.setCursor(0, 20);
  tft.setTextSize(2);
  tft.println("Temperaturas sobre 70°C");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Por favor repare el problema y reinicie este dispositivo");
}

void writeMotorStatus(){
  if(motor){
    tft.drawChar(100, 10, 'M', ST7735_WHITE, ST7735_BLACK, 2);
  }
  else{
    tft.drawChar(100, 10, 'M', ST7735_BLACK, ST7735_BLACK, 2);
  }
}

void writeWP1Status(){
  if(wp1){
    tft.drawChar(100, 20, '1', ST7735_WHITE, ST7735_BLACK, 2);
  }
  else{
    tft.drawChar(100, 20, '1', ST7735_BLACK, ST7735_BLACK, 2);
  }
}

void writeWP2Status(){
  if(wp2){
    tft.drawChar(100, 30, '2', ST7735_WHITE, ST7735_BLACK, 2);
  }
  else{
    tft.drawChar(100, 30, '2', ST7735_BLACK, ST7735_BLACK, 2);
  }
}

void printStatus(){
  if(funcionando){
    tft.setCursor(30, 120);
    tft.setTextColor(ST7735_WHITE);
    tft.print("AUTO");
  }
  else{
    tft.setCursor(30, 120);
    tft.setTextColor(ST7735_BLACK);
    tft.print("AUTO");
  }
}
