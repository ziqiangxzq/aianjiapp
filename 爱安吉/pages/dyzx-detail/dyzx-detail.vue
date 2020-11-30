<template>
	<view style="padding-bottom:100rpx">
		<view class="bodybox">
		<view class="title" v-html="luntanmsg.title"></view>
		<view style="border-bottom: 1rpx solid #f8f8f8;padding-bottom:40rpx;">
        <view class="headbox">
			<view class="identity">楼主</view>
			<view class="headimg">
				<img :src="luntanmsg.pics" style="width: 100%;height: 100%;">
			</view>
			<view class="nickbox">
			<view class="headtitle">{{luntanmsg.user_nick}}</view>
			<view class="sendtime">{{luntanmsg.create_date}}</view>
			</view>
		</view>
		<view class="content" v-html="luntanmsg.content"></view>
		<view>
			<view class="contentimagebox">
			<image class="contentimage" @click="openimage(index)" v-if="luntanmsg.pic.length>1" v-for="item,index in luntanmsg.pic" :src="item.content_pic">
	        <image v-if="luntanmsg.pic.length==1"  mode="widthFix" class="contentimagebig" @click="openimage(index)" v-for="item,index in luntanmsg.pic" :src="item.content_pic">
			</view>
			<view class="contentvideobox" v-if="luntanmsg.video_code">
				<video :src="luntanmsg.video_code" :poster="luntanmsg.video_pic" controls="" style="width: 100%;"></video>
			</view>	
		</view>
		</view>
		<!-- 回复列表开始 -->
		<view class="replybox">
			<view class="replyitem" v-for="itam,index in replyarr">
				<view class="headbox">
					<view class="identity">{{index + 1}}楼</view>
					<view class="headimg">
						<img :src="itam.reply_pics" style="width:100%;height:100%">
					</view>
					<view class="nickbox">
					<view class="headtitle">{{itam.user_nick}}</view>
					</view>
				</view>
		
			<view class="content" v-html="itam.reply_content"></view>
            <view class="contentimagebox">
				<image class="contentimage" @click="openreplyimg(itcm.reply_pic)" :src="itcm.reply_pic" v-for="itcm in itam.reply_pic">
			</view> 
            <view class="footbox">
				<view class="sendtimer">{{itam.reply_time}}</view>
				<view class="replybutton" @click="showreplyfloatbox(itam.reply_id)"></view>
			</view>
			 <!-- 回复回复列表开始 -->
			 <view class="replyreplybox" v-if="itam.reply_reply.length!=0" v-for="itdm in itam.reply_reply" >
				 <span style="color: #0081FF;">{{itdm.user_nick}}</span> : {{itdm.reply_content}}
			 </view>
			 <!-- 回复回复列表结束 -->
			</view>
		</view>
		<!-- 回复列表结束 -->
		</view>
				<comment ref="commentboxreply" fun="releasecomment" @releasecomment="releasecomment"></comment>
	</view>
</template>

<script>
	//?json=
	import comment from '../../components/comment.vue'
	export default {
		components:{comment},
		data() {
			return {
				luntanmsg:"",
				replyarr:"",
				thisreplyid:"",
				imglistsarr:[],
				tiebaid:uni.getStorageSync("tiebaid"),
				commentcontent:'',
				ajaxurl:'/news/reply_content.php',
				
			}
		},
		onLoad() {
		this.getlist()
		},
		methods: {
		showreplyfloatbox:function(a){
			    this.thisreplyid=a;
				this.ajaxurl='/news/reply_reply_content.php';
				this.$refs.commentboxreply.getfocus()
		},

		getlist:function(){//获取帖子内容及回复详情列表
		 uni.request({
		 	url:this.globalUrl+'/news/get_tieba_content_reply_by_content.php',
		 	data:{
             tieba_content_id:uni.getStorageSync("tiebaid")
		 	},
		 	dataType:"json",
		 	method:"POST",
		 	header:{
		 		'content-type': 'application/x-www-form-urlencoded'
		 	},
		 	success: (res) => {
				this.replyarr=res.data[0].reply;
		 		this.luntanmsg=res.data[0];
				for(var i = 0;i<res.data[0].pic.length;i++){
				this.imglistsarr.push(res.data[0].pic[i].content_pic)	
				}
		 		//console.log(this.replyarr[0].reply_content)
		 	}
		 })	
		},
		releasecomment:function(e) {
			//从子组件获取评论内容
			this.commentcontent=e;
		  var that = this;
		  
		  var json = [{
		  	"tieba_content_id": uni.getStorageSync("tiebaid"),
		  	"user_id": uni.getStorageSync("user_id"),
		  	"reply_content": that.commentcontent,
			"reply_id": that.thisreplyid,
		  }];
		  				
		  var url = that.globalUrl+that.ajaxurl;
		  uni.request({
		  	url: url,
		  	dataType: 'text',
		  	method:"POST",
		  	header : {'content-type':'application/x-www-form-urlencoded'},
		  	data: {
		  		user_id: uni.getStorageSync("user_id"),
		  		version:this.version,
		  		json: JSON.stringify(json)
		  	},
		  	success: (res) => {
				var data = eval('(' + res.data + ')');
					if (data[0].resultid == 1) {
						uni.showToast({
							icon: 'none',
							title:"发送成功，请等待审核~"
						});
					} else {
						uni.showToast({
							icon: 'none',
							title: "发送失败"
						});
					}
				}
			});
		},
	    openimage:function(a){
			uni.previewImage({
				urls:this.imglistsarr,
				indicator: "number",
				current:this.imglistsarr[a]
			});
		},
		openreplyimg:function(a){
			var imgarr=[];
			imgarr.push(a),
			uni.previewImage({
				urls:imgarr,
				indicator: "number",
				current:imgarr[0]
			});
		}
		}
	}
</script>

<style>
	.contentvideobox{
		position: relative;
        width: 100%;
	}
	.contentimagebox{
		position: relative;
		display: flex;
		margin-top: 5rpx;
		align-items: center;
		justify-content:space-between;
	}
	.replyreplybox{
		position: relative;
		width: calc(100% - 20rpx);
		margin-left: 10rpx;
		padding: 10rpx 0;
		border-top: 1px solid #f8f8f8;
	}
	.contentimage{
	    position: relative;
		width: 32%;
		height:150rpx;
		border-radius:10rpx;
		margin-top: 10rpx;
	}
	.contentimagebig{
	    position: relative;
		width: 100%;
		border-radius:10rpx;
		margin-top: 10rpx;		
	}
	.commentbutton {
		position: relative;
		width: 90%;
		height: 60rpx;
		display: flex;
		color:gray;
		border: 1px solid #eee;
		font-size: 20rpx;
		align-items: center;
		justify-content:left;
		border-radius: 100rpx;
	}
	.commentbuttonbox {
		position: fixed;
		width: 100%;
		height: 110rpx;
		background-color: #fff;
		bottom: 0;
		display: flex;
		align-items: center;
		justify-content: center;
		z-index: 40;
		left: 0;
		
		box-shadow: 0rpx -10rpx 20rpx 10rpx rgba(100, 100, 100, 0.1);
	}
	.footbox{
		position: relative;
		width: 100% - 100rpx;
		margin-top: 10rpx;
		padding-bottom:20rpx;
		font-size: 15rpx;
		display: flex;
		align-items: center;
		justify-content: space-between;
	}
	.replybutton{
		position: absolute;
		width: 30rpx;
		height: 30rpx;
		background: url(../../static/dyzx/comment.png) no-repeat center;
		background-size: 100% 100%;
		right: 0;
	}
	.replyitem{
		position: relative;
		width: 100%;
		border-bottom: 1rpx solid #eee;
	}
	.content{
		position: relative;
		width: 100% - 100rpx;
		font-size: 30rpx;
	}
	.identity{
		position:absolute;
		right: 0;
	}
	.nickbox{
		position: relative;
		align-items: center;
		justify-content: space-around;
		flex-direction: column;
	}
	.headtitle{
		position: relative;
		color: #0090FF;
		font-size: 30rpx;
		margin-left: 10rpx;
	}
	.sendtime{
		position: relative;
		margin-left: 10rpx;
		color: gray;
		font-size: 20rpx;
	}
	.sendtimer{
		position: relative;
		margin-top: 10rpx;
		color: gray;
		font-size:20rpx;
	}
	.headbox{
		position: relative;
		padding: 20rpx 0;
		display: flex;
		align-items: center;
	}
	.headimg{
		position: relative;
		width:80rpx;
		height: 80rpx;
		background-color: #000000;
		border-radius: 50rpx;
		overflow: hidden;
	}
	.bodybox{
		position: relative;
		width: calc(100% - 48rpx);
		margin-left: 24rpx;
		color: #444;
	}
	.title{
		position: relative;
		width: 100%;
		padding: 20rpx 0;
		font-size: 35rpx;
		font-weight: bold;
		border-bottom: 1px solid #eee;
	}
</style>
