<template>
	<view class="container">
		<view class="list-box" v-for="(item,index) in news" @click="gotodetail(item)">
			<view class="img-box">
				<image :src="item.pic_uri" class="tv-img"></image>
			</view>
			<text class="tv-name-text" v-html="item.title"></text>
			<text class="person-num-text">{{item.look_people}}人气</text>
		</view>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default{
		components: {
			uniLoadMore
		},
		data(){
			return{
				category_id:'',
				
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
			}
		},
		onLoad(options) {
			this.category_id=options.category_id
			this.getlist()
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
				var url = that.globalUrl + '/wchat/get_wchat_playback_new.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						page: that.page,
						recs: that.recs,
						category_id:that.category_id,
						
					},
					success: (res) => {
						var news = eval('(' + res.data + ')');
						
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
		gotodetail:function(arr){
			var that = this;
			console.log("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
			console.log(arr.jump_url+'?news_id='+arr.chat_id+'&title='+arr.title+'&video_uri='+arr.video_uri+'&pic_uri='+arr.pic_uri2);
			uni.navigateTo({
				url:arr.jump_url+'?news_id='+arr.chat_id+'&title='+arr.title+'&video_uri='+arr.video_uri+'&pic_uri='+arr.pic_uri2
			})
		},


		}
	}
</script>

<style>
	.container {
	}
	.list-box{
		position: relative;
		display: flex;
		padding:  10rpx 20rpx;
		border-bottom: 2rpx solid #e5e5e5 ;
	}
	.tv-img{
		width: 200rpx;
		height: 140rpx;
		margin-top: 16rpx;
	}
	.tv-name-text{
		margin-left: 20rpx;
		margin-top: 10rpx;
		
	}
	.person-num-text{
		position: absolute;
		right: 30rpx;
		color: #a8a8a8;
		font-size: 24rpx;
		bottom: 10rpx;
	}
</style>
