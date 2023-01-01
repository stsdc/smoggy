# Smoggy
_Firmware for ESP32 to measure weather condition and air quality_


* Support ESP32
* Support BME280
* Support PMS7003
* Battery voltage measurement
* Sending to Sensors.Community (Luftdaten) (every 2min)
* Sending to aqi.eco (every 2min)
* DeepSleep by default
* Press *boot* button to wake up and disable DeepSleep until next reset
* Settings page:
   - Show ID
   - Save aqi.eco  unique path 
 * Prepare to add Firebase support
   - Dummy data sending works; needs a method to accept real data

_Inspired by [Smogomierz](https://github.com/hackerspace-silesia/Smogomierz)_
