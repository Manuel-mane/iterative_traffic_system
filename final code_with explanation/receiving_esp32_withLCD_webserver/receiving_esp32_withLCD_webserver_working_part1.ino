/* 
 *Capstone 2 Project    : "Interactive Traffic System"
 *Author: Manuel Mane Penton          Professor. Hossain
 *        Nayib Ega        
 *        Balewa Glen 
 *        
 *Project About:
 *This code describe an IoT Interactive Traffic System which read the need on the traffic street and 
 *modifues street rails to improve the traffic flow. For it, the system uses wireless communication between
 *two arduino boards through MQTT protocol to send and receive information about the readings and for 
 *modifying and changing the LCDs and LEDs to address the traffic.
 *
 *
 *Part 2:    Rails modifier ESP32 / Web Server   (NORTH SIDE)
 *This code: 
 * -Describe the processing of the received readings of the traffic from the MKR1000.
 * -Send information back to the MKR1000 about the changes on the rails so the MKR1000 takes care
 * of the LCD and LEDs modification in the South Side
 * -Describe the Web Server interface with the Street Rails
 */



//used libraries
#include <LiquidCrystal.h>       //Library for LCD
#include <AsyncMqttClient.h>     //Library for MQTT protocol in ESP32
#include <WiFi.h>                //Library for Wifi connection


#define WIFI_SSID "Capstone"                   //Defining WiFi SSID
#define WIFI_PASSWORD "Capstone"               //DefininG WiFi passwrord
#define MQTT_HOST IPAddress(192, 168, 35, 2)   //Setting IP address of Broker (MQTT Protocl)
#define MQTT_PORT 1883                         //Default port for MQTT protocol
IPAddress ip;                                  //Saving in variable IP address ESP32 gets when connect to the wifi

// Create objects to handle MQTT client
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

//Objects for both LCDs
LiquidCrystal lcd1(15, 2, 4, 16, 17, 5); //Creates an LC object
LiquidCrystal lcd2(15, 18, 4, 16, 17, 5);

//////////////////////////////////////
//////////////////////////////////////
///     DEFINING VARIABLES       /////
//////////////////////////////////////
//////////////////////////////////////


////////////////////////////
//Variables for Web Server
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;


//For the received readings from the MKR1000
int sensor1;
int sensor2;
int sensor3;
int sensor4;


//rail leds for driver control
int leftred = 26;
int leftgreen = 25;
int rightred = 33;
int rightgreen = 32; 
boolean toggle = true;

////////////////////
//relays variables
int leftrail = 13;
int middlerail = 12;
int rightrail = 14;

//Variables for rail situation
int case1 = 0;
int case2 = 0;
int case3 = 0;
int manual = 0;


//LCD variables
char * LargeText;
int iLineNumber = 1;
int iCursor = 0;
int LCDtrigger = 23;
int LCDtrigger2 = 22;

//////////////////////////////
// Auxiliar variables to store the current output state
String railnorth = "NORTH";
String railsouth = "SOUTH";
String emergency_north = "EMERGENCY";
String emergency_south = "EMERGENCY";
String performance = "AUTOMATIC";
int emg_north;
int emg_south;
int north_way;
int south_way;
int automatic = 1;
/////////////////////////////////

////////////////////////////////
//Prototype functions
void count_processor();
void count_processor_north();
void count_processor_south();
void UpdateLCDDisplay();
void lcd_closing_north_rail();
void lcd_open_north_rail();
void web_server_reading_input();
void lcd_closing2_openingsouth2_lane();
/////////////////////////////////////

////////////////////////////////////
///// function to connect to WiFi //
////////////////////////////////////

void connectToWifi() {
   Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

////////////////////////////////////////
//  Functions for setting connection  //
//              with MQTT             //
////////////////////////////////////////

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}


//Connecting to WiFi 
void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      ip = WiFi.localIP();                    //Saving obtained IP to variable
      connectToMqtt();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      xTimerStop(mqttReconnectTimer, 0);      // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
      xTimerStart(wifiReconnectTimer, 0);
      break;
      default:
      break;
  }
}

// Subscribing the ESP32 to topics that it will receive the information from
// Add more topics that want your ESP32 to be subscribed to
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  // Subscribing to topics: "sensor1", "sensor2", "sensor3", "sensor4"
  uint16_t sensor1Id = mqttClient.subscribe("sensor1", 0);
  uint16_t sensor2Id = mqttClient.subscribe("sensor2", 0);
  uint16_t sensor3Id = mqttClient.subscribe("sensor3", 0);
  uint16_t sensor4Id = mqttClient.subscribe("sensor4", 0);
  Serial.print("Subscribing at QoS 0, packetId: ");
  Serial.println(sensor1Id);
  Serial.println(sensor2Id);
  Serial.println(sensor3Id);
  Serial.println(sensor4Id);
 }

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

// You can modify this function to handle what happens when you receive a certain message in a specific topic
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  String messageTemp;
  for (int i = 0; i < len; i++) {
    
    messageTemp += (char)payload[i];    //Obtaining the received message into messageTemp
    
  }
  // Check if the MQTT message was received on topic sensor1
  if (strcmp(topic, "sensor1") == 0) {
  Serial.println(messageTemp);
  sensor1 = messageTemp.toInt();     //Converting string messageTemp into int and saving it in variable "sensor1"
  
  }
  // Check if the MQTT message was received on topic sensor2
  if (strcmp(topic, "sensor2") == 0) {  
  Serial.println(messageTemp);
  sensor2 = messageTemp.toInt();     //Converting string messageTemp into int and saving it in variable "sensor2"
  }
  // Check if the MQTT message was received on topic sensor3
  if (strcmp(topic, "sensor3") == 0) {
  Serial.println(messageTemp);
  sensor3 = messageTemp.toInt();     //Converting string messageTemp into int and saving it in variable "sensor3"
  }
  // Check if the MQTT message was received on topic sensor4
  if (strcmp(topic, "sensor4") == 0) {
  Serial.println(messageTemp);
  sensor4 = messageTemp.toInt();     //Converting string messageTemp into int and saving it in variable "sensor4"
  }
//delay(500);

}
void setup() {

//LCD variables
lcd1.begin(16,2); //Initialize the interface to the LCD screen
lcd2.begin(16,2);
lcd1.clear();     //clean the LCDs
lcd2.clear();

///////////////////////////////////
///////////////////////////////////
// Configuring the mode of the  ///
//         variables            ///
///////////////////////////////////
///////////////////////////////////

//Defining leds
pinMode(leftred, OUTPUT);
pinMode(leftgreen, OUTPUT);
pinMode(rightred, OUTPUT);
pinMode(rightgreen, OUTPUT);

//for the relays
pinMode(leftrail, OUTPUT);
pinMode(middlerail, OUTPUT);
pinMode(rightrail, OUTPUT);

//Initial condition of street leds NORTH SIDE
digitalWrite(leftred, LOW); 
digitalWrite(leftgreen, HIGH);
digitalWrite(rightred, HIGH);
digitalWrite(rightgreen, LOW);

//Initial condition of street rails
digitalWrite(leftrail, LOW);
digitalWrite(middlerail, HIGH);
digitalWrite(rightrail, LOW);
  
  Serial.begin(115200);    //Start interface 115200

  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

//MQTT functions
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
  server.begin();          //Start connection with the server
  
}


void loop() {
 
/////////////////////////////////////////////////////////////////////////////////////
web_server_reading_input(); 

  if(automatic == 1)
  {
///////////////////////////////////////////////////
///    The system takes care of the            ////
///    street rails based on the reading       ////
///    of the sensors coming from the MKR1000  ////
///////////////////////////////////////////////////

if(case1 == 1)
{
  count_processor_north();
    }

else if(case2 == 1)
{
  count_processor_south();
}
else
{
count_processor();
}
delay(5000);       //Time that it takes to the system complete the changes of the LCDs and LEDs

}

}
