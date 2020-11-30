<template>
	<view>
		<view class="ub ub-ver ub-ac ub-pc">
			<image src="../../static/logo.png" class="logo" mode="widthFix"></image>
			<view class="version">{{version}}</view>
		</view>

		<view class="ub ub-ac ubb t-wrap" @click="get_main_version()">
			<view class="ub-f1 txt">检查更新</view>
			<image src="../../static/user/more.png" class="icon"></image>
		</view>

		<view class="ub ub-ac ubb t-wrap" @click="share_app();">
			<view class="ub-f1 txt">推荐给好友</view>
			<image src="../../static/user/more.png" class="icon"></image>
		</view>
		
		<!---分割线-->
		<!-- <u-gap height="8" bg-color="#EEEEEE" style="margin-top: 50upx;"></u-gap> -->

		<view class="ub ub-ver t-wrap">
			<!-- <view class="ub-f1 txt">扫码分享</view> -->
			<image src="../../static/2code.jpg" class="scanner" @click="openImage()"></image>
		</view>

		<view class="copyright">浙江文澜信息发展有限公司</view>
		
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
				version: this.version,
				//分享数数组
				shareInfo: {
					share_title: '爱安吉',
					share_content: '快来加入爱安吉app，一起玩！',
					share_url: '',
					share_pic: ''
				},
				//分享数数组
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			
			this.shareInfo.share_url = this.globalUrl2+'/wenlan/aianjidownload/index.html';
			this.version = plus.runtime.version;
		},
		methods: {
			get_main_version: function() {
				var that = this;
				var url = '/main/get_main_version.php';
				var data = {
				
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data[0].resultid == 1) { //有更新
						uni.showModal({
							title: res.data[0].msg,
							content: res.data[0].content,
							success: function(showResult) {
								if (showResult.confirm) {
									uni.navigateTo({
										url: '../webview/webview?url=' + res.data[0].update_url2
									})
								}
							}
						});
					} else {
						uni.showModal({
							content: res.data[0].msg,
							showCancel: false
						});
					}
				});
			},
			openImage: function() {
				var urls = ['../../static/2code.jpg'];
				this.previewImage(urls, 0);
			},
			share_app: function() {
				this.$refs.imsg.togglePopup('bottom', 'share');
			}
		}
	}
</script>

<style scoped>
	.logo {
		width: 150upx;
		height: 150upx;
		margin-top: 64rpx;
	}

	.version {
		margin-top: 10upx;
		margin-bottom: 50upx;
		color: #A8A8A8;
		font-size: 32upx;
	}

	.icon {
		width: 28rpx;
		height: 28rpx;
	}

	.txt {
		font-size: 30rpx;
		margin-left: 16rpx;
	}

	.t-wrap {
		padding: 24rpx 32rpx;
	}

	.phone {
		color: #A8A8A8;
		margin-right: 16rpx;
		font-size: 24rpx;
	}

	.copyright {
		position: absolute;
		width: 100%;
		bottom: 50upx;
		text-align: center;
		color: #A8A8A8;
	}

	.scanner {
		width: 300upx;
		height: 300upx;
		margin: 32upx auto 0 auto;
	}
</style>
