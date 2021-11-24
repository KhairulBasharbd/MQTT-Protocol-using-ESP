//I am Khairul.



//Including Library:
#include <ESP8266WiFi.h> //For WiFi Connectivity
#include <PubSubClient.h> //For MQTT


//WiFi ceredential:
const char* ssid = "STELLAR"; //EDIT HERE
const char* password = "stellarBD"; //EDIT HERE
WiFiClient espClient;
//MQTT Server:
const char* mqtt_server = "www.stellarbd.com"; //EDIT HERE
PubSubClient client(espClient);


void setup() {
	Serial.begin(115200);
	Serial.println("System Initialized");
	//WiFi setup:
	setup_wifi();
	Serial.println("WiFi Configured Successfully");
	//Mqtt server:
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);

}

void loop() {
	if (!client.connected()) { //This loop checks if mqtt is connected
    reconnect(); //If not then calls reconnect function
  }
  client.loop(); //This has to be run frequently to ensure MQTT is connected to server
  
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Callback function is used for MQTT Subscriber function:
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 }

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("espClient")) {
      	Serial.println("Connected");
  
      	//Once connected, publish an announcement...
      	client.publish("Your topic name", " The Message you want to send"); //EDIT HERE
        //... and resubscribe
      	client.subscribe("Topic name you want to subscribe"); //EDIT HERE
    } else {
      	Serial.print("failed, rc=");
      	Serial.print(client.state());
      	Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      	delay(5000);
    }
  }
}
//Upated by khairul Bashar for learning git