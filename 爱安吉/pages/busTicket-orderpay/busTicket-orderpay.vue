<template>
	<view class="container" :style="'height:'+ screenHeight +'px !important;'">
		<view class="order-box">
			<view class="address">
				{{orderdata.start_station}} ——— {{orderdata.end_station}}
			</view>
			<view class="datetime-box" style="margin-top: 10rpx;">
				<text>发车时间</text>
				<text style="color:#ff7e15;margin-left: 50rpx;font-size: 30rpx;">{{orderdata.taking_time}}</text>
			</view>
			<view class="datetime-box" style="margin-top: 10rpx;">
				<text>应付金额</text>
				<text style="color:#ff7e15;margin-left: 50rpx;font-size: 30rpx;">￥{{orderdata.amount}}</text>
			</view>
			<view class="datetime-box" style="margin-top: 10rpx;">
				<text>取票人</text>
				<text style="margin-left: 78rpx;font-size: 30rpx;">{{orderdata.user_name}}</text>
			</view>
			<view class="datetime-box" style="margin-top: 10rpx;">
				<text>手机号</text>
				<text style="margin-left: 78rpx;font-size: 30rpx;">{{orderdata.contactor_phone}}</text>
			</view>
			<view class="tips-text" style="margin-top: 10rpx;color: #a8a8a8;font-size: 24rpx;">
				汽车票余票变动频繁，请尽量在15分钟内完成支付，可提高出票成功率。
			</view>
		</view>
		<pay></pay>
	</view>
</template>

<script>
	import pay from '../../components/pay.vue'
	export default {
		components: {
			pay
		},
		data() {
			return {
				buyed_id: '',
				orderdata: [],
			}
		},
		onBackPress(event ) {
			if(event.from==='backbutton'){
				uni.showModal({
				title: '提示',
				content: '订单还未支付，请确定是否要退出',
				success: function(res) {
					if (res.confirm) {
						if (uni.getStorageSync('openway') == 'myorder') {
							// alert(1)
							uni.navigateBack({
								delta:1
							})
						}
						if (uni.getStorageSync('openway') == 'orderdetail') {
							uni.redirectTo({
								url: '../busTicket-myorder/busTicket-myorder'
							})
						}

					} else if (res.cancel) {
						console.log('用户点击取消');
					}
				},
			});
			return true; //阻止默认返回行为
			}
			else{

			}
		},
		onLoad(options) {
			this.buyed_id = options.buyed_id
			this.getordercontent()
			this.screenHeight = uni.getSystemInfoSync().windowHeight;
			// console.log('1111'+plus.runtime.uniVersion)
		},

		methods: {

			getordercontent: function() {
				var url = this.globalUrl + '/ticket/get_ticket_order.php';
				uni.request({
					url: url,
					data: {
						user_id: uni.getStorageSync("user_id"),
						buyed_id: this.buyed_id
					},
					dataType: 'json',
					method: 'post',
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					success: (res) => {
						this.orderdata = res.data[0]
					}
				})
			},


		}
	}
</script>

<style>
	.container {
		background-color: #f4f4f4;
	}

	.order-box {
		background-color: #FFFFFF;
		padding: 30rpx;
	}

	.address {
		font-size: 34rpx;
	}

</style>
