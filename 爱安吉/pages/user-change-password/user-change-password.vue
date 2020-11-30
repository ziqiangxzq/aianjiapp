<template>
	<view>
		<u-form :model="form" ref="uForm" label-align="center" :label-style="labelStyle">
			<u-form-item :label-width="300" label="原密码">
				<u-input v-model="form.oldpwd" type="password" />
			</u-form-item>
			<u-form-item :label-width="300" label="新密码">
				<u-input v-model="form.newpwd" type="password" />
			</u-form-item>
		</u-form>

		<view class="btn-big mtb" @click="changePassword();">
			<view class="btn-big-txt">提交
			</view>
		</view>
	</view>
</template>

<script>
	import MD5 from '../../common/MD5.js'
	
	export default {
		data() {
			return {
				form: {
					oldpwd: '',
					newpwd: '',
				},
				labelStyle: {
					color: '#a8a8a8'
				}
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			})
		},
		methods: {
			changePassword: function() {
				var that = this;
				var url = '/user/changePassword';
				var data = {
					"oldpwd": MD5(that.form.oldpwd),
					"newpwd": MD5(that.form.newpwd),
				};
				var header = {
					'content-type': 'application/json'
				}
				that.globalRequest(url, data, 'POST', 'JSON', header, function(res) {
					if (res.data.ret == 200) {
						uni.showToast({
							title: res.data.msg,
							duration: 1200,
							icon: 'none'
						});
						setTimeout(function() {
							uni.navigateBack({
							
							})
						}, 1500)
					} else {
						uni.showToast({
							title: res.data.msg,
							duration: 1200,
							icon: 'none'
						});
					}
				}, "globalUrlNew");
			}
		}
	}
</script>

<style>
	.wrapper {
		margin: 0 24rpx;
	}

	.mtb {
		margin: 64rpx 24rpx 0 24rpx;
	}
</style>
