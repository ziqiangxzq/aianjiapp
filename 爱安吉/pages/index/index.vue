<template>
	<view>
		<!--tab切换start-->
		<view>
			<!-- <u-sticky> -->
				<u-tabs :list="list" name="category_name" :is-scroll="true" :bold="true" :fontSize="34" :height="90" :duration="0"
				 :current="current" @change="change"></u-tabs>
			<!-- </u-sticky> -->
		</view>
		<!--tab切换end-->

		<!--轮播新闻start-->
		<u-swiper v-if="swiperNewsData != ''" :list="swiperNewsData" name="hot_pic" height="320" :effect3d="false" :autoplay="autoplay"
		 :mode="mode" @click="handleSwiperNews"></u-swiper>
		<!--轮播新闻end-->

		<!--中间模块start-->
		<u-grid :col="5" :border="false" v-if="current == 0">
			<u-grid-item v-for="(arr, i) in serviceData" :key="i" @click="handleMainModuel(arr);">
				<u-image :src="arr.icon" width="72rpx" height="72rpx" :lazy-load="true"></u-image>
				<view class="item_module_name" v-html="arr.nav_name">
				</view>
			</u-grid-item>
		</u-grid>
		<!--中间模块end-->

		<!--新闻列表start-->
		<news-list :newsListData="commonNewsData"></news-list>
		<!--新闻列表end-->

		<!--分页start-->
		<u-loadmore :status="status" color="#a8a8a8" />
		<!--分页end-->
		<u-back-top :scroll-top="scrollTop" top="100"></u-back-top>
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
				/*新闻类别tab*/
				list: [],
				current: 0,
				bg: {
					'backgroundColor': '#0090ff',
					'margin': '20rpx 10rpx',
					'borderRadius': '8rpx',
				},
				/*新闻类别tab*/

				//新闻列表数组
				commonNewsData: [],

				//轮播新闻
				swiperNewsData: [],
				autoplay: true,
				mode: "round",

				//中间模块
				serviceData: [],

				/*分页start*/
				status: 'loading',
				page: 1,
				recs: 20,
				/*分页end*/
				
				scrollTop: 0
			};
		},
		onShow() {
			this.get_mid_nav();
		},
		onLoad() {
			this.getNewsCategory();
		},
		//分页start
		onPullDownRefresh() {
			this.resetNewsList();

			this.getData();
			this.getHotNews();
		},
		onReachBottom() {
			this.page++;
			this.getData();
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
				this.swiperNewsData = [];
			},
			/*重置新闻列表(用于刷新和切换类别)end*/
			/*头部tab逻辑start*/
			getNewsCategory: function() { //获取新闻类别
				var that = this;
				var url = '/news/getNewsCategory';
				var data = {

				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.list = res.data.data;

					that.getData();
					that.getHotNews();
				}, "globalUrlNew");
			},
			change(index) { //点击头部tab回调

				if (this.list[index].category_url != null && this.list[index].category_url != '') {
					uni.navigateTo({
						url: this.list[index].category_url
					})
				} else {
					this.resetNewsList();

					this.current = index;
					this.getData();
					this.getHotNews();
				}
			},
			/*头部tab逻辑end*/

			/*新闻列表start*/
			getData: function(if_hot) { //获取新闻列表数据
				/**
				 * type 0：推荐；1：新闻；2：两山号、0
				 * if_miui 0：缩略图,1：组图,2：大图
				 */
				var that = this;
				var url = '';
				var data = {
					news_category_id: that.list[that.current].news_category_id,
					if_hot: 0,
					page: that.page,
					recs: that.recs,
				};

				if (that.list[that.current].type == 0) {
					url = '/news/getIndexNews';
				} else if (that.list[that.current].type == 1) {
					url = '/news/getNews';
				}
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
			getHotNews: function() {
				var that = this;
				var url = '';
				var data = {
					news_category_id: that.list[that.current].news_category_id,
					if_hot: 1,
					page: that.page,
					recs: 5,
				};
				if (that.list[that.current].type == 0) {
					url = '/news/getIndexNews';
				} else if (that.list[that.current].type == 1) {
					url = '/news/getNews';
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					for (var i = 0; i < res.data.data.length; i++) {
						that.swiperNewsData.push(res.data.data[i]);
					}
				}, "globalUrlNew");
			},
			handleSwiperNews: function(index) {
				this.open_news_detail(this.swiperNewsData[index])
			},
			/*新闻列表end*/

			/*中间模块start*/
			get_mid_nav: function() {
				var that = this;
				var url = '/main/get_mid_nav.php';
				var data = {
					search: ''
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.serviceData = res.data;
				});
			},
			/*中间模块end*/
		}
	}
</script>

<style scoped>
	/*中间模块start*/
	.icon {
		width: 72rpx;
		height: 72rpx;
	}

	.item_module_name {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}
	/*中间模块end*/
</style>
