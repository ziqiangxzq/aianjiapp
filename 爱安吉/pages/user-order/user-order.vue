<template>
	<view>
		<u-grid :col="2" :border="true">
			<u-grid-item v-for="(arr, i) in order_data" :key="i" @click="openOrderWin(i);">
				<image :src="arr.icon" class="icon"></image>
				<view class="key">{{arr.module_name}}</view>
			</u-grid-item>
		</u-grid>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				order_data: []
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			})
			this.get_main_order();
		},
		methods: {
			get_main_order: function() {

				var that = this;
				var url = '/main/get_main_order.php';
				var data = {

				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.order_data = res.data;
				});
			},
			openOrderWin: function(i) {
				uni.navigateTo({
					url: this.order_data[i].order_URL2
				})
			}
		}
	}
</script>

<style>
	.icon {
		width: 50upx;
		height: 50upx;
	}

	.key {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}
</style>
