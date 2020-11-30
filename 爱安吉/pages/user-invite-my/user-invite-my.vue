<template>
	<view>
		<u-form :model="form" ref="uForm" label-align="center" :label-style="labelStyle">
			<u-form-item :label-width="300" label="我的邀请码">
				<u-input v-model="form.invite_code" :disabled="true" />
			</u-form-item>
			<u-form-item :label-width="300" label="邀请人数">
				<u-input v-model="form.invite_num" :disabled="true" />
			</u-form-item>
			<u-form-item :label-width="300" label="邀请所获积分">
				<u-input v-model="form.invite_points" :disabled="true" />
			</u-form-item>
		</u-form>
		<view class="btn-big mtb" @click="invite_friend();">
			<view class="btn-big-txt">邀请好友，赚取积分
			</view>
		</view>
		<share ref="imsg" :shareInfo="shareInfo"></share>
	</view>
</template>

<script>
	import share from '../../components/share.vue'
	export default {
		components: {
			share
		},
		data() {
			return {
				form: [],
				labelStyle: {
					color: '#a8a8a8'
				},
				
				//分享数数组
				shareInfo: {
					share_title: '',
					share_content: '',
					share_url: '',
					share_pic: ''
				},
				//分享数数组
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.get_my_promoCode();
		},
		methods: {
			get_my_promoCode: function() {
				var that = this;
				var url = '/main/get_user_invite_code.php';
				var data = {

				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.form = res.data;
					that.shareInfo.share_title = res.data.share_title;
					that.shareInfo.share_content = res.data.share_content;
					that.shareInfo.share_url = that.globalUrl2+'/m.web/weixinShare/invite/invite_wx_share.php'
					+'?invite_code='+res.data.invite_code
					+'&user_id='+uni.getStorageSync("user_id")
					+'&user_nick='+res.data.user_nick
					+'&phone='+res.data.phone;
				});
			},
			invite_friend: function() {
				this.$refs.imsg.togglePopup('bottom', 'share');
			}
		}
	}
</script>

<style scoped>
	.mtb {
		margin: 64rpx 24rpx 0 24rpx;
	}
</style>
