<template>
	<view>
		<adv :category_id="2"></adv>
		<view v-for="(arr, i) in serviceData" :key="i" class="clear-both">
			<lab :name="arr.type_name"></lab>
			<u-grid :col="4" :border="false">
				<u-grid-item v-for="(arr, i) in arr.type_info" :key="i" @click="handleMainModuel(arr);">
					<u-image :src="arr.icon" width="64rpx" height="64rpx" :lazy-load="true"></u-image>
					<view class="module_name">{{arr.module_name}}</view>
				</u-grid-item>
			</u-grid>
		</view>
	</view>
</template>

<script>
	import lab from '../../components/lab.vue'
	import adv from '../../components/adv.vue'
	
	export default {
		components: {
			lab,
			adv
		},
		data() {
			return {
				serviceData: [],
			};
		},
		onShow() {
			this.get_main_new();
		},
		onLoad() {

		},
		methods: {
			get_main_new: function() {
				var that = this;
				var url = '/main/get_main_new.php';
				var data = {
					search: ''
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.serviceData = res.data;
				});
			}
		}
	}
</script>

<style scoped>
	page {
		display: flex;
		flex-direction: column;
		box-sizing: border-box;
	}

	.wrapper {
		float: left;
		width: 25%;
		margin: 24upx auto;
		text-align: center;
	}
	
	.icon {
		width: 64rpx;
		height: 64rpx;
	}

	.module_name {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}
</style>
