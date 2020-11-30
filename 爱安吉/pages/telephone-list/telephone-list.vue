<template>
	<view class="container" :style="'height:'+ screenHeight +'px !important;'">
		<view class="list-box" v-for="(item,index) in news" :class=" index % 2 ==0 ? 'list-grey' : 'list-white'" @click="callphone(item.phone_num)">
			<view class="img-box">
				<image src="../../static/telephone/phone.png" class="phone-img"></image>
			</view>
			<text class="phone-name-text">{{item.phone_name}}</text>
			<text class="phone-num-text">{{item.phone_num}}</text>
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
			this.screenHeight = uni.getSystemInfoSync().windowHeight;
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
				var url = that.globalUrl + '/help/get_help_phone.php';
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
			callphone: function(a) {
					uni.makePhoneCall({
					phoneNumber:a
				})
			},
		}
	}
</script>

<style>
	.list-box{
		display: flex;
		padding: 20rpx;
	}
	.list-grey{
		background-color: #fafafa;
	}
	.list-white {
		background-color: #FFFFFF;
	}
	.img-box{
		width: 80rpx;
		height: 80rpx;
		border-radius: 40rpx;
		background-color: #eeeeee;
		text-align: center;
	}
	.phone-img{
		width: 50rpx;
		height: 50rpx;
		margin-top: 16rpx;
	}
	.phone-name-text{
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
