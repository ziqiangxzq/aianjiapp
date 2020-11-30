<template>
	<view class="ub ub-ac lab-wrapper">
			<swiper class="swiper" circular :indicator-dots="indicatorDots" :autoplay="autoplay" :display-multiple-items="shownum" :interval="interval" :duration="duration">
				<swiper-item v-for="item in imgarr" @click="openurl(item.url)">
					<image class="swiper-item" mode="aspectFill" style="width: 100%;" :src="item.src"></image>
					<!-- <view class="swiper-item green">A</view> -->
				</swiper-item>
			</swiper>
	</view>
</template>

<script>
	export default {
		props: ["imgarr","shownum"],
		data() {
			return {
			indicatorDots:false,
			autoplay: false,
			interval: 3000,
			duration: 1500,
			showwidth:''
			}
		},onLoad:function(){
			//this.showwidth="width:"+100/this.shownum+"%"
		}
		,
		created: function() {
		},
		methods: {
		openurl:function(a){
			if(a!=''){
				window.location.href=a;
			}
			console.log(a)
		}
		}
	}
</script>

<style scoped>
	.swiper {
		height: 250rpx;
		margin-left: 25rpx;
		overflow: hidden;
		width:calc(100% - 50rpx);
	}
	
	.swiper-item{
		height: 250rpx;
		border-radius: 20rpx;
		overflow: hidden;
	}
	.slideunit{
		position: relative;
		width: 100%;
		height:250rpx;
		display: inline-block;
	}
	.green{
		background-color: #3DAF42;
	}
	.red{
		background-color: red;
	}
	.blue{
		background-color: #199BFF;
	}
</style>
