void lcd_open2_emg()
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
      digitalWrite(leftred, LOW);   // set the LED on
      digitalWrite(leftgreen, LOW);
      toggle = !toggle;
          }
    else
    {
      digitalWrite(leftred, HIGH);    // set the LED off
      digitalWrite(leftgreen, LOW);
      toggle = !toggle;
    } 
      }
    }
  
      digitalWrite(leftred, LOW);   // set the LED on
      digitalWrite(leftgreen, LOW); 
      delay(1000);
      digitalWrite(middlerail, LOW);    //state of the rails
      digitalWrite(rightrail, LOW);
      digitalWrite(leftrail, HIGH);
      digitalWrite(leftred, LOW);
      digitalWrite(leftgreen, HIGH);
      //delay(1000);

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
    
    Serial.println("North lane open");
}
