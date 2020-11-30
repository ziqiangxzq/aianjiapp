<template>
	<view>
		<view>
			<news-list :newsListData="data"></news-list>
		</view>
		<u-loadmore :status="status" :load-text="loadText" color="#a8a8a8" />
	</view>
</template>

<script>
	import newsList from '../../components/news-list.vue'

	export default {
		components: {
			newsList
		},
		data() {
			return {
				data: [],

				search: '',

				/*分页start*/
				status: 'loadmore',
				loadText: {
					loadmore: '请输入关键字搜索',
					loading: '努力加载中',
					nomore: '没有搜索到内容'
				},
				page: 1,
				recs: 7,
				/*分页end*/
			};
		},
		onLoad() {},
		onPullDownRefresh() {
			this.reload = true;
			this.last_id = false;
			this.data = [];
			this.page = 1;

			this.search_news_list();
		},
		onReachBottom() {
			this.page++;
			this.loadText.loadmore = "上拉加载更多";
			
			this.search_news_list();
		},
		methods: {
			search_news_list: function() { //获取新闻
				var that = this;
				var url = '/news/search_news_list.php';
				var data = {
					page: that.page,
					recs: that.recs,
					search: that.search,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					for (var i = 0; i < res.data.length; i++) {
						that.data.push(res.data[i]);
					}
					
					if(res.data.length < that.recs) {
						that.status = "nomore";
					}
					
				});
			},
			onNavigationBarSearchInputConfirmed(e) {
				this.reload = true;
				this.last_id = false;
				this.data = [];
				this.page = 1;

				this.search = e.text;
				this.search_news_list();
			},
		}
	}
</script>

<style>
	.tower-swiper .tower-item {
		transform: scale(calc(0.5 + var(--index) / 10));
		margin-left: calc(var(--left) * 100upx - 150upx);
		z-index: var(--index);
	}
</style>
