<template>
	<zb-list></zb-list>
</template>

<script>
	import zbList from '../../components/zb-list.vue'
	export default {
		components: {
			zbList,
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
		}
	}
</script>

<style>
</style>
