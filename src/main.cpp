#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

int Led_OnBoard = 2; // Initialize the Led_OnBoard

const char *ssid = "MahyaLink";         // Your wifi Name
const char *password = "102030ugd"; // Your wifi Password

const char *host = "192.168.1.131"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup()
{
  // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT); // Initialize the Led_OnBoard pin as an output
  Serial.begin(921600);
  WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, password); //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }

  digitalWrite(Led_OnBoard, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP
}

void loop()
{
  // put your main code here, to run repeatedly:
  HTTPClient client; //Declare object of class HTTPClient

  String LdrValueSend, postData;
  int ldrvalue = analogRead(A0);   //Read Analog value of LDR
  LdrValueSend = String(ldrvalue); //String to interger conversion

  //Post Data
  postData = "ldrvalue=" + LdrValueSend;

  client.begin("http://192.168.1.131/Nodemcu_db_record_view/InsertDB.php");              //Specify request destination
  client.addHeader("Access-Control-Allow-Origin", "*");
  client.addHeader("Content-Type", "text/plain");
  int httpCode = client.POST(postData);   //Send the request
  String payload = client.getString();    //Get the response payload

  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  // Serial.println(payload);    //Print request response payload
  Serial.println("LDR Value=" + LdrValueSend);
  
  client.end();  //Close connection

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}
