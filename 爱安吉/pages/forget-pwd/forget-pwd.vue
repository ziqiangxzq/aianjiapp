<template>
	<view class="wrap">
		<view class="lab-dl">忘记密码</view>

		<view>
			<input class="inpt uba inpt-radius inpt-top" type="number" v-model="phone" focus="true" placeholder="请输入手机号" />
			<view class="ub ub-ac inpt uba inpt-radius inpt-top">
				<input class="ub-f1 uni-font-size-base" type="text" v-model="phoneCode" placeholder="请输入验证码" />
				<uni-countdown timer="0" :phone="phone" ref="clearVerify" fontColor="#FFFFFF" bgrColor="#0090ff"></uni-countdown>
			</view>
			<input class="inpt uba inpt-radius inpt-top" type="password" v-model="password" placeholder="请设置密码" />
		</view>

		<view class="btn-big top-71" @click="resetPassword();">
			<view class="btn-big-txt">确定
			</view>
		</view>

	</view>
</template>

<script>
	import uniCountdown from "../../components/uni-countdown.vue";
	import MD5 from '../../common/MD5.js'
	
	export default {
		components: {
			uniCountdown
		},
		data() {
			return {
				phone: '',
				phoneCode: '',
				password: '',
			};
		},
		onShow() {
		},
		onLoad() {
			
		},
		methods: {
			resetPassword: function() { //重置密码
				var that = this;
				var url = '/user/resetPassword';
				var data = {
					"phone": that.phone,
					"password": MD5(that.password),
					"phoneCode": that.phoneCode,
				};
				var header = {
					'content-type': 'application/json'
				}
				that.globalRequest(url, data, 'POST', 'JSON', header, function(res) {
					uni.showToast({
						title: res.data.msg,
						duration: 1200,
						icon: 'none',
					});
					setTimeout(function() {
						if(res.data.ret == 200) {
							uni.navigateBack({
								
							})
						}
					}, 1500)
				}, "globalUrlNew");
			},
		}
	}
</script>

<style lang="scss">
	.wrap {
		padding: 0 58rpx;
	}

	/*登录*/
	.lab-dl {
		color: #000000;
		font-size: 43.2rpx;
		padding-top: 118rpx;
	}

	/*input*/
	.inpt-top {
		margin-top: 30rpx;
	}
	
	.top-71 {
		margin-top: 71rpx;
	}
</style>
