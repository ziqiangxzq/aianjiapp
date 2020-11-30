<template>
	<view>
		<view class="body">
			<input v-model="inputtitle" class="addtitle" type="text" placeholder="请输入主题">
			<textarea v-model="inputcontent" class="addcontent" type="text" placeholder="请输入内容"></textarea>
			<view class="buttonbox">
				<view class="uploadbutton" @click="choiceimg()">
					<img src="../../static/dyzx/camer.png" style="width: 100%;height: 100%;">
				</view>
				<view class="uploadbutton" @click="choicevideo()">
					<img src="../../static/dyzx/video.png" style="width: 100%;height: 100%;">
				</view>
			</view>
			<view class="imagebox" v-if="upimgarr!=''">
				<image :src="item.imgsrc" style="width: 33%;height: 160rpx;background-color: #000000;" mode="aspectFill" v-for="item in upimgarr">
			</view>
			<view class="videobox" v-if="videoshow==1">
				<video style="width: 100%;margin-top: 24rpx;" :src="videolicalurl"></video>
			</view>
			<view class="submitbutton" @click="submit()">发布</view>
		</view>
	</view>
</template>

<script>
	import MD5 from '../../common/MD5.js';
	export default {
		data() {
			return {
				videolicalurl:"",
				videosrc:'',
				videoshow:0,
				length:3,
				inputtitle:'',
				inputcontent:'',
				upimgarr:[],//本地图片数组
				subimgarr:[]//本地图片数组
			}
		},
		methods: {
			submitmsg:function(){
				        var dataobj=[{
							"tieba_category_id":4,
							"user_id":63714,
							"title":this.inputtitle,
							"content":this.inputcontent,
							"pic":this.subimgarr.join(";"),
							"video_code":this.videosrc
						}];
						uni.request({
							url:"https://www.meilianji.cn/web/news/release_content.php?json="+encodeURIComponent(JSON.stringify(dataobj)),
							data:{
							},
							dataType:"json",
							method:"POST",
							header:{
									"content-type":"application/x-www-form-urlencoded"
							},success: (res) => {
								console.log(res.data);
								if(res.data[0].resultid==1){
									uni.showToast({
										icon:'none',
										title:'提交成功！'
									})
									setTimeout(
										function(){
                                        uni.navigateBack({})
										},1500)
								}
                                console.log(res.data)
							}
						})		
			},
			submit:function(){
					if(this.inputtitle!=''){
						if(this.inputcontent!=''){
							this.uploadimg(0)
						}else{
						uni.showToast({
							icon:'none',
							title:"请输入发布内容~"
						})	
						}
					}else{
						uni.showToast({
							icon:'none',
							title:"请输入发布主题~"
						})
					}
			}
			,
			uploadimg:function(a){
				if(a<this.upimgarr.length){//图片上传
				var d = new Date();
				var imgName=d.getTime()+'10072';		
				uni.uploadFile({
					url:'https://www.meilianji.cn/radio/uploadimg/index.php?imgName='+imgName+'&imgPath=dyzx',
					filePath:this.upimgarr[a].imgsrc,
					fileType: 'image',
					name:'filename',
					success: (res) => {
				       var data = eval('(' + res.data + ')');
					   console.log("xxxxxxxxxxxxxxxxxxxxxx");
					   console.log(data);
					    this.subimgarr.push(data.pics);
						a++;
						this.uploadimg(a)	
					},
					fail: (err) => {
						
						uni.showModal({
							content: err.errMsg,
							showCancel: false
						});
					}
				});
				}else{//视频上传
				this.uploadvideo()	
				}

			},
			uploadvideo:function(){
			if(this.videolicalurl!=''){
            var tmp = Date.parse( new Date() ).toString();
            tmp = tmp.substr(0,10);
            var sig=  MD5(tmp +"32dd3c0eb6340a932a990e5832a0d2cf");
			var d = new Date();
			var imgName=d.getTime()+'10072';		
		    uni.uploadFile({
					url:'http://www.meilianji.cn/web/upload/uploadImg.php?imgName='+imgName+'&imgPath=dyzx&timestamp='+tmp+'&sign='+sig,
					filePath:this.videolicalurl,
					fileType: 'video',
					name:'filename',
					success: (res) => {
					 var data = eval('(' + res.data + ')');	
					 console.log(data.data.pic_path);
					 this.videosrc=data.data.pic_path;
					 this.submitmsg()

					},
					fail: (err) => {
						
						uni.showModal({
							content: err.errMsg,
							showCancel: false
						});
					}
				});				
			}else{
			this.submitmsg()	
			}

			},
			choiceimg:function(){//选择图片或拍摄图片
			uni.chooseImage({
				count:this.length,
				sizeType: ['compressed'],
				success: (res) => {
					console.log('chooseImage success, temp path is', res.tempFilePaths);
					var imageSrc = res.tempFilePaths;
					for(var i=0;i<imageSrc.length;i++){
					var obj={
					imgsrc:imageSrc[i],
					index:"i"	
					};	
					this.upimgarr.push(obj);			
					}
					//this.uploadimg()
				},
				fail: (err) => {
					console.log('chooseImage fail', err)
					// #ifdef MP
					uni.getSetting({
						success: (res) => {
							let authStatus = res.authSetting['scope.album'];
							if (!authStatus) {
								uni.showModal({
									title: '授权失败',
									content: 'Hello uni-app需要从您的相册获取图片，请在设置界面打开相关权限',
									success: (res) => {
										if (res.confirm) {
											uni.openSetting()
										}
									}
								})
							}
						}
					})
					// #endif
				}
			})
				
			},
			choicevideo:function(){//选择视频或拍摄视频
			var that=this;
			uni.chooseVideo({
				   count: 1,
				   sourceType: ['camera', 'album'],
				   success: function (res) {
					   that.videolicalurl=res.tempFilePath;
					   that.videoshow=1;
				                }
			})
				
			}
		}
	}
</script>

<style>
	.imagebox{
		position: relative;
		width: 100%;
		padding: 10rpx;
		border-radius: 10rpx;
		background-color: #eee;
		display:flex;
		justify-content:space-around;
	}
	.videobox{
		position: relative;
		width: 100%;
		padding: 10rpx;
		border-radius: 10rpx;
		margin-top: 24rpx;
		background-color: #eee;
		min-height: 1rem;
/* 		border:5rpx solid #18B566; */
	}
	.uploadbutton{
		position: relative;
		width: 120rpx;
		height:120rpx;
		background-color: #000;
		display: inline-block;
		margin-right: 10rpx;
	}
.body{
	position: relative;
	width: 100%;
	color:#444;
    padding:24rpx;	
}
.buttonbox{
	position: relative;
	width: 100%;
	margin-top: 24rpx;
}
.submitbutton{
	position: relative;
	width:100%;
	margin-top: 24rpx;
	padding: 20rpx 0;
	text-align:center;
	color: #fff;
	background-color: #0090ff;
	border-radius: 10rpx;
}
.addtitle{
	position: relative;
	width:calc(100% - 20rpx);
	padding:20rpx 10rpx;
	font-size: 28rpx;
	border-radius: 10rpx;
	background-color: #f8f8f8;
}
.addcontent{
	position: relative;
	width:calc(100% - 20rpx);
	margin-top: 24rpx;
	padding:20rpx 10rpx;
	font-size: 28rpx;
	border-radius: 10rpx;
	background-color: #f8f8f8;
}
</style>
