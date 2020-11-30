<template>
	<view>
		<!--直播start-->
		<view>
			<lab v-if="zbLiveData != ''" name="正在直播"></lab>
			<u-grid :col="2" :border="false">
				<u-grid-item v-for="(arr, i) in zbLiveData" :key="i" @click="openLive(arr);">
					<image class="zbIcon" :src="arr.pic_uri"></image>
					<view class="module_name_live" v-html="arr.title">
					</view>
				</u-grid-item>
			</u-grid>

			<lab name="精选回放" class="clear-both"></lab>
			<view v-for="(arr, i) in zbPlaybackData" :key="i" class="ubb zbPbWrapper" @click="openPlayBackList(arr);">
				<image :src="arr.pic_url" class="zbPbIcon"></image>
				<view class="module_name" v-html="arr.category_name">
				</view>
			</view>
		</view>
		<!--直播end-->
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
				/*直播start*/
				zbLiveData: [],
				zbPlaybackData: [],
				/*直播end*/
	        }
	    },
		created: function() {
			this.refreshLiveList()
		},
		methods: {
			/*直播start*/
			get_wchat_list_new: function() {
				var that = this;
				var url = '/wchat/get_wchat_list_new.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.zbLiveData = res.data;
				});
			},
			get_wchat_category: function() {
				var that = this;
				var url = '/wchat/get_wchat_category.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.zbPlaybackData = res.data;
				});
			},
			openPlayBackList: function(arr) { //打开直播回放列表
				uni.navigateTo({
					url: '../zb-list/zb-list?category_id=' + arr.category_id
				})
			},
			openLive: function(arr) {  //打开直播详情
				uni.navigateTo({
					url: arr.jump_url2
				})
			},
			/*直播end*/
			refreshLiveList: function() {
				this.get_wchat_list_new();
				this.get_wchat_category();
			}
		}
	}
</script>

<style scoped>
	/*直播start*/
	.zbWrapper {
		float: left;
		width: 50%;
		margin: 24upx auto;
		text-align: center;
	}
	
	.zbIcon {
		width: 90%;
		height: 192rpx;
		border-radius: 4rpx;
	}
	
	.zbPbIcon {
		width: 100%;
		height: 320rpx;
		border-radius: 4rpx;
	}
	
	.zbPbWrapper {
		padding: 24rpx 24rpx;
	}

	.module_name_live {
		font-size: 28rpx;
		letter-spacing: 1.2rpx;
		color: #1b1b1b;
		width: 90%;
		height: 112rpx;
	}
	
	.module_name {
		font-size: 28rpx;
		letter-spacing: 1.2rpx;
		color: #1b1b1b;
	}
	/*直播end*/
</style>
