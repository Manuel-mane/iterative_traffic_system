void lcd_open3_closing_south3()
{

Serial.println("LCD function for opening 3 lane for north");
    ////////////////////////////////////////////
    for (int i = 0; i < 100; i ++)
    {
      //LCD code
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      LargeText = "      LEFT LANE WILL OPEN TO IMPROVE TRAFFIC.    ";
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
      digitalWrite(middlerail, HIGH);
      delay(1000);
      digitalWrite(leftrail, LOW);
      digitalWrite(rightrail, LOW);
      digitalWrite(rightred, LOW);
      digitalWrite(rightgreen, HIGH);
      Serial.println("LCD function for opening 3 lane for north finished");
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
