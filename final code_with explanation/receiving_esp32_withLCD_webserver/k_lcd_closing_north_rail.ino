void lcd_closing_north_rail()
{
   //sending the information for the lcds on the other side
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "0");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);

    ////////////////////////////////////////////
    for (int i = 0; i < 100; i ++)
    {
      //LCD code
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      LargeText = "      Closing LEFT LANE, move to RIGHT LANE.    ";
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
      digitalWrite(rightred, LOW);    // set the LED off
      digitalWrite(rightgreen, HIGH);
      toggle = !toggle;
    } 
      }
    }
    digitalWrite(LCDtrigger2, LOW);
      digitalWrite(rightred, HIGH);   // set the LED on
      digitalWrite(rightgreen, LOW); 
      digitalWrite(rightrail, HIGH);
      delay(1000);
      digitalWrite(middlerail, LOW);
      digitalWrite(leftred, HIGH);
      digitalWrite(leftgreen, LOW);

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
