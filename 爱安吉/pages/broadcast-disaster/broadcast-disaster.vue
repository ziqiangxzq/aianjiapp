<template>
	<view class="disasterdetail">
		<view class="">
			<view class="box ubb bc-border" v-for="(item,index) in newsList" :key="index" v-show="item.news_type=='1'" @click="gotonewsdetails(item)">
				<view class="picture">
					<image :src="item.news_pic" mode=""></image>
				</view>
				<view class="toptitle">{{item.news_title}}</view>
				<view class="toptime">{{item.create_date}}</view>
			</view>
			<view class="box2 ubb " v-for="(item,index) in newsList" :key="index" v-show="item.news_type=='0'" @click="gotonewsdetails(item)">
				<view class="picture2">
					<image :src="item.news_pic" mode=""></image>
				</view>
				<view class="box3">
					<view class="ordinarytitle">{{item.news_title}}</view>
					<view class="ordinarytime">{{item.create_date}}</view>
				</view>
			</view>
		</view>
		<view class="isOver" v-if="flag">没有更多了</view>
	</view>
	
</template>

<script>
	export default{
		data(){
					return{
						newsList:[],
						shelterList:[],
						id:'',
						type_name:'',
						page:1,
					}
				},
		onLoad(options) {
			uni.setNavigationBarTitle({
				title: options.type_name
			})
			console.log(options)
			this.id = options.id;
			this.return_news();
			this.get_shelter();
			this.get_location();
		},
		methods:{
			return_news:function(){
				let that = this;
				var url = '/broadcast/get_newslist.php';
				var data ={
					id : that.id,
					page:that.page,
				}
				that.globalRequest(url,data,'POST','JSON','',function(res){
					if((res.data.data[0].news||[]).length<=0){
						that.flag = true;
					}
					that.newsList =[...that.newsList, ...res.data.data[0].news||[]];
				})
			},
			onReachBottom(){//分页
				var that = this
				console.log('页面触底了')
				if(!that.flag){
					this.page++
					this.return_news()
				}
				
			},
			gotonewsdetails(res){
				uni.navigateTo({
					url:res.link_url,
				});
				console.log(res.link_url)
			}
		}
	}
</script>

<style>
	.picture{
		position: relative;
		width: 750upx;
		height: 500upx;
	}
	.picture image{
		width: 100%;
		height:100%;
	}
	.box{
		margin-bottom: 40upx;
		margin-right: 16upx;
		padding: 20upx 0;
	}
	.toptitle{
		font-size:30upx;
		margin:15upx 16upx;
	}
	.toptime{
		padding: 10px;
		text-align: right;
		margin-top: 20upx;
		font-size: 17.6upx;
		color: #8d8d8d;	
	}
	.box2{
		flex-direction: column;
		margin: 15upx 11upx;
		display:flex;
	}
	.box3{
		flex-direction: row;
		margin: 15upx 10upx;
	}
	.ordinarytitle{
		position: absolute;
		left:230upx;
		flex-direction: row;
		font-size:30upx;
		margin:20 18upx;
	}
	.ordinarytime{
		position: relative;
		right: 15upx;
		margin-top: 120upx;
		font-size: 19upx;
		color: #8d8d8d;	
		padding: 5upx;
		text-align: right;
	}
	.picture2{
		position: absolute;
		width: 200upx;
		height: 120upx;
		margin: 10 15upx;
	}	
	.picture2 image{
		width: 100%;
		height: 100%;
	}
	.isOver{
		text-align: center;
		font-size: 15upx;
	}
</style>
