<template>
	<view>
		<news-list :newsListData="newsData"></news-list>
		<u-loadmore :status="status" color="#a8a8a8" />
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
				newsData: [],

				/*分页start*/
				status: 'more',
				page: 1,
				/*分页end*/
			}
		},
		onLoad: function() {
			this.getNewsRecommend('more_news', 'service', 2);
		},
		onPullDownRefresh() {
			this.page = 1;
			this.newsData = [];
			console.log("this.page="+this.page)
			this.getNewsRecommend('more_news', 'service', 2);
		},
		onReachBottom() {
			console.log("onReachBottom")
			this.status = 'loading';
			this.page++;
			this.getNewsRecommend('more_news', 'service', 2);
		},
		methods: {
			getNewsRecommend: function(froms, type, category) {
				var that = this;
				
				var url = '/news/get_news_recommend.php';
				var data = {
					from: froms,
					type: type,
					recs: 10,
					category: category,
					page: that.page,
				}
				
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					
					for (var i = 0; i < res.data.length; i++) {
						that.newsData.push(res.data[i]);
					}
					if(that.page) {
						uni.stopPullDownRefresh();
					}
					
					if(res.data.length < 10) {
						that.status = '';
					}
				});
			}
		}
	}
</script>

<style>
</style>
