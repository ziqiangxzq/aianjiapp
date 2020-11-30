<template>
	<view>
		<view class="grey-box">
			<view class="title-box">
				<view>
					出发地
				</view>
				<view>
					目的地
				</view>
			</view>
			<view class="addressbox">
				<!-- 目的地 -->
				<view class="startaddress address">安吉<span class="grayS">（固定）</span></view>
				<view class="iconbox center">
					<image src="../../static/bus/keche.png" class="icon">
				</view>
				<view class="endaddress address" v-on:click="openchoiceaddress()">{{endaddress}}</view>
			</view>
			<view class="datebox">
				<!-- 选择时间 -->
				<view style="color: #A8A8A8;font-size: 30rpx;">
					出发时间
				</view>
				<picker mode="date" :value="date" :start="startDate" :end="endDate" @change="bindDateChange">
					<view class="uni-input">{{date}}</view>
					<image src="../../static/bus/more.png" class="date-img">
				</picker>

			</view>
		</view>
		<view class="btn-big mtb" @click="selectdetail()">
			<view class="btn-big-txt">查 询
			</view>
		</view>
	</view>
</template>

<script>
	function getDate(type) {
		const date = new Date();

		let year = date.getFullYear();
		let month = date.getMonth() + 1;
		let day = date.getDate();

		if (type === 'start') {
			year = year - 1;
		} else if (type === 'end') {
			year = year + 1;
		}
		day = day > 9 ? day : '0' + day;
		month = month > 9 ? month : '0' + month;;
		return `${year}-${month}-${day}`;
	}
	export default {
		data() {
			return {
				date: getDate({
					format: true
				}),
				startDate: getDate('start'),
				endDate: getDate('end'),
				endaddress: "请选择"
			}
		},
		onLoad() {
			uni.setStorageSync("trickdate", getDate({
				format: true
			}));
		},
		onShow() {
			if (uni.getStorageSync("unitname") != '') { //若获取到缓存地址则选择展示缓存地址
				this.endaddress = uni.getStorageSync("unitname")
			} else {

			}
		},
		methods: {
			bindDateChange: function(e) { //日期改变
				var date1 = new Date();
				var date2 = new Date(date1);
				date2.setDate(date1.getDate() + 10); //10天后的日期
				// var date=new Date();
				var startTime = new Date(Date.parse(e.detail.value));
				var nowTime = new Date(Date.parse(getDate({
					format: true
				})));
				console.log("选择日期" + startTime);
				console.log("现在日期" + nowTime);
				if (startTime >= nowTime && date2 >= startTime) { //选择日期大于当前日期且在当前日期后11天内可选择
					this.date = e.detail.value;
					uni.setStorageSync("trickdate", this.date);
					console.log(this.date)
				} else { //选择日期小于当前日期不可选择
					uni.showToast({
						icon: 'none',
						title: "请选择正确售卖日期~"
					})
				};
				//if(e.detail.value)
			},
			selectdetail: function() { //跳转详情界面
				uni.navigateTo({
					url: '../busTicket-ticketlist/busTicket-ticketlist'
				})
			},
			openchoiceaddress: function() { //打开选择地址详情页面
				uni.redirectTo({
					url: '../busTicket-address/busTicket-address'
				})
			}
		},
		onNavigationBarButtonTap(e) { //跳转个人订单
			if (e.index == 0) {
				uni.navigateTo({
					url: '../busTicket-myorder/busTicket-myorder'
				});
			}
		},
	}
</script>

<style>
	page {
		color: #444;
		background-color: #fff;
	}

	.grey-box {
		width: 92%;
		margin: 0 auto;
		margin-top: 40rpx;
		background-color: #f8f8f8;
		border-radius: 16rpx;
		padding-top: 30rpx;
	}

	.icon {
		position: relative;
		width: 100%;
		height: 100%;
	}

	.iconbox {
		width: 80rpx;
		height: 80rpx;
		display: flex;
		align-items: center;
		justify-content: center;
	}

	.center {
		position: absolute;
		left: calc((100% - 80rpx) / 2);
	}

	.address {
		position: relative;
		font-size: 0.9rem;
		color: #444;
	}

	.grayS {
		position: relative;
		font-size: 0.8rem;
		color: gray;
	}

	.title-box {
		width: calc(100% - 48rpx);
		height: 40rpx;
		margin-left: 24rpx;
		color: #A8A8A8;
		padding: 0 24rpx;
		display: flex;
		align-items: center;
		justify-content: space-between;
	}

	.addressbox {
		position: relative;
		width: calc(100% - 48rpx);
		margin-left: 24rpx;
		margin-top: 20rpx;
		padding: 0 24rpx 24rpx 24rpx;
		border-bottom: 1rpx solid #eee;
		display: flex;
		align-items: center;
		justify-content: space-between;
	}

	.datebox {
		position: relative;
		width: calc(100% - 48rpx);
		height: 120rpx;
		color: #444;
		margin-left: 24rpx;
		padding: 24rpx;
		font-size: 34rpx;
		display: flex;
		align-items: center;
		/* justify-content:space-between; */
	}

	.uni-input {
		margin-left: 160rpx;
		line-height: 120rpx;
		display: inline-block;
	}

	.mtb {
		margin: 48rpx 24rpx 0 24rpx;
	}

	.date-img {
		position: absolute;
		right: 0;
		width: 56rpx;
		height: 56rpx;
		top: 32rpx;
	}
</style>
