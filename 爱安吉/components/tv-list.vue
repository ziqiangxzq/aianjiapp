<template>
	<view>
		<lab v-if="liveData != ''" name="正在直播"></lab>
		
		<u-grid :col="3" :border="false">
			<u-grid-item v-for="(arr, i) in liveData" :key="i" @click="openLiveDetail(arr)">
				<u-image :src="arr.pic" shape="circle" :lazy-load="true" width="120rpx" height="120rpx">
				</u-image>
				<view class="module_name" v-html="arr.category_name">
				</view>
			</u-grid-item>
		</u-grid>
		
		<lab v-if="ondemandData != ''" name="点播"></lab>
		<u-grid :col="2" :border="false">
			<u-grid-item v-for="(arr, i) in ondemandData" :key="i" @click="openOndemandDetail(arr)">
				<u-image :src="arr.pic" :lazy-load="true" width="90%" height="192rpx" border-radius="4rpx">
				</u-image>
				<view class="module_name" v-html="arr.category_name">
				</view>
			</u-grid-item>
		</u-grid>
	</view>
</template>

<script>
	import lab from './lab.vue'
	export default {
		components: {
			lab
		},
	    data() {
	        return {
				liveData: [],
				ondemandData: [],
	        }
	    },
		created: function() {
			this.liveData = [];
			this.get_video_live_category();
			this.get_video_ondemand_category();
		},
		methods: {
			/*看电视start*/
			//获取电视直播数据
			get_video_live_category: function() {
				var that = this;
				var url = '/video/get_video_live_category.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					for (var i = 0; i < res.data.length - 1; i++) {
						that.liveData.push(res.data[i]);
					}
				});
			},
			//获取电视点播数据
			get_video_ondemand_category: function() {
				var that = this;
				var url = '/video/get_video_ondemand_category.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.ondemandData = res.data;
				});
			},
			/*看电视end*/
			openLiveDetail: function(arr) {
				uni.navigateTo({
					url: '../../pages/webview/webview?url='+arr.jump_url2
				})
			},
			openOndemandDetail: function(arr) {
				var d = encodeURIComponent(arr.category_name)				uni.navigateTo({					url: '../../pages/television-list/television-list?category_id='+arr.category_id+'&pagetitle='+d,				})
			}
		}
	}
</script>

<style>
	.module_name {
		font-size: 28rpx;
		letter-spacing: 1.2rpx;
		color: #1b1b1b;
	}
	
	.zbIcon {
		width: 120rpx;
		height: 120rpx;
	}
	
	.dbIcon {
		width: 90%;
		height: 192rpx;
		border-radius: 4rpx;
	}
</style>
