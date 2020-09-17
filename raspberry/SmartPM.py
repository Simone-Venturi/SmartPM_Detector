# -*- coding: utf-8 -*-
"""
Created on Wed Jun  3 14:51:50 2020

@author: ventu
"""

#!/usr/bin/env python

import time
import serial
import numpy as np
import datetime

import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

from collections import deque

# Use a service account
cred = credentials.Certificate('/home/pi/Desktop/SmartPM/smart-city-dd9e8-firebase-adminsdk-soozc-dffb6c7d98.json')
firebase_admin.initialize_app(cred)

db = firestore.client()

name = "StationEmilia-Romagna"+ str(np.random.randint(10000))
print("Station name: "+name)
last_valid_temperature = 1
records = deque()
n = 0
#reading from specified port ttyACM0 or ttyUSB0 every 30seconds  
with serial.Serial('/dev/ttyACM0', 9600, timeout=30) as ser:    
    while 1:                
       message=ser.readline()
       stringMessage = message.decode("utf-8")
       print(stringMessage)
       values = stringMessage.split(",")
       #checking message:
       #   P,latitude,longitude,altitude, name
       #   D,concentrationPM25,ppmv25,concentrationPM10,ppmv10,humidity,temperature,timestamp
       if(values[0]=="P"):
           try:
               data = {"latitude": float(values[1]),"longitude": float(values[2]),"altitude": float(values[3]), "name": name}
               db.collection(u'stations').add(data)
               ser.write(str.encode('S\n'))
           except:
               ser.write(str.encode('F\n'))
       elif (values[0]=="D"):
           #check timespamp, GPS could not receive correct values
           try:
               d = datetime.datetime.strptime(values[1][:-1], "%d/%m/%Y %H:%M:%S")
               now =  datetime.datetime.today()
               if(d.year == now.year):
                   seconds = time.mktime(d.timetuple())
               else:
                   seconds = time.time()
           except ValueError:
               seconds = time.time()
           #check temperature
           if(values[2]!="nan"):
               last_valid_temperature = float(values[2])    
           #check ppmv2.5
           if(values[5]=="nan"):
               ppmv25 = float((int(values[4])* 0.0283168 / 100 /1000) *  (0.08205 * last_valid_temperature) / 0.01)
           else:
               ppmv25 = float(values[5])
           #check ppmv1.0    
           if(values[7]=="nan"):
               ppmv10 = float((int(values[6])* 0.0283168 / 100 /1000) *  (0.08205 * last_valid_temperature) / 0.01)
           else:
               ppmv10 = float(values[7])
           #create record to add to Firestore        
           data = {"concentrationPM25": int(values[4]),"ppmv25": ppmv25,
                   "concentrationPM10": int(values[6]),"ppmv10": ppmv10,
                   "humidity": float(values[3]), "temperature": float(values[2]), "timestamp": float(seconds)}
           records.append(data)
           for i in range (0,len(records)):
               elem = records.popleft()
               try:
                   db.collection(name).document(str(n)).set(elem)
                   n = n+1
               except:
                   records.append(elem)                   
