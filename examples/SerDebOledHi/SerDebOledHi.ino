#include <Arduino.h>/
#include <Wire.h>
#include <MicrOledPro.h>

//LCD_SH1106 lcd; /* for SH1106 OLED module */
LCD_SSD1306 lcd; /* for SSD1306 OLED module */

void setup()
{
  lcd.begin();
  lcd.clear();
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.println(F("Hello, world!"));

  Serial.begin(19200);      // open the serial port at 19200 bps:
//  Serial.print(F("Hello Serial"));
}

long lscount = 0;
int incomingByte = 0;   // for incoming serial data

void loop() {
  int in = 0;
  while (Serial.available() > 0) {
    if ( 0 == in ) {
      delay(20);  // pause for message to xmit
      in = 1;
      lcd.clear();
      lcd.setCursor(0, 0); // setCursor needed after clear() ???? BUGBUG
      lcd.setFontSize(FONT_SIZE_SMALL);
      lcd.println(F("_._.5._._0_._.5"));
      lcd.println(F("Msg Count"));
      lcd.printLong(lscount);
      lscount++;
      lcd.println(F(":Serial Msg #"));
    }
    // read the incoming byte:
    incomingByte = Serial.read();
    if ( -1 != incomingByte )
      // say what you got:
      lcd.print((char)incomingByte);
    if (Serial.available() == 0)
      delay(10);  // pause for message to xmit
  }
  if ( 0 != in ) {
    lcd.println("<end>");
    lcd.println(F("_._.5._._0_._.5"));
    lcd.println("<end>");
  }
}
