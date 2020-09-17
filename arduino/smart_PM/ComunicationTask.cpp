#include "ComunicationTask.h"
#include "config.h"

String content;

ComunicationTask::ComunicationTask(SharedContext *pContext) {
  this->pContext = pContext;
}

void ComunicationTask::init(long period) {
  Task::init(period);
  state = IDLE;
  start_time = millis();
}

void ComunicationTask::tick() {
  switch (state) {
    case IDLE:
      if ((millis() - start_time) >= TIME_MS_FOR_START_COMUNICATION) {
        state = SEND_POSITION;
      }
      break;    
    case SEND_POSITION:
      content= "";
      //send device position      
      if (pContext->isGPSValid()) {
        Serial.print("P,");
        Serial.print(pContext->getLat());
        Serial.print(",");
        Serial.print(pContext->getLng());
        Serial.print(",");
        Serial.print(pContext->getAltitude());
        Serial.print("\n");
        state = READING;
      }
      break;
    case READING:
      content = "";
      if(Serial.available()){
        while(Serial.available()){        
          char ch = (char) Serial.read();
          if (ch == '\n'){
            if(content == "F"){
               state = SEND_POSITION;
            } else if(content == "S"){
               state = SEND_DATA;
               pContext->stopGPS();
            }
          } else {
            content += ch;   
          }
        }
      } else {        
        state = SEND_POSITION;
      }
      break;
    case SEND_DATA:
      Serial.print("D,");
      char* timestamp;
      timestamp = pContext->getTimestamp();
      for (int i = 0; i < 20; i++) {
        Serial.print(timestamp[i]);
      }
      Serial.print(",");
      Serial.print(pContext->getTemperature());
      Serial.print(",");
      Serial.print(pContext->getHumidity());
      Serial.print(",");
      Serial.print(pContext->getConcentrationPM25());
      Serial.print(",");
      Serial.print(pContext->getPpmv25());
      Serial.print(",");
      Serial.print(pContext->getConcentrationPM10());
      Serial.print(",");
      Serial.print(pContext->getPpmv10());
      Serial.print("\n");
      break;
  }
}
