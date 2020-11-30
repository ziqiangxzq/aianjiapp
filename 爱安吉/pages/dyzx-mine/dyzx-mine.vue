<template>
	<view>
<!-- 		<view class="floatbox">
			<view class="floatbutton"></view>
			<view class="floatbutton"></view>
		</view> -->
		<view class="nocontent" v-if="nocontent==1">
                       您还没有发布内容~
		</view>
		<view class="ltlistbox">
			<view class="ltitem" @click="opendetail(item.tieba_content_id)" v-for="item,index in luntanlist">
				<view class="headbox">
				<view class="headimage">
					<img :src="item.pics" style="width: 100%;height: 100%;">
				</view>
				<view class="usernick">{{item.user_nick}}</view>
				</view>
				<view class="itemtitle" v-html="item.title"></view>
				<view class="itemcontent" v-html="item.content">
					
				</view>
				<view class="itemcontentimagebox" v-if="item.pic!=''">
				<view class="itemcontentimage" v-for="itam in item.pic">
					<image :src="itam.upload_pic" mode="aspectFill" style="position: absolute;width: 100%;height: 100%;"></image>
				</view>
				</view>
				<view class="footbox">
					<view class="sendtime">发布时间：{{item.create_date}}</view>
					<view class="footrightbox">
					<view class="replynum">{{item.reply_num}} 回复</view>
					<view class="like" @click="changegoodtype(index,item.tieba_content_id)" v-if="item.is_good==0"></view>
					<view class="like liked" @click="changegoodtype(index,item.tieba_content_id)" v-if="item.is_good==1"></view>
					<view class="likenum">{{item.goods_num}}</view>
				    </view>
				</view>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
			luntanlist:[],
			nocontent:0,
			page:1
			}
		},
		onLoad() {
			this.getluntanlist()
		},
		methods: {
		opendetail:function(a){
		uni.setStorageSync("tiebaid",a);
		uni.navigateTo({
			url:"../dyzx-detail/dyzx-detail"
		})		
			},
		changegoodtype:function(index,id){
			uni.request({
				url:'https://www.meilianji.cn/web/news/add_tieba_goods_num.php',
				data:{
                tieba_content_id:id,
				user_id:63714,
				is_new:1
				},
				dataType:"json",
				method:"POST",
				header:{
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: (res) => {
                  console.log(this.luntanlist[index])
				  if(this.luntanlist[index].is_good==1){//取消点赞状态
				  console.log("取消点赞状态");
					this.luntanlist[index].is_good=0;
					this.luntanlist[index].goods_num--;
					console.log(this.luntanlist[index].is_good)
				  }else{//修改为点赞状态
				  console.log("点赞状态");
					this.luntanlist[index].is_good=1; 
					this.luntanlist[index].goods_num++;
					console.log(this.luntanlist[index].is_good)
				  }
				}
			})				
			},
		getluntanlist:function(){//获取个人发布的第一资讯列表
			uni.request({
				url:'https://www.meilianji.cn/web/news/get_user_tieba_content2.php',
				data:{
					user_id:63714,
					page:this.page,
					recs:10
				},
				dataType:"json",
				method:"POST",
				header:{
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: (res) => {
					if(this.page==1){
					if(res.data!=''){
					this.luntanlist=res.data	
					}else{
					this.nocontent=1	
					}	
					}else{
					if(res.data!=''){
					for(var i=0;i<res.data.length;i++){
					this.luntanlist.push(res.data[i])	
					}	
					}else{
					uni.showToast({
						icon:"none",
						title:"没有了~"
					})	
					}	
					}
					

					console.log(this.luntanlist[0].pic[0].upload_pic)
				}
			})
		}	
		},onNavigationBarButtonTap(e) {
			console.log(e.index)
			if(e.index==0){
			uni.navigateTo({
				url:"../dyzx-mine/dyzx-mine"
			})
			}else if(e.index==1){
			uni.navigateTo({
				url:"../dyzx-add/dyzx-add"
			})				
			}
		},onReachBottom(){
			this.page++;
			this.getluntanlist()
		}
	}
</script>
      
<style>
	.nocontent{
		position: relative;
		width: 100%;
		font-size:30rpx;
		color:gray;
		text-align: center;
		padding: 200rpx 0;
	}
	.floatbutton{
		position: relative;
		width: 80rpx;
		height: 80rpx;
		box-shadow:0rpx 0rpx 20rpx 4rpx rgba(0,0,0,0.1);
		border-radius: 100rpx;
		background-color:#0090ff;
		
	}
	.floatbox{
		position:fixed;
		bottom: 0;
		right: 0;
		width: 250rpx;
		height: 100rpx;
		z-index: 10;
		display: flex;
		align-items: center;
		justify-content: space-around;
	}
	.ltitem{
		position: relative;
		width: 100%;
		color: #444;
		border-bottom: 15rpx solid #f8f8f8;
	}
	.footrightbox{
		position: absolute;
		right: 0;
		display: flex;
		align-items: center;
	}
	.likenum{
		position: relative;
		font-size: 20rpx;
		color:gray;
		display: inline-block;		
	}
	.replynum{
		position: relative;
		font-size: 20rpx;
		color:gray;
		display: inline-block;
	}
	.like{
		position: relative;
		margin-left: 20rpx;
		margin-right: 10rpx;
		background-color: #000000;
		display: inline-block;
		background:url("../../static/dyzx/xin.png") no-repeat left ;
		background-size:auto  80% ;
		width: 25rpx;
		height:25rpx;
	}
	.liked{
		background:url("../../static/dyzx/xin1.png") no-repeat left ;
		background-size:auto  80% ;		
	}
	.footbox{
		position: relative;
	    width: calc(100% - 138rpx);
		height: 50rpx;
		margin-top: 10rpx;
		background-color: #fff;
		margin-left:114rpx;
		display: flex;
		align-items: center;
		margin-bottom: 20rpx;
	}
	.sendtime{
		font-size:20rpx;
		color: gray;
	}
	.itemcontentimagebox{
	position: relative;
	width:calc(100% - 138rpx);
	margin-left:114rpx;
	display: flex;
	align-items: center;
	margin-top:20rpx;
	justify-content:space-between;
	}
	.itemcontentimage{
	position: relative;
	width:30%;
	height:150rpx;
	border-radius:10rpx;
	overflow: hidden;
	background-color: #000000;
	}
	.itemcontent{
	 width: 100%;
	 padding: 0 24rpx 0 114rpx;
	 font-size: 25rpx;
	 margin-top: 20rpx;
     color:gray;
	 overflow : hidden;
	 text-align: justify;
	 text-overflow: ellipsis;
	 display: -webkit-box;
	 -webkit-line-clamp:3;
	 -webkit-box-orient: vertical;
	}
	 .headbox{
		 position: relative;
		 width: 100%;
		 height: 80rpx;
		 line-height: 80rpx;
		 display: flex;
		 align-items:center;
		 padding: 0 24rpx;
	 }
 .usernick{
	 color: #0090ff;
	 margin-left:20rpx;
 }
 .headimage{
	 position: relative;
	 width: 70rpx;
	 height:70rpx;
	 overflow: hidden;
	 border: none;
	 box-shadow:0rpx 0rpx 20rpx 4rpx rgba(0,0,0,0.1);
	 background-color: #000000;
	 border-radius: 80rpx;
 }
 .itemtitle{
	 width: 100%;
	 padding: 0 24rpx 0 114rpx;
	 font-size: 30rpx;
 }
</style>
