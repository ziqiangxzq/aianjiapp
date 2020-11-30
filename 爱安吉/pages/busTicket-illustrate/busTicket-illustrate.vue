<template>
	<view class="container">
		<view class="content-box">
			<rich-text :nodes="illustratecontent"></rich-text>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				illustratecontent: ''
			}
		},
		onLoad() {
			this.get_content()
		},
		methods: {
			get_content: function() {
				var that = this;
				var url = that.globalUrl + '/ticket/get_notice_by_module_name.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						module_name: 90
					},
					success: (res) => {
						that.illustratecontent = eval('(' + res.data + ')')[0].notice_content;
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
		}
	}
</script>

<style>
	.content-box {
		margin: 20rpx;
		font-size: 30rpx;
	}
</style>
