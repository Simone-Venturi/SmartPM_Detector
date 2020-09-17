#include "config.h"
#include "GPSTask.h"
#include <SoftwareSerial.h>
#include "TinyGPSPlus.h"

TinyGPSPlus* gps;
SoftwareSerial ss(RX_PIN_GPS, TX_PIN_GPS);

GPSTask::GPSTask(SharedContext *pContext) {
  this->pContext = pContext;
  pContext->setPosition(0.0, 0.0, 0.0);
  ss.begin(GPS_BAUD);
}

void GPSTask::init(long period) {
  state = SCANNING;
  Task::init(period);
}

void GPSTask::tick() {
  switch (state) {
    case SCANNING:
      if (pContext->isGPSStopped() == false) {
        if (gps->location.isValid()) {
          pContext->setPosition(gps->location.lat(), gps->location.lng(), gps->altitude.meters());
          pContext->setValidGPS();
        }
        if (gps->date.isValid() && gps->time.isValid()) {
          pContext->setTimeStamp(gps->date.year(), gps->date.month(), gps->date.day(), gps->time.hour(), gps->time.minute(), gps->time.second());
        }
      } else {
        state = SCANNING_DATE;
      }
      break;

    case SCANNING_DATE:
      if (gps->date.isValid() && gps->time.isValid()) {
          pContext->setTimeStamp(gps->date.year(), gps->date.month(), gps->date.day(), gps->time.hour(), gps->time.minute(), gps->time.second());
      }
      break;
  }
}
