<template>
	<view>
		<view class="ubb title wrap">
			<view class="news_title" v-html="data.news_title"></view>
			<view class="ub ub-f1 ub-ac">
				<view class="create_date ub-f1">{{data.create_date}}</view>
				<view class="ub-ac uba voice-wrap" @click="playMp3()">
					<view class="ub ub-ac">
						<view>
							<u-loading :color="color" :show="if_play_mp3"></u-loading>
							<u-icon name="volume-up-fill" :color="color" :style="{display: if_show_icon}"></u-icon>
						</view>
						<view class="play-txt uni-color-primary">语音播报</view>
					</view>
				</view>
			</view>
		</view>

		<!--富文本内容start-->
		<jyf-parser ref="article"></jyf-parser>
		<!--富文本内容end-->

		<!--阅读数start-->
		<view style="padding: 0 32upx;color: #A8A8A8;padding-bottom: 50rpx;">{{click_num}}</view>
		<!--阅读数end-->

		<!--分享点赞start-->
		<view class="ub ub-f1">
			<view class="ub ub-f1"></view>
			<view @click="add_collection()">
				<image v-if="data.is_collect == 0" id="collect" src="../../static/collect.png" class="icon" />
				<image v-if="data.is_collect == 1" id="collect" src="../../static/collected.png" class="icon" />
			</view>
			<view style="margin-left: 48rpx;" @click="add_likes()">
				<view class="ub">
					<image v-if="data.is_likes == 0" id="like" src="../../static/good.png" class="icon" />
					<image v-if="data.is_likes == 1" id="like" src="../../static/gooded.png" class="icon" />
					<view class="num">{{data.likes_num}}</view>
				</view>
			</view>
		</view>
		<!--分享点赞end-->

		<!--评论列表start-->
		<lab name="精选评论"></lab>
		<u-empty v-if="comment_data.length == 0" :text="if_comment" mode="favor"></u-empty>
		<view v-for="(arr, index) in comment_data" :key="index" class="wrap ubb">
			<view class="comment_front">
				<view>
					<image :src="arr.pics" class="pics"></image>
				</view>

				<view class="comment_mid">
					<view class="user_nick">{{arr.user_nick}}</view>
					<view class="comment" v-html="arr.comment"></view>
				</view>
			</view>

			<view class="create_date_comment">{{arr.create_date}}
			</view>
		</view>
		<!--评论列表end-->

		<view style="height: 120rpx;background-color: #FFFFFF;"></view>

		<!--评论框start-->
		<comment fun="releasecomment" @releasecomment="releasecomment"></comment>
		<!--评论框end-->

		<!--分享start-->
		<share ref="imsg" :shareInfo="shareInfo"></share>
		<!--分享end-->
	</view>
</template>

<script>
	import share from '../../components/share.vue'
	import lab from '../../components/lab.vue'
	import comment from '../../components/comment.vue'
	export default {
		components: {
			share,
			lab,
			comment
		},
		data() {
			return {
				data: [],
				news_id: '',

				color: '#0090ff', //语言播放按钮颜色

				show: false,

				/*评论相关start*/
				comment_data: [],
				if_comment: '暂无评论',
				/*评论相关end*/

				//分享数数组
				shareInfo: {
					share_title: '',
					share_content: '',
					share_url: '',
					share_pic: ''
				},
				//分享数数组

				//新闻语音路径start
				audio_path: '',
				innerAudioContext: '',
				if_play_mp3: false,
				if_show_icon: 'block',
				//新闻语音路径end

				click_num: '',
			};
		},
		onShow() {},
		destroyed: function() {
			console.log("destroyed")
			this.innerAudioContext.destroy();
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			})
			this.news_id = options.news_id;

			this.innerAudioContext = uni.createInnerAudioContext();
			this.get_news_detail_content();
			this.get_news_comment_list_new();
		},
		methods: {
			//获取新闻详情
			get_news_detail_content: function() {
				var that = this;
				var url = '/news/getNewsDetail';
				var data = {
					news_id: that.news_id,
				};

				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					//增加积分
					uni.showToast({
						title: '+500',
						duration: 3000,
						icon: 'success'
					});
					that.data = res.data.data;
					that.$refs.article.setContent(that.data.news_content);

					that.shareInfo.share_title = that.data.news_title;
					that.shareInfo.share_content = that.data.news_title;
					that.shareInfo.share_url = that.globalUrl2 + "/m.web/news_detail_content/news_detail_content.php?news_id=" +
						that.news_id;
					that.shareInfo.share_pic = that.data.share_pic;

					that.click_num = that.data.click_num

					that.AipSpeech();
				}, "globalUrlNew");

			},
			//获取评论
			get_news_comment_list_new: function() {
				var that = this;
				var url = '/news/get_news_comment_list_new.php';
				var data = {
					news_id: that.news_id,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.comment_data = res.data;
				});
			},
			//收藏
			add_collection: function() {
				var that = this;
				var url = '/news/setNewsCollect';
				var data = {
					news_id: that.news_id,
				};

				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						if (res.data.data.state == 1) {
							that.data.is_collect = 1;
						} else {
							that.data.is_collect = 0;
						}
					} else {
						uni.showToast({
							title: res.data.msg,
							duration: 2000,
							icon: 'none'
						});
					}
				}, "globalUrlNew");
			},
			//点赞
			add_likes: function() {
				var that = this;
				var url = '/news/setNewsLikes';
				var data = {
					news_id: that.news_id,
				};

				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.ret == 200) {
						if (res.data.data.state == 1) {
							that.data.is_likes = 1;
							that.data.likes_num = res.data.data.num;
						} else {
							that.data.is_likes = 0;
							that.data.likes_num = res.data.data.num;
						}
					} else {
						uni.showToast({
							title: res.data.msg,
							duration: 2000,
							icon: 'none'
						});
					}
				}, "globalUrlNew");
			},
			//分享
			onNavigationBarButtonTap(e) {
				if (e.float == 'right') {
					this.$refs.imsg.togglePopup('bottom', 'share');
				}
			},
			//音频播放start
			AipSpeech: function() { //获取新闻语音路径
				var that = this;
				var url = '/news/AipSpeech.php';
				var data = {
					news_id: that.news_id,
					str: that.data.news_content
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.audio_path = res.data.audio_path;
					that.innerAudioContext.src = that.audio_path;
				});
			},
			playMp3: function() {
				var that = this;
				if (!that.innerAudioContext.paused) { //音频处于播放中，需要暂停
					that.toggleMp3Status(false, "block");
					that.innerAudioContext.pause();
				} else { //音频处于暂停中，需要播放
					that.toggleMp3Status(true, "none");
					that.innerAudioContext.play();
				}

				that.innerAudioContext.onError((res) => {
					console.log(res.errMsg);
					console.log(res.errCode);
					that.if_play_mp3 = false;
					that.if_show_icon = "block";
				});
			},
			toggleMp3Status: function(if_play_mp3, if_show_icon) { //切换音频播放状态
				this.if_play_mp3 = if_play_mp3;
				this.if_show_icon = if_show_icon;
			},
			//音频播放end
		}
	}
</script>

<style scoped lang="less">
	.wrap {
		margin: 22rpx 24rpx;
		font-size: 30rpx;
		color: #060606;
	}

	.u-content {
		line-height: 56rpx;
	}

	/*头部start*/
	.news_title {
		font-size: 40rpx;
		line-height: 48rpx;
	}

	.create_date {
		color: #A8A8A8;
		margin: 24rpx 0;
	}

	.title {
		margin-bottom: 16rpx;
	}

	/*头部end*/

	/*播放按钮start*/
	.play-txt {
		font-size: 16rpx;
		margin-left: 4rpx;
	}

	.voice-wrap {
		padding: 2rpx 8rpx;
		border-color: #0090ff;
		border-radius: 8rpx;
	}

	/*播放按钮end*/

	/*评论list start*/
	.comment_front {
		display: flex;
		flex-direction: row;
	}

	.pics {
		width: 70upx;
		height: 70upx;
		border-radius: 100%;
	}

	.comment_mid {
		display: flex;
		flex-direction: column;
		flex: 1;
		margin-left: 22upx;
	}

	.create_date_comment {
		color: #A8A8A8;
		font-size: 28upx;
		text-align: right;
	}

	.user_nick {
		color: #A8A8A8;
	}

	.comment {
		margin-top: 20upx;
	}

	/*评论list end*/

	/*评论框start*/
	.comment_wrap {
		position: fixed;
		width: 100%;
		bottom: 0;
		background: #FFFFFF;
		padding: 26upx 22upx;
	}

	/*评论框end*/

	/*收藏点赞start*/
	.icon {
		width: 38rpx;
		height: 38rpx;
	}

	.num {
		margin-left: 8rpx;
		margin-right: 32rpx;
		color: #A8A8A8;
		font-size: 32rpx;
	}

	/*收藏点赞end*/
</style>
