#ifndef __PMDETECTORTASK__
#define __PMDETECTORTASK__

#include "Arduino.h"
#include "SharedContext.h"
#include "Task.h"

class PMDetectorTask: public Task {
  public:
    PMDetectorTask(SharedContext *pContext);
    void init(long period);
    void tick();
  private:
    SharedContext* pContext;
    unsigned long start_time;
    float concentration;
    float ratio;
    uint32_t duration;
    uint32_t starttime;
    uint32_t endtime;
    uint32_t sampletime_ms;
    uint32_t lowpulseoccupancy;
    enum {IDLE, SCANNING_25, SCANNING_10} state;
    long getPM(int DUST_SENSOR_DIGITAL_PIN);
};
#endif
