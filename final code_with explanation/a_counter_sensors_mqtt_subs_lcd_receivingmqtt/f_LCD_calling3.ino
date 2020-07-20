void LCDcalling3()
{
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      delay(1000);
      lcd1.clear();
      lcd2.clear();
  for (int i = 0; i < 100; i ++)
    {
      //LCD code
     
      LargeText = "      EMERGENCY VEHICLE APPROACHING!!!!    MOVE TO RIGHT LANE!!!!    ";
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
      digitalWrite(rightred, LOW);   // set the LED on
      digitalWrite(rightgreen, LOW); 
      delay(1000);
      digitalWrite(rightred, HIGH);
      digitalWrite(rightgreen, LOW);
    //LCDtrigger = LOW;
     //LCD code
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("CLOSED LANE");
      lcd2.setCursor(0,0);
      lcd2.print("Drive carefully");
}
