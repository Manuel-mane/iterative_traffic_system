void LCDcalling2()
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
      
      LargeText = "      Left LANE will be opened to improve flow of traffic    ";
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
      digitalWrite(rightred, HIGH);    // set the LED off
      digitalWrite(rightgreen, LOW);
      toggle = !toggle;
    } 
      }
    }
      digitalWrite(rightred, LOW);   // set the LED on
      digitalWrite(rightgreen, LOW); 
      delay(1000);
      digitalWrite(rightred, LOW);
      digitalWrite(rightgreen, HIGH);
    //LCDtrigger = LOW;
     //LCD code
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Drive carefully");
      lcd2.setCursor(0,0);
      lcd2.print("Drive carefully");
}
