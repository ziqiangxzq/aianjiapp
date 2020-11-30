<template>
	<!--底部分享弹窗start-->
	<uni-popup ref="share" :type="type" :custom="true" closeable="false" @change="change">
		<view class="uni-share" style="z-index: 99999999;">
			<view class="uni-share-title">分享到</view>
			<view class="uni-share-content">
				<view v-for="(item, index) in bottomData" :key="index" class="uni-share-content-box" @click="share_wx(item.name);">
					<view class="uni-share-content-image">
						<image :src="item.icon" class="image" />
					</view>
					<view class="uni-share-content-text">{{ item.text }}</view>
				</view>
			</view>
			<view class="uni-share-btn" @click="cancel('share')">取消分享</view>
		</view>
	</uni-popup>
	<!--底部分享弹窗end-->
</template>

<script>
	import uniPopup from '@/components/uni-popup/uni-popup.vue';
	export default {
		props: ["shareInfo"],
		components: {
			uniPopup
		},
		data() {
			return {
				//分享start
				bottomData: [{
					text: '微信',
					icon: '../../static/share2.png',
					name: 'hy'
				}, {
					text: '朋友圈',
					icon: '../../static/share3.png',
					name: 'pyq'
				}],
				type: '',
				//分享end
			};
		},
		methods: {
			//弹窗start
			togglePopup: function(type, open) {
				switch (type) {
					case 'top':
						this.content = '顶部弹出 popup'
						break;
					case 'bottom':
						this.content = '底部弹出 popup'
						break;
					case 'center':
						this.content = '居中弹出 popup'
						break;
				}
				this.type = type
				if (open === 'tip') {
					this.show = true
				} else {
					this.$refs[open].open()
				}
			},
			cancel(type) {
				if (type === 'tip') {
					this.show = false
					return
				}
				this.$refs[type].close()
			},
			change(e) {
				console.log(e.show)
			},
			//弹窗end
			showActionSheet: function() {
				var that = this;
				uni.showActionSheet({
				    itemList: ['微信', '朋友圈'],
				    success: function (res) {
				        if(res.tapIndex == 0) {
							that.shareFriend();
						} else {
							that.shareFriendcricle();
						}
				    },
				    fail: function (res) {
				        console.log(res.errMsg);
				    }
				});
			},
			shareFriend: function() {
				var that = this;
				//分享到微信朋友
				uni.share({
					provider: "weixin",
					scene: "WXSceneSession", //分享到聊天界面
					type: 0, //type==0图文分享
					href: this.shareInfo.share_url,
					title: this.removeHTMLTag(this.shareInfo.share_title),
					summary: this.removeHTMLTag(this.shareInfo.share_content),
					imageUrl: this.shareInfo.share_pic, //推荐使用小于20Kb的图片
					success: function(res) {
						console.log("success:" + JSON.stringify(res));
					},
					fail: function(err) {
						console.log("fail:" + JSON.stringify(err));
					}
				});
			},
			//分享到微信朋友圈
			shareFriendcricle: function() {
				var that = this;
				uni.share({
					provider: "weixin",
					scene: "WXSenceTimeline", //分享到朋友圈
					type: 0,
					href: this.shareInfo.share_url,
					title: this.removeHTMLTag(this.shareInfo.share_title),
					summary: this.removeHTMLTag(this.shareInfo.share_content),
					imageUrl: this.shareInfo.share_pic, //推荐使用小于20Kb的图片
					success: function(res) {
						console.log("success:" + JSON.stringify(res));
					},
					fail: function(err) {
						console.log("fail:" + JSON.stringify(err));
					}
				});
			},
			share_wx: function(name) {
				if(this.shareInfo.share_pic == '') {
					this.shareInfo.share_pic = this.globalUrl2+'/news/share_wx.png';	
				}
				if (name == 'hy') {
					this.shareFriend();
				} else if (name == 'pyq') {
					this.shareFriendcricle();
				}
			},
			removeHTMLTag: function(str) {
				str = str.replace(/<\/?[^>]*>/g, '');
				//去除HTML tag
				str = str.replace(/[ | ]*\n/g, '\n');
				//去除行尾空白
				//str = str.replace(/\n[\s| | ]*\r/g,'\n'); //去除多余空行
				str = str.replace(/&nbsp;/ig, '');
				//去掉&nbsp;
				return str;
			},
		}
	}
</script>

<style>
</style>
