void lcd_closing3_emg()
{
      lcd2.clear();
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("ATTENTION DRIVERS!!!");
      lcd2.setCursor(0,0);
      lcd2.print("ATTENTION DRIVERS!!!");
   for (int i = 0; i < 100; i ++)
    { 
      
      LargeText = "      EMERGENCY VEHICLE APPROACHING. MOVE TO THE RIGHT LANE    ";
      UpdateLCDDisplay();
      delay(180);
      lcd1.clear();
      lcd2.clear();
      delay(70);
      
      if (i%5 == 0)
      {
         if(toggle)
    {
      digitalWrite(rightred, LOW);   // set the LED on
      digitalWrite(rightgreen, LOW);
      toggle = !toggle;
          }
    else
    {
      digitalWrite(rightred, LOW);    // set the LED off
      digitalWrite(rightgreen, HIGH);
      toggle = !toggle;
    } 
      }
    }
    Serial.println("Emergency lane for north lane is closed");
      digitalWrite(rightred, LOW);   // set the LED on
      digitalWrite(rightgreen, LOW); 
      digitalWrite(middlerail, HIGH);     //Position of the rails
      digitalWrite(rightrail, HIGH);
      delay(1000);
      digitalWrite(rightred, HIGH);
      digitalWrite(rightgreen, LOW);
      
     lcd1.clear();
    lcd1.setCursor(6,0);
    lcd1.print("Drive  ");
    lcd1.setCursor(4,1);
    lcd1.print("carefully ");
    lcd2.clear();
    lcd2.setCursor(6,0);
    lcd2.print("Drive ");
    lcd2.setCursor(4,1);
    lcd2.print("carefully ");
     
}
