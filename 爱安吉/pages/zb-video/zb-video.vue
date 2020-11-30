<template>
	<view class="container">
		<video :src="videosrc" controls class="video" :poster="pic_uri"></video>
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
			return{
				videosrc:'',
				
				//分享数数组
				shareInfo: {
					share_title: '',
					share_content: '',
					share_url: '',
					share_pic: ''
				},
				//分享数数组
				
				pic_uri:'',
			}
		},
		onLoad(options) {
			this.videosrc = options.video_uri
			this.pic_uri = options.pic_uri
			this.shareInfo.share_url = this.globalUrl2 + "/m.web/share/share_video.php?video_url=" + options.video_uri
			this.shareInfo.share_title = options.title
			this.shareInfo.share_content = options.title
		},
		methods:{
			onNavigationBarButtonTap(e) {
				if (e.float == 'right') {
					this.$refs.imsg.togglePopup('bottom', 'share');
				}
			},
		}
		
	}
</script>

<style>
	.video{
		width: 100%;
	}
</style>
