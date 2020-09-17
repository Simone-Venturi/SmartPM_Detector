#include "config.h"
#include <math.h>
#include "PMDetectorTask.h"
#include "DHT.h"

DHT dht(DHTPIN, DHTTYPE);

PMDetectorTask::PMDetectorTask(SharedContext *pContext) {
  this->pContext = pContext;
}

void PMDetectorTask::init(long period) {
  Task::init(period);
  lowpulseoccupancy = 0;
  ratio = 0;
  sampletime_ms = 3 * 1000;
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM10, INPUT);
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM25, INPUT);
  state = IDLE;
  start_time = millis();
  dht.begin();
}

void PMDetectorTask::tick() {
  switch (state) {
    case IDLE:
      if (millis() - start_time >= TIME_MS_FOR_DUST_SENSOR) {
        state = SCANNING_25;
      }
      break;

    case SCANNING_25:
      //get PM 2.5 density of particles over 2.5 µm.
      pContext->setConcentrationPM25(getPM(DUST_SENSOR_DIGITAL_PIN_PM25));
      pContext->setTemperature(dht.readTemperature());
      pContext->setHumidity(dht.readHumidity());
      pContext->setPpmv25((float)(pContext->getConcentrationPM25() * 0.0283168 / 100 /1000) *  (0.08205 * pContext->getTemperature()) / 0.01);
      //change to pause
      state = SCANNING_10;
      break;

    case SCANNING_10:
      //get PM 10 - density of particles over 10 µm.
      pContext->setConcentrationPM10(getPM(DUST_SENSOR_DIGITAL_PIN_PM10));
      pContext->setTemperature(dht.readTemperature());
      pContext->setHumidity(dht.readHumidity());
      pContext->setPpmv10((float)(pContext->getConcentrationPM10() * 0.0283168 / 100 /1000) *  (0.08205 * pContext->getTemperature()) / 0.01);
      //change to pause
      state = SCANNING_25;
      break;
  }
}

long PMDetectorTask::getPM(int DUST_SENSOR_DIGITAL_PIN) {
  starttime = millis();

  while (1) {
    duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();

    if ((endtime - starttime) > sampletime_ms) {
      ratio = (lowpulseoccupancy - endtime + starttime) / (sampletime_ms * 10.0); // Integer percentage 0=>100
      long concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
      lowpulseoccupancy = 0;
      return (concentration);
    }
  }
}
