<template>
	<view>
		<adv :category_id="8"></adv>
		<view class="wrapper"  v-for="item in mid_data" @click="openadvance(item.id,item.class_name)">
				<image class="icon" :src="item.img_src"></image>
				<view class="module_name" v-html="item.class_name">
				</view>
		</view>
		<adv :category_id="11"></adv>
		<view>
			<lab name="推荐岗位"></lab>
			<view class="recruitbox">
				<view class="unit" v-for="item in news" @click="openzpdetail(item.id)">
					<view class="money">{{item.salary}}</view>
					<view class="messagebox">
						<view>
							<view class="msgtitle">{{item.name}}</view>
							<view class="msgdesc mtop10">{{item.edution}} &nbsp; {{item.exp_require}}</view>
						</view>
						<view class="msgdesc">{{item.company}}</view>
					</view>
				</view>

			</view>
		</view>
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	
	import adv from '../../components/adv.vue'
	import MD5 from '../../common/MD5.js'
	import lab from '../../components/lab.vue';
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	export default {
		components: {
			lab,
			uniLoadMore,
			adv
		},
		data() {
			return {

				mid_data: [],
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
				recs: 10,
			};
		},

		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.module_name
			});
			this.getlist();
			this.get_mid_nav();
		},
		onPullDownRefresh() {
			this.reload = true;
			this.last_id = false;
			this.news = [];
			this.page = 1;
			this.getlist();
		},
		onReachBottom() {
			this.status = 'more';
			this.getlist();
		},
		methods: {
			get_mid_nav: function() { //获取中间模块
				var that = this;
				var url = that.globalUrl + '/ajzp/home_class.php';
				var timestamp = Date.parse(new Date()) / 1000;
				var s = timestamp + "32dd3c0eb6340a932a990e5832a0d2cf";
				var signature = MD5(s);
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						timestamp: timestamp,
						sign: signature,

					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						that.mid_data = data.data;
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
			},
			getlist: function() {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/ajzp/recommend_jobs.php';
				var timestamp = Date.parse(new Date()) / 1000;
				var s = timestamp + "32dd3c0eb6340a932a990e5832a0d2cf";
				var signature = MD5(s);
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
						timestamp: timestamp,
						sign: signature,

					},
					success: (res) => {
						var news = eval('(' + res.data + ')').data;
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
						console.log(that.news)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});

			},
			openadvance: function(a, b) {
				if (a == 1) {
					uni.navigateTo({
						url: '../zp-recruitinformation/zp-recruitinformation?pagetitle=' + b
					});
				} else {
					uni.navigateTo({
						url: '../zp-newslist/zp-newslist?pagetitle=' + b + '&classid=' + a
					});
				}

			},
			openzpdetail: function(a) {
				uni.navigateTo({
					url: '../zp-jobdetail/zp-jobdetail?jobid=' + a
				})
			}
		}
	};
</script>

<style>
	.uimgbox img {
		position: relative;
		width: 100%;
	}

	.messagebox .msgtitle {
		position: relative;
		font-size: 30rpx;
	}

	.messagebox .msgdesc {
		position: relative;
		font-size: 23rpx;
		color: #929292;
	}

	.unit {
		position: relative;
		padding: 25rpx 50rpx;
		border-bottom: 1px solid #fdfdfd;
	}

	.mtop10 {
		margin-top: 10rpx;
	}

	.money {
		position: absolute;
		font-size: 30rpx;
		right: 50rpx;
		top: 25rpx;
		color: #d92323;
	}

	.uimgbox {
		position: relative;
		width: 151rpx;
		height: 151rpx;
		border-radius: 20rpx;
		background-color: #000000;
		display: inline-block;
	}

	.umessagebox {
		position: absolute;
		width: calc(100% - 226rpx);
		height: 151rpx;
		margin-left: 25rpx;
		display: inline-block;
		top: 25rpx;
		background-color: #fff;
	}

	.messagebox {
		position: relative;
		width: 100%;
		height: 151rpx;
		display: flex;
		top: 0;
		flex-direction: column;
		justify-content: space-between;
	}
	.wrapper {
		display:inline-block;
		width: 25%;
		margin: 24upx auto;
		text-align: center;
	}
	
	.icon {
		width: 68rpx;
		height: 68rpx;
	}
	
	.module_name {
		font-size: 24rpx;
		letter-spacing: 1.2rpx;
		margin-top: 10rpx;
		color: #868686;
		text-overflow:ellipsis;
		white-space:nowrap;
		overflow: hidden;
	}
</style>
