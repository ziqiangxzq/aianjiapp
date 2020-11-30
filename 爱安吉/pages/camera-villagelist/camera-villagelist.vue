<template>
	<view class="container" :style="'height:'+ screenHeight +'px !important;'">
		<view class="mode-box" v-for="item in news" @click="gotovillageinfo(item.regionName,item.regionId)"> 
			<image :src="item.pic" class="village-img"></image>
			<view class="mode-text">{{item.regionName}}</view>
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
				controlUnitId:'',//列表类型ID
				
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
				recs: 30,
			}
		},
		onLoad(options) {
			this.screenHeight = uni.getSystemInfoSync().windowHeight;
			uni.setNavigationBarTitle({
				title: options.pagetitle
			});
			this.controlUnitId = options.controlUnitId
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
				var url = that.globalUrl + '/kananji/get_regioninfo_by_controlUnitId_list.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						controlUnitId:that.controlUnitId,
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
			gotovillageinfo:function(a,b){
				uni.navigateTo({
					url:'../camera-villageinfo/camera-villageinfo?pagetitle='+a +'&regionId='+b
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
		/* position: fixed; */
		display:inline-block;
		padding: 20rpx;
		width: 33.3%;
		top: 0rpx;
		text-align: center;
	}
	.village-img{
		width: 100%;
		height: 150rpx;
	}
	.mode-text{
		font-size: 28rpx;
		font-weight: 600;
	}
</style>
