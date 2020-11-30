<template>
	<view class="newsdetails">
		<view class="ubb title wrap">
			<view class="news_title">{{news_title}}</view>
			<view class="ub ub-f1 ub-ac">
				<view class="create_date ub-f1">{{news_time}}</view>
			</view>
			<!-- <view class="toptitle">{{newDetail[0].news_title}}</view>
			<view class="toptime">{{newDetail[0].create_date}}</view> -->
		</view>
		<jyf-parser :html="news_content" ref="article"></jyf-parser>
	</view>
</template>

<script>
	export default{
		data(){
					return{
						news_id:'',
						news_content: "",
						newDetail:[],
						news_title:"",
						news_time:"",
					}
					
				},
		onLoad(options) {
			console.log(options)
			this.news_id = options.news_id;
			
			this.getcontent();
		},
		methods:{
			getcontent:function(){
				let that = this;
				var url ='/broadcast/get_news_content.php'
				var data ={
					news_id :that.news_id,
				}
				that.globalRequest(url,data,'POST','JSON','',function(res){
					// that.newDetail=res.data.data.filter(item=>{
					// 	return item.news_id==that.news_id;
					// })
				//	that.$refs.article.setContent(that.data.news_content2);
					
					//that.shareInfo.share_title = that.data.news_title;
					//that.shareInfo.share_content = that.data.news_title;
					that.news_time = res.data.data[0].create_date
					that.news_title = res.data.data[0].news_title
					that.news_content =   res.data.data[0].news_content
					that.$refs.article.setContent(that.news_content);
					//console.log(that.newDetail);
				})
			},
		}
	}
</script>

<style>
	.news_title {
		margin: 10upx 15upx;
		font-size: 40rpx;
		line-height: 48rpx;
	}
	.create_date {
		color: #A8A8A8;
		margin: 24rpx 10upx;
	}
	.title {
		margin-bottom: 16rpx;
	}
</style>
