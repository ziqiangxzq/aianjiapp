<template>
	<view class="" >
		<view class="box ub" v-for="(item,index) in noticelist" :key="index" @tap="playvoice(item)">
			<image class="noticepicture" src="../../static/broadcast/stop.jpg" v-show="showUpImg!=item.id" @click="changeImg(item)"></image>
			<image class="noticepicture" src="../../static/broadcast/play.jpg" v-show="showUpImg==item.id" @click="changeImg(item)"></image>
			<view class="list ubb" >
				<view class="content">{{item.notice_content}}</view>
				<view class="time">{{item.create_date}}</view>
			</view>
		</view>
		<view class="isOver" v-if="flag">没有更多了</view>
	</view>
</template>

<script>
	const innerAudioContext = uni.createInnerAudioContext();
	export default{
		data(){
			return{
				noticelist:"",
				showUpImg :"",
				page:1,
				flag:false,
			}
		},
		onLoad() {
			this.get_notice_list();
		},
		methods:{
			changeImg (res){
				if(this.showUpImg!=res.id){//开始播放
					this.showUpImg=res.id;
					innerAudioContext.src=item.mp3_url;
					innerAudioContext.play();
				}else{//暂停
					this.showUpImg="";
					innerAudioContext.pause();
				}
			},
			get_notice_list:function(){
				var that = this;
				var url = '/broadcast/get_noticelist.php';
				var data ={
					page:that.page,
				}
				that.globalRequest(url,data,'POST','JSON','',function(res){
					console.log(res);
					if((res.data.data||[]).length<=0){
						that.flag=true;
					}
					that.noticelist = [...that.noticelist,...res.data.data||[]];
					console.log(noticelist);
				})
			},
			playvoice(res){
				innerAudioContext.autoplay = true;
				innerAudioContext.src =res.mp3_url;
				console.log(res);
				innerAudioContext.onPlay(() => {
				  console.log('开始播放');
				});
				// innerAudioContext.onPause(() =>{
				//   console.log('暂停播放');
				// });
				innerAudioContext.onError((res) => {
				  console.log(res.errMsg);
				  console.log(res.errCode);
				})
				
			},
			onReachBottom(){//分页
				var that = this
				console.log('页面触底了')
				if(!that.flag){
					this.page++
					this.get_notice_list()
				}
				
			}
		}
	}
</script>

<style>
	.list{
		margin: 20upx 10upx;
		flex-direction: row;
		
	}
	.content{
		position: absolute;
		left:130upx;
		flex-direction: row;
		font-size:28upx;
		margin:15 18upx;
	}
	.time{
		
		position: relative;
		right: 15upx;
		margin-top: 80upx;
		font-size: 17.6upx;
		color: #8d8d8d;	
		padding: 10upx;
		text-align: right;
	}
	.box{
		flex-direction: column;
		margin: 10upx 11upx;
		display:flex;
	}
	.noticepicture{
		display: flex;
		position: absolute;
		width: 72upx;
		height: 69upx;
		margin:10upx 20upx;
		left: 10upx;
	}
	.isOver{
		text-align: center;
		font-size: 25upx;
	}
</style>
