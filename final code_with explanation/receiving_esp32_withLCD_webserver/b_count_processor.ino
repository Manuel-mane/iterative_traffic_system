/*
 * This is the first function the system goes through 
 * to manage the street rails and LEDs when the
 * system receives the reading from the MKR1000
 */


void count_processor()
{ 

  //Calculating the account when the street configuration is
  //          NORTH - NORTH - SOUTH - SOUTH 
  
  int northcounter = sensor1 + sensor2;
  int southcounter = sensor3 + sensor4;

// if there were more vehicles going north than going south
  if(northcounter > 2*southcounter)
  {
    //Changing the rails mode NORTH - NORTH - NORTH - SOUTH

      railsouth = "NORTH";
      
    // sending the information the information "1" to the MKR1000 by publishing to the topic southside
    // 1 that MKR1000 receives and lead to a specific function that will modify the LCDs and LEDs of the 
    // south side
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "1");
    Serial.print("Publishing on topic southside at QoS 2, packetId: ");
    Serial.println(packetIdPub2);

    //Modifying the LCDs and LEDs
    
    for (int i = 0; i < 100; i ++)
    { 

      //LCD code - Display on both LCDs
      lcd1.setCursor(0,0);
      lcd1.print("Attention drivers!!!");
      lcd2.setCursor(0,0);
      lcd2.print("Attention drivers!!!");
      
      //Text displayed for changing lanes
      LargeText = "      Left LANE will be opened to improve flow of traffic    ";
      UpdateLCDDisplay();
      delay(180);
      lcd1.clear();
      lcd2.clear();
      delay(70);
      if (i%5 == 0)   // when i is multiple of 5 the LEDs will turn ON or OFF, meaning every 1.25 seconds
      {
         if(toggle)
    {
      digitalWrite(leftred, HIGH);   // set the LED on
      digitalWrite(leftgreen, LOW);
      toggle = !toggle;
          }
    else
    {
      digitalWrite(leftred, LOW);    // set the LED off
      digitalWrite(leftgreen, LOW);
      toggle = !toggle;
    } 
      }
    }
    
      digitalWrite(leftred, HIGH);   // set the LED on
      digitalWrite(leftgreen, LOW); 
      digitalWrite(leftrail, HIGH);
      delay(1000);
      digitalWrite(middlerail, LOW);
      digitalWrite(leftred, LOW);
      digitalWrite(leftgreen, HIGH);

    //setting the LCDs for regular message
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
    case1 = 1; // this variable is set so next time system receives the readings it knows
               // the system previouly entered to the state NORTH - NORTH - NORTH - SOUTH
               // so it starts processing the data from that viewpoint
    
    
  }

  // if there were more vehicles going south than going north
  else if(southcounter > 2*northcounter)
  {

    // sending the information the information "3" to the MKR1000 by publishing to the topic southside
    // 1 that MKR1000 receives and lead to a specific function that will modify the LCDs and LEDs of the 
    // south side
    railnorth = "SOUTH";
    //sending the information for the lcds on the other side
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "3");
    Serial.print("Publishing on topic southside at QoS 2, packetId: ");
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
      delay(180);
      lcd1.clear();
      lcd2.clear();
      delay(70);
      if (i%5 == 0)             // when i is multiple of 5 the LEDs will turn ON or OFF, meaning every 1.25 seconds
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

    // Setting the final configuration of the LEDs and LCDs when it is NORTH - SOUTH - SOUTH - SOUTH
      digitalWrite(rightred, HIGH);   // set the LED on
      digitalWrite(rightgreen, LOW); 
      digitalWrite(rightrail, HIGH);
      digitalWrite(middlerail, HIGH);
      digitalWrite(leftrail, LOW);
      delay(1000);
      digitalWrite(middlerail, LOW);
      digitalWrite(leftrail, LOW);
      digitalWrite(rightrail, HIGH);
      digitalWrite(leftred, HIGH);
      digitalWrite(leftgreen, LOW);

      //Normal configuration of LCDs
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
    
    case2 = 1; // this variable is set so next time system receives the readings it knows
               // the system previouly entered to the state NORTH - SOUTH - SOUTH - SOUTH
               // so it starts processing the data from that viewpoint
               
    Serial.println("South lane open");
    
  }

  //Conditions above don't apply
  
  else{
    
    railnorth = "NORTH";
    railsouth = "SOUTH";
    
    //Normal condition
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print(" Drive carefully ");
    lcd1.setCursor(0,1);
    lcd1.print(ip);
    lcd2.clear();
    lcd2.setCursor(6,0);
    lcd2.print("Drive ");
    lcd2.setCursor(4,1);
    lcd2.print("carefully ");
    
digitalWrite(leftred, HIGH);
digitalWrite(leftgreen, LOW);
digitalWrite(rightred, LOW);
digitalWrite(rightgreen, HIGH);

  }
}
