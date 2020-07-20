void lcd_closing2_openingsouth2_lane()
{
  Serial.println("LCD for closing 2 lane");
   //sending the information for the lcds on the other side
    /*uint16_t packetIdPub2 = mqttClient.publish("souththside", 2, true, "0");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Publishing 0: open 2nd lane of the south");*/

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
      //state of the rails
      digitalWrite(middlerail, HIGH);
      digitalWrite(rightrail, LOW);
      digitalWrite(leftrail, LOW);
      
      digitalWrite(leftred, HIGH);
      digitalWrite(leftgreen, LOW);
      Serial.println("LCD function for closing 2 lane finished");
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
