/*
 * Function that process the information when case2 = 1
 * meaning that the system is in the set NORTH - SOUTH - SOUTH - SOUTH
 */

void count_processor_south()
{
  int northcounter = sensor1;
  int southcounter = sensor2 + sensor3 + sensor4;

  //If situation still applies
  
  if(southcounter > 3*northcounter)
  {
    
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
    
    digitalWrite(rightred, HIGH);
    digitalWrite(rightgreen, LOW);
    digitalWrite(leftred, HIGH);
    digitalWrite(leftgreen, LOW);
   Serial.println("South line still open");


  }

  //previous situation doesn't apply anymore, so system is going
  //back to normal situation
  
  else 
  {
    railnorth = "NORTH";
    railsouth = "SOUTH";
    
    //Sending message '4' to the LCD on the other side of the road
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "4");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    //////////////////////////////////////////////////
    // sending the message to the LCDs
    
     for (int i = 0; i < 100; i ++)
    {
      //LCD code
      lcd2.clear();
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      LargeText = "      Left LANE will be opened to improve flow of traffic.    ";
      UpdateLCDDisplay();
      delay(180);
      lcd1.clear();
      lcd2.clear();
      delay(70);
      //code for blinking LED
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
   
digitalWrite(middlerail, HIGH);
digitalWrite(rightrail, HIGH);
digitalWrite(leftrail, LOW);
digitalWrite(leftred, HIGH);
digitalWrite(leftgreen, LOW);
delay(1000);
digitalWrite(rightrail, LOW);
digitalWrite(leftrail, LOW);
digitalWrite(rightred, LOW);
digitalWrite(rightgreen, HIGH);
Serial.println("Back to normal condition. South lane closed");

case2 = 0;
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
}
