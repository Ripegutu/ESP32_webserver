#include <WiFi.h>

const char* ssid = "SSID HERE";
const char* password = "PassWord HERE";

WiFiServer server(80);

String header;

String outputState_1 = "off";
String outputState_2 = "off";
String outputState_3 = "off";
String outputState_4 = "off";
String outputState_5 = "off";

int pin_1 = 2;
int pin_2 = 15;
int pin_3 = 4;
int pin_4 = 16;
int pin_5 = 17;

double currentTime = millis();

double previousTime = 0;

int timeoutTime = 2000;


void setup() {
Serial.begin(115200);

pinMode(pin_1, OUTPUT);
pinMode(pin_2, OUTPUT);
pinMode(pin_3, OUTPUT);
pinMode(pin_4, OUTPUT);
pinMode(pin_5, OUTPUT);

digitalWrite(pin_1, LOW);
digitalWrite(pin_2, LOW);
digitalWrite(pin_3, LOW);
digitalWrite(pin_4, LOW);
digitalWrite(pin_5, LOW);

//Connect to WIFI.
Serial.print("Connecting to:");
Serial.println(ssid);
WiFi.begin(ssid,password);
while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }

//Print local IP adress and start web server
Serial.println("");
Serial.println("Wifi connected.");
Serial.println("IP adress: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listening for incoming clients

  if (client) {
    Serial.println("New client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;

    while (client.connected() && currentTime - previousTime <= timeoutTime){
      currentTime = millis();
      if (client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if ( currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection:close");
            client.println();

            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("Pin1 on");
              outputState_1 = "on";
              digitalWrite(pin_1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("Pin1 off");
              outputState_1 = "off";
              digitalWrite(pin_1, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("Pin2 on");
              outputState_2 = "on";
              digitalWrite(pin_2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("Pin2 off");
              outputState_2 = "off";
              digitalWrite(pin_2, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("Pin3 on");
              outputState_3 = "on";
              digitalWrite(pin_3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("Pin3 off");
              outputState_3 = "off";
              digitalWrite(pin_3, LOW);
            }else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Pin4 on");
              outputState_4 = "on";
              digitalWrite(pin_4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Pin4 off");
              outputState_4 = "off";
              digitalWrite(pin_4, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("Pin5 on");
              outputState_5 = "on";
              digitalWrite(pin_5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("Pin5 off");
              outputState_5 = "off";
              digitalWrite(pin_5, LOW);
            }

             // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Web Server for On/Off Control</h1>");
            
            // Display current state, and ON/OFF buttons for pin_1
            client.println("<p>Output 1 - State " + outputState_1 + "</p>");
            // If the outputState_1 is off, it displays the ON button       
            if (outputState_1=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for pin_2 
            client.println("<p>Output 2 - State " + outputState_2 + "</p>");
            // If the outputState_2 is off, it displays the ON button       
            if (outputState_2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for pin_3 
            client.println("<p>Output 3 - State " + outputState_3 + "</p>");
            // If the outputState_3 is off, it displays the ON button       
            if (outputState_3=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for pin_4 
            client.println("<p>Output 4 - State " + outputState_4 + "</p>");
            // If the outputState_4 is off, it displays the ON button       
            if (outputState_4=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for pin_5 
            client.println("<p>Output 5 - State " + outputState_5 + "</p>");
            // If the outputState_5 is off, it displays the ON button       
            if (outputState_5=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
            
            } else {
              currentLine = "";
              }
              }
              else if (c != '\r'){
                currentLine += c;}
              
              }
            }
    header = "";
  client.stop();
  Serial.println("Client disconnected");
  Serial.println("");
          }


 
}
