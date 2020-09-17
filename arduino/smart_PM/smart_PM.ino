#include "Scheduler.h"
#include "config.h"
#include "SharedContext.h"
#include "PMDetectorTask.h"
#include "GPSTask.h"
#include "ComunicationTask.h"

Scheduler sched;

void setup() {  
  sched.init(5000);
  SharedContext* pContext = new SharedContext();
  Serial.begin(9600);

  PMDetectorTask* pmDetector = new PMDetectorTask(pContext);
  pmDetector->init(15000);
  sched.addTask(pmDetector);

  GPSTask* gps = new GPSTask(pContext);
  gps->init(20000);
  sched.addTask(gps);

  ComunicationTask* comunication = new ComunicationTask(pContext);
  comunication->init(30000);
  sched.addTask(comunication);
}

void loop() {
  sched.schedule();
}
