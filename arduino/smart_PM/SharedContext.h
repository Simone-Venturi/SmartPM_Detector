#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

#include <inttypes.h>

class SharedContext {
  public:
    SharedContext();
    bool isGPSValid();
    void setValidGPS();
    bool isGPSStopped();
    void stopGPS();
    long getConcentrationPM25();
    void setConcentrationPM25(long value);
    float getPpmv25();
    void setPpmv25(float value);
    long getConcentrationPM10();
    void setConcentrationPM10(long value);
    float getPpmv10();
    void setPpmv10(float value);
    float getTemperature();
    void setTemperature(float value);
    float getHumidity();
    void setHumidity(float value);
    double getLat();
    double getLng();
    double getAltitude();
    void setPosition(double lat, double lng, double altitude);
    char* getTimestamp();
    void setTimeStamp(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond);
    void setTimeStamp(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);

  private:
    volatile bool validGPS = false;
    volatile bool stopped = false;
    volatile long concentrationPM25 = 0;
    volatile float ppmv25 = 0;
    volatile long concentrationPM10 = 0;
    volatile float ppmv10 = 0;
    volatile float temperature = 0;
    volatile float humidity = 0;
    volatile struct gpsPos{
      double lat;
      double lng;
      double altitude;
    } gpsPosition;
    char timestamp[20];
};


#endif
