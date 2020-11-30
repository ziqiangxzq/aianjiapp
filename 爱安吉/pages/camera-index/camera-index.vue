<template>
	<view>
		<adv :category_id="5"></adv>
	
				<view class="wrapper"  v-for="item in mid_data" @click="gotolist(item.category_id,item.category_name)">
					<image class="icon" :src="item.category_pics"></image>
					<view class="module_name" v-html="item.category_name">
					</view>
				
			</view>
        <lab name="推荐视频" more="更多" fun="gotomore" @gotomore="gotomore"></lab>
		<camera-list :listdata="news"></camera-list>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import adv from '../../components/adv.vue'
	import lab from '../../components/lab.vue'
	import cameraList from '../../components/camera-list.vue'
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		components: {
			lab,
			uniLoadMore,
			cameraList,
			adv
		},
		data() {
			return {
				mid_data: [],
				
				swiperNewsData: [{
					pic_uri: '../../static/bg.jpg'
				}],
				autoplay: true,
				mode: "round",
				
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
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.get_mid_nav();
			this.getlist();
			// this.tabToggle_0();
			// this.get_real_weather();
		},
		onShow() {},
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
			get_mid_nav: function() { //获取中间模块
				var that = this;
				var url = that.globalUrl + '/kananji/get_camera_category.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						that.mid_data = data;
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
			},
			getlist: function() {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/kananji/get_camerainfo_top.php';
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

					},
					success: (res) => {
						var news = eval('(' + res.data + ')').data;
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
						console.log(that.news)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});

			},
			gotolist:function(a,b){
				uni.navigateTo({
					url:'../camera-list/camera-list?category_id='+a+'&pagetitle='+b
				})
			},
			gotomore:function(){
				uni.navigateTo({
					url:'../camera-more/camera-more'
				})
			},
			
		}
	}
</script>

<style scoped>
	.wrapper {
		display:inline-block;
		width: 25%;
		margin: 24upx auto;
		text-align: center;
	}
	
	.icon {
		width: 68rpx;
		height: 68rpx;
	}
	
	.module_name {
		font-size: 24rpx;
		letter-spacing: 1.2rpx;
		margin-top: 10rpx;
		color: #868686;
		text-overflow:ellipsis;
		white-space:nowrap;
		overflow: hidden;
	}
</style>
