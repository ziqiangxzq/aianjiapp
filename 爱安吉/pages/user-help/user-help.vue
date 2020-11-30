<template>
	<view class="container">
		<view class="content-box">
		<view class="blank" v-if="helpcontent==''">
			暂无内容 敬请期待~
		</view>
		<rich-text :nodes="helpcontent"></rich-text>
		</view>
	</view>
</template>

<script>
	export default{
		data(){
			return{
					helpcontent:''
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
			　　title: options.module_name
			})
			this.get_content()
		},
		methods:{
			get_content: function() {
				var that = this;
				var url = that.globalUrl + '/main/get_main_help.php';
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
						that.helpcontent = eval('(' + res.data + ')')[0].content;
						console.log(that.helpcontent)
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
		}
	}
</script>

<style>
	.content-box{
		margin: 20rpx;
		font-size: 30rpx;
	}
	.blank{
		font-size: 30rpx;
		padding-top: 20rpx;
		text-align: center;
		margin-top: 20rpx;
		color: #a8a8a8;
	}
</style>
