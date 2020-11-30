<template>
	<view>
		<u-sticky>
			<u-tabs :list="list" :is-scroll="false" :bold="true" :fontSize="32" :duration="0.3" :current="current" @change="change">
			</u-tabs>
		</u-sticky>

		<!--看电视start-->
		<view v-show="current === 0">
			<tv-list></tv-list>
		</view>
		<!--看电视end-->

		<!--听广播start-->
		<view v-show="current === 1">
		</view>
		<!--听广播end-->

		<!--读报纸start-->
		<view v-show="current === 2">
			<!-- <lab name="读报纸"></lab>
			<view class="zbWrapper" @click="openWebview()">
				<image class="zbIcon" src="../../static/circle.png"></image>
				<view class="module_name">安吉新闻
				</view>
			</view> -->
		</view>
		<!--读报纸end-->
		<!--听广播star-->
         <radioindex refs="radioindex" v-show="current === 1"></radioindex>
		<!--听广播end-->
	</view>
</template>

<script>
	import tvList from '../../components/tv-list.vue'
	import lab from '../../components/lab.vue'
	import radioindex from '../../components/radioindex.vue'
	export default {
		components: {
			lab,
			radioindex,
			tvList
		},
		data() {
			return {
				/*头部tab*/
				list: [{
					name: '看电视'
				}, {
					name: '听广播'
				}, {
					name: '读报纸'
				}],
				current: 0,
				/*头部tab*/

				//看电视
				liveData: [],
				ondemandData: [],
				//看电视
			};
		},
		onShow() {},
		onLoad() {
			this.get_read_newspapers_url();
		//	this.get_video_live_category();
		//	this.get_video_ondemand_category();
		},
		methods: {
			//头部tab回调
			change: function(index) {
				if(index != 2) {
					this.current = index;
				}
				switch (index) {
					case 0: //看电视
						this.liveData = [];
						this.get_video_live_category();
						this.get_video_ondemand_category();
						break;
					case 1: //听广播
						break;
					case 2: //读报纸
						this.openWebview(this.newspapers_url);
						break;
				}
			},
			get_read_newspapers_url: function() {
				var that = this;
				var url = '/video/get_read_newspapers_url.php';
				var data = {
					
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.newspapers_url = res.data.data;
				});
			}
		}
	}
</script>

<style scoped>
</style>
