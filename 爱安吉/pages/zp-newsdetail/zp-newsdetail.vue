<template>
	<view class="container">

		<view class="news_wrap">
			<view v-html="data.title" class="news_title">
			</view>
			<view v-html="data.create_time" class="create_date">
			</view>
		</view>

		<!-- <jyf-parser :html="data.content" ref="article"></jyf-parser> -->
		<view class="content-box">
					<rich-text :nodes="data.content" class="content-text"></rich-text>
		<image :src="data.thumb" mode="aspectFill" class="content-img"></image>
		</view>


		<!-- <view class="click_num">{{data.click_num}}</view> -->

		

	</view>
</template>

<script>
	import MD5 from '../../common/MD5.js'
	export default {
		components: {
		},
		data() {
			return {
				data: [],
				article_id: '',
				news_content: '',
				type: '',
			};
		},
		onShow() {},
		onLoad(options) {
			this.article_id = options.article_id;

			this.get_news_detail_content();
		},
		methods: {
			get_news_detail_content: function() {
				var that = this;
				var url = that.globalUrl + '/ajzp/articledetial.php';
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
						article_id:that.article_id,
						timestamp: timestamp,
						sign: signature,
					},
					success: (res) => {
						that.data = eval('(' + res.data + ')').data[0];
						
						// that.data = res.data.data;
						console.log(that.data)
						//that.news_content = data[0].news_content2
						// that.$refs.article.setContent(data[0].news_content2);
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
		}
	}
</script>

<style scoped lang="less">
	.news_wrap {
		border-bottom: 1upx solid #EEEEEE;
		padding: 22upx 0;
		margin-bottom: 20upx;
	}

	.news_title {
		font-weight: bold;
		font-size: 36upx;
		margin: 0 22upx;
	}

	.create_date {
		font-size: 30upx;
		margin: 0 22upx;
		color: #A8A8A8;
		margin-top: 20upx;
		text-align: right;
	}


	.num {
		color: #FFFFFF;
		font-size: 0.7em;
	}
	.content-img{
	width: 100%;
	height: 200rpx;
	margin: 14rpx auto;
	}
	.content-box{
		width: 92%;
		margin: 0 auto;
	}
	.content-text {
		font-size: 28rpx;
	}
</style>
