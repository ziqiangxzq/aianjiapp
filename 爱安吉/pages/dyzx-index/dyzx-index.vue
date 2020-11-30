<template>
	<view>
<!-- 		<view class="floatbox">
			<view class="floatbutton"></view>
			<view class="floatbutton"></view>
		</view> -->
		<view class="sendbutton" @click="openaddtieba()">
			
		</view>
		<adv :category_id="3"></adv>
		<view class="ltlistbox">
			<view class="ltitem ubb bc-border" @click="opentiebadetail(item.tieba_content_id)" v-for="item,index in luntanlist">
				<view class="headbox">
				<view class="headimage">
					<img :src="item.pics" style="width: 100%;height: 100%;">
				</view>
				<view class="usernick">{{item.user_nick}}</view>
				</view>
				<view class="itemtitle" v-html="item.title"></view>
				<view class="itemcontent" v-html="item.content">
					
				</view>
				<view class="itemcontentimage" v-if="item.pic.length!=0" v-for="itam in item.pic">
					<image :src="itam.upload_pic" mode="aspectFill" style="width: 100%;height: 100%;"></image>
				</view>
				<view class="footbox">
					<view class="sendtime">{{item.create_date}}</view>
					<view class="footrightbox">
					<view class="replynum" style="color:#cdcdcd">
					<view class="commentbox"></view>{{item.reply_num}}
					</view>
					<view class="like" @click="changegoodtype(index,item.tieba_content_id)" v-if="item.is_good==0"></view>
					<view class="like liked" @click="changegoodtype(index,item.tieba_content_id)" v-if="item.is_good==1"></view>
					<view class="likenum" style="color:#cdcdcd">{{item.goods_num}}</view>
				    </view>
				</view>
			</view>
		</view>
	</view>
</template>

<script>
	import adv from '../../components/adv.vue'
	import slideshowHead from '../../components/slideshow-head.vue';
	export default {
		components:{slideshowHead,			
		adv},
		data() {
			return {
			page:1,
			luntanlist:[],
			slidearr: [{url: 'http://www.baidu.com', type:'',id:'',src: '../../static/radio/poster.png' }, {url: 'http://www.baidu.com', src: '../../static/radio/poster.png' }],
			}
		},
		onLoad() {
			this.getluntanlist()
		},
		methods: {
		openaddtieba:function(){
		uni.navigateTo({
			url:'../dyzx-add/dyzx-add'
		})	
		},
		opentiebadetail:function(a){
			uni.setStorageSync("tiebaid",a);
			uni.navigateTo({
				url:'../dyzx-detail/dyzx-detail'
			})
				console.log(a)
			},
		changegoodtype:function(index,id){
			window.event?window.event.cancelBubble=true : e.stopPropagation();
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
		getluntanlist:function(){
			uni.request({
				url:'https://www.meilianji.cn/web/news/get_tieba_content_by_category.php',
				data:{
					recs:15,
					page:this.page,
					tieba_category_id:4,
					user_id:63714
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
					//console.log(this.luntanlist[0].pic[0].upload_pic)						
					}else{
					uni.showToast({
						icon:"none",
						title:"暂无内容"
					})	
					}
					}else{
					if(res.data!=''){
					for(var i=0;i<res.data.length;i++){
					this.luntanlist.push(res.data[i])	
					}	
					}else{
					uni.showToast({
						icon:"none",
						title:"暂无内容"
					})							
					}	
					}

				}
			})
		}	
		},onNavigationBarButtonTap(e) {
			console.log(e.index)
			if(e.index==0){
			uni.navigateTo({
				url:"../dyzx-mine/dyzx-mine"
			})
			}
		},onReachBottom(){
		  // console.log("xxxxxxxxxxxxxxxxxxxxxxx");
           this.page++;
		   this.getluntanlist()
		}
		
	}
</script>
      
<style>
	.sendbutton{
		position: fixed;
		bottom:300rpx;
		right: 50rpx;
		width: 80rpx;
		height:80rpx;
		background: url(../../static/dyzx/add.png) no-repeat center;
		background-size: 100% 100%;
		border-radius: 40rpx;
		z-index: 20;
	}
	.floatbutton{
		position: relative;
		width: 80rpx;
		height: 80rpx;
		box-shadow:0rpx 0rpx 20rpx 4rpx rgba(0,0,0,0.1);
		border-radius: 100rpx;
		background-color:#0090ff;
	}
	.headadimage{
		position: relative;
		width: 100%;
		background-color: #000000;
		margin-bottom:30rpx;
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
		/* border-bottom: 15rpx solid #f8f8f8; */
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
		display:flex;
		align-items: center;
	}
	.commentbox{
	position: relative;
	margin-left: 20rpx;
	margin-right: 10rpx;
	background-color: #000000;
	display: inline-block;
	background:url("../../static/dyzx/comment.png") no-repeat left ;
	background-size:auto  100% ;
	width: 25rpx;
	height:25rpx;	
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
	    width: calc(100% - 48rpx);
		height: 50rpx;
		margin-top: 20rpx;
		background-color: #fff;
		margin-left:24rpx;
		display: flex;
		align-items: center;
		margin-bottom: 20rpx;
	}
	.sendtime{
		font-size:20rpx;
		color:#b3b3b3;
	}
	.itemcontentimage{
	position: relative;
	width: calc(100% - 48rpx);
	height: 300rpx;
	background-color: #fff;
	margin-left:24rpx;
	margin-top: 20rpx;
	border-radius: 10rpx;
	overflow: hidden;
	}
	.itemcontent{
	 width: 100%;
	 padding: 0 24rpx 0 24rpx;
	 font-size: 24rpx;
     color:gray;
	 overflow : hidden;
	 text-align: justify;
	 text-overflow: ellipsis;
	 display: -webkit-box;
	 -webkit-line-clamp:2;
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
	 padding:24rpx;
	 font-size: 30rpx;
 }
</style>
