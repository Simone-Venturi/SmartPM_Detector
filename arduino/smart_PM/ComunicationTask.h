#ifndef __COMUNICATIONTASK__
#define __COMUNICATIONTASK__

#include "Task.h"
#include "SharedContext.h"
#include "Arduino.h"


class ComunicationTask: public Task {

  public:
    ComunicationTask(SharedContext* pContext);
    void init(long period);
    void tick();

  private:
    unsigned long start_time;
    enum {IDLE, SEND_POSITION, READING, SEND_DATA} state;
    SharedContext* pContext;
};



#endif
