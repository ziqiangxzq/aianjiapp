<template>
	<view class="container" :style="'height:'+ screenHeight +'px !important;'">
		<view class="mode-box" v-for="(item,index) in modedata" @click="golist(item.category_id,item.category_name)">
			<image :src="item.pic" class="mode-img"></image>
			<view class="mode-text">{{item.category_name}}</view>
		</view>
	</view>
</template>

<script>
	import MD5 from '../../common/MD5.js'
	export default{
		data(){
			return{
				 screenHeight: '',
				modedata:[]
			}
		},
		onLoad(options) {
			this.getmode()
			 this.screenHeight = uni.getSystemInfoSync().windowHeight;
			 uni.setNavigationBarTitle({
			 	title: options.module_name
			 })
			 console.log(options)
		},
		methods:{
			getmode:function(){
				
					var that = this;
					var url = that.globalUrl + '/help/get_help_phone_category.php';
					var timestamp = Date.parse(new Date())/1000;
					var s = timestamp+"32dd3c0eb6340a932a990e5832a0d2cf";
					var signature = MD5(s);
					uni.request({
						url: url,
						dataType: 'text',
						method: "POST",
						header: {
							'content-type': 'application/x-www-form-urlencoded'
						},
						data: {

						},
						success: (res) => {
							that.modedata = eval('(' + res.data + ')');
						},
						fail: (err) => {}, 
						complete: () => {}
					});
			},
			golist:function(a,b){
				uni.navigateTo({
					url: '../telephone-list/telephone-list?pagetitle=' + b +'&category_id='+a,
				});
			}
		}
	}
</script>

<style>
	.container {
		border-top: 2rpx solid #e5e5e5 ;
		font-size:0rpx;
	}
	.mode-box{
		/* position: fixed; */
		display:inline-block;
		width: 25%;
		height: 200rpx;
		border-right: 2rpx solid #ececec;
		border-bottom: 2rpx solid #ececec;
		top: 0rpx;
		text-align: center;
	}
	.mode-img{
		margin-top: 40rpx;
		width: 64rpx;
		height: 64rpx;
		
	}
	.mode-text{
		font-size:28rpx;
		margin-top: 10rpx;
		color: #888888;
	}
</style>
