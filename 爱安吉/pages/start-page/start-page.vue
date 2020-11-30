<template>
	<view>
		<view class="jump" @click.stop="openIndex()">跳过
			<span style="color: red;margin-left: 3rpx;">{{cut_down_time_long}}</span>
		</view>
		<u-swiper name="pic" :list="list" :height="height" interval="3500" @click="listClick"></u-swiper>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				list: [],
				height: 0,
				cut_down_time_long: 0,
				
				//推送start
				tags: ['aianji'],
				ccid: '',
				//推送end
			}
		},
		onLoad: function() {
			var _me = this;
			uni.getSystemInfo({ //获取手机屏幕高度信息，让swiper的高度和手机屏幕一样高
				success: function(res) {
					uni.setStorageSync("model", res.model);
					uni.setStorageSync("pixelRatio", res.pixelRatio);
					uni.setStorageSync("windowWidth", res.windowWidth);
					uni.setStorageSync("windowHeight", res.windowHeight);
					uni.setStorageSync("platformName", res.platform);
			
					_me.height = res.windowHeight*2;
				}
			});
			
			this.get_main_pic(); //获取启动页图片
			this.getLocation(); //获取定位
			this.openPush(); //打开推送
		},
		onReady() {
			
		},
		methods: {
			get_main_pic: function() { //获取广告图片
				var that = this;
				var url = '/revision/get_main_pic.php';
				var data = {
					category_id: 13,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.list = res.data.data;
					that.cut_down_time_long = 3*that.list.length-1;
					that.daojishi();
				})
			},
			openIndex: function() { //点击跳过
				clearInterval(this.t);
				uni.switchTab({
					url: '/pages/index/index'
				});
			},
			listClick: function(index) {  //点击轮播图片
				var link = this.list[index].link;
				if(link != '') {
					uni.switchTab({
						url: '/pages/index/index'
					});
					uni.navigateTo({
						url: link
					})
					this.stop_daojishi();
				}
			},
			daojishi: function() {
				var that = this;
				var i = that.cut_down_time_long;
				that.t = setInterval(function() {
					if (i > 0) {
						that.cut_down_time_long = i;
						i--;
					} else {
						clearInterval(that.t);
						uni.switchTab({
							url: '/pages/index/index'
						});
					}
				}, 1000);
			},
			stop_daojishi: function() {
				clearInterval(this.t);
			},
			//推送start
			openPush: function() {
				var that = this;
				var cid = plus.device.uuid;
				console.log("cid " + cid)
				var clientid;
				var timer = setInterval(function() {
					if (clientid != null && clientid != "null") {
						clearInterval(timer);
						return;
					}
					clientid = plus.push.getClientInfo().clientid;
					that.ccid = clientid;
			
					that.bindAliasAndTag(uni.getStorageSync("user_id"), that.tags);
				}, 1000);
			},
			bindAliasAndTag: function(alias, tags) {
				var isAndorid, PushManager, context, Instance, GeTuiSdk;
			
				if (plus.os.name == 'Android') {
					isAndorid = true;
				} else {
					isAndorid = false;
				}
			
				if (isAndorid) {
					PushManager = plus.android.importClass("com.igexin.sdk.PushManager");
					context = plus.android.runtimeMainActivity().getContext();
					Instance = PushManager.getInstance();
				} else {
					GeTuiSdk = plus.ios.importClass("GeTuiSdk");
				}
			
				if (isAndorid) {
					console.log('获取到cid==', Instance.getClientid(context));
					console.log('获取到版本号==', Instance.getVersion(context));
					console.log('获取到tags==', JSON.stringify(tags));
					console.log('获取到alias==', alias);
			
					//绑定别名
					Instance.bindAlias(context, alias);
			
					//绑定标签
					var Tag = plus.android.importClass("com.igexin.sdk.Tag");
					var tagParam = new Array();
					for (let i = 0; i < tags.length; i++) {
						var tag = new Tag();
						tag.setName(tags[i]);
						tagParam[i] = tag;
			
						console.log('tags[' + i + ']==', tags[i]);
					}
					console.log('tagParam==', JSON.stringify(tagParam));
					Instance.setTag(context, tagParam, Date.now() + "");
				} else {
					console.log("ios alias = " + alias)
					GeTuiSdk.bindAliasandSequenceNum(alias, alias);
					GeTuiSdk.setTags(tags);
				}
			},
			//推送end
		}
	}
</script>

<style lang="scss" scoped>
	.jump {
		position: absolute;
		top: 5%;
		z-index: 999;
		right: 2%;
		background-color: #000000;
		opacity: 0.6;
		padding: 10rpx 10rpx;
		border-radius: 10rpx;
		font-size: 26rpx;
		color: #FFFFFF;
	}
</style>
