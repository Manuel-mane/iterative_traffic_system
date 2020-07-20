/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
///           FUNCTION THAT DESCRIBES THE           /////
///              WEB SERVER INTERFACE               /////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


void web_server_reading_input()
{
     WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            //client.println("Refresh: 5"); // refresh the page automatically every 5 sec 
            client.println(); 

/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////       READING INPUTS        //////////////////////////
/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

if (header.indexOf("GET /north/emergency") >= 0) {    //If button /north/emergency is pressed
              if(emergency_north == "EMERGENCY")      //If the pressed button was "emergency" state, it will change to "closed"
              {
               Serial.println("North emergency rail activated");
               emergency_north = "CLOSED";
               emg_north = 1;
              }
              else {                                  //If the pressed button was "closed" state, it will change to "emergency"
                emergency_north = "EMERGENCY";
                emg_north = 1;
               }
            }
            
if (header.indexOf("GET /south/emergency") >= 0) {    //If button "/south/emergency" is pressed
              if(emergency_south == "EMERGENCY")      //If the pressed button was "emergency" state, it will change to "closed"
              {
                Serial.println("North emergency rail activated");
                emergency_south = "CLOSED";
                emg_south = 1;
              }
              else {                                  //If the pressed button was "closed" state, it will change to "emergency"
                emergency_south = "EMERGENCY";
                emg_south = 1;
            }
            }

////////////// READING MANUAL OR AUTOMATIC

            if (header.indexOf("GET /manual/automatic") >= 0)    //If button /manual/automatic is pressed
            {
            if (performance == "AUTOMATIC")                      //If pressed button was "automatic", it will change to "manual"
            {
              performance = "MANUAL";
              automatic = 0;
              Serial.println("It is manual");
            }
            else                                                 //If pressed button was "manual", it will change to "automatic"
            {
              performance = "AUTOMATIC";
              automatic = 1;
              Serial.println("It is automatic");
            }
            }

/////////////  READING RAILS 
            //reading rails setup
            
            if (header.indexOf("GET /south/north") >= 0) {    //If button "/south/north" is pressed
           
              if(railnorth == "NORTH")                        //If railnorth is "North", it will change to "south"
              {railnorth = "SOUTH";
              Serial.println("North rail is now south");
              north_way = 1;                                  // this variable shows that button was pressed
              }
              else {railnorth = "NORTH";                      //If railnorth is "south", it will change to "north"
              Serial.println("North rail is back to north");
              north_way = 1;                                  // this variable shows that button was pressed
              }
              
            } 
            
            else if (header.indexOf("GET /north/south") >= 0) {//If button "/north/south" was pressed
              
              if(railsouth == "SOUTH")                         //If railsouth is "south", it will change to "north"
              {railsouth = "NORTH";  
              Serial.println("South rail is open as normal");            
               south_way = 1;                                  //this variable shows that button was pressed
              }
              else                                             //If railsouth is "north", it will change to "south"
              {
                railsouth = "SOUTH";
              Serial.println("South rail is oh north direction");
              south_way = 1;                                   //this variable shows that button was pressed
              }
            } 


   //////////////////////////////////////////////////////
   ///////////////////////////////////////////////////
   //////    STRUCTURE OF BUTTONS        ///////////////
   ////////////////////////////////////////////////////
   /////////////////////////////////////////////////////

            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<title>ESP32 Web Server</title>");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #FF9;}");
            client.println(".button { background-color: #4CAF50;border-radius: 30px;color: white;padding: 16px 40px;text-decoration: none;font-size: 30px;margin: 2px;cursor: pointer;"); //grey color
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");  //setting green color property for button2
            client.println(".button5 {background-color: #C0C0C0;}");  //setting while color property for button5
            client.println(".button4 {background-color: #0000FF;");  //setting blue color property for button4
            client.println(".button3 {background-color: #FF0000;}</style></head>");  //setting red color property for button3
            
            // Web Page Heading
            client.println("<body><h1>STREET RAIL WEB-SERVER</h1>");       //Name of the web server
            client.println("<h2>Street rail control</h2>");
            
            //Notice for web user  
            
            client.println("<p>");
            client.println("<p style=\"font-size:150%;\"><pre style=\"font-size:130%; font-family:verdana;\"> This interface controls the traffic street");
            client.println("rails. Take into account that only one of the following");
            client.println("structures can be set: </pre></p>");
            client.println("<ul style=\"font-size:120%; font-family:verdana;\">");
            client.println("<li>SOUTH - SOUTH - NORTH - NORTH</li>");
            client.println("<li>SOUTH - NORTH - NORTH - NORTH</li>");
            client.println("<li>SOUTH - SOUTH - SOUTH - NORTH</li></ul>");

            ////////////////////////////////////////////////////////////////////////////////////////////////
            //////////                                                                     /////////////////
            /////////            STRUCTURE OF THE BUTTONS                                  /////////////////
            /////////                                                                      /////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////


            ////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////    RAILS BUTTONS IF EMERGENCY IS ACTIVATED                     //////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////`


            /// BOTH EMERGENCY CLOSED
            //if north is clicked
if(emergency_north == "CLOSED" && emergency_south == "CLOSED" && emg_north == 1 && emg_south == 0)  //done
{
  automatic = 0;
  performance = "MANUAL";
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State   |||||||                ");
            client.println("   North-rail State</p>");
     if(railnorth == "SOUTH")
     {
      //this situation means that both rails are closed because of emergency but southside had 3 rails
     //// NORTH AND SOUTH RAILS BUTTONS    ////////
         railnorth = "NORTH"; //this means than when emergency finishs, street rails will be back to their regular state
              client.println("<P><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

              ///// EMERGENCY BUTTONS  

              client.println("<h2>Street rail emergency module</h2><p>");
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //LCD
              //////////////////////////////////
              // send mqtt to close 3 south rail  ///
              /////////////////////////////////////
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "2");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              digitalWrite(leftrail, HIGH);
              digitalWrite(middlerail, HIGH);
              digitalWrite(rightrail, HIGH);
              Serial.println("Emergency closed when railnorth was south");
              ////////////////////////////////////////
              emg_north = 0;  
              
              }
              else {

                //// NORTH AND SOUTH RAILS BUTTONS    ////////
         //both rails are closed after request from north side
              client.println("<P><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

              ///// EMERGENCY BUTTONS  

              client.println("<h2>Street rail emergency module</h2><p>");
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
      /////LCD COMMUNICATION
              lcd_closing3_emg(); //done
              digitalWrite(leftrail, HIGH);
              digitalWrite(middlerail, HIGH);
              digitalWrite(rightrail, HIGH);
     
    emg_north = 0;
    Serial.println("Emergency closed when railnorth was north");
              }
}

/////if south is clicked
//both emergency rails are closed after southside emergency being requested
else if(emergency_north == "CLOSED" && emergency_south == "CLOSED" && emg_south == 1 && emg_north == 0)  
{
          performance = "MANUAL";
          automatic = 0;
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State   |||||||                ");
            client.println("   North-rail State</p>");
     if(railsouth == "NORTH")       
     {
     //// NORTH AND SOUTH RAILS BUTTONS    ////////
         railsouth = "SOUTH";
              client.println("<P><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

              ///// EMERGENCY BUTTONS  

              client.println("<h2>Street rail emergency module</h2><p>");
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              Serial.println("Emergency closed when for south when north was south");
        //lcd for north to close for emergency
        lcd_closing3_emg();        //lcd for emegergency vehicle coming in the northside rail
              digitalWrite(leftrail, HIGH);
              digitalWrite(middlerail, HIGH);
              digitalWrite(rightrail, HIGH);
emg_south = 0;
     }
     else {

      //railsouht is in south state, regular condition
       client.println("<P><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

              ///// EMERGENCY BUTTONS  

              client.println("<h2>Street rail emergency module</h2><p>");
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
      /////LCD COMMUNICATION
////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/// SEND EMERGENCY MQTT TO CLOSE   ///////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////////
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "2");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              digitalWrite(middlerail, HIGH);
              digitalWrite(leftrail, HIGH);
              digitalWrite(rightrail, HIGH);
      
   Serial.println("Emergency closed when for south");
  
    emg_south = 0;
     }
}
else if(emergency_north == "CLOSED" && emergency_south == "CLOSED" && emg_south == 0 && emg_north == 0)
{ //both lines are closed. Nothing pressed
  
  performance = "MANUAL";
automatic = 0;

//rail conditions are returned to regular state when both lanes are on emergency state
railnorth = "NORTH";
railsouth = "SOUTH";
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State   |||||||                ");
            client.println("   North-rail State</p>");
            
              client.println("<P><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

              ///// EMERGENCY BUTTONS  

              client.println("<h2>Street rail emergency module</h2><p>");
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //lcd drive safely emergency vehicle approaching
}
//
//SECTION OF BOTH EMERGENCY ACTIVATED
//            FINISHED
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/////////                                ///////////////////
/////////  NORTH CLOSED AND SOUTH OPEN   ////////////////////
/////////                                ////////////////////
/////////////////////////////////////////////////////////////

//emergency when north got clicked and now north is closed and south is open

else if(emergency_north == "CLOSED" && emergency_south != "CLOSED" && emg_north == 1 && emg_south == 0) 
{  // emergenccy north was pressed
  
  performance = "MANUAL";
  automatic = 0;
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");
            
            if(railsouth == "NORTH")
              {
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //lcd closing north lane for emergency
              lcd_closing2_emg();
              
              Serial.println("Emergency closed for north when south was north");
              }

              //if the north rail was opened to the south side
              
            else if(railnorth == "SOUTH")
            {
               client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
               client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              // lcd send mqtt to close south lane for emergency
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "5");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //Rails position
              digitalWrite(leftrail, LOW);
              digitalWrite(middlerail, HIGH);
              digitalWrite(rightrail, HIGH);
              Serial.println("Emergency closed for north when railnorth was south");
            }
            
              else{  //the lanes are acting in their regular state
                
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              
           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //lcd close north lane for emergency
              
              lcd_closing3_emg();
              }
     
    emg_north = 0;
   }


 // North rail is closed and sourth rail is open as result of pressing the south emergency button\
 // meaning that priorly, both emergency lanes were closed, when this happens (both emergency lanes closed)
 // the traffic rails go back to their regular setting, northrail addressong to north and southrail to south
 // emg_south == 1
 
else if(emergency_north == "CLOSED" && emergency_south != "CLOSED" && emg_south == 1 && emg_north == 0)//done
{
performance = "MANUAL";
automatic = 0;
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");
            
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
              
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //send mqtt to open south rail
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "6");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //Street rails state
              digitalWrite(leftrail, LOW);
              digitalWrite(middlerail, HIGH);
              digitalWrite(rightrail, HIGH);
              Serial.println("Emergency was cleared for south");
              emg_south = 0;
              
}

//State when North rail is closed and South is opened but not one was pressed

else if(emergency_north == "CLOSED" && emergency_south != "CLOSED" && emg_south == 0 && emg_north == 0)
{
  performance = "MANUAL";
  automatic = 0;

   client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");

            if(railsouth == "NORTH")
              {
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //lcd closing north lane for emergency
                            
              Serial.println("Emergency closed for north when south was north");
              }              
            
            else
            {
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">NORTH EMERGENCY ACTIVATED</button></a></p>");
             client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
            }
}
//////////////////////////////////////////
/// NORTH CLOSED AND SOUTH OPEN END   ////
//////////////////////////////////////////

//////////////////////////////////////////
/// NORTH OPEN AND SOUTH CLOSED START ////
//////////////////////////////////////////


   // when north got clicked and now north is open and south is closed
else if(emergency_north != "CLOSED" && emergency_south == "CLOSED" && emg_north == 1 && emg_south == 0)//DONE
   {
    //This state describes that priorly both lanes were closed, meaning rail state went back to its normal state
    //were northrail is north and southrail goes to south. As result, when pressing emg-nort, the north rail which
    //was in emg state opens up.
    
            performance = "MANUAL";
            automatic = 0;
               client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");
            
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
             
              client.println("<p><a href=\"/south/emergency\"><button class =\"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
               /////LCD COMMUNICATION OPEN NORTH RAIL
               lcd_open_north_rail();
     Serial.println("Emergency opened for north");
               emg_north = 0;
   }

   // south got clicked
   else if(emergency_north != "CLOSED" && emergency_south == "CLOSED" && emg_south == 1 && emg_north == 0)//done
   {
    
   performance = "MANUAL";
   automatic = 0;
               client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");;
            if(railnorth == "SOUTH")
              {
                //////////////////////////////////////////////////////////////////////////////////////////
                //this state describes when emeg is coming from the northside but the northrail is    ////
                //opened to the south                                                                 ////
                //////////////////////////////////////////////////////////////////////////////////////////
                
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<p><a href=\"/south/emergency\"><button class =\"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE</button></a></p>");
              
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");

              //lcd send mqtt to close south rail for emergency
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "5");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //State of the rails
              digitalWrite(leftrail, LOW);
              digitalWrite(middlerail, HIGH);
              digitalWrite(righttrail, HIGH);
              Serial.println("Emergency closed for south when railnorth was south");
              }
              else if(railsouth == "NORTH")
              {
                ////////////////////////////////////////////////////////////////////////
                // this state describe when emg is coming from the south but the //////
                // the south rail is opened to the north coming traffic          //////
                ///////////////////////////////////////////////////////////////////////
                
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<p><a href=\"/south/emergency\"><button class =\"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE</button></a></p>");
              
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");

              // lcd to close north rail for emergency 
              lcd_closing2_emg();
            Serial.println("Emergency closed for south when railsouth was north");
              }
              
              else{
                ////////////////////////////////////////////////////////////////////////////////////////
                ///             this state describes when emg is coming from the south and         /////
                ///                   the street rails are in their normal settup                  /////
                ////////////////////////////////////////////////////////////////////////////////////////
                
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<p><a href=\"/south/emergency\"><button class =\"button button5\">SOUTH EMERGENCY ACTIVATED</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE</button></a></p>");
              
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //lcd send mqtt closing south lane for emergency
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "2");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //state of the street rails
              digitalWrite(middlerail, HIGH);
              digitalWrite(leftrail, HIGH);
              Serial.println("Emergency was closed for south");
              }
                emg_south = 0;
   }
else if(emergency_north != "CLOSED" && emergency_south == "CLOSED" && emg_south == 0 && emg_north == 0)//done
{
  //this state describes when south is closed and north is open but no buttons were pressed
  
  performance = "MANUAL";
  automatic = 0;

     client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");
            if(railnorth == "SOUTH")
              {
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              }
              
              else
              {
                client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button5\">CLOSED</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              }
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //lcd drive safely emergency vehicle approaching
}
//////////////////////////////////////////
//// EMG NORTH OPEN AND EMG SOUTH CLOSED ///
/////       FINISHED                     ////
/////////////////////////////////////////////

////////////////////////////////////////////
////   BOTH EMERGENCY ARE OPEN  //////////
////////////////////////////////////////////

//north got clicked
else if(emergency_north != "CLOSED" && emergency_south != "CLOSED" && emg_north == 1 && emg_south == 0)//done
{   performance = "MANUAL";
    automatic = 0;
  
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");

        if(railnorth == "SOUTH")
        {
          //this state describes when there not emergency because emg-north was cleared
          
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              // lcd send mqtt to open south lane
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "3");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //State of the rails
              digitalWrite(leftrail, LOW);
              digitalWrite(middlerail, LOW);
              digitalWrite(rightrail, HIGH);
              Serial.println("Emergency opened for north when rail north is south");

        }
        else if(railsouth == "NORTH")
        {
          client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //lcd to open north lane
              lcd_open2_emg();
              Serial.println("Emergency opened for north when railsouth was north");
        }
           else {
          
            client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //lcd open north lane
              lcd_open_north_rail();
              Serial.println("Emergency opened for north");
           }

            emg_north = 0;
}          

            //south got clicked
            //state for both emergency cleared when emg_south was clicked
else if(emergency_north != "CLOSED" && emergency_south != "CLOSED" && emg_south == 1)//done
{
       automatic = 0;
       performance = "MANUAL";
            client.println("<p><button type=\"button\" disabled class=\"button button5\">MANUAL</button></a>");
            client.println("<p>South-rail State  ||||| ");
            client.println("    North-rail State</p>");
            
            if(railnorth == "SOUTH")
            {
              //this state described when both emg are clear after emg_south was pressed
              //but railnorth was addressoing to the south side
              
               client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");

              //lcd send mqtt to open south lane
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "3");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              //state of the rails
              digitalWrite(leftrail, LOW);
              digitalWrite(middlerail, LOW);
              digitalWrite(rightrail, HIGH);
              Serial.println("Emergency opened for south when rail north was south");
            }
            
            else if(railsouth == "NORTH")
            {
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              //lcd to open north lane
              lcd_open2_emg();
              Serial.println("Emergency opened for south when railsouth was north");
            }
            
          else{
            client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");

   ////////////////////////////////////////
   ////////////////////////////////////////
   //// SEND MQTT TO OPEN south lane //////
   ////////////////////////////////////////
   ////////////////////////////////////////
              uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "6");
              Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
              Serial.println(packetIdPub2);
              delay(24000);
              digitalWrite(rightrail, LOW);
              digitalWrite(middlerail, HIGH);
              Serial.println("Emergency opened for south");
          }
               emg_south = 0;
}          

/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//// EMERGENCY BUTTONS CLEARED ////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
else if(emergency_north != "CLOSED" && emergency_south != "CLOSED" && emg_south != 1 && emg_north != 1)
{

  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////
  // THE FOLLOWING STATES TAKE CARE OF THE MANUAL INTERFACE //
  // WITH THE RAIL SYSTEM, ALWAYS WHEN THERE ARE NOT ANY    //
  // EMERGENCY ACTIVATED                                    //
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////
            
  if(performance == "MANUAL")   //MEANING WE ARE MANUALLY CHANGING THE STREET RAILS SYSTEM
  { 
  manual = 1;
  automatic = 0;
  Serial.println("Inside manual");
    client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">MANUAL</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
     
    if(railnorth == "SOUTH" && north_way == 1) 
    { 
      //This state describes when railnorth was on north and it was clicked 
      
      if(railsouth == "NORTH")
      {
        
        railnorth = "NORTH";  //they go back to their regular settup
        railsouth = "SOUTH";
        
        client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
        client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
        client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
        client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
        client.println("<h2>Street rail emergency module</h2><p>");   
        client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
        client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
        client.println("<p style=\"font-size:150%;\">");
        client.println("NOTE: When emergency is pressed the lane will close</p>");
        client.println("</body></html>");
        //lcd closing left lane

        //SEND MQTT TO THE SOUTHSIDE TO OPEN SOUTH LANE
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "6");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Publishing 0: open 2nd lane of the south");

//CLOSE THE LEFT NORTH LANE OF THE NORTH SIDE TO GIVE IT TO THE SOUTH
        lcd_closing2_openingsouth2_lane();
        
         }
      else
      {
        //northrail was pressed, so it was going to give access to the south side
        
      
       
        client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
        client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
        client.println("<a href=\"/south/north\"><button class=\"button button2\">SOUTH</button>");
        client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
        client.println("<h2>Street rail emergency module</h2><p>");   
        client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
        client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
        client.println("<p style=\"font-size:150%;\">");
        client.println("NOTE: When emergency is pressed the lane will close</p>");
     
        client.println("</body></html>");
        
        //sends mqtt to the southside to open one more rail
        uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "3");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Openning 3rd lane in south side");


     //send message that the rail is closing, to move to the right
        lcd_closing3_openingsouth_lane();
    
      }
     north_way = 0;
    }

    //when railnorth is giving access to the south but not button was pressed
 
   
   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////

   else if(railsouth == "NORTH" && south_way == 1)//done
    {
      //this state describes that railsouth was clicked from south to north
     
     if(railnorth == "SOUTH")
     {
      //in the case railnorth is south, then this one will pass to be north
              railnorth == "NORTH";
              railsouth == "SOUTH";
      
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
             
              //send mqtt to close the line from the southside
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "4");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Closing 3rd lane of south side");

    //message to open northside lane for northside
              lcd_open3_closing_south3();
              
     }
     else {
      //railsouth was changed to north, and rails were in the normal setup
      
              client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
              client.println("<a href=\"/north/south\"><button class=\"button button4\">NORTH</button>");
              client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
              client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
              client.println("<h2>Street rail emergency module</h2><p>");   
              client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
              client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
              client.println("<p style=\"font-size:150%;\">");
              client.println("NOTE: When emergency is pressed the lane will close</p>");
              client.println("</body></html>");
              
              //send mqtt to close southside lane
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "7");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Closing 2nd lane of south side");

    //lcd for message of opening an extra lane for northside
              lcd_open2_closing_south2();
             
     }
              
              south_way = 0;
   }
   
  
    ////////////////////////////////
    /////////////////////////////
    
    else if(railnorth == "NORTH" && north_way == 1 )
    {
      //railnorth was pressed and set back to its normal condition
      client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
      client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");
      client.println("<h2>Street rail emergency module</h2><p>");   
      client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
      client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
      client.println("<p style=\"font-size:150%;\">");
      client.println("NOTE: When emergency is pressed the lane will close</p>");
      client.println("</body></html>");
      north_way = 0;
              
//send mqtt to the southside to close their extra lane
    uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "4");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Closing 3rd lane of south side");

    //send message through the lcd to opening regular north lane
              lcd_open3_closing_south3();
             
        }

     
    else if (railsouth == "SOUTH" && south_way == 1)
    {
     //southside button was pressed to open it back to its normal condition
     
      client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<a href=\"/north/south\"><button class=\"button button2\">SOUTH</button>");
      client.println("<a href=\"/south/north\"><button class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

      client.println("<h2>Street rail emergency module</h2><p>");   
      client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
      client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
      client.println("<p style=\"font-size:150%;\">");
      client.println("NOTE: When emergency is pressed the lane will close</p>");
      client.println("</body></html>");
      
       //send mqtt to the southside about opening the south lane
       uint16_t packetIdPub2 = mqttClient.publish("southside", 2, true, "6");
    Serial.print("Publishing on topic esp32/temperature at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
    Serial.println("Publishing 0: open 2nd lane of the south");

    //send message through the lcd about closing the extra lane
       lcd_closing2_openingsouth2_lane();
       
             south_way = 0;
    }
    
    else //if(railnorth == "NORTH" && railsouth == "SOUTH" && north_way == 0 && south_way == 0)
    {
   if (railnorth == "SOUTH" && north_way == 0)
    {
      
      client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
    else if(railsouth == "NORTH" && south_way == 0)
    {
      client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">AUTOMATIC</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
      client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
    else{
     client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">AUTOMATIC</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
      client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
    }
  }
    // The HTTP response ends with another blank line
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  //                                                               //
  //      MANUAL INTERFACE OF THE WEB SERVER END                  ///          
  //                                                               //
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

  // AUTOMATIC MODE
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  //       WEB SERVER IN AUTOMATIC MODE              //
  /////////////////////////////////////////////////////                                    
  //     STREET RAILS BEHAVE ACCORDING TO            //
  //       THE SENSOR READINGS                       //
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  
  else if(performance == "AUTOMATIC")
  {
    manual = 0;
    if (railnorth == "SOUTH")
    {
      client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">AUTOMATIC</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
     int automatic = 1;
     client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
    else if(railsouth == "NORTH")
    {
      client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">AUTOMATIC</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
     int automatic = 1;
     client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
    else{
     client.println("<p><a href=\"/manual/automatic\"><button class = \"button button5\">AUTOMATIC</button></a>");
     client.println("<p>South-rail State       |||||||");
     client.println("      North-rail State</p>");
     int automatic = 1;
     client.println("<p><button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button2\">SOUTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button>");
      client.println("<button type=\"button\" disabled class=\"button button4\">NORTH</button></p>");

           client.println("<h2>Street rail emergency module</h2><p>");   
           client.println("<p><a href=\"/south/emergency\"><button class = \"button button5\">EMERGENCY(SOUTH-SIDE)</button></a>");
           client.println("<a href=\"/north/emergency\"><button class = \"button button5\">EMERGENCY(NORTH-SIDE)</button></a></p>");
           client.println("<p style=\"font-size:150%;\">");
           client.println("NOTE: When emergency is pressed the lane will close</p>");
           client.println("</body></html>");
    }
  }
}
          ////////////////////////////////////////////////////////////////////
          ///////////////////////////////////////////////////////////////////
          ///         SETTING OF BUTTONS FINISHED                        /////
          ////////////////////////////////////////////////////////////////////
          ///////////////////////////////////////////////////////////////////

          //CLOSING WEB SERVER PAGE

  // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    //client.stop();
   Serial.println("Client disconnected.");
    Serial.println("");
  }
}


            
