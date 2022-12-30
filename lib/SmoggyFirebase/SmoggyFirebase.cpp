#include "SmoggyFirebase.hpp"
//Provide the token generation process info.
// #include "addons/TokenHelper.h
//Provide the RTDB payload printing info and other helper functions.
// #include <addons/RTDBHelper.h>

SmoggyFirebase::SmoggyFirebase(){};

void SmoggyFirebase::setup() {
    this->config = FirebaseConfig();
    this->auth = FirebaseAuth();
    this->config.api_key = API_KEY;
    this->config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    this->isSignedUp = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

    /* Assign the callback function for the long running token generation task */
  // config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
};

void SmoggyFirebase::send() {
  if (Firebase.ready() && this->isSignedUp) {
    if (Firebase.RTDB.setInt(&fbdo, "test/int", 123)){
          Serial.println("PASSED");
          Serial.println("PATH: " + fbdo.dataPath());
          Serial.println("TYPE: " + fbdo.dataType());
        } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
};