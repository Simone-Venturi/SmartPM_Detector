// configuration and utilities for Firebase / Firestore

import firebase from 'firebase/app'
import 'firebase/firestore'

// db firebase
export const db = firebase
  .initializeApp({
                  apiKey: "AIzaSyAkKHJdaW3KDwcPMsRbFG7kFxRtaWKizpY",
                  authDomain: "smart-city-dd9e8.firebaseapp.com",
                  databaseURL: "https://smart-city-dd9e8.firebaseio.com",
                  projectId: "smart-city-dd9e8",
                  storageBucket: "smart-city-dd9e8.appspot.com",
                  messagingSenderId: "143567068370",
                  appId: "1:143567068370:web:d19770b2a274f91b89e10b",
                  measurementId: "G-VM5X6TYNTM"
                 })
  .firestore()

const { Timestamp, GeoPoint } = firebase.firestore
export { Timestamp, GeoPoint }

// from Firestore doc to item for Chart
export function getData2Visualize(samples, data2visualize, color){
    let dataFromFirebase = {
      'PM10': [],
      'timestamp': [],
      'PM2.5' :[],
      'humidity': [],
      'temperature':[],
      'ppmv10': [],
      'ppmv2.5':[]
    }
    samples.forEach(function(sample){
         dataFromFirebase['PM10'].push(sample['concentrationPM10'])
         dataFromFirebase['timestamp'].push(timeConverter(sample['timestamp']))
         dataFromFirebase['PM2.5'].push(sample['concentrationPM25'])
         dataFromFirebase['temperature'].push(sample['temperature'])
         dataFromFirebase['humidity'].push(sample['humidity'])
         dataFromFirebase['ppmv10'].push(sample['ppmv10'])
         dataFromFirebase['ppmv2.5'].push(sample['ppmv25'])
    })

    let data = {
                 labels: dataFromFirebase['timestamp'],
                 datasets: [{
                               label: data2visualize,
                               backgroundColor: color,
                               data: dataFromFirebase[data2visualize]
                }]
    };
    return data;
}


function timeConverter(UNIX_timestamp){

  // from UNIX_timestamp to Date in format hh:mm:ss dd-MM-yyyy
  var date = new Date(UNIX_timestamp*1000);
  var year = date.getFullYear();
  var month = date.getMonth()+1;
  var day = date.getDate();
  var hours = date.getHours();
  var minutes = "0" + date.getMinutes();
  var seconds = "0" + date.getSeconds();

  return hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2)+" "+day+'-'+month+'-'+year;
}