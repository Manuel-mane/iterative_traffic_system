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
 *Part 1:    Street Rails sensors / MKR1000   (NORTH SIDE)
 *This code: 
 * -Read the traffic on the different rails and buil an counter for each.
 * -Send the counter information after a period of time to the ESP32.
 * -Receive the proccessed information from the MKR1000 to modify the LEDs and LCDs
 * for the drivers coming from the southside of the street.
 */

#include <WiFi101.h>           //Library for stablishing WiFi connection in MKR1000
#include <LiquidCrystal.h>     //Library for LCDs
#include <ArduinoMqttClient.h> //Library for MQTT protocol in MKR1000

#define SECRET_SSID "Capstone" //Defining the SSID of the WiFi the board is connecting to
#define SECRET_PASS "Capstone" //Defining the password of the WiFi the board is connecting to

char ssid[] = SECRET_SSID;        //saving the prior information in variables
char pass[] = SECRET_PASS;

////////////////////////////////////////
//   DEFINING THE VARIABLES          ///
////////////////////////////////////////

//Variables of the sensors
int sensor1 = A4;
int sensor2 = A3;
int sensor3 = A2;
int sensor4 = A1;

//Variables for the counter of the street traffic, through the sensors
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;

//Timer the system will use that will dictate when the counter is sent to the ESP32
int timer = 0;  //counter for a minute

//Variable for LCD
int messagelcd = 0;

//Variables for the LEDs
int rightgreen = 10;
int rightred = 11;
int leftgreen = 8;
int leftred = 9;

//Variables used in the processing of the counters
int A = 0;
int B = 0;
int D = 0;
int C = 0;

//port for the MQTT connection
int port = 1883;
String rail;
boolean toggle = true;

//Function prototypes
void sensor_reading();
void reconnect();
void LCDcalling();
void LCDcalling2();
void UpdateLCDDisplay();

//LCD Variables
LiquidCrystal lcd1(5, 4, 3, 2, 1, 6);
LiquidCrystal lcd2(5, 7, 3, 2, 1, 6);
char * LargeText;
int iLineNumber = 1;
int iCursor = 0;
//int LCDtrigger = 8;
//int LCDtrigger2 = 9;

//variables for the MQTT protocol
//Topics the system is suscribed to, so from where it will receive the information from the ESP32
const char *ID = "Sensors readings";  // Name of our device, must be unique
const char *TOPIC = "sensor1";  // Topic to subcribe to
const char *TOPIC2 = "sensor2";
const char *TOPIC3 = "sensor3";
const char *TOPIC4 = "sensor4";
const char *TOPIC5 = "southside";


//Stablishing a connection with the broker
//IPAddress
const char broker[] = "192.168.35.2"; // IP address of your MQTT broker eg. 192.168.1.50
WiFiClient wclient;
MqttClient mqttClient(wclient); // Setup MQTT client



void setup() {
  // put your setup code here, to run once:
//Stablishing the input and output mode of the variables
pinMode (A1, INPUT);
pinMode (A2, INPUT);
pinMode (A3, INPUT);
pinMode (A4, INPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);

//Initial condition
digitalWrite(rightgreen, HIGH);
digitalWrite(rightred, LOW);
digitalWrite(leftgreen, LOW);
digitalWrite(leftred, HIGH);

//Initial settup of the LCD
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Initializing");
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Initializing ");

//Connectiong to the network 
Serial.begin(115200);
Serial.print("\nConnecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass); // Connect to network

while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
}
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //String IP = WiFi.localIP();

//attempting connection with the mqtt broker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if(!mqttClient.connect(broker, port)) {
    
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(TOPIC5);
  Serial.println();
  mqttClient.subscribe(TOPIC5);    

}

//The following function reads the message the system receives through MQTT protocol
void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");
///////////////////////////////////////////////
  String messagemqtt;
  //int message = mqttClient.parseMessage();
  for (int i = 0; i < messageSize; i++) {
  messagemqtt += (char)mqttClient.read();          //Saving the received message into messagemqtt
  }
  messagelcd = messagemqtt.toInt();                //Converting the string into int
  Serial.println(messagelcd);

  // According to the received message it will call the different functions that
  // will update the LEDs and LCDs
  if(messagelcd == 7)
  {
    LCDcalling();                  
  }
  else if(messagelcd == 6)
  {
    LCDcalling2();
  }
  else if(messagelcd == 2)
  {
    LCDcalling3();
  }
  else if(messagelcd == 3)
  {
    LCDcalling4();
  }
  else if(messagelcd == 4)
  {
    LCDcalling5();
  }
  else if(messagelcd == 5)
  {
    LCDcalling6();
  }
  Serial.println();
}
void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.poll();
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Drive carefully");
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Drive carefully ");
    
sensor_reading();

delay (500); //   Wait half second 
timer++;

if (timer == 60)  //After a minute pass
{ Serial.println(" Sending the data ");
  
  timer = 0;            //reset the timer back to the beginning
 
if (!mqttClient.connected())  // Reconnect if connection is lost
  {
    reconnect();

  }

  //Send the recollected counter to the ESP32 using MQTT protocol
    mqttClient.beginMessage(TOPIC);
    mqttClient.print(counter1);
    mqttClient.endMessage();

    mqttClient.beginMessage(TOPIC2);
    mqttClient.print(counter2);
    mqttClient.endMessage();

    mqttClient.beginMessage(TOPIC3);
    mqttClient.print(counter3);
    mqttClient.endMessage();

    mqttClient.beginMessage(TOPIC4);
    mqttClient.print(counter4);
    mqttClient.endMessage();

    
  //Resetting the counters
  counter1 = 0; 
  counter2 = 0;
  counter3 = 0;
  counter4 = 0;
  
}
}
