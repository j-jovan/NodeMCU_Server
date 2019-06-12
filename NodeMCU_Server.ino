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

  int ledPins[] = {13, 12, 14, 2, 0, 4, 5, 16}; //Array koji sadrzi sve pinove.
  int pinCount = 8; // Broj item-a u nizu ledPins[], jer sizeof() ne radi
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
    digitalWrite(ledPins[thisPin], LOW);
  }

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  // Fiksiranje IP adrese
  IPAddress ip(192, 168, 0, 200);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  WiFi.mode(WIFI_STA);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // server.begin podize server
  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Provera da li se klijent konektovao
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Cekaj dok klijent ne posalje zahtev
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Procitaj zahtev
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Uporedi zahtev

  int value13 = LOW;
  if (request.indexOf("/PIN13=ON") != -1)  {
    digitalWrite(ledPin13, HIGH);
    value13 = HIGH;
  }
  if (request.indexOf("/PIN13=OFF") != -1)  {
    digitalWrite(ledPin13, LOW);
    value13 = LOW;
  }
  int value12 = LOW;
  if (request.indexOf("/PIN12=ON") != -1)  {
    digitalWrite(ledPin12, HIGH);
    value12 = HIGH;
  }
  if (request.indexOf("/PIN12=OFF") != -1)  {
    digitalWrite(ledPin12, LOW);
    value12 = LOW;
  }
  int value14 = LOW;
  if (request.indexOf("/PIN14=ON") != -1)  {
    digitalWrite(ledPin14, HIGH);
    value14 = HIGH;
  }
  if (request.indexOf("/PIN14=OFF") != -1)  {
    digitalWrite(ledPin14, LOW);
    value14 = LOW;
  }
  int value2 = LOW;
  if (request.indexOf("/PIN2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/PIN2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
    value2 = LOW;
  }
  int value0 = LOW;
  if (request.indexOf("/PIN0=ON") != -1)  {
    digitalWrite(ledPin0, HIGH);
    value0 = HIGH;
  }
  if (request.indexOf("/PIN0=OFF") != -1)  {
    digitalWrite(ledPin0, LOW);
    value0 = LOW;
  }

  int value4 = LOW;
  if (request.indexOf("/PIN4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
    value4 = HIGH;
  }
  if (request.indexOf("/PIN4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
    value4 = LOW;
  }

  int value5 = LOW;
  if (request.indexOf("/PIN5=ON") != -1)  {
    digitalWrite(ledPin5, HIGH);
    value5 = HIGH;
  }
  if (request.indexOf("/PIN5=OFF") != -1)  {
    digitalWrite(ledPin5, LOW);
    value5 = LOW;
  }
  int value16 = LOW;
  if (request.indexOf("/PIN16=ON") != -1)  {
    digitalWrite(ledPin16, HIGH);
    value16 = HIGH;
  }
  if (request.indexOf("/PIN16=OFF") != -1)  {
    digitalWrite(ledPin16, LOW);
    value16 = LOW;
  }

  //Sledeci deo koda ce ukljuciti sve pinove redno, pa ce ih iskljuciti
  int valueRedno1 = HIGH;
  if (request.indexOf("/REDNO1") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while (repeat < brojPonavljanja) {
      rednoUkljucivanje();
      valueRedno1 = LOW;
      repeat++;
    }
  }

  int valueRedno2 = HIGH;
  if (request.indexOf("/REDNO2") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while (repeat < brojPonavljanja) {
      rednoUkljucivanje2();
      valueRedno1 = LOW;
      repeat++;
    }
  }

  int valueRedno3 = HIGH;
  if (request.indexOf("/REDNO3") != -1)  {
    int repeat = 0;
    int brojPonavljanja = 65;
    while (repeat < brojPonavljanja) {
      rednoUkljucivanje3();
      valueRedno3 = LOW;
      repeat++;
    }
  }

  // Vrati odgovor
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin 13 is now: ");

  if (value13 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN13=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN13=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 12 is now: ");

  if (value12 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN12=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN12=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 14 is now: ");

  if (value14 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN14=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN14=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 2 is now: ");

  if (value2 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN2=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN2=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 0 is now: ");

  if (value0 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN0=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN0=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 4 is now: ");

  if (value4 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN4=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN4=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 5 is now: ");

  if (value5 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN5=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN5=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");

  client.print("Led pin 16 is now: ");

  if (value16 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.println("<a href=\"/PIN16=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/PIN16=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  client.println("<a href=\"/REDNO1\"\"><button>Diode Redno 1 </button></a>");
  client.println("<a href=\"/REDNO2\"\"><button>Diode Redno 2 </button></a>");
  client.println("<a href=\"/REDNO3\"\"><button>Diode Redno 3 </button></a>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
