    // Include the libraries:
    // LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
    #include <Wire.h> // Library for I2C communication
    #include <LiquidCrystal_I2C.h> // Library for LCD
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

    const int batteries = 3;
    const int batteryPin[] = {A0, A2, A6, A4};
    const int basePin[] = {A1, A3, A7, A5};
    const float R[] = {10.0, 10.0, 10.0, 10.0};  // ohms
    const int ledPin[]= {9, 8, 7, 6};
    const float stopVoltage = 0.9;
    const float resetVoltage = 0.1;
    const int batteryOn = 1;
    const int batteryStop = 0;
    const int batteryReset = -1;
    const float referenceVoltage = 5.00;
    
    

    float batteryVoltage[3] = {0.0, 0.0, 0.0};  // volts
    float baseVoltage[3] = {0.0, 0.0, 0.0}; // volts
    float capacity[3] = {0L, 0L, 0L};  // mAh
    float energy[3] = {0L, 0L, 0L};  // mWh
    unsigned long previousTime = 0L;  // milliseconds
    unsigned long currentTime = 0L;  // milliseconds
    int batteryStatus[3] = {batteryReset, batteryReset, batteryReset};

    float latestViableCurrent[3] = {0.0, 0.0, 0.0}; // this is temporary
    unsigned long lastUpdate = 0L;
    long animationStep = -200;
    byte cursorLCD = 15;
    int numberOfColumns = 16;
    long randomVariable = 0;
    boolean waitForAnimationDelay = true;
    int printCycle = 0;
    
    void animationSetup() {
      for (int i=0; i < 8; i++) {
        byte charLine[8];
        for (int j=0; j < 8; j++) {
          if (j > i) charLine[7-j]=B00000;
          else charLine[7-j]=B11111;
        }
        lcd.createChar(i, charLine);
      }
    }

    void setup() {
      Serial.begin(9600);
      lcd.init();
      lcd.backlight();
      animationSetup();
    }

    void animation1() {
      lcd.setCursor(14,0);
      lcd.write(byte(animationStep % 8));
      // lcd.write(7);
      animationStep++;
    }    
    
    void animation3() {
      byte character[2];
      for (int column = 0; column < numberOfColumns; column++) {
        int actualValue=cos(animationStep*(0.1+column*0.01))*8.5+9;
        if (actualValue == 17) {
          character[0]=byte(255);
          character[1]=byte(255);
        }
        else if (actualValue > 9) {
          character[0]=byte(actualValue-10);
          character[1]=byte(255);
        }
        else if (actualValue == 9) {
          character[0]=byte(32);
          character[1]=byte(255);
        }
        else if (actualValue == 8) {
          character[0]=byte(32);
          character[1]=byte(255);
        }
        else if (actualValue == 0) {
          character[0]=byte(32);
          character[1]=byte(32);
        }      
        else {
          character[0]=byte(32);
          character[1]=byte(actualValue-1);
        }
        lcd.setCursor(15-column,0);
        lcd.write(character[0]);
        lcd.setCursor(15-column,1);
        lcd.write(character[1]);
        }
      // lcd.write(byte(animationStep % 8));
      // lcd.write(7);
      animationStep++;
    }
    
    void loop() {
      animation3();
    }
