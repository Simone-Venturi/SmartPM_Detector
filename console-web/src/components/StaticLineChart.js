// component for LineChart static with data from Firestore
import { Line} from 'vue-chartjs'
import {db, getData2Visualize} from './../firebase.js'

export default {
  extends: Line,
  props: {
    collection: String,    // type of data
    data: String,          // date of the graph
    starttimestamp: Date,  // start date to filter from 
    endtimestamp: Date     // end date to filter until
  },
  data () {
    return {
      samples: []  // data from Firestore
    }
  },
  mounted() {
    // colors for the data
    let colors = {
      "ppmv2.5": '#D3D3D3',
      "ppmv10":'#D3D3D3',
      "PM2.5":'#606060',
      "PM10": '#606060',
      "humidity":'#99ccff',
      "temperature":'#ff0000' 
     }; 
    // get data only once from Firestore
    db.collection(this.collection).where('timestamp', '>=', Math.round(this.starttimestamp.getTime()/1000)).where('timestamp', '<=', Math.round( this.endtimestamp.getTime()/1000)).orderBy("timestamp").get()
    .then(snapshot => {
      snapshot.forEach(doc => {
                let item = doc.data()
                item.id = doc.id
                this.samples.push(item)})
      // show only 15 samples
      if(this.samples.length > 15){
        let sampledsamples = []
        var samplingstep = Math.round(this.samples.length / 15)
        for(let i=0; i<this.samples.length; i+=samplingstep){
          sampledsamples.push(this.samples[i])}
        this.samples = sampledsamples
      }
      this.renderChart(getData2Visualize(this.samples, this.data, colors[this.data]), this.options)
  })}
}
