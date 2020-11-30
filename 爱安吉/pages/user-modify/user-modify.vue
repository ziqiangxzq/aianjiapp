<template>
	<view>
		<u-form :model="form" ref="uForm" label-align="center" :label-style="labelStyle">
			<u-form-item :label-width="300" label="昵称">
				<u-input v-model="form.user_nick" />
			</u-form-item>
			<u-form-item :label-width="300" label="绑定手机号">
				<u-input v-model="form.phone" :disabled="true" />
			</u-form-item>
			<u-form-item :label-width="300" label="真实姓名">
				<u-input v-model="form.user_name" :disabled="true" />
			</u-form-item>
			<u-form-item :label-width="300" label="身份证号">
				<u-input v-model="form.idcard" :disabled="true" />
			</u-form-item>
		</u-form>
		
		<view class="btn-big mtb" @click="user_updateinfo();">
			<view class="btn-big-txt">提交
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				form: {
					user_nick: '',
					user_name: '',
					idcard: '',
					phone: '',
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
			this.user_loadinfo();
		},
		methods: {
			user_loadinfo: function() {
				var that = this;
				var url = '/main/user_loadinfo.php';
				var data = {
					
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.form.user_nick = res.data[0].user_nick;
					that.form.user_name = res.data[0].user_name;
					that.form.idcard = res.data[0].idcard;
					that.form.phone = res.data[0].phone;
				});
			},
			user_updateinfo: function() {
				var that = this;
				var url = '/main/user_updateinfo_new.php';
				var data = {
					user_nick: that.form.user_nick,
					user_name: that.form.user_name,
					idcard: that.form.idcard,
					phone: that.form.phone,
				}
				var header = {
					'content-type': 'application/json'	
				}
				that.globalRequest(url, data, 'POST', 'JSON', header, function(res) {
					if(res.data.ret == 200) {
						uni.showToast({
						    title: res.data.msg,
						    duration: 1200,
							icon: 'none'
						});
						setTimeout(function() {  
						    uni.navigateBack();
						}, 1200);
					} else {
						uni.showModal({
							content: res.data.msg,
							showCancel: false
						});
					}
				});
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
