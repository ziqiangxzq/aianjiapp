<template>
	<tv-list></tv-list>
</template>

<script>
	import tvList from '../../components/tv-list.vue'

	export default {
		components: {
			tvList
		},
		data() {},
		onLoad:function(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
		}
	}
</script>

<style>
</style>
