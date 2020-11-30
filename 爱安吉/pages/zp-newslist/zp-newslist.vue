<template>
	<view class="container">
		<view class="all-news-box">
		
			<view class="news-list-box" v-for="(item,index) in news" @click="open_news_detail(item.article_id)">
				<image :src="item.thumb" class="news-list-img"></image>
				<text class="news-list-title">{{item.title}}</text>
				<text class="news-list-top" v-if="item.is_top==1">置顶</text>
				<text class="news-list-block" v-else></text>
				<text class="news-list-date">{{item.create_time}}</text>
			</view>
		</view>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	import MD5 from '../../common/MD5.js'
	export default{
		components: {
			uniLoadMore
		},
		data(){
			return{
				last_id: false,
					reload: false,
					status: 'more',
					news: [],  //新闻
					contentText: {
						contentdown: '上拉加载更多',
						contentrefresh: '加载中',
						contentnomore: '没有更多内容了'
					},
					page: 1,
					recs: 10,
					classid:'',
			}
		},
				onShow() {
				},
				onLoad(options) {
					this.classid = options.classid
					console.log(this.classid)
					uni.setNavigationBarTitle({
					　　title: options.pagetitle
					})
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
		methods:{
			getlist: function() {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/ajzp/articlelist.php';
				var timestamp = Date.parse(new Date())/1000;
				var s = timestamp+"32dd3c0eb6340a932a990e5832a0d2cf";
				var signature = MD5(s);
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						// user_id: uni.getStorageSync("user_id"),
						// version: this.version,
						// longitude: uni.getStorageSync("longitude"),
						// latitude: uni.getStorageSync("latitude"),
						page: that.page,
						recs: that.recs,
						class:that.classid,
						timestamp: timestamp,
						sign: signature,
						
					},
					success: (res) => {
						var news = eval('(' + res.data + ')').data;
						// that.data = list;
						// console.log(that.data)
						// var news = res.data.data;
						
						for(var i=0; i<news.length; i++) {
							that.news.push(news[i]);
						}
						if(that.reload) {
							uni.stopPullDownRefresh();
						}
						that.last_id = true;
						that.reload = false;
						if(news.length < that.recs) {
							that.status = '';
						}
						
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
				
			},
			open_news_detail:function(a){
				uni.navigateTo({
					url: '../zp-newsdetail/zp-newsdetail?article_id=' + a
				})
			},
		}
	}
</script>

<style>
	.all-news-box {
		width: 92%;
		/* height: 100rpx; */
		margin: 14rpx auto;
		margin-top: 16rpx;
	}
	.news-list-box {
		position: relative;
		margin-top: 10rpx;
		margin-bottom: 4rpx;
		border-bottom: 2rpx solid #e2e2e2;
		padding: 10rpx 0;
	}
	.news-list-img {
		height: 130rpx;
		width: 233rpx;
	}
	.news-list-title{
		position: absolute;
		width: 440rpx;
		left: 250rpx;
		font-size:24rpx ;
		-webkit-line-clamp: 2;
		/* display: -webkit-box; */
		overflow: hidden;
		text-overflow: ellipsis;
		-webkit-box-orient: vertical;
	}
	.news-list-top{
		/* position: absolute; */
		/* bottom: 0; */
		margin-left: 170rpx;
		color: #D92323;
		font-size: 20rpx;
		border: 1rpx solid #D92323;
		border-radius: 6rpx;
		/* right: 220rpx; */
	}
	.news-list-block{
		margin-left: 212rpx;
		
	}
	.news-list-date {
		/* position: absolute; */
		/* bottom: 0; */
		font-size: 20rpx;
		margin-left: 10rpx;
		/* right:0rpx; */
		color: #adadad;
	}
</style>
