<template>
	<view>
		
	<view class="bottom-box">
		<view class="input-box" @click="getfocus()">
			说点什么吧~
		</view>
	</view>
	<view class="all-popup-box" v-if="popupstate==1" @touchmove.stop.prevent="moveHandle">
	<view class="popup-box" @click="popupstate=0;">
		</view>
		<view class="popup-box-white">
		<view class="popup-head-box">
			<text @click="popupstate=0" style="width: 110rpx; height: 70rpx; text-align: center;">取消</text>
			<text style="font-size: 34rpx;">写评论</text>
			<text style="color: #A8A8A8; width: 110rpx; height: 70rpx; text-align: center;" v-if="commentcontent==''">发布</text>
			<text style="color: #0090ff; width: 110rpx; height: 70rpx; text-align: center;" v-else @click="handleFun(fun)">发布</text>
		</view>
		<view class="textarea-box">
			<textarea value="" v-model="commentcontent" placeholder="请输入内容" :focus="focusstate" :show-confirm-bar="false" cursor-spacing="10"/>
		</view>	
		</view>
	</view>
	</view>
</template>

<script>
	export default {
		props: ["fun"],
		data() {
			return {
			commentcontent:'',
			focusstate:false,
			popupstate:0,
			}
		},
		created: function() {
		},
		methods: {
			//fun为父组件传过来的函数名
			handleFun: function(fun) {
			    this.$emit(fun,this.commentcontent)
				this.popupstate=0
			},
			moveHandle:function(){
				
			},
			getfocus:function(){
				this.popupstate=1;
				this.focusstate=false
				this.$nextTick(function(){
					this.focusstate=true
				})
			}
		}
	}
</script>

<style scoped>
	.bottom-box{
		position:fixed;
		bottom: 0;
		z-index: 10;
		width: 750rpx;
		height: 80rpx;
		border-top:1rpx solid #e7e7e7;
		background-color: #FFFFFF
	}
	.input-box{
		width: 90%;
		height: 50rpx;
		background-color: #eeeeee;
		margin: 0 auto;
		margin-top: 15rpx;
		border-radius: 25rpx;
		color: #A8A8A8;
		padding-left: 20rpx;
		line-height: 50rpx;
	}
	.all-popup-box{
		z-index: 20;
	}
	.popup-box{
		position: fixed;
		top: 0;
		width: 100%;
		height: 100%;
		z-index: 20;
		background-color: rgba(0, 0, 0, 0.4);
	}
	.popup-box-white{
		position: fixed;
		background-color: #FFFFFF;
		width: 100%;
		padding-bottom: 30rpx;
		bottom:0rpx;
		z-index: 30;
	}
	.popup-head-box{
		display: flex;
		justify-content: space-between;
		line-height: 70rpx;
	}
	textarea{
		background-color: #eeeeee;
		padding: 10rpx;
		width: 92%;
		margin: 0 auto;
		height: 100rpx;
	}
	.textarea-box{
	}
</style>
