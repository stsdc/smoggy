# Smoggy
_Firmware for ESP32 to measure weather condition and air quality_


* Support ESP32
* Support BME280
* Support PMS7003
* Battery voltage measurement
* No measurement if low battery
* Sending to Sensors.Community (Luftdaten) (every 2min)
* Sending to aqi.eco (every 3min)
* DeepSleep by default
* Press *boot* button to wake up and disable DeepSleep until next reset
* Settings page:
   - Show ID
   - Save aqi.eco  unique path 
 * Prepare to add Firebase support
   - Dummy data sending works; needs a method to accept real data

## Installing
Look at this instructions: https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/flashing-firmware.html

_Inspired by [Smogomierz](https://github.com/hackerspace-silesia/Smogomierz)_
