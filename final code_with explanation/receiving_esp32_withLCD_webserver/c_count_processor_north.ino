/*
 * Function that process the information when case1 = 1
 * meaning that the system is in the set NORTH - NORTH - NORTH - SOUTH
 */

void count_processor_north()
{
 
  int northcounter = sensor1 + sensor2 + sensor3;
  int southcounter = sensor4;

  //if there still more vehicles in the north way
  if(northcounter > 3*southcounter)
  { 
    
    digitalWrite(rightred, LOW);
    digitalWrite(rightgreen, HIGH);
    digitalWrite(leftred, LOW);
    digitalWrite(leftgreen, HIGH);
    Serial.println("North line still open");

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

  // previous situation no longer applies so street rails 
  // are going back to normal condition
  
  else
  {
    railnorth = "NORTH";
    railsouth = "SOUTH";
   
    //sending message '0' for the LCD on the other side
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "0");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    ////////////////////////////////////////////////
    // sending message to the LCDs
    
     for (int i = 0; i < 100; i ++)
    {
      //LCD code
      lcd2.clear();
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      LargeText = "      Closing LEFT LANE, move to RIGHT LANE.    ";
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
    

digitalWrite(middlerail, HIGH);    
digitalWrite(leftred, HIGH);
digitalWrite(leftgreen, LOW);
delay(1000);
digitalWrite(leftrail, LOW);
digitalWrite(rightred, LOW);
digitalWrite(rightgreen, HIGH);

case1 = 0;
Serial.println("Back to normal condition. North lane closed");
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
