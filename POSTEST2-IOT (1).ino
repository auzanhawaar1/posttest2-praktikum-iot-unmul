#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid="OjanPhone";
const char* pass ="auzan223";

#define LED1 D5
#define BUZZER1 D6
#define BTNPLUS D1
#define BTNMIN D2
#define BTNONOFF D3

ESP8266WebServer server(80);
String webpage;

int nilaicahaya = 0;
int nilaiBuzzer= 100;
bool Enablebtn = false;
int btnstateplus = 0;
int btnstatemin = 0;
int btnon = 0;
void setup(){
  Serial.begin(115200);
  delay(10);
  pinMode(LED1,OUTPUT);
  pinMode(BUZZER1,OUTPUT);
  pinMode(BTNONOFF,INPUT);
  pinMode(BTNPLUS,INPUT);
  pinMode(BTNMIN,INPUT);
  // Connect ke WiFi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur WiFi 
  WiFi.mode(WIFI_STA);                      // Mode Station
  // WiFi.mode(WIFI_AP);                      // Mode AP
  WiFi.begin(ssid, pass);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.println("Ip Adrress : ");
 Serial.println(WiFi.localIP());
  Web();
  server.on("/",[](){
    server.send(200,"text/html",webpage);
  });
}
void loop(){
   server.handleClient();
   btnstateplus = digitalRead(BTNPLUS);
   btnstatemin = digitalRead(BTNMIN);
   btnon = digitalRead(BTNONOFF);

   if (btnon == LOW) {
    Enablebtn = !Enablebtn;
    delay(1000);
   }
  if(Enablebtn){
    digitalWrite(LED1,HIGH);
  tone(BUZZER1,nilaiBuzzer);
   }else{
     noTone(BUZZER1);
     digitalWrite(LED1,0);
   }
   if(btnstateplus == LOW && !Enablebtn){
    if(nilaiBuzzer < 2500){
    Serial.println(nilaiBuzzer);
    nilaiBuzzer += 10; 
    delay(200);
    }
    if(nilaicahaya > 0  && nilaicahaya < 249 ){
      nilaicahaya = min(nilaicahaya + 3, 249);
      analogWrite(LED1, nilaicahaya);
      delay(200);
    }
   
   }
   if(btnstatemin == LOW && !Enablebtn){
    if(nilaiBuzzer > 2500 && nilaiBuzzer > 0){
    Serial.println(nilaiBuzzer);
    nilaiBuzzer -= 10;
    delay(200);
   }
   if(nilaicahaya < 249 && nilaicahaya > 0){
      Serial.println(nilaicahaya);
      nilaicahaya -= 3;
       delay(200);
   }
   
   }

   
}
   void Web(){
    webpage += "<h1> Web Control ESP8266</h1>";
    webpage += "nilai cahaya LED";
    webpage += "<a><br>";
  webpage += String(nilaicahaya) ;
  webpage += "Nilai Nada buzzer";
  webpage += "<a></a><br>";
  webpage += String(nilaiBuzzer);
   }