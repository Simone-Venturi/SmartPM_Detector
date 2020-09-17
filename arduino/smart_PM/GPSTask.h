#ifndef __GPSTASK__
#define __GPSTASK__

#include "Arduino.h"
#include "SharedContext.h"
#include "Task.h"

class GPSTask: public Task {
  public:
    GPSTask(SharedContext *pContext);
    void init(long period);
    void tick();
  private:
    SharedContext* pContext;
    enum {SCANNING, SCANNING_DATE} state;
};
#endif
