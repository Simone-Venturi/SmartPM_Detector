<template>
  <div>

    <!-- legend -->
    <b-card title="" img-alt="Image" img-top tag="article" style="background-color:#f7f7e4; max-width: 100rem; margin:  10px auto;" class="mb-2" variant="primary">
      <h3 style="color: #606060;">Legend of the data</h3>
      <b-container class="bv-example-row">
      <b-row>
        <b-col>
        <p style="color: #606060; text-align:left">
<b>PM10:</b> percentage of small particles with an aerodynamic diameter less than or equal to a nominal 10 micrometer.<br>
<b>ppmv10:</b> percentage of PM10 expressed in parts per million per volume.<br>
<b>temperature:</b> value of temperature expressed in Celsius degrees.
</p>
</b-col>
<b-col>
<p style="color: #606060; text-align:left">
<b>PM2.5:</b> percentage of small particles with an aerodynamic diameter less than or equal to a nominal 2.5 micrometer.<br>
<b>ppmv2.5:</b> percentage of PM2.5 expressed in parts per million per volume.<br>
<b>humidity:</b> value of the humidity in the air.<br>
</p>
</b-col>
</b-row>
<b-row>
<b-col>
<p style="color: #606060;"><br>Consult the ranges for this data on the ARPA site: <a href="https://www.inquinamento-italia.com/come-interpretare-i-dati-arpa-su-pm10-e-pm25-forniti-dalle-centraline-di-qualita-aria-soglie-pericolose/#:~:text=5%20previsto%20dalla%20normativa%20italiana,di%20soli%2010%20%CE%BCg%2Fmc">more info</a></p>
</b-col>
      </b-row>
      </b-container>
    </b-card>
    <!-- legend-->

    <!-- graphs -->
    <b-card title="" img-alt="Image" img-top tag="article" style="background-color:#f7f7e4; max-width: 100rem; margin:  10px auto;" class="mb-2" variant="primary">
      <h3 style="color: #606060;">Last data registered on the station - {{this.collection}}</h3>
      <b-container class="bv-example-row">
      <b-row>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#D3D3D3' data="ppmv2.5" class="small"></LineChart></b-col>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#D3D3D3' data="ppmv10" class="small"></LineChart></b-col>  
      </b-row>
      <b-row>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#606060' data="PM2.5" class="small"></LineChart></b-col>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#606060' data="PM10" class="small"></LineChart></b-col>
       </b-row>
      <b-row>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#99ccff' data="humidity" class="small"></LineChart></b-col>
        <b-col><LineChart :key=this.collection :chart-data = this.datacollections :collection = this.collection color='#ff0000' data="temperature" class="small"></LineChart></b-col>
      </b-row>
      </b-container>
    </b-card>
    <!-- end graphs-->

    <!-- filter -->
    <b-card title="" img-alt="Image" img-top tag="article" style="background-color:#f7f7e4; max-width: 100rem; margin: 10px auto;" class="mb-2">
      <b-container class="bv-example-row">
      <h3 style="color: #606060;">Filter data <small> - measurement or time</small></h3>
      <b-row>
       <b-col>
        <form @submit="onsubmit" >
        <div class="clearfix" style="margin:80px"> </div>
        <h4 style="color: #606060;">Select the measurement</h4>
        <b-form-group id="datatype"  label-for="datatype" style="color: #606060;">
        <b-form-select id="datatype" v-model="form.datatype" class="mb-2 mr-sm-2 mb-sm-0"
          :options="['ppmv2.5','ppmv10','PM2.5','PM10','humidity','temperature']" :value="null"  required></b-form-select>
        </b-form-group>

        <h4 style="color: #606060;">Select the time range</h4>
        <b-form-group id="datetime"  label-for="datetime" style="color: black;">
        <date-range-picker
            ref="picker"
            opens="center"
            :locale-data="{ firstDay: 1, format: 'DD-MM-YYYY HH:mm:ss' }"
            :singleDatePicker="false"
            :timePicker="true"
            :timePicker24Hour="true"
            :showWeekNumbers="true"
            :showDropdowns="true"
            :autoApply="true"
            :linkedCalendars="false"
            v-model="form.datetime"
            required>
        <template v-slot:input="picker">
            {{ picker.startDate }}- {{ picker.endDate}}
        </template>
        </date-range-picker>
        </b-form-group>
        <b-button type="submit" >Show data</b-button>
        </form>
       </b-col>
       <b-col>
        <StaticLineChart :key=this.reload :chart-data = this.datacollections :collection = this.collection :data="form.datatype" :starttimestamp = "form.datetime.startDate" :endtimestamp = "form.datetime.endDate" class="small"></StaticLineChart>     
       </b-col>
      </b-row>
      </b-container>
    </b-card> 
    <!-- end filter -->

    <!-- select station -->
    <b-card img-alt="Image" img-top tag="article" style="background-color:#f7f7e4; max-width: 100rem; margin:  10px auto;" class="mb-2">
      <h3 style="color: #606060;">Change the station <small> - select from dropdown or click on the map</small></h3>
      <b-dropdown id="dropdown-1" text="Select the station" class="m-md-2" >
        <b-dropdown-item v-on:click="reloadlinechart(station.name)" v-for="station in stations" :key="station.name">{{station.name}}</b-dropdown-item>
      </b-dropdown>
      <GmapMap 
          ref="mapRef"
          :center="{lat: this.stations[0].latitude, lng: this.stations[0].longitude}"
          :zoom="16"
          :options="{zoomControl: true, mapTypeControl: false, scaleControl: false, streetViewControl: true, rotateControl: false, fullscreenControl: true, disableDefaultUi: false}"
          map-type-id="roadmap"
          style="width: 100%; height: 300px"
      >
      <GmapMarker
          :key="index"
          v-for="(m, index) in this.markers"
          :position="m.position"
          :clickable="true"
          :draggable="true"
          @click="reloadlinechart(m.name)"
      />
      </GmapMap>
    </b-card> 
    <!-- end select station -->
  </div>
</template>

<script>
import DateRangePicker from 'vue2-daterange-picker'
import LineChart from './../components/LineChart'
import StaticLineChart from './../components/StaticLineChart'
import {db} from './../firebase.js'
import 'vue2-daterange-picker/dist/vue2-daterange-picker.css'

export default {
  components: {
    LineChart, 
    StaticLineChart,
    DateRangePicker
  },
  data(){
    return{
      stations:[{latitude:0, longitude:0}],   // list of stations
      markers: [],                            // markers of the stations in the map
      name: "",                                 
      collection : this.$route.params.name,   // type of data to visualize
      datacollections : new Object(),         // default property in Char componente
      selected:null,                          //
      reload: 0,                              // reload page
      form: {datatype: '', datetime: {'startDate' : new Date(),'endDate': new Date()},}  // from initialization
    }
  },
  mounted(){
    // get list of stations from Firestore
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
    // reload chart to visualize specific data when sublit filter
    onsubmit(evt) {
      evt.preventDefault()
      this.reload = this.reload +1;
    },
    // populate the maps with the position of the stations
    takeposition(){
      this.stations.forEach(station => {
      this.markers.push({ 
          'position':{'lat': parseFloat(station.latitude),'lng': parseFloat(station.longitude)},
          'name': station.name})}
    )},
    // reload charts when change the station
    reloadlinechart(stationname){
      this.form =  { datatype: '', datetime: {'startDate' : new Date(),'endDate':new Date()},}
      this.collection = stationname;
    }
  }
}
</script>

<style>
  .small {
    max-width: 600px;
    margin:  10px auto;
  }
  .m-md-2 .dropdown-menu {
    max-height: 100px;
    overflow-y: auto;
  }
</style>