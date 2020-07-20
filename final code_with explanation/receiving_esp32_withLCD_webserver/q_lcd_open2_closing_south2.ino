void lcd_open2_closing_south2()
{
   //sending the information for the lcds on the other side
   /* uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "1");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Closing 2nd lane of south side");
*/
Serial.println("LCD function for opening 2 lane for north");
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
      digitalWrite(leftrail, HIGH);
      delay(1000);
      digitalWrite(middlerail, LOW);
      digitalWrite(leftred, LOW);
      digitalWrite(leftgreen, HIGH);
      Serial.println("LCD function for opening 2 lane for north finished");
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
