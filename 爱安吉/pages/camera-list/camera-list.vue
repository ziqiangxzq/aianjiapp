<template>
	<view class="container">
		<camera-list :listdata="news"></camera-list>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import cameraList from '../../components/camera-list.vue'
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		components: {
			uniLoadMore,
			cameraList
		},
		data() {
			return {
				category_id:'',//列表类型ID
				
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
				recs: 16,
			}
		},
		onLoad(options) {
			this.category_id = options.category_id
			uni.setNavigationBarTitle({
				title: options.pagetitle
			});
			this.getlist();
			console.log(options)
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
				var url = that.globalUrl + '/kananji/get_camerainfo_by_camera_category.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						category_id:that.category_id,
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
						console.log(that.news)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
	
			},
		}
	}
</script>

<style>
	.container{
	}
</style>
