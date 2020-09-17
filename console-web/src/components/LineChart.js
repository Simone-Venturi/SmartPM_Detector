// component for realtime graph with data from Firestore
import { Line, mixins } from 'vue-chartjs'
const { reactiveProp } = mixins
import {db, getData2Visualize} from './../firebase.js'

export default {
  extends: Line,
  mixins: [reactiveProp],
  props: {
    collection: String,  // type of data to show
    color: String,       // colore of the line
    data: String         // data to visualize
  },
  data: () => ({ samples: [] }), // data from Firestore
  mounted() {
      db.collection(this.collection).orderBy("timestamp").limitToLast(15).onSnapshot(ref => {
        ref.docChanges().forEach(change => {
          // modify list on data change
          const { newIndex, oldIndex, doc, type } = change
          if (type === 'added') {
            this.samples.splice(newIndex, 0, doc.data())
          } else if (type === 'modified') {
            this.samples.splice(oldIndex, 1)
            this.samples.splice(newIndex, 0, doc.data())
          } else if (type === 'removed') {
            this.samples.splice(oldIndex, 1)
          }
        })
      // chart render
      this.renderChart(getData2Visualize(this.samples, this.data, this.color), this.options)
    })
  }
}
