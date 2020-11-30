<template>
	<view class="ub ub-ac lab-wrapper">
		<image src="../static/circle.png" class="circle"></image>
		<view class="ub-f1 lab-txt">{{name}}</view>
		<view class="uni-color-primary uni-font-size-sm" @click="handleFun(fun)">{{more}}</view>
	</view>
</template>

<script>
	export default {
		props: ["name", "more", "fun"],
		data() {
			return {
	
			}
		},
		created: function() {
		},
		methods: {
			//fun为父组件传过来的函数名
			handleFun: function(fun) {
			    this.$emit(fun)
			},
		}
	}
</script>

<style scoped>
	.lab-wrapper {
		padding: 16rpx 24rpx;
	}
	
	.circle {
		width: 18rpx;
		height: 18rpx;
	}
	
	.lab-txt {
		font-size: 36rpx;
		line-height: 50rpx;
		letter-spacing: 0.6rpx;
		color: #060606;
		margin-left: 8rpx;
		font-weight: bold;
	}
</style>
