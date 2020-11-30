<template>
	<view class="container">
		<video :src="videosrc" controls class="video" :poster="video_pic"></video>
		<share ref="imsg" :shareInfo="shareInfo"></share>
	</view>
</template>

<script>
	import share from '../../components/share.vue'
	export default {
		components: {
			share
		},
		data() {
			return {
				contentid: '',
				listip: '',
				videosrc: '',
				video_pic: '',
				pagetitle: '',
				//分享数数组
				shareInfo: {
					share_title: '',
					share_content: '',
					share_url: '',
					share_pic: ''
				},
				//分享数数组
			}
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.pagetitle
			})
			this.shareInfo.share_title = options.pagetitle
			this.shareInfo.share_content = options.pagetitle
			this.pagetitle = options.pagetitle
			this.contentid = options.contentid
			this.getvideo()
		},

		methods: {
			getvideo: function() {
				var that = this;
				var url = that.globalUrl + '/dianbo/get_video_byid.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						contentid: that.contentid,
					},
					success: (res) => {
						that.data = eval('(' + res.data + ')')[0];
						that.videosrc = that.data.video
						that.video_pic = that.data.video_pic
						that.shareInfo.share_url = that.globalUrl2 + "/m.web/share/share_video.php?video_url=" + that.videosrc
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			onNavigationBarButtonTap(e) {
				if (e.float == 'right') {
					this.$refs.imsg.togglePopup('bottom', 'share');
				}
			},
		}
	}
</script>

<style>
	.video {
		width: 100%;
	}
</style>
