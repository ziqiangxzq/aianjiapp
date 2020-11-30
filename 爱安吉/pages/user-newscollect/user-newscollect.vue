<template>
	<view class="container">
		<u-sticky>
			<u-tabs :list="list" :is-scroll="false" :bold="true" :fontSize="32" :duration="0" :current="current" @change="change">
			</u-tabs>
		</u-sticky>
		<view v-show="current === 0">
			<view class="list-box" v-for="item in news" @click="open_news_detail(item)">
				<view class="title-box">
					{{item.news_title}}
				</view>
				<view class="date-box">
					{{item.create_date}}
				</view>
			</view>
		</view>
		<view v-show="current === 1">
			<view class="list-box" v-for="item in news" @click="open_news_detail(item)">
				<view class="title-box">
					{{item.message}}
				</view>
				<view class="date-box">
					{{item.create_date}}
				</view>
			</view>
		</view>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>

</template>

<script>
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		components: {
			uniLoadMore
		},
		data() {
			return {
				current: 0,
				list: [{
					name: '收藏'
				}, {
					name: '推送'
				}],

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
				recs: 12,
			}
		},
		onLoad(options) {
			this.classid = options.classid
			console.log(this.classid)
		uni.setNavigationBarTitle({
		　　title: options.module_name
		})
			this.getlist('/news/collection_list.php');
		},
		onPullDownRefresh() {
			this.reload = true;
			this.last_id = false;
			this.news = [];
			this.page = 1;
			if (this.current == 0) {
				this.getlist('/news/collection_list.php')
			} else {
				this.getlist('/news/push_list.php')
			}
		},
		onReachBottom() {
			this.status = 'more';
			if (this.current == 0) {
				this.getlist('/news/collection_list.php')
			} else {
				this.getlist('/news/push_list.php')
			}
		},
		methods: {
			getlist: function(a) {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + a;
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						page: that.page,
						recs: that.recs,
						user_id: uni.getStorageSync('user_id'),

					},
					success: (res) => {

						var news = eval('(' + res.data + ')');

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
						console

					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});

			},
			open_news_detail: function(arr) {
				uni.navigateTo({
					url: '../news-detail/news-detail?module_name=新闻详情&news_id=' + arr.news_id
				})
			},
			change(index) {
				this.page = 1;
				this.current = index;
				if (index == 0) {
					this.reload = true;
					this.last_id = false;
					this.news = [];
					this.page = 1;
					this.getlist('/news/collection_list.php')
				} else {
					this.reload = true;
					this.last_id = false;
					this.news = [];
					this.page = 1;
					this.getlist('/news/push_list.php')
				}
				// this.resetCategroy(); //重置二级类别
				// this.getData();
			},
		}
	}
</script>

<style>
	.list-box {
		padding: 20rpx 30rpx;
		border-bottom: 1rpx solid #efefef;
	}

	.date-box {
		color: #A8A8A8;
		font-size: 24rpx;
		margin-top: 20rpx;
	}
</style>
