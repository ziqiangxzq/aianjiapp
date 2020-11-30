<template>
	<view>
		<news-list :newsListData="commonNewsData"></news-list>
		
		<!--分页start-->
		<u-loadmore :status="status" color="#a8a8a8" />
		<!--分页end-->
	</view>
</template>

<script>
	import newsList from '../../components/news-list.vue'
	export default {
		components: {
			newsList,
		},
		data() {
			return {

				commonNewsData: [],

				/*分页start*/
				status: 'loading',
				page: 1,
				recs: 20,
				/*分页end*/
				
				news_category_id: 0,
			};
		},
		onShow() {},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.news_category_id = options.news_category_id;
			this.getNews();
		},
		//分页start
		onPullDownRefresh() {
			this.resetNewsList();

			this.getNews();
		},
		onReachBottom() {
			this.page++;
			this.getNews();
		},
		//分页end
		onPageScroll(e) {
			this.scrollTop = e.scrollTop;
		},
		methods: {
			/*重置新闻列表(用于刷新和切换类别)start*/
			resetNewsList: function() {
				this.page = 1;
				this.status = "loading";
				this.commonNewsData = [];
			},
			/*重置新闻列表(用于刷新和切换类别)end*/

			getNews: function() {
				var that = this;
				var url = '/news/getNews';
				var data = {
					news_category_id: that.news_category_id,
					page: that.page,
					recs: that.recs
				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					for (var i = 0; i < res.data.data.length; i++) {
						that.commonNewsData.push(res.data.data[i]);
					}

					if (res.data.data.length < that.recs) {
						that.status = "nomore";
					}
				}, "globalUrlNew");
				
				if (that.page == 1) {
					uni.stopPullDownRefresh();
				}
			},
		}
	}
</script>

<style scoped>
</style>
