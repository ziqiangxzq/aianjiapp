<template>
	<!-- <view>
		<video src="rtsp://113.214.19.50:554/ncg://192.168.65.2:7099:0:33062403001320018025:0:0?streamform=rtp"
		:danmu-list="danmuList">
		</video>
		<video src="rtsp://chengjie:Abc123456@101.64.235.70:556/ncg://33052300611320512627:SUB?token=&cnid=21&transcode=0"></video>
		<video src="rtsp://101.64.235.70:556/ncg://33052300611320512627:SUB?token=&cnid=21&transcode=0&user=chengjie&password=Abc123456"></video>
		<video src="rtsp://113.214.19.50:554/ncg://192.168.65.2:7099:0:33062403001320018025:0:0?streamform=rtp"></video>
		<video src="rtsp://101.64.235.70:556/ncg://10.1.7.17:7099:0:330523050024366060:0:0?streamform=rtp"></video>
	</view> -->
		<view class="container">
			<view class="fixed-box">
				
			<view class="video-box">
				<video id="myVideo" src="http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8" @error="videoErrorCallback" :danmu-list="danmuList"
				 enable-danmu danmu-btn controls class="video"></video>
			</view>
			<view class="title-box">
				评论
			</view>
			</view>
			<view class="comment-list-box">
				<view class="comment-box" v-for="item in news">
					<view class="img-name-date-box">
						<image :src="item.pics" class="head-img"></image>
						<text class="name-text uni-color-primary">{{item.user_nick}}</text>
						<text class="date-text">{{item.create_date.slice(0, 16)}}</text>
					</view>
					<view class="content-box" v-html="item.content">
						
					</view>
				</view>
				<uni-load-more :status="status" :content-text="contentText" />
			</view>
				<comment fun="releasecomment" @releasecomment="releasecomment"></comment>
		</view>
</template>
<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	import comment from '../../components/comment.vue'
	export default {
		components: {
			uniLoadMore,
			comment
		},
		data() {
			return {
				cameraIndexCode: '',
				camera_type: '',
				data: [],
				src: '',

				danmuList: [
				],
				//评论相关
				last_id: false,
				reload: false,
				status: 'more',
				news: [], //新闻
				contentText: {
					contentdown: '上拉加载更多',
					contentrefresh: '加载中',
					contentnomore: '没有更多内容了'
				},
				page: 1,
				recs: 16,
				
				commentcontent:'',
			}
		},
		onShow() {
			this.getlist();
		},
		onLoad(options) {
			this.cameraIndexCode = options.cameraIndexCode
			this.camera_type = options.camera_type
			uni.setNavigationBarTitle({
				title: options.pagetitle
			})
			this.getvideo();
			this.getdanmulist();
		},

		    onReady: function(res) {
		        this.videoContext = uni.createVideoContext('myVideo')
		    },
			onPullDownRefresh() {
				this.reload = true;
				this.last_id = false;
				this.news = [];
				this.page = 1;
				this.getlist();
			},
			onReachBottom() {
				this.status = 'more';
				this.getlist();
			},
		methods: {
			getvideo: function() {
				var that = this;
				var url = that.globalUrl + '/kananji/get_web_ip.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						cameraIndexCode: that.cameraIndexCode,
						camera_type: that.camera_type,
						user_id: uni.getStorageSync('user_id'),
					},
					success: (res) => {
						that.data = eval('(' + res.data + ')')[0];
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			getdanmulist: function() {
				var that = this;
				var url = that.globalUrl + '/kananji/get_camera_bullet_chat.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						cameraIndexCode: that.cameraIndexCode,
			
					},
					success: (res) => {
						that.danmuList = eval('(' + res.data + ')').list;
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
			
			},
			getlist: function() {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/kananji/get_camera_comment.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						cameraIndexCode: that.cameraIndexCode,
						recs:that.recs,
						page:that.page,
					},
					success: (res) => {
						var news = eval('(' + res.data + ')').list;
						console.log(news)
						for (var i = 0; i < news.length; i++) {
							that.news.push(news[i]);
						}
						if (that.reload) {
							uni.stopPullDownRefresh();
						}
						that.last_id = true;
						that.reload = false;
						if (news.length < that.recs) {
							that.status = '';
						}
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
				
			},
			sendDanmu: function() {
				this.videoContext.sendDanmu({
					text: this.commentcontent,
					color: this.getRandomColor()
				});
				this.commentcontent = '';
			},
			releasecomment:function(e) {
				//从子组件获取评论内容
				this.commentcontent=e;
				var that = this;
				var url = that.globalUrl + '/kananji/release_comment.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						cameraIndexCode: that.cameraIndexCode,
						user_id: uni.getStorageSync('user_id'),
						cameraIndexCode: that.cameraIndexCode,
						content:that.commentcontent,
						pic:'',
						
							
					},
					success: (res) => {
						var msg = eval('(' + res.data + ')');
				     uni.showToast({
				     	icon:"none",
						title:msg.msg,
				     });
					 that.reload = true;
					 that.last_id = false;
					 that.news = [];
					 that.page = 1;
					 that.getlist();
					 that.sendDanmu();
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
			},
			getRandomColor: function() {
				const rgb = []
				for (let i = 0; i < 3; ++i) {
					let color = Math.floor(Math.random() * 256).toString(16)
					color = color.length == 1 ? '0' + color : color
					rgb.push(color)
				}
				return '#' + rgb.join('')
			},
		}
	}
</script>

<style>
	.container{
	}
	.video-box{
		width: 750rpx;
		height: 450rpx;
	}
	.video {
		width: 100%;
		height: 100%;
		
	}
	.fixed-box{
		position:fixed;
		/* top: 0; */
		z-index: 1;
		background-color: #FFFFFF;
	}
	.title-box{
		width: 100%;
		font-size: 32rpx;
		margin-top: 20rpx;
		margin-left: 20rpx;
		font-weight: bold;
	}
	.comment-list-box{
		padding-top: 520rpx;
	}
	.comment-box{
		padding: 20rpx;
	}
	.head-img{
		height: 60rpx;
		width: 60rpx;
		border-radius: 30rpx;
		vertical-align:middle
	}
	.name-text{
		font-size: 26rpx;
		margin-left: 10rpx;
	}
	.date-text{
		float: right;
		color: #A8A8A8;
		font-size: 24rpx;
		line-height: 60rpx;
	}
	.content-box{
		margin-left: 70rpx;
		padding-bottom: 20rpx;
		border-bottom:1rpx solid #e7e7e7;
	}
</style>
