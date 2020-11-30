<template>
	<view>
		<web-view :webview-styles="webviewStyles" :src="url"></web-view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				url: '',

				webviewStyles: {
					progress: {
						color: '#0090ff'
					}
				}
			}
		},
		onLoad(e) {
			console.log('外链url ' + e.url)
			this.url = e.url;
		},
		methods: {}
	}
</script>

<style>
</style>
