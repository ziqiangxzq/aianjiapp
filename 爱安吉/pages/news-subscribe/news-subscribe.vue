<template>
	<view>
		<!--tab切换start-->
		<view>
			<u-tabs :list="list" :is-scroll="false" :bold="true" :fontSize="34" :height="90" :duration="0" :current="current"
			 @change="change"></u-tabs>
		</view>
		<!--tab切换end-->

		<view v-if="current == 0">
			<!--订阅号类别start-->
			<lab name="分类"></lab>
			<u-grid :col="4" :border="false">
				<u-grid-item v-for="(arr, i) in subscribeCategoryArr" :key="i" @click="openSubscribeCategory(arr);">
					<u-image :src="arr.icon" width="80rpx" height="80rpx" :lazy-load="true"></u-image>
					<view class="item_module_name" v-html="arr.category_name">
					</view>
				</u-grid-item>
			</u-grid>
			<!--订阅号类别end-->

			<!--推荐订阅号start-->
			<lab name="推荐"></lab>
			<u-grid :col="3" :border="true">
				<u-grid-item v-for="(arr, i) in subscribeHotArr" :key="i" @click="openSubscribeCategory(arr);">
					<u-image :src="arr.icon" width="100rpx" height="100rpx" :lazy-load="true" shape="circle"></u-image>
					<view class="item_module_name_tj" v-html="arr.category_name">
					</view>
					<is-subscribe :newsArr="arr"></is-subscribe>
				</u-grid-item>
			</u-grid>
			<!--推荐订阅号end-->

			<!--最新动态start-->
			<lab name="最新动态"></lab>
		</view>
		
		<view v-if="current == 1">
			<!--我的订阅号-->
			<u-grid :col="6" :border="false">
				<u-grid-item bg-color="#eeeeee" v-for="(arr, i) in userNewsCategoryArr" :key="i" @click="openSubscribeCategory(arr);">
					<u-image :src="arr.icon" width="60rpx" height="60rpx" :lazy-load="true" shape="circle"></u-image>
					<view class="item_module_name" v-html="arr.category_name">
					</view>
				</u-grid-item>
			</u-grid>
		</view>
		
		<!--动态start-->
		<news-list :newsListData="commonNewsData"></news-list>
		<!--动态end-->
		
		<!--分页start-->
		<u-loadmore :status="status" color="#a8a8a8" />
		<!--分页end-->

		<u-back-top :scroll-top="scrollTop" top="100"></u-back-top>
	</view>
</template>

<script>
	import newsList from '../../components/news-list.vue'
	import lab from '../../components/lab.vue'
	import isSubscribe from '../../components/is-subscribe.vue'
	export default {
		components: {
			newsList,
			lab,
			isSubscribe,
		},
		data() {
			return {
				/*类别tab*/
				list: [{
					name: "热门"
				}, {
					name: "我的订阅"
				}],
				current: 0,
				bg: {
					'backgroundColor': '#0090ff',
					'margin': '20rpx 10rpx',
					'borderRadius': '8rpx',
				},
				/*类别tab*/

				/*订阅号类别start*/
				subscribeCategoryArr: [],
				/*订阅号类别end*/

				/*推荐订阅号start*/
				subscribeHotArr: [],
				/*推荐订阅号end*/

				commonNewsData: [],

				/*分页start*/
				status: 'loading',
				page: 1,
				recs: 20,
				/*分页end*/
				scrollTop: 0,
				
				/*我的订阅start*/
				userNewsCategoryArr: [],
				/*我的订阅end*/
			};
		},
		onShow() {},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.getLsNewsCategory(0); //类别
			this.getLsNewsCategory(1); //推荐
			
			this.getData(); //最新
		},
		//分页start
		onPullDownRefresh() {
			this.resetNewsList();
			
			if(this.current == 0) {
				this.getLsNewsCategory(0); //类别
				this.getLsNewsCategory(1); //推荐
			} else {
				this.getUserNewsCategory(); //我的订阅	
			}
			
			this.getData(); //动态
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
			},
			/*重置新闻列表(用于刷新和切换类别)end*/

			/*头部tab切换回调start*/
			change(index) {
				this.current = index;
				this.resetNewsList();
				if(index == 0) {
					this.getData();
				} else {
					this.getUserNewsCategory();
					this.getData();
				}
			},
			/*头部tab切换回调end*/

			/*订阅号类别、推荐逻辑start*/
			getLsNewsCategory: function(if_category) { //获取新闻类别
				var that = this;
				var url = '/news/getLsNewsCategory';
				var data = {
					news_category_id: 0,
					is_recommend: if_category
				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						if (if_category == 0) {
							that.subscribeCategoryArr = res.data.data;
						} else {
							that.subscribeHotArr = res.data.data;
						}
					}
				}, "globalUrlNew");
			},
			//打开分类
			openSubscribeCategory: function(arr) {
				uni.navigateTo({
					url: arr.category_url
				})
			},
			/*订阅号类别、推荐end*/

			/*动态start*/
			getData: function(if_hot) {
				var that = this;
				var url = '';
				var data = {
					page: that.page,
					recs: that.recs
				};
				if (that.current == 0) {
					url = '/news/getSubscribeNewNews';
				} else if (that.current == 1) {
					url = '/news/getUserSubscribeNews';
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
			/*动态end*/
			
			/*我的订阅start*/
			getUserNewsCategory: function() {
				var that = this;
				var url = '/news/getUserNewsCategory';
				var data = {
					
				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if(res.data.ret == 200) {
						that.userNewsCategoryArr = res.data.data;
					}
				}, "globalUrlNew");
			},
			/*我的订阅end*/
		}
	}
</script>

<style scoped>
	/*订阅号类别start*/
	.item_module_name {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}
	/*订阅号类别end*/

	/*推荐订阅号start*/
	.item_module_name_tj {
		margin-top: 8rpx;
		font-size: 28rpx;
		margin-bottom: 12rpx;
	}

	/*推荐订阅号end*/
</style>
