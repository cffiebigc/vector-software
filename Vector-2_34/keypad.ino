// Software de control para máquina de Vector
// Creado por Carlos Fiebig Cosmelli - cffiebigc@gmail.com

void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
    case PRESSED:
      switch(key){
        case 'A':
          prevTemp1 = tcMotorE;
          prevTemp2 = tcMotorS;
          prevTemp3 = tCasa;
          showPwr = !showPwr;
          funcionando = !funcionando;
          if (funcionando){
            stabilize = true; 
          }
          else {
            offset1 = offset2 = offset3 = 0;
          }
          printStatus();
          break;
        case 'B':
          if(!funcionando){
            heatWater();
            writeMotorStatus();
            writeWP1Status();
          }
          break;
        case 'C':
          if(!funcionando){
            turnOffEverything();
            writeMotorStatus();
            writeWP1Status();
          }
          break;
        case 'D':
          if(!funcionando){
            wp2 = !wp2;
            if(wp2)
              digitalWrite(W_PUMP2, HIGH);
            else
              digitalWrite(W_PUMP2, LOW);
            writeWP2Status();
          }
          break;
        case '#':
          break;
        case '*':
          break;
        break;
      }
    case RELEASED:
      if (key == '*') {
      }
      break;

    case HOLD:
      if (key == '*') {
      }
      break;
  }
}
