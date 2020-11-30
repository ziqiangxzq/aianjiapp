<template>
	<view class="container">
		<view class="out-box" v-for="item in news" @click="gotovillagelist(item.controlUnitId,item.controlName)">
			<view class="img-box">
				<image :src="item.pic" class="area-img"></image>
				<view class="area-name">
					{{item.controlName}}
				</view>
			</view>
				<view class="content-box">
					<text v-html="item.content"></text>
				</view>
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
				recs: 10,
			}
		},
		onLoad(options) {
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
				var url = that.globalUrl + '/kananji/get_controlunit_by_parentId_list.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						parentId:1,
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
			gotovillagelist:function(a,b) {
				uni.navigateTo({
					url:'../camera-villagelist/camera-villagelist?controlUnitId='+a+'&pagetitle='+b
				})
			},
		}
	}
</script>

<style>
	.container{
	}

	.out-box{
		width: 100%;
		padding: 20rpx 10rpx 0 10rpx;
		border-bottom: 1rpx  solid #ebebeb;
	}
	.img-box{
		position: relative;
		border-radius: 8rpx;
		width: 97%;
		height: 300rpx;
		margin: 0rpx auto;
	}
	.area-img{
		border-radius: 8rpx;
		width: 100%;
		height: 100%;
	}
	.area-name{
		padding: 10rpx 20rpx;
		position: absolute;
		bottom: 0;
		right: 0;
		color: #FFFFFF;
		font-size: 30rpx;
		background-color: rgba(0,0,0,0.4);
		border-radius: 8rpx;
	}
	.foot-box{
		display: flex;
	}
	.content-box{
		
		width: 100%;
		font-size: 26rpx;
		padding: 16rpx;
	}

</style>
