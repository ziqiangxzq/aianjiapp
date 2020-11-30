<template>
	<view>
		<view class="resultbox" v-html="content"></view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				content:''
			}
		},
        onLoad() {
        	this.getpointrule()
        }
		,
		methods: {
			getpointrule:function(){
				//https://www.meilianji.cn/web/main/get_notice_by_module_name.php?module_name=23
				uni.request({	
					url:"https://www.meilianji.cn/web/main/get_notice_by_module_name.php",
					dataType:"JSON",
					data:{module_name:23},
					method:'POST',
					header:{
					'content-type':'application/x-www-form-urlencoded'	
					},
					success:res=>{
						//console.log(res.data[0].notice_content)
						this.content=res.data[0].notice_content;
					}
				})
			}
		}
	}
</script>

<style>
.resultbox{
	position: relative;
	width:100%;
	padding:24rpx;
	color: #444;
	line-height:40rpx;
}
</style>
