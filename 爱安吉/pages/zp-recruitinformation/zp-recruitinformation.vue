<template>
	<view>
		<adv :category_id="12" class="adv"></adv>
		<view class="dropbox">
			<HMfilterDropdown :menuTop="0" :filterData="selectdata" :defaultSelected ="defaultSelected"  :updateMenuName="true" @confirm="confirm" dataFormat="Object"></HMfilterDropdown>
		</view>
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
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
	</view>
</template>

<script>
	import HMfilterDropdown from '@/components/HM-filterDropdown/HM-filterDropdown.vue';
	import adv from '../../components/adv.vue'
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	import MD5 from '../../common/MD5.js'
	export default {
		components: {
			adv,
			uniLoadMore,
			HMfilterDropdown
		},
		data() {
			return {

				selectdata:[{
					name: '岗位类型',
					type: 'hierarchy',
					submenu:[],
					},
					{
						name: '文化程度',
						type: 'hierarchy',
						submenu:[],
						},
						{
							name: '日期范围',
							type: 'hierarchy',
							submenu:[],
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
				recs: 10,
				
				jobtype:[],
				jobvalue:'',
				education:[],
				educationvalue:'',
				datetime:[],
				datetimevalue:'',
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.pagetitle
			})
			this.getlist();
			this.getjobtype();
			this.geteducation();
			this.getdatetime();
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
			getlist: function(a,b,c) {
				var that = this;
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				var url = that.globalUrl + '/ajzp/recruit_information.php';
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
						edution:b,
						sit:a,
						date_range:c,

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
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});

			},
			//获取岗位类型列表
			getjobtype:function(){
				var that = this;
				var url = that.globalUrl + '/ajzp/jobclass.php';
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
						that.jobtype = eval('(' + res.data + ')').data;
						that.selectdata[0].submenu = that.jobtype
						console.log(that.selectdata)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
				
			},
			//获取学历列表
			geteducation:function(){
				var that = this;
				var url = that.globalUrl + '/ajzp/education.php';
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
						that.education = eval('(' + res.data + ')').data;
						that.selectdata[1].submenu = that.education
						console.log(that.education)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
				
			},
			//获取日期范围列表
			getdatetime:function(){
				var that = this;
				var url = that.globalUrl + '/ajzp/date_range.php';
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
						that.datetime = eval('(' + res.data + ')').data;
						that.selectdata[2].submenu = that.datetime
						console.log(that.selectdata)
					},
					fail: (err) => {},
					complete: () => {
						this.loading = false;
					}
				});
				
			},
			confirm(e){
				this.indexArr = e.index;
				this.valueArr = e.value;
				console.log(this.indexArr)
				console.log(this.valueArr)
				this.jobvalue = this.valueArr[0][1]
				this.educationvalue = this.valueArr[1][0]
				this.datetimevalue = this.valueArr[2][0]
				
				console.log(this.datetimevalue)
				this.reload = true;
				this.last_id = false;
				this.news = [];
				this.page = 1;
				this.getlist(this.jobvalue,this.educationvalue,this.datetimevalue)
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
	.adv{
		position: relative;
		z-index: 999;
	}
/* 	.dropbox {
		display: flex;
		position: relative;
		width: 100%;
	} */


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
</style>
