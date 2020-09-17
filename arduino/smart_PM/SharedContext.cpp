#include "SharedContext.h"
#include <stdio.h>

SharedContext::SharedContext() {

}
bool SharedContext::isGPSValid() {
  return validGPS;
}
void SharedContext::setValidGPS() {
  validGPS = true;
}
bool SharedContext::isGPSStopped() {
  return stopped;
}
void SharedContext::stopGPS() {
  stopped = true;
}
long SharedContext::getConcentrationPM25() {
  return concentrationPM25;
}
void SharedContext::setConcentrationPM25(long value) {
  concentrationPM25 = value;
}
float SharedContext::getPpmv25() {
  return ppmv25;
}
void SharedContext::setPpmv25(float value) {
  ppmv25 = value;
}
long SharedContext::getConcentrationPM10() {
  return concentrationPM10;
}
void SharedContext::setConcentrationPM10(long value) {
  concentrationPM10 = value;
}
float SharedContext::getPpmv10() {
  return ppmv10;
}
void SharedContext::setPpmv10(float value) {
  ppmv10 = value;
}
float SharedContext::getTemperature() {
  return temperature;
}
void SharedContext::setTemperature(float value) {
  temperature = value;
}
float SharedContext::getHumidity() {
  return humidity;
}
void SharedContext::setHumidity(float value) {
  humidity = value;
}
double SharedContext::getLat() {
  return gpsPosition.lat;
}
double SharedContext::getLng() {
  return gpsPosition.lng;
}
double SharedContext::getAltitude() {
  return gpsPosition.altitude;
}
void SharedContext::setPosition(double lat, double lng, double altitude) {
  gpsPosition.lat = lat;
  gpsPosition.lng = lng;
  gpsPosition.altitude = altitude;
}

char* SharedContext::getTimestamp() {
  return timestamp;
}
void SharedContext::setTimeStamp(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond) {
  snprintf(timestamp, sizeof(timestamp), "%02d-%02d-%4d %02d:%02d:%02d:%03d", month, day, year, hour, minute, second, centisecond);
}
void SharedContext::setTimeStamp(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
  snprintf(timestamp, sizeof(timestamp), "%02d/%02d/%4d %02d:%02d:%02d", day, month, year, hour, minute, second);
  //snprintf(timestamp, sizeof(timestamp), "%02s/%02s/%4s %02s:%02s:%02s", "07", "06", "2020", "12", "08", "47");
}
