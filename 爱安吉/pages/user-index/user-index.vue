<template>
	<view>
		<view class="ub ub-ac user-wrapper">
			<u-upload :custom-btn="true" ref="uUpload" :deletable="true" :show-upload-list="showUploadList" :action="action"
			 :name="name" :max-count="maxCount" @on-success="uploadedSuccess" @on-remove="onRemove">
				<view slot="addBtn" class="user-img">
					<u-icon name="photo" size="80" color="#c0c4cc"></u-icon>
				</view>
			</u-upload>
			<view class="user-info">
				<view class="user-nick">{{userInfo.user_nick}}</view>
				<view class="user-level">LV.3</view>
			</view>
		</view>
		<view class="ub">
			<view class="ub ub-ver ub-ac item">
				<view class="value">2109</view>
				<view class="key">云豆子</view>
			</view>
			<view class="ub ub-ver ub-ac item">
				<view class="value">{{userInfo.points}}</view>
				<view class="key">我的积分</view>
			</view>
			<view class="ub ub-ver ub-ac item">
				<view class="value">2109</view>
				<view class="key">我的邀请</view>
			</view>
			<view class="ub ub-ver ub-ac item">
				<view class="value">Tv16sn</view>
				<view class="key">邀请码</view>
			</view>
		</view>

		<!---分割线-->
		<u-gap height="8" bg-color="#EEEEEE"></u-gap>

		<!--个人中心模块上部-->
		<u-grid :col="4" :border="false">
			<u-grid-item v-for="(arr, i) in p_module_up" :key="i" @click="handleMainModuel(arr);">
				<image :src="arr.icon" class="m-icon"></image>
				<view class="key">{{arr.module_name}}</view>
			</u-grid-item>
		</u-grid>

		<!---分割线-->
		<u-gap height="8" bg-color="#EEEEEE"></u-gap>

		<!--个人中心模块下部-->
		<view class="ub ub-ac ubb t-wrap" v-for="(arr, i) in p_module_down" :key="i" @click="handleMainModuel(arr);">
			<image v-if="arr.icon != ''" :src="arr.icon" class="icon"></image>
			<view class="ub-f1 txt">{{arr.module_name}}</view>
			<view class="phone">{{arr.notice}}</view>
			<image src="../../static/user/more.png" class="icon"></image>
		</view>

		<view class="btn-big mtb" @click="exit_login()();">
			<view class="btn-big-txt">退出登录
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				/*上传图片start*/
				action: '',
				showUploadList: true,
				// 如果将某个ref的组件实例赋值给data中的变量，在小程序中会因为循环引用而报错
				// 这里直接获取内部的lists变量即可
				lists: [{
					url: ''
				}],
				name: 'filename',
				maxCount: 1,
				/*上传图片end*/

				userInfo: [], //用户信息

				p_module_up: [], //个人中心模块上部
				p_module_down: [], //个人中心模块下部

			}
		},
		// 只有onReady生命周期才能调用refs操作组件
		onReady() {
			//得到整个组件对象，内部图片列表变量为"lists"
			this.lists = this.$refs.uUpload.lists;
		},
		onShow() {
			/*获取用户信息start*/
			//	this.lists = [];
			if (uni.getStorageSync('user_id') == '') {
				uni.showModal({
					content: '请先登录',
					success: (showResult) => {
						if (showResult.confirm) {
							uni.navigateTo({
								url: '../login/login'
							});
						} else {
							uni.switchTab({
								url: '../index/index'
							})
						}
					}
				});
			} else {
				this.user_searchInfo();
			}
			/*获取用户信息end*/
		},
		onLoad() {
			/*上传服务器路径start*/
			this.action = this.getUploadImgUrl();
			/*上传服务器路径end*/

			/*获取个人中心模块start*/
			this.get_main_personal_center_new();
			/*获取个人中心模块end*/
		},
		methods: {
			//退出登录start
			exit_login: function() {
				uni.clearStorage();
				uni.clearStorageSync();
				uni.switchTab({
					url: '../index/index'
				});
			},
			//退出登录end
			onRemove: function(index, lists, name) {
				this.user_modify_headportrait_del();
			},
			//修改用户头像
			uploadedSuccess: function(res, index, lists, name) {
				var that = this;
				var url = '/main/user_modify_headportrait.php';
				var data = {
					pics: res.data.pic_path
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						uni.showToast({
							title: res.data.msg,
							duration: 2000,
							icon: 'none'
						});
					}
				})
			},
			//删除用户头像
			user_modify_headportrait_del: function() {
				var that = this;
				var url = '/main/user_modify_headportrait_del.php';
				var data = {

				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						//	that.user_searchInfo();
					}
				})
			},
			//获取用户信息
			user_searchInfo: function() {
				var that = this;
				var url = '/user/getUserInfo';
				var data = {};
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						that.lists[0] = {
							url: res.data.data.headimg
						}
						that.userInfo = res.data.data;
					} else {
						uni.showToast({
							title: res.data.msg,
							duration: 1200,
							icon: 'none'
						});
					}
				}, "globalUrlNew");
			},
			//获取个人中心模块
			get_main_personal_center_new: function() {
				var that = this;
				var url = '/main/get_main_personal_center_new.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.p_module_up = res.data.data[0];
					that.p_module_down = res.data.data[1];
				})
			}
		}
	}
</script>

<style scoped>
	.user-wrapper {
		margin: 0 24rpx;
	}

	.user-img {
		width: 112rpx;
		height: 112rpx;
		border-radius: 100%;
		margin-left: 24rpx;
	}

	.user-info {
		margin-left: 32rpx;
	}

	.user-nick {
		font-size: 36rpx;
	}

	.user-level {
		font-size: 32rpx;
		color: #f27714;
		margin-top: ;
	}

	.item {
		margin: 40rpx 0;
	}

	.m-icon {
		width: 56rpx;
		height: 56rpx;
	}

	.key {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}

	.value {
		font-weight: bold;
		font-size: 36rpx;
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

	/* 退出登录 */
	.mtb {
		margin: 48rpx 24rpx 0 24rpx;
	}
</style>
