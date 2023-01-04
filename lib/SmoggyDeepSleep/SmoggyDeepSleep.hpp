#include "Arduino.h"
#define uS_TO_S_FACTOR 1000000ULL         /* Conversion factor for micro seconds to seconds */

#define TIME_TO_SLEEP_uS MEASURMENT_INTERVAL / 1000 * uS_TO_S_FACTOR


class SmoggyDeepSleep {
    public:
        SmoggyDeepSleep();
        void setup(int time_to_sleep);
        void start();
        bool DEEP_SLEEP_EN;
        int MEASURMENT_INTERVAL;
};