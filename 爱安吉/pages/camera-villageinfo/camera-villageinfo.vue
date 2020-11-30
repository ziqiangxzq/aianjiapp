<template>
	<view class="container">
		<view class="mode-box" v-for="item in news" @click="openCameraPlay(item.cameraIndexCode,item.type,item.camerName)">
			<image src="../../static/camera/camera.png" class="camera-img"></image>
			<text class="mode-text">{{item.camerName}}</text>
		</view>
		
		
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		components: {
			uniLoadMore,
		},
		data() {
			return {
				regionId:'',//列表类型ID
				
				screenHeight: '',//屏幕高度
				
				last_id: false,
				reload: false,
				status: 'more',
				news: [], //新闻
				contentText: {
					contentdown: '上拉加载更多',
					contentrefresh: '加载中',
					contentnomore: '没有更多内容了'
				},
				page: 1,
				recs: 20,
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.pagetitle
			});
			this.regionId = options.regionId
			this.getlist();
		},
		onPullDownRefresh() {
			this.reload = true;
			this.last_id = false;
			this.news = [];
			this.page = 1;
			this.getlist();
		},
		onReachBottom() {
			this.status = 'more';
			this.getlist();
		},
		methods: {
			getlist: function() {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/kananji/get_camerainfo_by_regionId_list.php?';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						regionId:that.regionId,
						if_community:0,
						page: that.page,
						recs: that.recs,
	
					},
					success: (res) => {
						var news = eval('(' + res.data + ')');
						for (var i = 0; i < news.length; i++) {
							that.news.push(news[i]);
						}
						if (that.reload) {
							uni.stopPullDownRefresh();
						}
						that.last_id = true;
						that.reload = false;
						if (news.length < that.recs) {
							that.status = '';
						}
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
	
			},
			openCameraPlay: function(a,b,c) {
				uni.navigateTo({
					url: '../camera-play/camera-play?cameraIndexCode='+a+'&camera_type='+b+'&pagetitle='+c
				})
			},
		}
	}
</script>

<style>
	.container{
		padding-top: 20rpx;
	}
	.mode-box{
width: 100%;
padding: 20rpx 50rpx;
		border-bottom: 1rpx  solid #ebebeb;
	}
	.camera-img{
		width: 52rpx;
		height: 52rpx;
		top: 10rpx;
	}
	.mode-text{
		height: 81rpx;
		line-height: 81rpx;
		margin-left: 20rpx;
		font-size: 28rpx;
		font-weight: 600;
	}
</style>
