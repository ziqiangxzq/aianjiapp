<template>
	<view class="container">
		<view class="list-box" v-for="(item,index) in news" @click="gotodetail(item.contentid,item.title)">
			<view class="img-box">
				<image src="../../static/television/news_vedio.png" class="tv-img"></image>
			</view>
			<text class="tv-name-text" v-html="item.title"></text>
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
					recs: 15,
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.pagetitle
			})
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
				var url = that.globalUrl + '/dianbo/get_video_lists.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						page_no: that.page,
						recs: that.recs,
						catid:that.category_id,
						
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
		gotodetail:function(a,b){
			var d = encodeURIComponent(this.removeHTMLTag(b))  
			var that = this
			uni.navigateTo({
				url:'../television-detail/television-detail?contentid='+a+'&pagetitle='+d
			})
		},
		         removeHTMLTag:function(str) {
		            str = str.replace(/<\/?[^>]*>/g,''); //去除HTML tag
		            str = str.replace(/[ | ]*\n/g,'\n'); //去除行尾空白
		            //str = str.replace(/\n[\s| | ]*\r/g,'\n'); //去除多余空行
		            str=str.replace(/&nbsp;/ig,'');//去掉&nbsp;
		            return str;
		        }

		}
	}
</script>

<style>
	.container {
	}
	.list-box{
		display: flex;
		padding: 20rpx;
		border-bottom: 2rpx solid #e5e5e5 ;
	}
	.tv-img{
		width: 50rpx;
		height: 50rpx;
		margin-top: 16rpx;
	}
	.tv-name-text{
		color: #838383;
		margin-left: 20rpx;
		line-height: 80rpx;
	}
	.phone-num-text{
		position: absolute;
		right: 20rpx;
		line-height: 80rpx;
		color: #838383;
		font-size: 30rpx;
	}
</style>
