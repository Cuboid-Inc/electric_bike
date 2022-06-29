#include <FirebaseESP8266.h>
#include <String.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "electric-bike0631-default-rtdb.asia-southeast1.firebasedatabase.app"       // "YOUR FIREBASE HOST COPIED" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "OEQQo6J2d1sskCPFMidbRvbiZW6weLrtzYpoxoAd"
String path = "123";

FirebaseData firebaseData;
int relaypin = 5; // D1(gpio5)
int button = 4; //D2(gpio4)
int buttonState=0;
void setup() {
  Serial.begin(115200);
    pinMode(relaypin, OUTPUT);
 pinMode(button, INPUT);
   Serial.print("Connecting ...");
  WiFi.begin("Khan Pro", "khan5805");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
void loop() {
  buttonState=digitalRead(button); 
if (buttonState == 1){
  Firebase.setString(firebaseData, path + "/status", "true");
 digitalWrite(relaypin, LOW);
 Serial.println("The Stand Is Up"); 
 delay(200);
 }
 if (buttonState==0){
  Firebase.setString(firebaseData, path + "/status", "false");
 digitalWrite(relaypin, HIGH);
 Serial.println("The Stand Is Down"); 
 delay(200);
 } 
  Firebase.getString(firebaseData, path + "/fcm");
  printResult(firebaseData , "fcm");
  
  }


void printResult(FirebaseData &data , String cmd){
  if (data.dataType() == "string") {
    Serial.println(cmd + data.stringData());
  }
}
