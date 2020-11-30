<template>
	<view>
		<u-form :model="form" ref="uForm" label-align="left">
			<u-form-item>
				<u-input v-model="form.invite_code" placeholder="请输入邀请码"/>
			</u-form-item>
		</u-form>
		<view class="btn-big mtb" @click="write_invite_code();">
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
					invite_code: '',
				},
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
			　　title: options.module_name
			})
		},
		methods: {
			write_invite_code: function() {
				var that = this;
				var url = '/main/write_invite_code.php';
				var data = {
					invite_code: that.form.invite_code,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					uni.showModal({
						content: res.data.msg,
						showCancel: false
					});
				});
			}
		}
	}
</script>

<style scoped>
	.mtb {
		margin: 64rpx 24rpx 0 24rpx;
	}
</style>
