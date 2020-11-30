<template>
	<view>
		<u-swiper v-if="swiperNewsData != ''" :list="swiperNewsData" name="pic" height="240" :effect3d="false" :autoplay="autoplay"
		 :mode="mode" @click="listClick"></u-swiper>
	</view>
</template>

<script>
	export default {
		//category_id 1:健康医疗;2:服务模块;3:发布模块;4:融媒体模块;5,看安吉;6,美食;7,数字电视;8:招聘广告;9,保洁服务;10,快递服务
		props: ["category_id"],
		data() {
			return {
				//轮播
				swiperNewsData: [],
				autoplay: true,
				mode: "round",
				swiperNewsData: [],
			};
		},
		created: function() {
			this.get_main_pic();
		},
		methods: {
			get_main_pic: function() { //获取广告图片
				var that = this;
				var url = '/revision/get_main_pic.php';
				var data = {
					category_id: that.category_id,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.swiperNewsData = res.data.data;
				})
			},
			listClick: function(index) {  //打开广告图片
				var link = this.swiperNewsData[index].link;
				if(link != '') {
					uni.navigateTo({
						url: link
					})
				}
			}
		}
	}
</script>

<style>

</style>
