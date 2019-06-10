#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

int ledPin13 = 13;
int ledPin12 = 12;
int ledPin14 = 14;
int ledPin2 = 2;
int ledPin0 = 0;
int ledPin4 = 4;
int ledPin5 = 5;
int ledPin16 = 16;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin13, OUTPUT);
  digitalWrite(ledPin13, LOW);
  pinMode(ledPin12, OUTPUT);
  digitalWrite(ledPin12, LOW);
  pinMode(ledPin14, OUTPUT);
  digitalWrite(ledPin14, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  pinMode(ledPin0, OUTPUT);
  digitalWrite(ledPin0, LOW);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin4, LOW);
  pinMode(ledPin5, OUTPUT);
  digitalWrite(ledPin5, LOW);
  pinMode(ledPin16, OUTPUT);
  digitalWrite(ledPin16, LOW);

  // Connect to WiFi network
  Serial.println();
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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value13 = LOW;
  if (request.indexOf("/LED13=ON") != -1)  {
    digitalWrite(ledPin13, HIGH);
    value13 = HIGH;
  }
  if (request.indexOf("/LED13=OFF") != -1)  {
    digitalWrite(ledPin13, LOW);
    value13 = LOW;
  }

  int value12 = LOW;
  if (request.indexOf("/LED12=ON") != -1)  {
    digitalWrite(ledPin12, HIGH);
    value12 = HIGH;
  }
  if (request.indexOf("/LED12=OFF") != -1)  {
    digitalWrite(ledPin12, LOW);
    value12 = LOW;
  }
  int value14 = LOW;
  if (request.indexOf("/LED14=ON") != -1)  {
    digitalWrite(ledPin14, HIGH);
    value14 = HIGH;
  }
  if (request.indexOf("/LED14=OFF") != -1)  {
    digitalWrite(ledPin14, LOW);
    value14 = LOW;
  }

  int value2 = LOW;
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
    value2 = LOW;
  }

  int value0 = LOW;
  if (request.indexOf("/LED0=ON") != -1)  {
    digitalWrite(ledPin0, HIGH);
    value0 = HIGH;
  }
  if (request.indexOf("/LED0=OFF") != -1)  {
    digitalWrite(ledPin0, LOW);
    value0 = LOW;
  }

  int value4 = LOW;
  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
    value4 = HIGH;
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
    value4 = LOW;
  }

  int value5 = LOW;
  if (request.indexOf("/LED5=ON") != -1)  {
    digitalWrite(ledPin5, HIGH);
    value5 = HIGH;
  }
  if (request.indexOf("/LED5=OFF") != -1)  {
    digitalWrite(ledPin5, LOW);
    value5 = LOW;
  }

  int value16 = LOW;
  if (request.indexOf("/LED16=ON") != -1)  {
    digitalWrite(ledPin16, HIGH);
    value16 = HIGH;
  }
  if (request.indexOf("/LED16=OFF") != -1)  {
    digitalWrite(ledPin16, LOW);
    value16 = LOW;
  }

  //Sledeci deo koda ce ukljuciti sve pinove redno, pa ce ih iskljuciti
  int valueRedno1 = HIGH;
  if (request.indexOf("/REDNO1") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while(repeat < brojPonavljanja){
    rednoUkljucivanje();
    valueRedno1 = LOW;
    repeat++;
    }
  }

  int valueRedno2 = HIGH;
  if (request.indexOf("/REDNO2") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while(repeat < brojPonavljanja){
    rednoUkljucivanje2();
    valueRedno1 = LOW;
    repeat++;
    }
  }

  int valueRedno3 = HIGH;
  if (request.indexOf("/REDNO3") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while(repeat < brojPonavljanja){
    rednoUkljucivanje3();
    valueRedno3 = LOW;
    repeat++;
    }
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin 13 is now: ");

  if (value13 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED13=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED13=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  //j
  client.print("Led pin 12 is now: ");

  if (value12 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED12=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED12=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  //j

  client.print("Led pin 14 is now: ");

  if (value14 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED14=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED14=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 2 is now: ");

  if (value2 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 0 is now: ");

  if (value0 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED0=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED0=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 4 is now: ");

  if (value4 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED4=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED4=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 5 is now: ");

  if (value5 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED5=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED5=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 16 is now: ");

  if (value16 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/LED16=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED16=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  client.println("<a href=\"/REDNO1\"\"><button>Diode Redno 1 </button></a>");
  client.println("<a href=\"/REDNO2\"\"><button>Diode Redno 2 </button></a>");
  client.println("<a href=\"/REDNO3\"\"><button>Diode Redno 3 </button></a>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
