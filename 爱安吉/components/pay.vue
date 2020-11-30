<template>
	<view style="background-color:#f4f4f4;">
		<view class="pay-box">
			<view class="title-box">
				使用第三方平台支付
			</view>
			<view class="pay-way-box" style="border-bottom: 1rpx solid #f0f0f0;">
				<image src="../static/bus/iconfont-zhifubao.png" class="pay-img"></image>
				<view class="pay-text-box">
					<view>支付宝</view>
					<view style="color: #A8A8A8;">推荐已安装支付宝客户端的用户使用</view>
				</view>
				<image :src="payway==0?activecheckimg:checkimg" class="check-img" @click="payway=0"></image>
			</view>
		
			<view class="pay-way-box">
				<image src="../static/bus/weixin.png" class="pay-img"></image>
				<view class="pay-text-box">
					<view>微信</view>
					<view style="color: #A8A8A8;">推荐微信用户使用</view>
				</view>
				<image :src="payway==1?activecheckimg:checkimg" class="check-img" @click="payway=1"></image>
			</view>
		
		
		</view>
		<view class="btn-big mtb" @click="topay()">
			<view class="btn-big-txt">确认支付
			</view>
		</view>
	</view>
</template>

<script>
	
	export default{
		props:{
			
		},
		data(){
			return{
				payway: 0,
				activecheckimg: '../../static/bus/checkedblue.png',
				checkimg: '../../static/bus/checked.png',
				providerList: [],
			}
		},
		mounted() {
			// #ifdef APP-PLUS
			uni.getProvider({
				service: "payment",
				success: (e) => {
					console.log("payment success:" + JSON.stringify(e));
					let providerList = [];
					e.provider.map((value) => {
						switch (value) {
							case 'alipay':
								providerList.push({
									name: '支付宝',
									id: value,
									loading: false
								});
								break;
							case 'wxpay':
								providerList.push({
									name: '微信',
									id: value,
									loading: false
								});
								break;
							default:
								break;
						}
					})
					this.providerList = providerList;
					console.log(this.providerList)
				},
				fail: (e) => {
					console.log("获取支付通道失败：", e);
				}
			});
			// #endif
		},
		methods:{
			//支付相关
			topay: function() {
				if (this.payway == 0) {
					this.requestPayment(this.providerList[0], 0)
				}
				if (this.payway == 1) {
					this.requestPayment(this.providerList[1], 1)
				}
			},
			
			async requestPayment(e, index) {
				this.providerList[index].loading = true;
				let orderInfo = await this.getOrderInfo(e.id);
				console.log("得到订单信息", orderInfo);
				if (orderInfo.statusCode !== 200) {
					console.log("获得订单信息失败", orderInfo);
					uni.showModal({
						content: "获得订单信息失败",
						showCancel: false
					})
					return;
				}
				uni.requestPayment({
					provider: e.id,
					orderInfo: orderInfo.data,
					success: (e) => {
						console.log("success", e);
						uni.showToast({
							title: "感谢您的赞助!"
						})
					},
					fail: (e) => {
						console.log("fail", e);
						uni.showModal({
							content: "支付失败,原因为: " + e.errMsg,
							showCancel: false
						})
					},
					complete: () => {
						this.providerList[index].loading = false;
					}
				})
			},
			getOrderInfo(e) {
				let appid = "";
				// #ifdef APP-PLUS
				appid = plus.runtime.appid;
				// #endif
				let url = 'https://demo.dcloud.net.cn/payment/?payid=' + e + '&appid=' + appid + '&total=0.01';
				return new Promise((res) => {
					uni.request({
						url: url,
						success: (result) => {
							res(result);
						},
						fail: (e) => {
							res(e);
						}
					})
				})
			},
		}
		
	}
</script>

<style>
	.pay-box {
		background-color: #FFFFFF;
		margin-top: 60rpx;
	}
	
	.title-box {
		padding: 30rpx;
		border-bottom: 1rpx solid #f0f0f0;
	}
	
	.pay-way-box {
		position: relative;
		display: flex;
		flex-direction: row;
		padding: 40rpx 30rpx;
	}
	
	.pay-img {
		width: 80rpx;
		height: 80rpx;
	}
	
	.pay-text-box {
		margin-left: 20rpx;
	}
	
	.check-img {
		position: absolute;
		width: 50rpx;
		height: 50rpx;
		border-radius: 25rpx;
		right: 30rpx;
		top: 45rpx;
	}
	
	.mtb {
		margin: 48rpx 24rpx 0 24rpx;
	}
</style>
