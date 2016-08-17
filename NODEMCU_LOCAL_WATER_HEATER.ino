/* NODEMCU PINS
   D0 -> GPIO 16
   D1 -> GPIO 05
   D2 -> GPIO 04
   D3 -> GPIO 00
   D4 -> GPIO 02
   D5 -> GPIO 14
   D6 -> GPIO 12
   D7 -> GPIO 13
   D8 -> GPIO 15
   THESE TWO SEEMS NOT WORKING
   SDD3 -> GPIO 10
   SDD2 -> GPIO 09
*/

#include <ESP8266WiFi.h>
#include <stdint.h>

  IPAddress ip(192,168,1,25);  //Node static IP, these may be not very correct but it works
  IPAddress gateway(192,168,168,168);
  IPAddress subnet(255,255,255,0);

const char* ssid = "WIFI ROUTER NAME";
const char* password = "WIFI PASS";
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;  
int outputValue = 0;
int timeVal = 0;
int value = 0;
 
int RelayPin = 05; // (D1 on Nodemcu)
int connectionLed = 04; // ((D2 on Nodemcu)
int dugme = 14;

WiFiServer server(80);

void WIFI_connect(){
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(connectionLed, HIGH);
    delay(50);
    digitalWrite(connectionLed, LOW);
    Serial.print(".");
    delay(50);
  }
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(connectionLed, HIGH);
  }

  Serial.println("");
  Serial.println("WiFi connected");
 
  }
  
void setup() {
  
  Serial.begin(115200);
  delay(10);
 
  pinMode(RelayPin, OUTPUT);
  pinMode(connectionLed, OUTPUT);
  digitalWrite(RelayPin, LOW);
  digitalWrite(connectionLed, LOW);
  pinMode(dugme, INPUT);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 WIFI_connect();
}
 
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
     delay(1);
     
   if((1.6*sensorValue) >= 100){
    digitalWrite(RelayPin, LOW); 
    value = 0;
    sensorValue = 100;
      delay(1);
   }
      

    if(digitalRead(dugme) == HIGH){
 if(value ==0){digitalWrite(RelayPin, HIGH);
 value = 1;}else if(value ==1){digitalWrite(RelayPin, HIGH);
 value = 0;}
 delay(1);
  }
  

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    delay(1);
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  client.println("HTTP/1.1 200 OK");
  // Match the request
    if (request.indexOf("/GET=SENSORVAL") != -1)  {
  
   client.println("Content-Type: text");
   client.println(""); //  do not forget this one
   client.println(1.6*sensorValue);
  }
  
  if (request.indexOf("/GET=ON") != -1)  {
    digitalWrite(RelayPin, HIGH);
    value = 1;
  }
  if (request.indexOf("/GET=OFF") != -1)  {
    digitalWrite(RelayPin, LOW);
    value = 0;
  }
// Set RelayPin according to the request
Send some favicon
if(request.indexOf("/favicon.ico") != -1){
client.println("<img alt='favketil.png'"); 
client.println("src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAALEgAACxIB0t1+/AAAABZ0RVh0Q3JlYXRpb24gVGltZQAwOC8wNy8xNkCdBcoAAAAcdEVYdFNvZnR3YXJlAEFkb2JlIEZpcmV3b3JrcyBDUzbovLKMAAAA8ElEQVRIidWWwRGCMBBF/zLc0Q50RguwCShEOoAyoAJphFTBnYsdqBV8D5jARHQcSHD4pySHvPzdzSYCgPAokgIAIQC0VeoFckwrMw5dbvZNIUkREc5xpcMjIizifj1X/TgAgLZK97+ebKoCADicL1cXm5GUoYsi7lwa0BJaL6iIcRqGzxsoq9mMrXsPnS6I9ebob6BcdQWyiKOsZuMcZPc7rXXmqExkM5y/8rN1DsoVbnbYspp3p6AykZ0FNW4AQMjuy6DbuUvpBxGwnvKxapkqu7EGwLttHxKSH2t/ph65QqTD5/MeRcOJceSLph09AQQYVFoq2cKeAAAAAElFTkSuQmCC' />");
}
 
  // Return the response

  if(request.indexOf("/LED=") == -1 && request.indexOf("/favicon.ico") == -1){
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
 client.println(" <!DOCTYPE HTML>        ");                                                                                   
client.println(" <html> ");
client.println(" <style> body{ ");
client.println(" height: 100%;  ");
client.println(" background-color: cornflowerblue;"); 
client.println(" display: flex;  ");
client.println(" align-items: center;");   
client.println(" justify-content: center;");
client.println("transition: background-color 2s;} ");
  client.println("  #wrap{transform: scale(2);");
   client.println(" }");
client.println(" </style>");
client.println("<div id='wrap'>");
client.println(" <svg viewBox='0 0 286 398'");
client.println("  xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' xml:space='preserve'");
client.println("  x='0px' y='0px' width='286px' height='398px'");
client.println(" >");
client.println("  <g id='Layer%201'>");
client.println("    <path d='M 50 343 L 231 343 L 221 307 L 62 307 L 50 343 Z' stroke='#000000' stroke-width='4' fill='#8c4600'/>");
client.println("    <path d='M 62 307 C 62 307 66 188 60 178 C 54 168 41 141 41 141 L 178 141 L 234 141 L 234 156.6667 L 178 161.6667 L 178 307 L 62 307 Z' stroke='#000000' stroke-width='4' fill='#db9c64'/>");
client.println("    <path d='M 178 202.5 L 173.493 202.5 L 167.493 199.5 L 161.4931 202.5 L 155.4932 199.5 L 149.4936 202.5 L 143.4941 199.5 L 137.4941 202.5 L 131.4949 199.5 L 125.4955 202.5 L 119.4958 199.5 L 113.496 202.5 L 107.4967 199.5 L 101.4969 202.5 L 95.4974 199.5 L 89.4975 202.5 L 83.4979 199.5 L 77.4989 202.5 L 71.4996 199.5 L 65.4999 202.5 L 62.85 202.5 C 64.2466 240.2103 63 307 63 307 L 178 307 L 178 202.5 Z' stroke='#000000' stroke-width='4' fill='#99e5ff'/>");
client.println("    <path d='M 190 307 C 190 307 216.6351 272.3889 216 240 C 215.3333 206 201 159 201 159 L 231 157 C 231 157 246.6667 209 246 240 C 245.3333 271 221 307 221 307 L 190 307 Z' stroke='#000000' stroke-width='4' fill='#8c4600'/>");
client.println("    <path id='Ellipse' d='M 103 324 C 103 314.611 110.611 307 120 307 C 129.389 307 137 314.611 137 324 C 137 333.389 129.389 341 120 341 C 110.611 341 103 333.389 103 324 Z' stroke='#000000' stroke-width='4' fill='#d90000'/>");
client.println("    <path id='wire' d='M 79 307 L 79 271 L 85 284 L 92 273 L 99 284 L 106 272 L 112 284 L 119 272 L 124 283 L 132 271 L 138 282 L 144 270.6667 L 151 284 L 158 270 L 158 305 ' stroke='#000000' stroke-width='4' fill='none'/>");
client.println("  </g>");
client.println(" </svg>");
client.println(" <div style= 'font-size: x-large;margin-top: -175px;margin-left: 80px;'><span id='val'>30.00</span><span>C</span></div></div>");
client.println(" <script>");
client.println("     var bulb = document.getElementsByTagName('svg')[0];");
client.println("     var bulbElipse = document.getElementsByTagName('svg')[0].getElementById('Ellipse');");
client.println("     var wire = document.getElementsByTagName('svg')[0].getElementById('wire');");
client.println("     var onOff = 'off';");
client.println("     var readyToReceive= true;");
client.println(" bulb.onclick = function(){");
client.println("     var xhttp = new XMLHttpRequest();");
client.println("     xhttp.onreadystatechange = function(e) {");
client.println("      if (xhttp.readyState == 4 && xhttp.status == 200) {");
client.println("readyToReceive = true;");
client.println("        if(onOff == 'off'){onOff = 'on';      ");
client.println("        bulbElipse.style.fill = 'yellow';          ");
client.println("        wire.style.stroke = 'orange';          ");
client.println("document.body.style.backgroundColor = 'coral';}");
client.println("        else if(onOff == 'on'){onOff = 'off';   ");
client.println("        bulbElipse.style.fill = 'red';      ");
client.println("        wire.style.stroke = 'black'; ");
client.println("document.body.style.backgroundColor = 'cornflowerblue';}");
client.println("        }");
client.println("    };");
client.println("     var link;");
client.println("         if(onOff == 'off'){link = '/GET=ON';}");
client.println("         else if(onOff =='on'){link = '/GET=OFF';}");
client.println("  if(readyToReceive){readyToReceive = false;");
client.println(" xhttp.open('GET', link, true);");
client.println("    xhttp.send();}");
client.println(" }");
client.println(" function getSensorVal(){");
client.println(" var xhttp = new XMLHttpRequest();");
client.println(" xhttp.onreadystatechange = function(e) {");
client.println("      if (xhttp.readyState == 4 && xhttp.status == 200) {");
client.println("      document.getElementById('val').innerHTML =xhttp.responseText;");
client.println("if(+document.getElementById('val').innerHTML >= 100){ onOff = 'off'; bulbElipse.style.fill = 'red'; wire.style.stroke = 'black'; document.body.style.backgroundColor = 'cornflowerblue'; }");
client.println(" if(onOff == on){window.alert('Su kaynadı');}    } }");
client.println("      xhttp.open('GET', 'GET=SENSORVAL', true);");
client.println("    xhttp.send();");
client.println(" }");
client.println("      setInterval(getSensorVal, 1000);");
client.println("  </script>");
client.println(" </html>");

  }
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
