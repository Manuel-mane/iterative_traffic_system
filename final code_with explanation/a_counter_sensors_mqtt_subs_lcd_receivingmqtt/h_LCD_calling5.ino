void LCDcalling5()
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
      
      LargeText = "      CLOSING LEFT LANE MOVE TO RIGHT LANE!!!   ";
      UpdateLCDDisplay();
      delay(180);
      lcd1.clear();
      lcd2.clear();
      delay(70);
  if (i%5 == 0)
      {
         if(toggle)
    {
      digitalWrite(leftred, LOW);   // set the LED on
      digitalWrite(leftgreen, LOW);
      toggle = !toggle;
          }
    else
    {
      digitalWrite(leftred, LOW);    // set the LED off
      digitalWrite(leftgreen, HIGH);
      toggle = !toggle;
    } 
      }
    }
      digitalWrite(leftred, LOW);   // set the LED on
      digitalWrite(leftgreen, LOW); 
      delay(1000);
      digitalWrite(leftred, HIGH);
      digitalWrite(leftgreen, LOW);
    //LCDtrigger = LOW;
     //LCD code
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Drive carefully");
      lcd2.setCursor(0,0);
      lcd2.print("Drive carefully");
}
