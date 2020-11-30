<template>
	<view>
		<view v-if="newsListData != ''" v-for="(arr, index) in newsListData" :key="index">
			<!--是否为订阅号新闻-->
			<view class="ub ub-ac ub-pc news_wrapper" v-if="arr.news_type == 2">
				<u-image :src="arr.category_icon" shape="circle" :lazy-load="true" width="80rpx" height="80rpx">
				</u-image>
				<view class="ml16 ub-f1 category_name" v-html="arr.category_name"></view>
				<is-subscribe :newsArr="arr"></is-subscribe>
			</view>
			<!--是否为订阅号新闻-->

			<!--视频-->
			<view class="ub ub-ver ubb bc-border news_wrapper" v-if="arr.news_type_id == 5">
				<video :poster="arr.video_pic" :src="arr.video_code" class="big_pic_video" x5-video-player-type="h5-page"></video>
				<view class="ub ub-ver ub-f1">
					<view class="mt16">
						<image v-if="arr.label_icon != ''" :src="arr.label_icon" class="top " style="float:left;display: block;" />
						<view class="news_title" v-html="arr.news_title">
						</view>
					</view>
					<view class="ub ub-ac mt16">
						<view class="ub ub-ae create_date">
							{{arr.create_date}}
						</view>
						<u-icon name="zhuanfa" color="#a8a8a8" @click="shareVideo(arr);"></u-icon>
					</view>
				</view>
			</view>
			<!--视频-->

			<!--缩略图-->
			<view class="ub ubb bc-border news_wrapper" v-else-if="arr.if_miui == 0" @click="open_news_detail(arr)">
				<view class="ub ub-ver ub-f1 mr16">
					<view>
						<image v-if="arr.label_icon != ''" :src="arr.label_icon" class="top" style="float:left;display: block;" />
						<view class="news_title" v-html="arr.news_title">
						</view>
					</view>
					<view class="ub ub-ae">
						<view class="ub create_date">
							{{arr.create_date}}
						</view>
					</view>
				</view>
				<u-image :src="arr.pic_uri[0]" :lazy-load="true" width="228" height="152rpx" border-radius="4rpx">
					<u-loading slot="loading"></u-loading>
				</u-image>
			</view>
			<!--缩略图-->

			<!--组图-->
			<view class="ub ub-ver ubb bc-border news_wrapper" v-else-if="arr.if_miui == 1" @click="open_news_detail(arr)">
				<view class="ub ub-ver ub-f1">
					<view>
						<image v-if="arr.label_icon != ''" :src="arr.label_icon" class="top " style="float:left;display: block;" />
						<view class="news_title" v-html="arr.news_title">
						</view>
					</view>
					<view class="ub ub-ac mt16">
						<view class="ub ub-ae create_date">
							{{arr.create_date}}
						</view>
					</view>
				</view>
				<view class="ub mt16">
					<u-image :src="arr.pic_uri[0]" :lazy-load="true" width="30%" height="152rpx" border-radius="4rpx">
						<u-loading slot="loading"></u-loading>
					</u-image>
					<view style="width: 5%;"></view>
					<u-image :src="arr.pic_uri[1]" :lazy-load="true" width="30%" height="152rpx" border-radius="4rpx">
						<u-loading slot="loading"></u-loading>
					</u-image>
					<view style="width: 5%;"></view>
					<u-image :src="arr.pic_uri[2]" :lazy-load="true" width="30%" height="152rpx" border-radius="4rpx">
						<u-loading slot="loading"></u-loading>
					</u-image>
				</view>
			</view>
			<!--组图-->

			<!--大图-->
			<view class="ub ub-ver ubb bc-border news_wrapper" v-else-if="arr.if_miui == 2" @click="open_news_detail(arr)">
				<u-image :src="arr.pic_uri[0]" :lazy-load="true" width="100%" height="320rpx" border-radius="4rpx">
					<u-loading slot="loading"></u-loading>
				</u-image>
				<view class="ub ub-ver ub-f1">
					<view class="mt16">
						<image v-if="arr.label_icon != ''" :src="arr.label_icon" class="top " style="float:left;display: block;" />
						<view class="news_title" v-html="arr.news_title">
						</view>
					</view>
					<view class="ub ub-ac mt16">
						<view class="ub ub-ae create_date">
							{{arr.create_date}}
						</view>
					</view>
				</view>
			</view>
			<!--大图-->

			<!--无图-->
			<view class="ub ubb bc-border news_wrapper" v-else-if="arr.if_miui == 3" @click="open_news_detail(arr)">
				<view class="ub ub-ver ub-f1 mr16">
					<view class="ub ub-ver ub-f1 news_title" v-html="arr.news_title">
					</view>
					<view class="ub ub-ae">
						<image v-if="arr.icon != ''" :src="arr.icon" class="top mr16" />
						<view class="ub create_date">
							{{arr.create_date}}
						</view>
					</view>
				</view>
			</view>
			<!--无图-->
		</view>
		<share ref="imsg" :shareInfo="shareInfo"></share>
	</view>
</template>

<script>
	import share from './share.vue'
	import isSubscribe from './is-subscribe.vue'

	export default {
		props: ["newsListData"],
		components: {
			share,
			isSubscribe,
		},
		data() {
			return {
				//分享数数组
				shareInfo: {
					share_title: '',
					share_content: '',
					share_url: '',
					share_pic: ''
				}
				//分享数数组
			}
		},
		created: function() {
			this.$on('handleChange', function() {
				console.log('something handled!');
			});
		},
		methods: {
			shareVideo: function(arr) {
				this.get_news_detail_content(arr.news_id)
			},
			get_news_detail_content: function(news_id) {
				var that = this;
				var url = '/news/get_news_detail_content.php';
				var data = {
					news_id: news_id,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.shareInfo.share_title = res.data[0].news_title;
					that.shareInfo.share_content = res.data[0].news_title;
					that.shareInfo.share_url = that.globalUrl2 + "/m.web/news_detail_content/news_detail_content.php?news_id=" +
						news_id;
					that.shareInfo.share_pic = res.data[0].share_pic;

					that.$refs.imsg.showActionSheet('bottom', 'share');
				});
			},
		}
	}
</script>

<style scoped>
	.news_wrapper {
		padding: 20rpx 24rpx;
	}

	.news_title {
		font-size: 30rpx;
		line-height: 46rpx;
	}

	.category_name {
		font-size: 30rpx;
		color: #060606;
	}

	.top {
		width: 64rpx;
		height: 32rpx;
		margin-top: 6rpx;
		margin-right: 6rpx;
	}

	.create_date {
		font-size: 20rpx;
		color: #b3b3b3;
	}

	.mr16 {
		margin-right: 16rpx;
	}

	.mt16 {
		margin-top: 16rpx;
	}

	.ml16 {
		margin-left: 16rpx;
	}

	/*缩略图*/
	.small_pic {
		width: 228rpx;
		height: 152rpx;
		border-radius: 4rpx;
	}

	/*缩略图*/

	/*大图*/
	.big_pic {
		width: 100%;
		height: 320rpx;
		border-radius: 4rpx;
	}

	/*大图*/

	/*视频大图*/
	.big_pic_video {
		width: 100%;
		height: 380rpx;
		border-radius: 4rpx;
	}

	/*视频大图*/

	/*组图*/
	.zu_pic {
		width: 30%;
		height: 150rpx;
		border-radius: 4rpx;
		margin-right: 3%;
	}

	/*组图*/
</style>
