import Vue from 'vue'
import App from './App.vue'
import router from './router'
import VueCtkDateTimePicker from 'vue-ctk-date-time-picker';
import { BootstrapVue, IconsPlugin } from 'bootstrap-vue'
import 'firebase/firestore'
//import firestorePlugin from 'vuefire'
import * as VueGoogleMaps from 'vue2-google-maps'

import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'
import 'semantic-ui-css/semantic.css';
import 'vue-ctk-date-time-picker/dist/vue-ctk-date-time-picker.css';

Vue.component('VueCtkDateTimePicker', VueCtkDateTimePicker);
Vue.use(BootstrapVue)
Vue.use(IconsPlugin)
Vue.use(VueGoogleMaps, {
  load: {
    key: 'AIzaSyAoSVBulHHUW8HUMQsa10WMHqkXsNjcouY',
    libraries: 'places',
  },
})

new Vue({
  //firestorePlugin,
  router,
  render: h => h(App),
}).$mount('#app')
