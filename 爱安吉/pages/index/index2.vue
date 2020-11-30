<template>
	<view>
		<!-- 天气弹窗 star -->
		<u-popup mode="center" v-model="weathershow" border-radius="10">
			<view class="ub ub-ver ub-f1 pop-content">
			<view class="weawarnhead" :style="{backgroundColor:weatherarr[weatherindex].colorcode}">
				<view class="warnicon" >
					<img style="width: 100%;height:100%" :src="weatherarr[weatherindex].levelimagename">
				</view>
			</view>   
			<view class="weawarncontent">
			<view class="warnicona">
				<img  :src="weatherarr[weatherindex].imageurl">
			</view>
			<view class="weawarncontent">{{weatherarr[weatherindex].content}}</view>
			</view>
				<view class="weawarnbottonbox" :style="{backgroundColor:weatherarr[weatherindex].colorcode}">
					<view style="padding: 20rpx 0;color: #FFFFFF;" @click="nextwarn()" v-if="weatherarr.length!=weatherindex+1">下一条</view>
					<view style="padding: 20rpx 0;color: #FFFFFF;" @click="nextwarn()"  v-if="weatherarr.length==weatherindex+1">我知道了</view>
				</view>
			</view>
		</u-popup>	
		<!-- 天气弹窗 end -->
		<!--通用弹窗start-->
		<u-popup mode="center" v-model="show" closeable="true" border-radius="10">
			<view class="ub ub-ver ub-f1 pop-content">
				<image :src="commPopInfo.img" mode="widthFix"></image>
				<view style="margin: 64rpx 0" v-html="commPopInfo.content"></view>
				<view :style="{backgroundColor: commPopInfo.btbColor,margin: '0 24rpx 24rpx 24rpx',}" @click="openCommPop();">
					<view style="padding: 20rpx 0;color: #FFFFFF;">{{commPopInfo.btnContent}}
					</view>
				</view>
			</view>
		</u-popup>
		<!--通用弹窗end-->
		
		<!--tab切换start-->
		<view>
			<!-- <u-sticky> -->
			<u-tabs :list="list" :is-scroll="true" :bold="true" :fontSize="34" :duration="0.3" :current="current" @change="change"></u-tabs>
			<u-tabs :list="categoryList" name="category_name" :is-scroll="true" :fontSize="24" :current="categoryCurrent"
			 @change="categoryChange" :active-item-style="bg" active-color="#ffffff" :duration="0" :height="60" :show-bar="false"></u-tabs>
			<!-- </u-sticky> -->
		</view>
		<!--tab切换end-->
		
		<!--内容start-->
		<view>
			<!--轮播新闻-->
			<u-swiper v-if="swiperNewsData != ''" :list="swiperNewsData" name="pic_uri" height="320" :effect3d="false" :autoplay="autoplay"
			 :mode="mode" @click="handleSwiperNews"></u-swiper>

			<!--推荐start-->
			<view v-show="current === 0">
				<!--推荐模块-->
				<u-grid :col="5" :border="false">
					<u-grid-item v-for="(arr, i) in serviceData" :key="i" @click="handleMainModuel(arr);">
						<image class="icon" :src="arr.icon"></image>
						<view class="item_module_name" v-html="arr.nav_name">
						</view>
					</u-grid-item>
				</u-grid>

				<!-- <view v-if="serviceData != ''" v-for="(item, j) in serviceData" :key="j">
					<view class="wrapper" @click="open_service_win(i, j)">
						<image class="icon" :src="item.icon"></image>
						<view class="item_module_name" v-html="item.nav_name">
						</view>
					</view>
				</view> -->
				<!--热点新闻-->
				<lab class="ubb clear-both" name="热点" more="更多" fun="getHotNewsMore" @getHotNewsMore="getHotNewsMore"></lab>
				<news-list :newsListData="hotNewsData"></news-list>

				<!--7天最热-->
				<u-notice-bar mode="vertical" type="none" color="#060606" fontSize="30" padding="18rpx 32rpx" :no-list-hidde="false"
				 :volume-icon="false" :list="dayNewsData"></u-notice-bar>

				<!--专题-->
				<lab name="专题"></lab>
				<u-swiper :list="specialNewsData" name="pic_uri" :effect3d="false" @click="handleSpecial"></u-swiper>

				<!--直播-->
				<lab name="直播"></lab>
				<view class="ub scroll">
					<view class="box" v-for="(item, index) in liveNewsData" :key="index" @click="handleLive(item)">
						<image :src="item.pic_uri" class="live-icon"></image>
						<view class="live-name" v-html="item.news_title"></view>
					</view>
				</view>

				<!--乡镇部门新闻-->
				<lab name="乡镇部门"></lab>
				<news-list :newsListData="xzNewsData"></news-list>

				<!--应用服务-->
				<lab name="应用服务" more="更多" fun="getServiceNewsMore" @getServiceNewsMore="getServiceNewsMore"></lab>
				<news-list :newsListData="serviceNewsData"></news-list>

			</view>
			<!--推荐end-->

			<!--直播start-->
			<view v-show="current === 2">
				<zb-list ref="refreshLiveList"></zb-list>
			</view>
			<!--直播end-->

			<!--tab其他类别(视频、媒体、国内、乡镇、部门)start-->
			<view v-show="current !== 0 && current !== 2">
				<news-list :newsListData="commonNewsData"></news-list>
			</view>
			<!--tab其他类别(视频、媒体、国内、乡镇、部门)end-->
		</view>
		<!--内容end-->
		
		<u-loadmore :status="status" color="#a8a8a8" />
	</view>
</template>

<script>
	import newsList from '../../components/news-list.vue'
	import lab from '../../components/lab.vue'
	import zbList from '../../components/zb-list.vue'
	export default {
		components: {
			newsList,
			lab,
			zbList,
		},
		data() {
			return {
				// 天气预警 star
				weatherindex:0,
				weathershow:false,
				weatherarryuanshi:[],
				weatherarr:[
				{
					index:"",
					colorcode:"",
					content:"",
					imageurl:"",
					levelimagename:""
				}	
				],
				// 天气预警 end
				/*头部tab*/
				list: [{
					name: '推荐'
				}, {
					name: '两山号'
				}, {
					name: '视频'
				}, {
					name: '专题'
				}, {
					name: '媒体聚焦'
				}, {
					name: '国内'
				}],
				current: 0,
				bg: {
					'backgroundColor': '#0090ff',
					'margin': '20rpx 10rpx',
					'borderRadius': '8rpx',
				},
				/*头部tab*/

				/*推荐*/
				//轮播新闻
				swiperNewsData: [],
				autoplay: true,
				mode: "round",
				//热点新闻
				hotNewsData: [],
				//7天最热
				dayNewsData: [],
				//专题
				specialNewsData: [],
				//直播
				liveNewsData: [],
				//乡镇部门
				xzNewsData: [],
				//应用服务
				serviceNewsData: [],
				//中间模块
				serviceData: [],
				/*推荐*/

				/*新闻*/
				commonNewsData: [],
				/*新闻*/

				/*乡镇部门类别*/
				categoryList: [],
				categoryCurrent: 0,
				isXz: false,
				/*乡镇部门类别*/

				//天气链接
				weather_jump_url: "https://smart.zj121.com/typhoonWap/",

				/*分页start*/
				status: 'nomore',
				//list: 15,
				page: 1,
				/*分页end*/

				//通用弹窗相关start
				show: false,
				commPopInfo: [],
				//通用弹窗相关end
			}
		},
		onLoad() {
			this.tabToggle_0();
			this.get_real_weather();

			this.get_commpop_status(); //获取通用弹窗
		},
		onShow() {
			
		},
		onPullDownRefresh() {
			this.page = 1;
			console.log("this.page="+this.page)
			this.getData();
		},
		methods: {
			//天气预警star
			getawarnimage:function(a,b,c,d,e){//获取预警信息相关图片 为防止for循环异步进行 以if++形式循环事件
			var d=d;
			if(d<e){
			var wetherwarnurl="/weatherwarn.php?type="+a+"&level="+b+"&content="+c;
			var data={};
			var that=this;
			this.globalRequest(wetherwarnurl, data, 'POST', 'JSON', '', function(res){//上传预警状况 预警等级 预警内容 返回预警内容 天气图片 预警颜色代码
			
			var dataobj={
				index:d,
				colorcode:res.data.colorcode,
				content:res.data.content,
				imageurl:res.data.imageurl,
				levelimagename:res.data.levelimagename
			}
			
			that.weatherarr.push(dataobj);
			that.weathershow=true;
			d=d+1;
			console.log(d);
			console.log(that.weatherarryuanshi[d].name,that.weatherarryuanshi[d].serverity,that.weatherarryuanshi[d].content,d,that.weatherarryuanshi.length);
			that.getawarnimage(that.weatherarryuanshi[d].name,that.weatherarryuanshi[d].serverity,that.weatherarryuanshi[d].content,d,that.weatherarryuanshi.length)		
			})
				}
			  if(d==e){
				 that.weathershow=true
			  }
					
			},
			nextwarn:function(){//点击预警框底部按钮时执行事件
			if(this.weatherarr.length!=this.weatherindex+1){//不是最后一条预警 加载下一条预警
				this.weatherindex=this.weatherindex+1;
				//this.span()
			}else{//是最后一条预警 关闭预警弹窗
				this.weathershow=false
			    // this.span()
			}	
			},
			//天气预警end
			//弹窗start
			get_commpop_status: function() {
				var that = this;
				var url = '/main/get_commpop_status.php';
				var data = {

				}

				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (res.data.if_jump == 1) { //需要跳出弹窗
						that.commPopInfo = res.data;
						that.show = true;
					} else { //天气弹窗
					var wetherwarnurl="/weather2/GetPublishingWarningSign.php";
					var data={};
					that.globalRequest(wetherwarnurl, data, 'POST', 'JSON', '', function(res){
						//假数据
						console.log(res.data)
					// res.data={"code":1,"message":"wuyujing","data":[
					//  	   {content: '安吉县自然资源和规划局、安吉县气象局2020年4月15日13时41分联合发布冰雹黄色预警信号：',name:"冰雹",serverity:"黄色"},
					// 		   {content: '安吉县自然资源和规划局、安吉县气象局2020年4月15日13时41分联合发布暴雨蓝色预警信号联合发布暴雨蓝色预警信号：',name:"暴雨",serverity:"蓝色" },
					//         {content: '安吉县自然资源和规划局、安吉县气象局2020年4月15日13时41分联合发布冰雹橙色预警信号联合发布冰雹橙色预警信号：',name:"冰雹",serverity:"橙色" },
					//         {content: '安吉县自然资源和规划局、安吉县气象局2020年4月15日13时41分联合发布冰雹红色色预警信号：',name:"冰雹",serverity:"红色" 
					//             }]};					
					that.weatherarryuanshi=res.data.data;
					if(res.data.data.length!=0){//有天气预警信息执行弹窗事件 以0开始
						 that.weatherarr=[];	
						 that.getawarnimage(res.data.data[0].name,res.data.data[0].serverity,res.data.data[0].content,0,res.data.data.length)
					}else{//无天气预警信息不做任何操作
						
					}
					}) 
					}
				});
			},
			openCommPop: function() {
				uni.navigateTo({
					url: this.commPopInfo.jump_url2
				})
			},
			//弹窗end
			//分页
			onReachBottom() {
				console.log("onReachBottom")
				this.page++;

				if (this.current == 3 || this.current == 4) { //乡镇部门特判
					this.getNewsList('index_news_content', 'xz', this.categoryList[this.categoryCurrent].news_category_id, this.page++);
					return;
				}

				this.getData(this.current);
			},
			getData() {
				switch (this.current) {
					case 0: //推荐
						this.status = "nomore";
						this.tabToggle_0();
						break;
					case 1: //新闻
						this.status = "loading";
						this.getSliderNewsList(-100);
						this.getNewsList('index_news_content', 'newsContent', -100, this.page)
						break;
					case 2: //直播
						this.status = "nomore";
						this.$refs.refreshLiveList.refreshLiveList();
						//this.get_wchat_list_new();
						//this.get_wchat_category();
						break;
					case 3: //乡镇
						this.status = "loading";
						this.autoplay = false;
						this.mode = "none";
						this.isXz = true;
						this.get_news_category_list_main("index", "xz", 1);
						break;
					case 4: //部门
						this.status = "loading";
						this.autoplay = false;
						this.mode = "none";
						this.isXz = true;
						this.get_news_category_list_main("index", "bm", 3);
						break;
					case 5: //视频
						this.status = "loading";
						this.getSliderNewsList(57);
						this.getNewsList('index_news_content_sp', 'newsContent', 57, this.page)
						break;
					case 6: //媒体聚焦
						this.status = "loading";
						this.getSliderNewsList(56);
						this.getNewsList('index_news_content_mtjj', 'newsContent', 56, this.page)
						break;
					case 7: //国内
						this.status = "loading";
						this.getSliderNewsList(55);
						this.getNewsList('index_news_content_gr', 'newsContent', 55, this.page)
						break;
				}
				
				if(this.page == 1) {
					uni.stopPullDownRefresh();
				}
			},
			//头部tab回调
			change(index) {
				this.page = 1;
				this.current = index;
				this.resetCategroy(); //重置二级类别
				this.getData();
			},
			tabToggle_0: function() {
				this.getSwiperNewsList();
				this.get_mid_nav();
				this.getHotNewsList();
				//	this.getDayNewsList();
				this.getSpecialNewsList();
				this.getLiveNewsList();
				this.getXzNewsList();
				this.getServiceNewsList();
			},
			//获取推荐滚动新闻
			getSwiperNewsList: function() {
				this.getNewsRecommend('main', 'slider', 2, 1);
			},
			//获取热点新闻
			getHotNewsList: function() {
				this.getNewsRecommend('main', 'hotPoint', 2, 1);
			},
			//7天最热新闻
			getDayNewsList: function() {
				this.getNewsRecommend('main', 'hotDay', 2, 1);
			},
			//获取专题新闻
			getSpecialNewsList: function() {
				this.getNewsRecommend('main', 'special', 2, 1);
			},
			//获取直播新闻
			getLiveNewsList: function() {
				this.getNewsRecommend('main', 'live', 2, 1);
			},
			//获取乡镇部门新闻
			getXzNewsList: function() {
				this.getNewsRecommend('main', 'xiangZhenHotPoint', 2, 1);
			},
			//获取应用服务新闻
			getServiceNewsList: function() {
				this.getNewsRecommend('main', 'service', 2, 1);
			},
			//获取推荐新闻
			getNewsRecommend: function(froms, type, category, page) {
				var that = this;
				var url = '/news/get_news_recommend.php';
				var data = {
					from: froms,
					type: type,
					recs: 10,
					category: category,
					page: page,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					switch (type) {
						case 'slider':
							that.swiperNewsData = res.data;
							break;
						case 'hotPoint':
							that.hotNewsData = res.data;
							break;
						case 'hotDay':
							for (var i = 0; i < res.data.length; i++) {
								that.dayNewsData.push(res.data[i].news_title);
							}
							break;
						case 'special':
							that.specialNewsData = res.data;
							break;
						case 'live':
							that.liveNewsData = res.data;
							break;
						case 'xiangZhenHotPoint':
							that.xzNewsData = res.data;
							break;
						case 'service':
							that.serviceNewsData = res.data;
							break;
					}
				});
			},
			//获取新闻类别的新闻
			getNewsList: function(froms, type, category, page) {
				if (this.page == 1) {
					this.commonNewsData = [];
				}
				var that = this;
				var url = '/news/get_news_list.php';
				var data = {
					from: froms,
					type: type,
					recs: 10,
					news_category_id: category,
					page: page,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					for (var i = 0; i < res.data.length; i++) {
						that.commonNewsData.push(res.data[i]);
					}
					
					if(res.data.length == 0) {
						that.status = "nomore";
					}
				});
			},
			//获取滚动新闻
			getSliderNewsList: function(category) {
				if (this.page != 1) {
					return;
				}
				var that = this;
				var url = '/news/get_news_hot_pic_by_news_category_id_new.php';
				var data = {
					news_category_id: category,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if (!that.isXz) {
						that.swiperNewsData = res.data;
					} else {
						that.swiperNewsData.push(res.data[0]);
					}
				});
			},
			//获取中间模块
			get_mid_nav: function() {
				var that = this;
				var url = '/main/get_mid_nav.php';
				var data = {
					search: ''
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.serviceData = res.data;
				});
			},
			/*乡镇部门逻辑start*/
			//类别切换
			categoryChange: function(index) {
				var news_category_id = this.categoryList[index].news_category_id;
				this.page = 1;
				this.categoryCurrent = index;
				this.swiperNewsData = [];
				this.commonNewsData = [];
				this.getSliderNewsList(news_category_id);
				this.getNewsList('index_news_content', 'xz', news_category_id, 1);
			},
			//获取二级类别
			get_news_category_list_main: function(froms, type, category) {
				var that = this;
				var url = '/news/get_news_category_list_main.php';
				var data = {
					from: froms,
					type: type,
					category: category,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					that.categoryList = res.data;
					that.categoryChange(0)
				});
			},
			//重置二级类别
			resetCategroy: function() {
				this.categoryCurrent = 0;
				this.categoryList = [];

				this.autoplay = true;
				this.mode = "round";

				this.swiperNewsData = [];
				this.isXz = false;
			},
			/*乡镇部门逻辑end*/
			
			/*title start*/
			//获取天气
			get_real_weather: function() {
				var that = this;
				var url = '/weather2/get_real_weather.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					// #ifdef APP-PLUS
					var currentWebview = that.$mp.page.$getAppWebview();
					console.log(currentWebview)
					var tn = currentWebview.getStyle().titleNView;
					tn.buttons[0].text = res.data.data.tempStr; //[0] 按钮的下标
					currentWebview.setStyle({
						titleNView: tn
					});
					// #endif
				});
			},
			//点击title图标
			onNavigationBarButtonTap(e) {
				console.log(e.index)
				if (e.index == 0) {
					if (this.weather_jump_url != '') {
						uni.navigateTo({
							url: '../webview/webview?url=' + this.weather_jump_url
						})
					}
				} else if (e.index == 1) {

				} else if (e.index == 2) {
					uni.navigateTo({
						url: '../news-search/news-search'
					})
				}
			},
			/*title end*/
			/*首页新闻打开逻辑start*/
			//打开专题
			handleSpecial: function(index) {
				this.handleNewsOpen(this.specialNewsData[index].jump_url2)
			},
			//打开直播
			handleLive: function(item) {
				this.handleNewsOpen(item.jump_url2)
			},
			//打开滚动新闻
			handleSwiperNews: function(index) {
				this.handleNewsOpen(this.swiperNewsData[index].jump_url2)
			},
			//打开新闻
			handleNewsOpen: function(jump_url2) {
				uni.navigateTo({
					url: jump_url2
				})
			},
			/*首页新闻打开逻辑end*/
			/*打开热点更多start*/
			getHotNewsMore: function() {
				this.change(1);
			},
			/*打开热点更多end*/
			/*打开应用新闻更多start*/
			getServiceNewsMore: function() {
				uni.navigateTo({
					url: "../news-service/news-service"
				})
			},
			/*打开应用新闻更多end*/
		}
	}
</script>

<style scoped>
	/* 天气预警star */
	.weawarnhead{
		position: relative;width: 16rem;height: 2.5rem;display: flex;align-items: center;justify-content: center;
	}
	.warnicon{
		position: absolute;bottom: 0;width: 2.5rem;height: 2.5rem;
	}
	.weawarncontent{
		display: flex;align-items: center;flex-direction: column;margin-top:20rpx;
	}
	.warnicona{
		width: 2.5rem;height: 2.5rem;background-color: #000000;
	}
	.warnicona img{
		width: 100%;height: 100%;
	}
	.weawarncontent{
		margin: 40rpx 0;width:15rem;margin-left: 0.5rem;
	}
	.weawarnbottonbox{
		margin:0 24rpx 24rpx 24rpx;border-radius:0.2rem;overflow: hidden;
	}
	/* 天气预警end */
	.slot-wrap {
		display: flex;
		align-items: center;
		/* 如果您想让slot内容占满整个导航栏的宽度 */
		/* flex: 1; */
		/* 如果您想让slot内容与导航栏左右有空隙 */
		/* padding: 0 30rpx; */
	}

	/*直播start*/
	.scroll {
		overflow-x: auto;
	}

	.box {
		width: 45%;
		padding-left: 22upx;
	}

	.box:last-child {
		margin-right: 0;
	}

	.live-icon {
		width: 320rpx;
		height: 160rpx;
		border-radius: 4upx;
	}

	.live-name {
		width: 320rpx;
		overflow: hidden;
		text-overflow: ellipsis;
		display: -webkit-box;
		-webkit-line-clamp: 5;
		-webkit-box-orient: vertical;
	}
	/*直播end*/

	/*中间模块start*/
	.wrapper {
		float: left;
		width: 20%;
		margin: 24upx auto;
		text-align: center;
	}

	.icon {
		width: 72rpx;
		height: 72rpx;
	}

	.item_module_name {
		color: #4d4d4d;
		margin-top: 8rpx;
		font-size: 24rpx;
	}
	/*中间模块end*/
	
	/*弹窗start*/
	.pop-content {
		text-align: center;
	}

	/*弹窗end*/
</style>
