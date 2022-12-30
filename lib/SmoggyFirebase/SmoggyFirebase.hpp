#ifndef SMOGGY_FIREBASE_H
#define SMOGGY_FIREBASE_H

#include <Arduino.h>
#include <Firebase_ESP_Client.h>

#define API_KEY ""
#define DATABASE_URL ""


class SmoggyFirebase {
    public:
        void begin();
        void send();
        void setup();
        SmoggyFirebase();

    private:
        FirebaseConfig config;
        FirebaseData fbdo;
        FirebaseAuth auth;
        bool isSignedUp;

};
#endif