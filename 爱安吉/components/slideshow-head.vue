<template>
	<view class="ub ub-ac lab-wrapper">
			<swiper class="swiper" circular :indicator-dots="indicatorDots" :autoplay="autoplay" :interval="interval" :duration="duration">
				<swiper-item v-for="item in imgarr" @click="openurl(item.type,item.modelurl,item.url)">
					<image class="swiper-item" mode="aspectFill" style="width: 100%;" :src="item.src"></image>
					<!-- <view class="swiper-item green">A</view> -->
				</swiper-item>
			</swiper>
	</view>
</template>

<script>
	export default {
		props: ["imgarr"],
		data() {
			return {
			indicatorDots:false,
			autoplay: true,
			interval: 4000,
			duration: 1500	
			}
		},
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
		width: 100%;
	}
	
	.swiper-item{
		height: 250rpx;
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
