# SmartPM_Detector

## Air quality monitoring system 


Project for the Smart City exam, MSc in Engineering and Computer Science at the University of Bologna. 

The object of this project is the realization of a low budget air quality monitoring system, with particular reguard for the sample of the concentration of PM10 and PM2.5.

The project is divided into three folders:
- arduino: code to take data from the sensors and send to Rasperry;
- raspberry: take data form serial port and save in Firestore database;
- console-web: web application realized with Vue to show and analize data.

Technologies: Arduino, Raspberry, Firestore e Vue.

Hardware and sensors: Arduino Uno, Raspberry pi 3, DHT22 (humidity and temperature), DSM501A (PM10, PM2.5), GPS NEO-6M.

In the report called "Relazione Smart City - gruppo 83" is presented the detailed description of architecture and implementation scheme.

## Sistema per il monitoraggio della qualità dell'aria

Progetto sviluppato per l'esame di Smart city e Tecnologie Abilitanti del corso di laurea magistrale in ingegneria e scienze informatiche, Università di Bologna.

La cartella contiene il codice per la realizzazione di un sistema di monitoraggio dell'aria a basso costo, in particolare per il rilevamento della concentrazione di PM nell'aria.

Il codice si suddivide in tre componenti principali:
- arduino: programma per raccogliere dati dai sensori DHT22 (umidità e temperatura), DSM501A (sensore ottico di rilevamento polveri) e GPS NEO-6M (sensore GPS).
- raspberry: programma per ricevere i dati dall'arduino e inviarli al database Firestore di Firebase;
- console-web: esempio di interfaccia grafica per l'analisi dei dati raccolti.

Tecnologie: Arduino, Raspberry, Firestore e Vue.

Hardware e sensori: Arduino Uno, Raspberry pi 3, DHT22 (humidity and temperature), DSM501A (PM10, PM2.5), GPS NEO-6M.

La descrizione dettagliata del progetto e lo schema dei componenti hardware è presente nel pdf .

