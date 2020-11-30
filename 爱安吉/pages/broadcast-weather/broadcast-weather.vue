<template>
	<view class="weather">
		{{weather}}
	</view>
</template>

<script>
	export default{
		data(){
			return{
				weather:""
			}
		},
		onLoad() {
			this.weather_forecast();
		},
		methods:{
			weather_forecast:function(){
				var that = this;
				var url = '/broadcast/get_notice.php';
				var data ={
				}
				that.globalRequest(url,data,'POST','JSON','',function(res){
					console.log(res);
					that.weather = res.data.data[0].notice_content
				})
			}
		}
	}
</script>

<style>
	.weather{
		padding:15upx 15upx;
	}
</style>
