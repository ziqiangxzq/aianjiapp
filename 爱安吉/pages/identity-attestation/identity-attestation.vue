<template>
	<view class="wrap">
		<view class="lab-dl">实名认证</view>

		<view>
			<input class="inpt uba inpt-radius inpt-top" type="idcard" focus="true" placeholder="请输入身份证号" />
			<input class="inpt uba inpt-radius inpt-top" type="text" placeholder="请输入姓名" />

		</view>
		<view class="btn-big top-71" @click="openIdentityAttestation();">
			<view class="btn-big-txt">实名认证
			</view>
		</view>

	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			};
		},
		onShow() {
			
		},
		onLoad() {

		},
		methods: {
			bindPickerChange: function(e) {
				console.log('picker发送选择改变，携带值为', e.target.value)
				this.index = e.target.value
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
