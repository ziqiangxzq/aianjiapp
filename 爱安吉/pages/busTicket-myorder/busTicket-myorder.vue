<template>
	<view class="container" :style="'min-height:'+ screenHeight +'px !important;'">
		<view class="head-tab-box">
			<text :style="{'color':item.value==ticket_stauts?'#0090ff':'#000000'}" class="head-tab-item-text" v-for="item in tabdata"
			 @click="choosetab(item.value)">{{item.name}}</text>
		</view>
		<view class="order-box" v-for="item in news">
			<view class="order-head-box" v-if="item.state==5">
				<image src="../../static/bus/bus1.png" class="bus-img"></image>
				<text class="order-head-text">已完成</text>
				<text class="order-head-price">￥{{item.amount}}</text>
			</view>
			<view class="order-head-box" v-if="item.state==4">
				<image src="../../static/bus/bus1.png" class="bus-img"></image>
				<text class="order-head-text">已取消</text>
				<text class="order-head-price">￥{{item.amount}}</text>
			</view>
			<view class="order-head-box" v-if="item.state==3">
				<image src="../../static/bus/bus.png" class="bus-img"></image>
				<text class="order-head-text" style="color: #000000;">已支付</text>
				<text class="order-head-price" style="color: #ff7e15;">￥{{item.amount}}</text>
			</view>
			<view class="order-head-box" v-if="item.state==1">
				<image src="../../static/bus/bus.png" class="bus-img"></image>
				<text class="order-head-text" style="color: #000000;">待支付</text>
				<text class="order-head-price" style="color: #ff7e15;">￥{{item.amount}}</text>
			</view>
			<view class="order-content-box" style="color: #A8A8A8;" v-if="item.state==5">
				<view class="address-box">
					<text class="address-text">{{item.start_station}}</text>
					<view class="line-text"></view>
					<text class="address-text" style="margin-left: 20rpx;">{{item.end_station}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">订单编号： {{item.order_id}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">取票密码： {{item.get_ticket_pwd}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">发车时间： {{item.taking_time}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">购买时间： {{item.buy_date}}</text>
				</view>
				<view class="delete-btn" @click="deleteoredr(item.buyed_id,item.order_id)">
					删除
				</view>
			</view>
			<view class="order-content-box" style="color: #A8A8A8;" v-if="item.state==4">
				<view class="address-box">
					<text class="address-text">{{item.start_station}}</text>
					<view class="line-text"></view>
					<text class="address-text" style="margin-left: 20rpx;">{{item.end_station}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">订单编号： {{item.order_id}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">发车时间： {{item.taking_time}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">下单时间： {{item.makeorder_date}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">{{item.status_msg}}</text>
				</view>
				<view class="delete-btn" @click="deleteoredr(item.buyed_id,item.order_id)">
					删除
				</view>
			</view>
			<view class="order-content-box" v-if="item.state==3">
				<view class="address-box">
					<text class="address-text">{{item.start_station}}</text>
					<view class="line-text"></view>
					<text class="address-text" style="margin-left: 20rpx;">{{item.end_station}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">订单编号： </text>
					<text class="ordernum-text" style="color: #ff7e15;margin-left: 8rpx;">{{item.order_id}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">取票密码：</text>
					<text class="ordernum-text" style="color: #ff7e15;margin-left: 8rpx;">{{item.get_ticket_pwd}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">发车时间： {{item.taking_time}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">购买时间： {{item.buy_date}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text" style="color: #A8A8A8;">可凭取票密码及订单号或取票人身份证在取票机中取票。请您在发车时间前取票。</text>
				</view>
				<view class="delete-btn" @click="returnoredr(item.order_id)">
					退票
				</view>
			</view>
			<view class="order-content-box" v-if="item.state==1">
				<view class="address-box">
					<text class="address-text">{{item.start_station}}</text>
					<view class="line-text"></view>
					<text class="address-text" style="margin-left: 20rpx;">{{item.end_station}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">订单编号： {{item.order_id}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">发车时间： {{item.taking_time}}</text>
				</view>
				<view class="ordernum-box">
					<text class="ordernum-text">下单时间： {{item.makeorder_date}}</text>
				</view>
				<view class="btn-box">
					<view class="cancel-btn" @click="cancleoredr(item.get_ticket_pwd,item.order_id)">
						取消订单
					</view>
					<view class="pay-btn" @click="gotopay(item.buyed_id)">
						去支付
					</view>
				</view>

			</view>
		</view>




		<uni-load-more :status="status" :content-text="contentText" />
	</view>

</template>

<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		data() {
			return {
				ticket_stauts: '0',
				tabdata: [{
						name: '全部订单',
						value: '0',
					},
					{
						name: '已支付',
						value: '3',
					},
					{
						name: '待支付',
						value: '1',
					},
					{
						name: '已完成',
						value: '5',
					},
					{
						name: '已取消',
						value: '4',
					}
				],

				last_id: false,
				reload: false,
				status: 'more',
				news: [], //新闻
				contentText: {
					contentdown: '上拉加载更多',
					contentrefresh: '加载中',
					contentnomore: '没有更多内容了'
				},
				page: 1,
				recs: 10,
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.pagetitle
			})
			this.category_id = options.category_id

			this.getlist(this.ticket_stauts)
			this.screenHeight = uni.getSystemInfoSync().windowHeight;
		},
		onPullDownRefresh() {
			this.reload = true;
			this.last_id = false;
			this.news = [];
			this.page = 1;
			this.getlist(this.ticket_stauts);
		},
		onReachBottom() {
			this.status = 'more';
			this.getlist(this.ticket_stauts);
		},
		onBackPress(e) {
			uni.redirectTo({
				url: '../busTicket-index/busTicket-index'
			})
		},
		methods: {
			getlist: function(a) {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/ticket/query_order_info.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						page: that.page,
						recs: that.recs,
						stauts: a,
						user_id: uni.getStorageSync("user_id"),
					},
					success: (res) => {
						var news = eval('(' + res.data + ')');

						for (var i = 0; i < news.length; i++) {
							that.news.push(news[i]);
						}
						if (that.reload) {
							uni.stopPullDownRefresh();
						}
						that.last_id = true;
						that.reload = false;
						if (news.length < that.recs) {
							that.status = '';
						}

					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
			},
			choosetab: function(a) {
				this.ticket_stauts = a
				this.reload = true;
				this.last_id = false;
				this.news = [];
				this.page = 1;
				this.getlist(a);
			},
			deleteoredr: function(a, b) {
				var that = this
				uni.showModal({
					title: '提示',
					content: '确定删除该订单么？',
					success: function(res) {
						if (res.confirm) {
							var url = that.globalUrl + '/ticket/delete_ticket_order.php';
							uni.request({
								url: url,
								data: {
									buyed_id: a
								},
								dataType: 'json',
								method: 'post',
								header: {
									'content-type': 'application/x-www-form-urlencoded'
								},
								success: (res) => {
									if (res.data[0].resultid == 1) {
										uni.showToast({
											icon: 'none',
											title: '订单已删除',
											duration: 2000
										});
									}
									that.reload = true;
									that.last_id = false;
									that.news = [];
									that.page = 1;
									that.getlist(that.ticket_stauts);

								},
								fail() {
									uni.showToast({
										icon: 'none',
										title: '网络错误！',
										duration: 2000
									});
								}
							})
						} else if (res.cancel) {
							console.log('用户点击取消');
						}
					}
				});
			},
			returnoredr: function(a) {
				uni.showToast({
					icon: 'none',
					title: '请求退票中...',
					duration: 500
				});
				var that = this
				var url = that.globalUrl + '/ticket/get_ReturnOrderFee.php';
				uni.request({
					url: url,
					data: {
						orderID: a
					},
					dataType: 'json',
					method: 'post',
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					success: (res) => {
						if (res.data.resultid == 1) {
							uni.showModal({
								title: '提示',
								content: res.data.msg,
								success: function(res) {
									if (res.confirm) {
										var url = that.globalUrl + '/ticket/web_ReturnOrder2.php';
										uni.request({
											url: url,
											data: {
												orderID: a
											},
											dataType: 'json',
											method: 'post',
											header: {
												'content-type': 'application/x-www-form-urlencoded'
											},
											success: (res) => {
												if (res.data.resultid == 1) {
													uni.showModal({
														content: res.data.msg,
														showCancel: false,
														success: function(res) {

														}
													});
												}

											},
											fail() {
												uni.showToast({
													icon: 'none',
													title: '网络错误！',
													duration: 2000
												});
											}
										})
									} else if (res.cancel) {
										console.log('用户点击取消');
									}
								}
							});
							that.reload = true;
							that.last_id = false;
							that.news = [];
							that.page = 1;
							that.getlist(that.ticket_stauts);
						} else {
							uni.showModal({
								content: res.data.msg,
								showCancel: false,
								success: function(res) {

								}
							});
						}


					},
					fail() {
						uni.showToast({
							icon: 'none',
							title: '网络错误！',
							duration: 2000
						});
					}
				})
			},
			cancleoredr: function(a, b) {
				var that = this
				uni.showModal({
					title: '提示',
					content: '您可以直接支付该订单,确定取消吗?',
					success: function(res) {
						if (res.confirm) {
							var url = that.globalUrl + '/ticket/web_Cancelorder.php';
							uni.request({
								url: url,
								data: {
									orderPassword: a,
									orderID: b,
								},
								dataType: 'json',
								method: 'post',
								header: {
									'content-type': 'application/x-www-form-urlencoded'
								},
								success: (res) => {
									if (res.data[0].resultid == 1) {
										uni.showToast({
											icon: 'none',
											title: '订单已取消',
											duration: 2000
										});
									}
									that.reload = true;
									that.last_id = false;
									that.news = [];
									that.page = 1;
									that.getlist(that.ticket_stauts);

								},
								fail() {
									uni.showToast({
										icon: 'none',
										title: '网络错误！',
										duration: 2000
									});
								}
							})
						} else if (res.cancel) {
							console.log('用户点击取消');
						}
					}
				});
			},
			gotopay: function(a) {
				uni.setStorageSync('openway','myorder')
				uni.navigateTo({
					url: '../busTicket-orderpay/busTicket-orderpay?buyed_id=' + a
				})
			}
		},

	}
</script>

<style>
	.container {
		background-color: #eeeeee;
	}

	.head-tab-box {
		background-color: #FFFFFF;
		padding: 20rpx 30rpx;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
	}

	.order-box {
		background-color: #FFFFFF;
		width: 92%;
		margin: 0 auto;
		margin-top: 20rpx;
		border-radius: 10rpx;
	}

	.order-head-box {
		color: #A8A8A8;
		height: 72rpx;
		padding: 10rpx;
		border-bottom: 1rpx solid #e2e2e2;
	}

	.bus-img {
		width: 52rpx;
		height: 52rpx;
		vertical-align: middle;
	}

	.order-head-text {
		margin-left: 16rpx;
	}

	.order-head-price {
		float: right;
		line-height: 52rpx;
	}

	.order-content-box {
		padding: 20rpx 10rpx;
	}

	.address-text {
		font-size: 32rpx;
	}

	.ordernum-box {
		margin-top: 10rpx;
	}

	.ordernum-text {
		font-size: 26rpx;
	}

	.delete-btn {
		color: #0090ff;
		border: 1rpx solid #0090ff;
		width: 117rpx;
		height: 60rpx;
		line-height: 60rpx;
		border-radius: 10rpx;
		margin-left: 540rpx;
		text-align: center;
	}

	.btn-box {
		margin-top: 10rpx;
		display: flex;
	}

	.cancel-btn {
		color: #0090ff;
		border: 1rpx solid #0090ff;
		width: 122rpx;
		height: 60rpx;
		line-height: 60rpx;
		border-radius: 10rpx;
		text-align: center;
		margin-left: 380rpx;
	}

	.pay-btn {
		color: #FFFFFF;
		background-color: #ff7e15;
		width: 122rpx;
		height: 60rpx;
		line-height: 60rpx;
		border-radius: 10rpx;
		text-align: center;
		margin-left: 30rpx;
	}
	.line-text{
		width: 120rpx;
		height: 1rpx;
		border-top: 2rpx solid #a8a8a8;
		margin-left: 20rpx;
		display: inline-block;
		padding-bottom: 12rpx;
	}
</style>
