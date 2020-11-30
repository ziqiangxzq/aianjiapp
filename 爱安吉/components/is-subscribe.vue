<template>
	<view>
		<view class="is_subscribe_no" v-if="newsArr.is_subscribe == 0" @click.stop="setCategorySubscribe(newsArr, 1)">订阅</view>
		<view class="is_subscribe_yes" v-if="newsArr.is_subscribe == 1" @click.stop="setCategorySubscribe(newsArr, 0)">已订阅</view>
	</view>
</template>

<script>
	export default {
		props: ["newsArr"],
		components: {

		},
		data() {
			return {

			}
		},
		created: function() {
			this.$on('handleChange', function() {
				console.log('something handled!');
			});
		},
		methods: {
			setCategorySubscribe: function(arr, state) { //获取新闻类别
				var that = this;
				var url = '/news/setCategorySubscribe';
				var data = {
					news_category_id: arr.news_category_id,
					state: state,
				};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					uni.showToast({
						title: res.data.msg,
						duration: 1000,
						icon: 'none'
					});
					if (res.data.ret == 200) {
						arr.is_subscribe = state;
					}
				}, "globalUrlNew");
			},
		}
	}
</script>

<style>
	/*是否订阅按钮start*/
	.is_subscribe_no {
		color: #0090ff;
		border: 1rpx solid #0090ff;
		border-radius: 10rpx;
		padding: 4rpx 16rpx;
		font-size: 22rpx;
	}

	.is_subscribe_yes {
		color: #A8A8A8;
		border: 1rpx solid #A8A8A8;
		border-radius: 10rpx;
		padding: 4rpx 16rpx;
		font-size: 22rpx;
	}

	/*是否订阅按钮end*/
</style>
