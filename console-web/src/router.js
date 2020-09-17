// routes of the web application
import Vue from 'vue'
import Router from 'vue-router'
import LineChart from './Views/LineChart.vue'
import StationList from './Views/Home.vue'

Vue.use(Router)

export default new Router({
	routes: [
		{
			// Home
            path: '/',
            name: 'StationList',
            component: StationList
		},
		{
			// Chart View
			path: '/linecharts',
			name: 'LineChart',
			component: LineChart
		}	
	]
})
