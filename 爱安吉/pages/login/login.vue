<template>
	<view class="wrap">
		<view class="lab-dl">登录</view>

		<view>
			<input class="inpt uba inpt-radius inpt-top" type="number" v-model="loginName" focus="true" placeholder="请输入账号" />
			<input class="inpt uba inpt-radius inpt-top" type="password" v-model="password" placeholder="请输入密码" />
		</view>

		<view class="ub uni-font-size-sm mtb">
			<view class="ub-f1 uni-text-color-grey" @click="openForgetPwd();">忘记密码？</view>
			<view class="uni-color-primary" @click="openRegist();">立即注册</view>
		</view>

		<view class="btn-big" @click="login();">
			<view class="btn-big-txt">登录
			</view>
		</view>

		<view class="ub-f1 ub-ac uni-font-size-sm top-25 uni-text-color-grey">
			登录即同意
			<span class="uni-color-primary" @click="openProtocol('70', '用户协议');">《用户协议》</span>
			与
			<span class="uni-color-primary" @click="openProtocol('105', '隐私协议');">《隐私协议》</span>
		</view>
	</view>
</template>

<script>
	import MD5 from '../../common/MD5.js'
	
	export default {
		data() {
			return {
				loginName: '',
				password: '',
			};
		},
		onShow() {},
		onLoad() {

		},
		methods: {
			openRegist: function() { //打开注册页面
				uni.navigateTo({
					url: '../regist/regist'
				})
			},
			openForgetPwd: function() { //打开忘记密码页面
				uni.navigateTo({
					url: '../forget-pwd/forget-pwd'
				})
			},
			openProtocol: function(module_name, title_name) { //打开协议页面
				uni.navigateTo({
					url: '../protocol/protocol?module_name=' + module_name + '&title_name=' + title_name
				})
			},
			login: function() { //登录
				var that = this;
				var url = '/user/login';
				var data = {
					"loginType": 0,
					"loginName": that.loginName,
					"password": MD5(that.password),
					"phoneCode": "",
					"wechatIv": "",
					"wechatUser": ""
				};
				var header = {
					'content-type': 'application/json'
				}
				that.globalRequest(url, data, 'POST', 'JSON', header, function(res) {
					if(res.data.ret == 200) {
							//用户id
							uni.setStorageSync("user_id", res.data.data.user_id);
							//用户昵称
							uni.setStorageSync("nickname", res.data.data.user_nick);
							//缓存密码
							uni.setStorageSync("password", res.data.data.passwd);
							//手机号码
							uni.setStorageSync("phonenum", res.data.data.phone);
							//用户头像
							uni.setStorageSync("userImg", res.data.data.pics);
							//设置登录成功标志
							uni.setStorageSync("login_if", 1);
							//user_token
							uni.setStorageSync("user_token", res.data.data.user_token);
							//user_token
							uni.setStorageSync("user_token", res.data.data.user_token);
							
							uni.navigateBack({
								
							})
					} else {
						uni.showToast({
						    title: res.data.msg,
						    duration: 1200,
							icon: 'none'
						});
					}
				}, "globalUrlNew");
			},
		}
	}
</script>

<style lang="scss">
	.wrap {
		margin: 0 58rpx;
	}

	/*登录*/
	.lab-dl {
		color: #000000;
		font-size: 43.2rpx;
		padding-top: 118rpx;
	}

	/*input*/
	.inpt-top {
		margin-top: 60rpx;
	}

	.mtb {
		margin: 22rpx 0 71rpx 0;
	}

	.top-25 {
		margin-top: 25rpx;
	}
</style>
