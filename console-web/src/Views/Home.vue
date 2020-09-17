<template>
  <div>
    <b-card img-alt="Image" img-top tag="article"
      style="background-color:#f7f7e4; max-width: 100rem; margin:  20px auto;" class="mb-2">
      <b-container class="bv-example-row">
        <h3 style="color: #606060;">Choose the station <small> - select from dropdown or click on the map</small></h3>
        <b-row>
         <b-col>
         <!-- Stations Dropdown -->
         <b-dropdown id="dropdown-1" text="Select the station" class="m-md-2" >
          <b-dropdown-item v-on:click="linechart(station.name)" v-for="station in stations" :key="station.name">{{station.name}}</b-dropdown-item>
         </b-dropdown>
         </b-col>
        </b-row>
      </b-container>
      
      <!-- Stations map -->
      <div id="map">
        <GmapMap 
          ref="mapRef"
          :center="{lat: this.stations[0].latitude, lng: this.stations[0].longitude}"
          :zoom="16"
          :options="{zoomControl: true, mapTypeControl: false, scaleControl: false, streetViewControl: true, rotateControl: false, fullscreenControl: true, disableDefaultUi: false}"
          map-type-id="roadmap"
          style="width: 100%; height: 500px"
        >
        <GmapMarker
              :key="index"
              v-for="(m, index) in this.markers"
              :position="m.position"
              :clickable="true"
              :draggable="true"
              @click="linechart(m.name)"
        />
        </GmapMap>
      </div>   
    </b-card>
  </div>
</template>

<script>
import {db} from './../firebase.js'
export default {
    components: {},
    data() {
      return {
          stations:[{latitude:0, longitude:0}],    // list of the stations
          markers: [],    // list of markers in the map
          name: "",       // name of the element    
        }
    },
    // get data from Firestore
    created(){
        db.collection("stations").onSnapshot(ref => {
        ref.docChanges().forEach(change => {
          const { newIndex, oldIndex, doc, type } = change
          if (type === 'added') {
            this.stations.splice(newIndex, 0, doc.data())
          } else if (type === 'modified') {
            this.stations.splice(oldIndex, 1)
            this.stations.splice(newIndex, 0, doc.data())
          } else if (type === 'removed') {
            this.stations.splice(oldIndex, 1) 
          }
          this.takeposition()
        })
      })
    },
    methods: {
      // populate map
      takeposition(){
        this.stations.forEach(station => {
          this.markers.push({ 'position':{'lat': parseFloat(station.latitude),'lng': parseFloat(station.longitude)},
                              'name': station.name})})
      },
      // method to load correct data in LineChart view
      linechart(station_name){
           this.$router.push({name: "LineChart", params: {name: station_name}})
       }       
    }
  }
</script>

<style>
  .small {
    max-width: 380px;
    margin:  10px auto;
  }
  .m-md-2 .dropdown-menu {
    max-height: 100px;
    overflow-y: auto;
  }
</style>
