<template>
	<view>
<!-- 		<view style="width: 100%;hieght:2rem;background-color: #000000;">
		<audio style="width: 100%;height: 100%;" src="https://lss-55718baeb5b2b6d4.hlsplay.aodianyun.com/tv_radio_32664/radio_channel_595__redirect__32664.m3u8" controls=""></audio>
		</view> -->
		<slideshowHead :imgarr="slidearr"></slideshowHead>
		<lab name="主播"></lab>
		<view class="anchorbox">
			<view class="anchoritem" @click="openprodetail(item.radio_id)" v-for="item in anchorboxarr">
				<view class="itemimg">
					<image :src="item.pic_url" style="width: 100%;height: 100%;">
				</view>
				<view class="itemtitle" v-html="item.title"></view>
			</view>
		</view>
		<lab name="节目"></lab>
		<view class="anchorbox">
			<view class="programitem" @click="openprogramdetail(item.video_uri,item.title,item.pic_uri,item.look_people)" v-for="item in programarr">
				<view class="itemimg">
					<img :src="item.pic_uri" style="width: 100%;height: 100%;">
				</view>
				<view class="itemtitlea" v-html="item.title"></view>
			</view>
		</view>
		<view class="footbox" v-if="showtype==1">
			<view class="radiohead" >
				<image :src="musicposter" mode="aspectFill">
			</view>
			<view class="radiotitle">声动101</view>
			<view class="buttonbox">
				<view class="button" @click="changemusictype()">
					<img :src="typeimage">
				</view>
				<view class="button" @click="hideit()">
					<img src="static/radio/close.png">
				</view>
			</view>
		</view>
		<view class="footsmlbox"  @click="showit()" v-if="showtype==0">
			<view class="imghead">
				<img src="static/radio/1001.png" style="width: 100%;height: 100%; background-color: #f7970f;">
			</view>
		</view>
	</view>
</template>

<script>
	var  bgAudioMannager = uni.createInnerAudioContext();
	import slideshowHead from 'components/slideshow-head.vue';
	import lab from "components/lab.vue"
	export default {
		components:{lab,slideshowHead},
		data() {
			return {
			play:0,
			slidearr: [{url: 'http://www.baidu.com', type:'',id:'',src: '../../static/radio/poster.png' }, {url: 'http://www.baidu.com', src: '../../static/radio/poster.png' }],
			musicip:"",
			musicposter:"../../static/radio/1001.png",
			musictitle:"",
			anchorboxarr:[1,1,1,1],
			programarr:[1,1,1],
			typeimage:"../../static/radio/play.png",
			showtype:1//1为100%全屏展示 0为隐藏展示
			}
		},
		onLoad() {
		},
		onShow(){
		},
		created() {
			this.getradiolist();
			this.getarchlist();
			this.getprogramlist();
		},
		methods: {
			showit:function(){
			this.showtype=1	
			},
			hideit:function(){
			this.showtype=0	
			},
			openprogramdetail:function(a,b,c,d){
				uni.setStorageSync("radiourl",a);
				uni.setStorageSync("radiotitle",b);
				uni.setStorageSync("radioposter",c);
				uni.setStorageSync("radiolooknum",d);
				uni.navigateTo({
					url:"../radio-programdetail/radio-programdetail"
				})
			}
			,
			changemusictype:function(){
				// 音频播放 使用uni自定义插件uni.createInnerAudioContext()进行播放
				// uni.createInnerAudioContext()只需全局创建一次即可 多次创建会出现多条并发音轨
				// 全局创建后在自定义播放暂停方法中调用插件的play() pause()/stop()方法即可控制音频的播放和暂停
				
				//方案1
				//调用main.js文件中定义好的播放方法 由于是在播放方法中注册创建uni.createInnerAudioContext() 所以调用暂停方法时会创建多条音轨 这样会造成音频暂停无效
				// if(this.play==0){//目前为暂停状态 开始播放 
                //    this.ScanAudio(0);	
				// this.play=1
				// }else{//目前为播放状态 暂停
				// this.ScanAudio(1);
				// this.play=0
				// }
                //方案三  //可正常播放暂停
				 bgAudioMannager.autoplay = false;
				 bgAudioMannager.src = this.musicip;
				 //'https://lss-55718baeb5b2b6d4.hlsplay.aodianyun.com/tv_radio_32664/radio_channel_595__redirect__32664.m3u8';
				 //bgAudioMannager.src="https://img-cdn-qiniu.dcloud.net.cn/uniapp/audio/music.mp3";
				 if(this.play==0){
				 	bgAudioMannager.play()
				 	bgAudioMannager.onPlay(()=>{
						this.typeimage="static/radio/pause.png";
				 		console.log("已播放");
						this.play=1
				 	})
				 }else{
				 	bgAudioMannager.stop();
				 	bgAudioMannager.onStop(()=>{
						this.typeimage="static/radio/play.png";
				 		console.log("已暂停");
						this.play=0
				 	})
				 }
				//方案2 与方案一相同 由于uni.createInnerAudioContext()不是只创建一次 在暂停一条音轨后又会创建一条音轨 会造成多条音轨同时播放
				// const innerAudioContext = uni.createInnerAudioContext();
				// innerAudioContext.autoplay = true;
				// innerAudioContext.src = 'https://lss-55718baeb5b2b6d4.hlsplay.aodianyun.com/tv_radio_32664/radio_channel_595__redirect__32664.m3u8';
				// innerAudioContext.onPlay(() => {
				//   console.log('开始播放');
				// });
				// innerAudioContext.onError((res) => {
				//   console.log(res.errMsg);
				//   console.log(res.errCode);
				// });
			},
			createmusic:function(){
			},
			getarchlist:function(){//获取主播列表
			uni.request({
				url:this.globalUrl+"/radio/get_radio_list.php",
				dataType:"json",
				method:"POST",
				data:{
					page:1,
					recs:100
				},
				header:{
						"content-type":"application/x-www-form-urlencoded"
				},
				success: (res) => {
					this.anchorboxarr=res.data;
					console.log(res.data)
				}})
			},
			getprogramlist:function(){//获取节目列表
				uni.request({
					url:this.globalUrl+"/wchat/get_wchat_playback.php",
					dataType:"json",
					method:"POST",
					data:{
					category_id:7,
					recs:100,
					page:1},
					header:{
							"content-type":"application/x-www-form-urlencoded"
					},
					success: (res) => {
						this.programarr=res.data;
						console.log(res.data)
					}})
			},
			getradiolist:function(){
				uni.request({
					url:this.globalUrl+"/video/get_video_live_category.php",
					dataType:"json",
					method:"POST",
					data:{},
					header:{
							"content-type":"application/x-www-form-urlencoded"
					},
					success: (res) => {
						for(var i=0;i<res.data.length;i++){
							if(res.data[i].if_radio==1&&res.data[i].category_id==129){
								console.log(res.data[i].pic);
								this.musicip=res.data[i].ip;
								//this.musicposter=res.data[i].pic;
								this.musictitle=res.data[i].category_name;
								//uni.createInnerAudioContext()
							 }
						}
                        console.log(res.data)
					}
				})
			},
			openprodetail:function(a){
				uni.setStorageSync("radio_id",a);
				uni.navigateTo({
					url:'../radio-anchordetail/radio-anchordetail'
				})
				console.log(a)
			}
		}
	}
</script>

<style>
	.imghead{
		position: absolute;
		width: 50rpx;
		height: 50rpx;
		right:10rpx;
		top: 10rpx;
		overflow: hidden;
		border-radius: 150rpx;
		background-color: #fff;
	}
	.footsmlbox{
	position:fixed;
	width: 120rpx;
	height: 70rpx;
	bottom:130rpx;
	border-radius: 0 50rpx 50rpx 0;
	background-color:rgba(0,0,0,0.8);
	margin-left:0;
	}
    .anchorbox{
		position: relative;
		overflow-x:scroll;
		white-space:nowrap
	}
	.anchoritem{
		position: relative;
		padding: 20rpx 20rpx 0 20rpx;
		width:340rpx;
		display: inline-block;
	}
	.programitem{
		position: relative;
		padding: 20rpx 20rpx 0 20rpx;
		width:340rpx;
		display: inline-block;
	    line-height: 0;
	}
	.itemimg{
		position: relative;
		width:300rpx;
		height:180rpx;
		overflow: hidden;
		border-radius:20rpx;
		background-color: #000000;
	}
	.itemtitle{
		position: relative;
		width: 100%;
		height: 2rem;
		color: #444;
		text-align: center;
		padding: 10rpx 0;
		overflow: hidden;
		white-space: nowrap;
		text-overflow: ellipsis;
		display: flex;
		align-items: center;
		justify-content: center;
	}
	.itemtitlea{
		position: relative;
		width: 100%;
		height: 100rpx;
		line-height:80rpx;
		color: #444;
		text-align: center;
		padding: 10rpx 0;
		overflow: hidden;
		white-space: nowrap;
		text-overflow: ellipsis;
	}
	.headadbox{
		position: relative;
		width: 100%;
		height:8rem;
		background-color: #000000;
	}
	.buttonbox{
		position:absolute;
		right:5rpx;
		display: flex;
		align-items: center;
	}
	.button{
		position: relative;
		width: 55rpx;
		margin-right: 20rpx;
		height: 55rpx;
	}
	.button img{
		width:100%;
		height:100%;
	}
	.radiotitle{
		position: relative;
		color: #fff;
		font-size: 30rpx;
		margin-left:10rpx;
	}
.radiohead{
	width:135rpx;
	height:135rpx;
	background:url(../static/radio/radiobg.png) no-repeat center;
	background-size: 100% 100%;
	border-radius: 100rpx;
	background-color: #000000;
	display: flex;
	align-items: center;
	justify-content: center;
}	
.radiohead image{
	position: relative;
	width: 70rpx;
	height:70rpx;
	border-radius: 80rpx;
}
.footbox{
	position:fixed;
	bottom:120rpx;
	margin-left: 24rpx;
	height:120rpx;
	display:flex;
	align-items: center;
	width: calc(100% - 48rpx);
	background-color: rgba(0,0,0,0.4);
	border-radius:100rpx;
}
</style>

