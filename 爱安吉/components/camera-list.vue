<template>
	<view class="wrap">
		<view class="item" @click="openCameraPlay(item.cameraIndexCode,item.camera_type,item.camerName)" v-for="item in listdata">
			<image class="icon loc-l" :src="item.pic"></image>
			<view class="ub ub-ac txt-l">
				<view class="ub-f1">
					<image src="../static/camera/1.gif" class="voice"></image>
				</view>
				<view class="view-num">{{item.click_num}}人观看</view>
			</view>
			<view class="camera-name-l">{{item.camerName}}</view>
		</view>
	</view>
</template>

<script>
	export default {
		props: ["listdata"],
		data() {
			return {}
		},
		methods: {
			openCameraPlay: function(a,b,c) {
				uni.navigateTo({
					url: '../camera-play/camera-play?cameraIndexCode='+a+'&camera_type='+b+'&pagetitle='+c
				})
			}
		}
	}
</script>

<style scoped>
	.wrap {
		width: 100%;
		float: left;
	}

	.item {
		position: relative;
		width: 50%;
		float: left;
		margin-top: 24rpx;
	}

	.icon {
		width: 90%;
		height: 240rpx;
		border-radius: 8rpx;
	}

	.voice {
		width: 81rpx;
		height: 32rpx;
	}

	.loc-l {
		margin-left: 7%;
	}

	.loc-r {
		margin-left: 3%;
	}

	.txt-l {
		position: absolute;
		top: 8rpx;
		padding-left: 9%;
		padding-right: 5%;
		width: 100%;
		font-size: 24rpx;
	}
	
	.camera-name-l {
		position: absolute;
		bottom: 24rpx;
		padding-left: 9%;
		padding-right: 5%;
		width: 100%;
		font-size: 28rpx;
		color: #FFFFFF;
	}
	
	.loc-l {
		margin-left: 7%;
	}
	
	.loc-r {
		margin-left: 3%;
	}
	
	.txt-r {
		position: absolute;
		top: 8rpx;
		padding-left: 5%;
		padding-right: 9%;
		width: 100%;
		font-size: 24rpx;
	}
	
	.camera-name-r {
		position: absolute;
		bottom: 24rpx;
		padding-left: 5%;
		padding-right: 9%;
		width: 100%;
		font-size: 28rpx;
		color: #FFFFFF;
	}
	
	.view-num {
		color: #FFFFFF;
		text-align: end;
	}
</style>
