<template>
	<jyf-parser :html="notice_content" ref="article"></jyf-parser>
</template>

<script>
	export default {
		data() {
			return {
				notice_content: '',
				module_name: '',
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
			　　title: options.title_name
			})
			this.module_name = options.module_name;
			this.get_notice_by_module_name();
		},
		methods: {
			get_notice_by_module_name: function() {
				var that = this;
				var url = '/main/get_notice_by_module_name.php';
				var data = {
					module_name: that.module_name,
					user_id: '',
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.$refs.article.setContent(res.data[0].notice_content);
				});
			}
		}
	}
</script>

<style>
</style>
