<template>
	<view class="broadcast">
		<view class="">
			<view class="box" >
				<view class="topbox ub">
					<view><image class="picture" src="../../static/broadcast/5.png" @tap="playvoice"></image></view>
					<view class="notice" >{{notice}}</view>
				</view>
				<view class="viewmore" @click="gotonotification">查看更多 ></view>
			</view>
			<view class="ub">
				<view class="ub ub-ver ub-ac item" v-for="(item,index) in typeList" :key="index" v-show = "item.id!=2" @click="gototype(item)">
					<image class="m-icon" :src="item.type_pic"></image>
					<view class="key">{{item.type_name}}</view>
				</view>
				<view class="ub ub-ver ub-ac item" v-for="(item,index) in typeList" :key="index" v-show = "item.id==2" @click="gotomap">
					<image class="m-icon" :src="item.type_pic"></image>
					<view class="key">{{item.type_name}}</view>
				</view>
			</view>
			<adv :category_id="14"></adv>
			<view class="firstnews ubb bc-border" v-for="(item,index) in newsList" :key="index" v-show = "item.news_type==1" @click="gotonewsdetails(item)">
				<image class="image2" :src="item.news_pic"></image>
				<view class="newstitle">{{item.news_title}}</view>
				<view class="newstime">{{item.create_date}}</view>
			</view>
			<view class="box1 ubb"  v-for="(item,index) in newsList" :key="index" v-show = "item.news_type==0" @click="gotonewsdetails(item)">
				<image :src="item.news_pic" class="image3"></image>
				<view  class="box2">
					<view class="newstitle2">{{item.news_title}}</view>
					<view class="newstime2">{{item.create_date}}</view>
				</view>
			</view>
		</view>
		<view class="isOver" v-if="flag">没有更多了</view>
	</view>
	
</template>

<script>
	import adv from '../../components/adv.vue'
	const innerAudioContext = uni.createInnerAudioContext();
	export default{
		components: {
			adv
		},
		data(){
			return{
				notice:"",
				newsList:[],
				typeList:[],
				page:1,
				flag:false,
			}
		},
		onLoad() {
			this.get_notice();//获取天气
			this.recommended_news();//获取新闻
			this.get_emergency_type();//获取新闻类别
			this.play_voice();
			
		},
		
		methods:{
			gototype(res){//前往分类模块
				uni.navigateTo({
					url:res.link_url
				});
			},
			get_notice:function(){
				var that = this;
				var url = '/broadcast/get_notice.php';
				var data = {
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					console.log(res);
					that.notice = res.data.data[0].notice_content
				})
			},
			playvoice(res){
				innerAudioContext.autoplay = true;
				innerAudioContext.src = res.data.data[0].mp3_url;
				innerAudioContext.onPlay(() => {
				  console.log('开始播放');
				});
				innerAudioContext.onError((res) => {
				  console.log(res.errMsg);
				  console.log(res.errCode);
				});
			},
			recommended_news:function(){
				var that =this;
				var url = '/broadcast/get_recommend_newslist.php';
				var data = {
					if_recommend:1,
					page:that.page,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					if((res.data.data||[]).length<=0){
						that.flag = true;
					}
					that.newsList =[...that.newsList,...res.data.data||[]];
					console.log(that.newsList);
				})
			},
			onReachBottom(){//分页
				var that = this
				console.log('页面触底了')
				if(!that.flag){
					this.page++
					this.recommended_news()
				}
				
			},
			get_emergency_type:function(){
				var that = this;
				var url = '/broadcast/get_emergency_type.php';
				var data ={
				}
				that.globalRequest(url,data,'POST','JSON','',function(res){
					console.log(res);
					that.typeList = res.data.data||[];
				})
			},
			gotonewsdetails(res){//前往新闻详情
				uni.navigateTo({
					url:res.link_url,
				});
				console.log(res.link_url)
			},
			gotomap(){//前往附近避灾点地图页
				uni.navigateTo({
					url:'../broadcast-shelter/broadcast-shelter'
				});
			},
			gotonotification(){//前往天气预报页
				uni.navigateTo({
					url:'../broadcast-notification/broadcast-notification'
				});
			}
		}
	}
</script>

<style>
	.box{
		border-radius: 24.8rpx;
		background: #e8f5ff;
		margin: auto;
		margin-top:38rpx;
		padding: 24upx 22upx;
		margin: 0 22upx;
	}
	.picture{
		width: 72rpx;
		height: 69rpx;
		margin-top:15rpx;
		margin-right:39upx;
	}
	.notice{
		margin: 20upx 10upx;
	}
	.viewmore{
		text-align: right;
		color: #2ea6dc;
	}
	.item {
		margin: 40rpx 0;
	}
	.m-icon {
		width: 72rpx;
		height: 72rpx;
	}
	.key {
		color: #919191;
		margin-top: 27rpx;
		font-size: 24rpx;
	} 
	.box1{
		flex-direction: column;
		margin: 20upx 11upx;
		display:flex;

	}
	.box2{
		flex-direction: row;
		margin: 20upx 10upx;
	}
	.firstnews{
		margin: 20upx 16upx;
	}
	.image2{
		width: 711rpx;
		height: 324rpx;
		margin:20upx 8upx;
	}
	.newstitle{
		flex-direction: row;
		font-size:30upx;
		margin:0 16upx;
	}
	.newstitle2{
		position: absolute;
		left:230upx;
		flex-direction: row;
		font-size:28upx;
		margin:30 18upx;
	}
	.newstime{
		position: relative;
		right: 15upx;
		margin-top: 40upx;
		font-size: 17.6upx;
		color: #8d8d8d;	
		padding: 10upx;
		text-align: right;
	}
	.newstime2{
		position: relative;
		right: 15upx;
		margin-top: 120upx;
		font-size: 19upx;
		color: #8d8d8d;	
		padding: 5upx;
		text-align: right;
	}
	.image3{
		display: flex;
		position: absolute;
		margin-top: 15upx;
		width: 210rpx;
		height: 130rpx;
	}
	.image3 image{
		width: 100%;
		height: 100%;
	}
	.isOver{
		text-align: center;
		font-size: 25upx;
	}
</style>
