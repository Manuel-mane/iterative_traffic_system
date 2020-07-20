void lcd_open_north_rail()
{
  
    for (int i = 0; i < 100; i ++)
    { 

      //LCD code
      //Display on both LCDs
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      
      //Text displayed for changing lanes
      LargeText = "      Left LANE will be opened to improve flow of traffic    ";
      UpdateLCDDisplay();
      delay(150);
      lcd1.clear();
      lcd2.clear();
      delay(50);
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
      digitalWrite(middlerail, HIGH);
      delay(1000);
      digitalWrite(rightrail, LOW);
      digitalWrite(rightred, LOW);
      digitalWrite(rightgreen, HIGH);
      //delay(1000);

    
    Serial.println("North lane open");
}
