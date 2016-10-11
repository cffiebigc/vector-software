// Software de control para máquina de Vector
// Creado por Carlos Fiebig Cosmelli - cffiebigc@gmail.com

void writeIRMS() {
  if (showPwr)
    price = 162.19*2.2/3600*(millis()/1000);
  tft.setCursor(0, 10);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Consumo equipo");
  tft.setCursor(0, 30);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("W:");
  tft.println("2200"); // Apparent power W
  tft.setTextColor(ST7735_MAGENTA);
  tft.print("A:");
  tft.print("10"); // A
  tft.setCursor(0, 70);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Costo de consumo");
  tft.setCursor(0, 90);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_GREEN);
  tft.print("$:");
  tft.print(price);
}

void deleteIRMS() {
  tft.fillRect(20, 85 , 100, 25, ST7735_BLACK);
}
