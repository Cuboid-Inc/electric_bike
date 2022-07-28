#include <FirebaseESP8266.h>
#include <String.h>
#include <ESP8266WiFi.h>
#include "Fetch.h"

#define FINGERPRINT "2C 0F 6B 84 9E 00 A5 72 F4 96 10 9E 72 19 E7 AF A0 B6 EF 3D"
#define FIREBASE_HOST "electric-bike0631-default-rtdb.asia-southeast1.firebasedatabase.app"       // "YOUR FIREBASE HOST COPIED" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "OEQQo6J2d1sskCPFMidbRvbiZW6weLrtzYpoxoAd"
String path = "123";

FirebaseData firebaseData;
int relaypin = 5; // D1(gpio5)
int button = 4; //D2(gpio4)
int buttonState=0;
const char* serverName = "https://fcm.googleapis.com/fcm/send";
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
bool downNotification = true;
bool upNotification = true;
void loop() {
     Firebase.getString(firebaseData, path + "/fcm");
  String fcm = firebaseData.stringData();
  buttonState=digitalRead(button); 
if (buttonState == 1){
  
  Firebase.setString(firebaseData, path + "/status", "true");
 digitalWrite(relaypin, LOW);
 Serial.println("The Stand Is Up"); 
 delay(200);
  if(upNotification){
  downNotification = true;
  upNotification = false;
    String body = "{\"notification\":{\"title\":\"\",\"body\":\"Stand Is UP!\"},\"to\":\""+fcm+"\"}";
  
  RequestOptions options;
    options.method = "POST";
    options.headers["Content-Type"] = "application/json";
    options.headers["Content-Length"] = String(body.length());
    options.headers["Authorization"] = "key=AAAA9TH0kjE:APA91bEdgulTpBSUMFqVwodcNjaE4JzOYHE9LQ8_fEz1umqdHnXaHm_ve5K1E3ymSljyrWP7SHdnS25-s6JGeCADM5viNVwMmFQUgj9Gp4aQretexIsea2fZZENp_W5PB_F_wwrm-XME";
    options.body = body;
    options.fingerprint = FINGERPRINT;

    // Making the request.
    Response response = fetch(serverName, options);
    Serial.println(response);
  }
 }
 if (buttonState==0){
    
  Firebase.setString(firebaseData, path + "/status", "false");
 digitalWrite(relaypin, HIGH);
 Serial.println("The Stand Is Down"); 
 delay(200);
 if(downNotification){
  downNotification = false;
  upNotification = true;
    String body = "{\"notification\":{\"title\":\"WARNING\",\"body\":\"Stand Is Down!\"},\"to\":\""+fcm+"\"}";
  
  RequestOptions options;
    options.method = "POST";
    options.headers["Content-Type"] = "application/json";
    options.headers["Content-Length"] = String(body.length());
    options.headers["Authorization"] = "key=AAAA9TH0kjE:APA91bEdgulTpBSUMFqVwodcNjaE4JzOYHE9LQ8_fEz1umqdHnXaHm_ve5K1E3ymSljyrWP7SHdnS25-s6JGeCADM5viNVwMmFQUgj9Gp4aQretexIsea2fZZENp_W5PB_F_wwrm-XME";
    options.body = body;
    options.fingerprint = FINGERPRINT;

    // Making the request.
    Response response = fetch(serverName, options);
    Serial.println(response);
  }
 } 

//  printResult(firebaseData , "fcm");

  
  }


void printResult(FirebaseData &data , String cmd){
  if (data.dataType() == "string") {
    Serial.println(cmd + data.stringData());
  }
}
