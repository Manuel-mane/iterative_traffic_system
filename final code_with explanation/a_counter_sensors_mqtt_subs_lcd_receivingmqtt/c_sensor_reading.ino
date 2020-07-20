/*
 * This function builds the counter from the readings of the IR sensors
 */

void sensor_reading() {
if(analogRead(sensor1) < 200)
  {    A = 1;
  }
 
  if(analogRead(sensor2) < 200)
  { B = 1;}
  
  if(analogRead(sensor3) < 200)
  {C = 1; }
 
  if (analogRead(sensor4) < 200)
  { D = 1;}

//ask if the sensor finished reading. Add the variables beforehand.
Serial.begin(9600);
  if(A == 1 && analogRead(sensor1) > 800 )
  {
   
      counter1 = counter1 +  1; 
      Serial.println("counter1");
      Serial.println(counter1);
      
      A = 0;
  
  }
  if (B == 1 && analogRead(sensor2) > 800)
  {

      counter2 = counter2 + 1;
      Serial.println("counter2");
      Serial.println(counter2);
      B = 0;
    
  }
  if (C == 1 && analogRead(sensor3) > 800)
  {
    
      counter3 ++;
      Serial.println("counter3");
      Serial.println(counter3);
      C = 0;
    
  }
  if (D == 1 && analogRead(sensor4) > 800)
  {
    
      counter4 ++;
      Serial.println("counter4");
      Serial.println(counter4);
      D = 0;
   
  }
}
