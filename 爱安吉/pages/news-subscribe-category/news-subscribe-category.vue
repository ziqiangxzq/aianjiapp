<template>
	<view>
		<!--订阅号start-->
		<lab name="推荐"></lab>
		<u-grid :col="3" :border="true">
			<u-grid-item v-for="(arr, i) in subscribeCategoryArr" :key="i" @click="openSubscribe(arr)">
				<u-image :src="arr.icon" width="100rpx" height="100rpx" :lazy-load="true" shape="circle"></u-image>
				<view class="item_module_name_tj" v-html="arr.category_name">
				</view>
				<is-subscribe :newsArr="arr"></is-subscribe>
			</u-grid-item>
		</u-grid>
		<!--订阅号end-->
	</view>
</template>

<script>
	import isSubscribe from '../../components/is-subscribe.vue'
	export default {
		components: {
			isSubscribe,
		},
		data() {
			return {
				/*订阅号start*/
				subscribeCategoryArr: [],
				/*订阅号end*/
				
				news_category_id: 0,
			};
		},
		onShow() {},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.news_category_id = options.news_category_id;
			this.getLsNewsCategory();
		},
		methods: {
			getLsNewsCategory: function(news_category_id) { //获取新闻类别
				var that = this;
				var url = '/news/getLsNewsCategory';
				var data = {
					news_category_id: that.news_category_id,
					is_recommend: 0
				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						that.subscribeCategoryArr = res.data.data;
					}
				}, "globalUrlNew");
			},
			openSubscribe: function(arr) {
				uni.navigateTo({
					url: arr.category_url
				})
			},
		}
	}
</script>

<style scoped>

	/*订阅号start*/
	.item_module_name_tj {
		margin-top: 8rpx;
		font-size: 28rpx;
		margin-bottom: 12rpx;
	}

	/*订阅号end*/
</style>
