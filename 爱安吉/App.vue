<script>
	export default {
		data() {
			return {
				//新闻语音路径start
				innerAudioContext: '',
				//新闻语音路径end
			}
		},
		onLaunch: function() {
			var _that = this;
			uni.setStorageSync("if_message", 1); //ios推送相关
			console.log('App Launch');
			// #ifdef APP-PLUS
			// 锁定屏幕方向
			plus.screen.lockOrientation('portrait-primary'); //锁定

			//监听click事件，用户从消息中心点击触发的 从系统消息中心点击消息启动应用事件
			plus.push.addEventListener("click", function(msg) {
				//根据payload传递过来的数据，打开一个详情
				var payload = msg.payload;
				//{"title":"222","content":"333"}

				if (payload) {


					// payload 按照规范是 Object，但实际推送过来有可能是 String，需要多一步处理；
					if (typeof payload === 'string') {
						payload = JSON.parse(payload);
					}


					uni.showModal({
						content: payload.content
					})

					if (typeof payload === 'object') {
						
						if (payload.push_type == "broadcast") { //广播
							_that.innerAudioContext = uni.createInnerAudioContext();
							_that.innerAudioContext.autoplay = true;
							_that.innerAudioContext.src = payload.mp3_url;
							console.log(_that.innerAudioContext.src)
							_that.innerAudioContext.onPlay(() => {
								console.log('开始播放');
							});
							_that.innerAudioContext.onError((res) => {
								console.log(res.errMsg);
								console.log(res.errCode);
							});
						}
						
						if (payload.url) {
							if (plus.os.name != 'iOS') {
								setTimeout(function(res) {
									uni.navigateTo({
										url: payload.url
									})
								}, 1000)
							} else {
								setTimeout(function(res) {
									uni.navigateTo({
										url: payload.url
									})
								}, 3000)
							}
						}
					}
				}
			}, false);

			//监听receive事件  应用从推送服务器接收到推送消息事件
			plus.push.addEventListener("receive", function(msg) {

				//根据payload传递过来的数据，打开一个详情
				var payload = msg.payload;


				if (payload) {
					//如透传消息不符合格式，则“payload”属性为string类型
					//这里的示例以json字符串去解析，实际上也可以做字符串匹配
					if (typeof(payload) == "string") {
						try {
							payload = JSON.parse(payload);
						} catch (error) {
							console.log(error);
						}
					}

					uni.showModal({
						content: payload.content
					})
console.log("payload.push_type="+payload.push_type)
					if (payload.push_type == "broadcast") { //广播
						_that.innerAudioContext = uni.createInnerAudioContext();
						_that.innerAudioContext.autoplay = true;
						_that.innerAudioContext.src = payload.mp3_url;
						console.log(_that.innerAudioContext.src)
						_that.innerAudioContext.onPlay(() => {
							console.log('开始播放');
						});
						_that.innerAudioContext.onError((res) => {
							console.log(res.errMsg);
							console.log(res.errCode);
						});

						if (payload.url) {
							if (plus.os.name != 'iOS') {
								setTimeout(function(res) {
									uni.navigateTo({
										url: payload.url
									})
								}, 1000)
							} else {
								setTimeout(function(res) {
									uni.navigateTo({
										url: payload.url
									})
								}, 3000)
							}
						}
					}

					if (payload.push_type != "broadcast") {
						if (plus.os.name != 'iOS') {
							plus.push.createMessage(payload.content, payload);
						} else {
							//iOS应用正处于前台运行时收到推送，也触发receive事件，此时payload为json对象
							if (uni.getStorageSync("if_message") == 1) {
								console.log("JSON.stringify(payload)=" + JSON.stringify(payload))
								plus.push.createMessage(msg.title, JSON.stringify(payload));
							}
							uni.setStorageSync("if_message", 0);
						}
					}
				}

			}, true);

			// 检测升级
			var that = this;
			var url = '/main/get_main_version.php';
			var data = {}
			that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
				if (res.data[0].resultid == 1) { //有更新
					uni.showModal({
						title: res.data[0].msg,
						content: res.data[0].content,
						success: function(showResult) {
							if (showResult.confirm) {
								uni.navigateTo({
									url: '../webview/webview?url=' + res.data[0].update_url2
								})
							}
						}
					});
				}
			});
			// #endif
		},
		onShow: function() {
			console.log('App Show')

		},
		onHide: function() {
			console.log('App Hide')
			this.innerAudioContext.destroy();
		},
	}
</script>

<style lang="scss">
	@import "uview-ui/index.scss";

	/*布局相关 start*/
	.ub {
		/*横排*/
		display: flex;
		flex: 1;
		flex-direction: row;
	}

	.ub-ver {
		/*竖排*/
		display: flex;
		flex: 1;
		flex-direction: column;
	}

	.ub-f1 {
		flex: 1;
	}

	.ub-ac {
		align-items: center;
	}

	.ub-ae {
		align-items: flex-end;
	}

	.ub-pc {
		-webkit-box-pack: center;
		box-pack: center;
	}

	.ub-pe {
		-webkit-box-pack: end;
		box-pack: end;
	}

	.ub-pj {
		-webkit-box-pack: justify;
		box-pack: justify;
	}

	.ub-ver {
		-webkit-box-orient: vertical;
		box-orient: vertical;
	}

	/*布局相关 end*/

	/*按钮相关 start*/
	.btn-big {
		display: flex;
		background-color: $uni-btn-primary;
		height: $uni-btn-big;
		border-radius: $uni-btn-radius;
	}

	.btn-big-txt {
		color: #FFFFFF;
		font-size: $uni-btn-big-size;
		margin: auto auto;
	}

	.btn-small {
		display: flex;
		background-color: $uni-btn-primary;
		height: $uni-btn-big;
	}

	/*按钮相关 end*/

	/*input相关 start*/
	.inpt {
		flex: 1;
		font-size: $uni-border-size;
		height: $uni-btn-big;
		padding: 0 $uni-border-size;
	}

	.inpt-radius {
		border-radius: $uni-btn-radius;
	}

	.uba {
		border: 1rpx solid $uni-border-color;
	}

	.ubb {
		border-bottom: 1rpx solid $uni-border-color;
	}

	/*input相关 end*/

	/*颜色相关 start*/
	page {
		color: #060606;
	}

	.uni-color-primary {
		color: $uni-color-primary;
	}

	.uni-text-color-grey {
		color: $uni-text-color-grey;
	}

	/*颜色相关 end*/

	/*字体相关 start*/
	.uni-font-size-sm {
		font-size: $uni-font-size-sm;
	}

	.uni-font-size-base {
		font-size: $uni-font-size-base;
	}

	.uni-font-size-lg {
		font-size: $uni-font-size-lg;
	}

	/*字体相关 end*/

	.clear-both {
		clear: both;
	}

	.uni-video-video {
		z-index: -100;
	}

	video {
		z-index: -100;
	}

	/* 底部分享 start*/
	.uni-share {
		background: #fff;
	}

	.uni-share-title {
		line-height: 60upx;
		font-size: 24upx;
		padding: 15upx 0;
		text-align: center;
	}

	.uni-share-content {
		display: flex;
		flex-wrap: wrap;
		padding: 15px;
	}

	.uni-share-content-box {
		display: flex;
		flex-direction: column;
		align-items: center;
		width: 25%;
		box-sizing: border-box;
	}

	.uni-share-content-image {
		display: flex;
		justify-content: center;
		align-items: center;
		width: 100upx;
		height: 100upx;
		overflow: hidden;
		border-radius: 10upx;
	}

	.uni-share-content-image .image {
		width: 100%;
		height: 100%;
	}

	.uni-share-content-text {
		font-size: 26upx;
		color: #333;
		padding-top: 5px;
		padding-bottom: 10px;
	}

	.uni-share-btn {
		height: 90upx;
		line-height: 90upx;
		border-top: 1px #f5f5f5 solid;
		text-align: center;
		color: #666;
	}

	/* 底部分享 end*/
</style>
