#include <FirebaseESP32.h>
#include <String.h>
#define FIREBASE_HOST "electric-bike0631-default-rtdb.asia-southeast1.firebasedatabase.app"       // "YOUR FIREBASE HOST COPIED" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "OEQQo6J2d1sskCPFMidbRvbiZW6weLrtzYpoxoAd"
String path = "123";

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
void loop() {

  Firebase.getString(firebaseData, path + "/fcm");
  printResult(firebaseData , "fcm");
  Firebase.setString(firebaseData, path + "/status", "true");
  }


void printResult(FirebaseData &data , String cmd){
  if (data.dataType() == "string") {
    Serial.println(cmd + data.stringData());
  }
}
