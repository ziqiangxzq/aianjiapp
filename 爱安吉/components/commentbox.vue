<template>
	<view>
	<view class="commentfloatbox" v-if="floatboxshow == 1">
		<view class="commentbox">
			<view class="commentrel">
				<view class="commentheadbox">
				<!-- 	{{ commenttext.length }}/500字 -->
					<view class="buttonbox">
						<view class="buttoncal" @click="hidefloatbox()">取消</view>
						<view class="buttonsub bluebg" @click="submitcomment()">提交</view>
					</view>
				</view>
				<view class="inputbox">
					<textarea v-model="commenttext" @focus="hideother()" v-if="textshow == 1" class="textarea" placeholder="请输入您的评论~"></textarea>
				</view>
				<view class="commentfootbox" v-if="opimage==1&&opemjo==1">
					<view class="imgbutton" v-if="opimage==1" @click="showimg()"><img :src="imgbuttonsrc" /></view>
					<view class="videobutton" v-if="opemjo==1" @click="showemoji()"><img :src="emojibuttonsrc" /></view>
				</view>
			</view>
		</view>
		<view class="bottmbox">
			<view class="imginputbox"  v-if="imageshow == 1">
				<view style="position:relative;width: 5.5rem;height:5.5rem;margin:0.4rem;border-radius: 0.4rem;"  v-for="item in upimgarr">
					<image @click="seeimage(item.imgsrc)" :src="item.imgsrc"  style="width: 100%;height: 100%;" mode="aspectFill">
					<view class="del" @click="delimg(item.index)">
						<img src="../static/close.png" style="width:20rpx;height:20rpx;">
					</view>	
			    </view>  	
			<view style="color: gray;"  v-if="upimgarr.length ==0">请上传您的图片~</view>
			<view class="imguploadbox" v-if="upimgarr.length < 3">
				<img @click="choiceimage()" src="../static/zb/add.png" />
			</view>
			<view class="alertmsg">{{upimgarr.length}}/3</view>
			</view>
		<view class="videoinputbox" v-if="emojishow == 1">
		<view class="emojibox">
			<view class="emojiitem" v-for="item in emojiarr">
				<img style="width:60rpx;height:60rpx" @click="choiceemoji(item.name)" :src="item.url">
			</view>
		</view>	
		</view>
		</view>
		
	</view>
	</view>
</template>
<script>
	//<commentbox ref="commentbox" opemjo="0" opimage="1" ajaxname="json" ajaxurl="news/reply_content.php" newsid="tieba_content_id" userid="user_id" textname="reply_content" picname="reply_pic"  :newsidvalue="tiebaid" useridvalue="63714"></commentbox>
	//"floatboxshow" 控制floatbox的显示隐藏 1显示0隐藏
	//"opemjo" 控制是否上传emjo内容
	//"opimage" 控制是否上传图片内容
	//"ajaxurl" 评论上传接口地址
	//"newsid"  接口内上传参数 关键字id
	//"userid"  接口内上传梣属 用户id
	//"textname" 接口内上传参数 文字内容
	//"picname"  接口内上传参数图片地址
	//"ajaxname" ajax传参名称
	//"othername" ajaxjson数组内其他属性
	//"othervalue" ajax数组内其他属性值
	export default {
		props: ["floatboxshow","opemjo","opimage","ajaxurl","newsid","userid","textname","picname","newsidvalue","useridvalue","ajaxname","othername","othervalue"],
		data() {
			return {
		    subimgarr:[],
			upimgarr:[],
			upimglength:3,
			emojishow: 0,
			imageshow: 0,
			textshow: 1,
			commenttext: '',
			imgbuttonsrc: '../static/zb/img.png',
			emojibuttonsrc: '../static/zb/smail.png',
			emojiarr:[],
			};
		},
		onLoad() {
	    //console.log(this.othername)
		}
		,methods:{
			seeimage:function(image){//图片预览
							var imgArr = [];
							imgArr.push(image);
							//预览图片
							uni.previewImage({
								urls: imgArr,
								current: imgArr[0]
							});
					},
			delimg:function(a){//删除图片数组
			this.upimgarr.splice(a,1);
			console.log(this.upimgarr);
			},
			hideother:function(){//隐藏底部图片上传框和表情框
			this.imgbuttonsrc = '../static/zb/img.png';
			this.emojishow=0;
			this.imageshow=0;
			this.textshow=1;	
			},
			choiceimage:function(){
			var length=this.upimglength - this.upimgarr; 
			uni.chooseImage({
				count:length,
				sizeType: ['compressed'],
				sourceType: ['album'],
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
			var that=this;
			setTimeout(function(){
				console.log(that.upimgarr);
			},500)
			},
			getxml:function(){//从xml文件中获取信息创建表情数组
			console.log("getemojiarr");
			uni.request({
				
				url:"../static/emojicons/emojicons.xml",
				dataType:"text/xml",
				success: (res) => {
					var name=res.data.match(/<key>(\S*)key>/g);
					var url=res.data.match(/<string>(\S*)string>/g);
					for(var i=0;i<name.length;i++){
						var reg = new RegExp("<key>","g");
						var rea = new RegExp("</key>","g");
						name[i]=name[i].replace(reg,"");
						name[i]=name[i].replace(rea,"");
					}
					for(var i=0;i<url.length;i++){
						var reg = new RegExp("<string>","g");
						var rea = new RegExp("</string>","g");
						url[i]=url[i].replace(reg,"");
						url[i]=url[i].replace(rea,"");
					}
					for(var r=0;r<name.length;r++){
						var obj={
							name:name[r],
							url:"../static/emojicons/"+url[r]
						}
						this.emojiarr.push(obj)
					}
					console.log(this.emojiarr);
					var str = res.data.substring(res.data.indexOf("<key>") + 5,res.data.indexOf("</key>"))
					console.log(str)
					// let a = new DOMParser()​​;
					// var xmldoc=a.parserFromString(res.data,'application/xml')
				 //    console.log(xmldoc)
				}
			})		
			},
			uploadimg:function(a){//上传图片到服务器 上传完成发布评论
				//console.log(this.upimgarr[a]);
				if(a<this.upimgarr.length){
				//console.log(this.upimgarr[a]);
				var d = new Date();
				var imgName=d.getTime()+'10072';	
				uni.uploadFile({
					//url:'http://xinchang.meilianji.cn/main/uploadimg/index.php?imgName='+imgName,
					url:'https://www.meilianji.cn/radio/uploadimg/index.php?imgName='+imgName+'&imgPath=minyi',
					//url:'http://vol.jingdongxincheng.net/volunteer/activity_summary/uploadimg/index.php?imgName='+imgName,
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
				}else{
				this.subcomment()	
				}

			},
			submitcomment:function(){//先上传图片 图片上传完成后再发布评论
			//console.log(this.ajaxurl)
			this.uploadimg(0);
			}
			,
			subcomment: function() {//发布评论
			    var newsid= this.newsid;
				var userid=this.userid;
				var textname=this.textname;
				var picname=this.picname;
		        var newsidvalue=this.newsidvalue;
				var useridvalue=this.useridvalue;
				var othername=this.othername;
				console.log("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxop");
				console.log(this.othername);
				var commentjson ={};
				commentjson[newsid]= newsidvalue;
				commentjson[userid]= useridvalue;
				commentjson[textname]= this.commenttext;
				commentjson[picname]= this.subimgarr.join(";");
				if(othername!=''){
				commentjson[othername]= this.othervalue;	
				}
				var commentjsona = [commentjson];
				
				uni.request({
					url:this.ajaxurl+"?"+this.ajaxname+"="+JSON.stringify(commentjsona),
					data: {
					},
					method: 'POST',
					dataType: 'json',
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					success: res => {
						var that = this;
						if (res.data[0].resultid == 1) {
							uni.showToast({
								icon: 'none',
								title:"发送成功，请等待审核~"
							});
							this.commenttext = '';
							setTimeout(function() {
								that.hidefloatbox();
							}, 1500);
						} else {
							uni.showToast({
								icon: 'none',
								title: res.data[0].message
							});
						}
						console.log(res.data);
					}
				});
			},
			hidefloatbox: function() {//隐藏浮动窗口
				this.floatboxshow = 0;
			},
			showcommentfloatbox: function() {
				console.log("ppppppppppppp");
				this.floatboxshow = 1;
			},
			showemoji: function() {//展示表情窗口
				if(this.emojishow==0){
				this.getxml();
				this.imgbuttonsrc = '../static/zb/img.png';
				this.imageshow = 0;
				this.textshow = 1;
				this.emojishow = 1;	
				}else{
				this.imgbuttonsrc = '../static/zb/img.png';
				this.emojibuttonsrc = '../static/zb/smail.png';
				this.imageshow = 0;
				this.textshow = 1;
				this.emojishow = 0;						
				}

				// if (this.videoshow == 0) {
				// 	this.imgbuttonsrc = '../static/zb/img.png';
				// 	this.emojibuttonsrc = '../static/zb/smail.png';
				// 	this.imageshow = 0;
				// 	this.textshow = 0;
				// 	this.videoshow = 1;
				// } else {
				// 	this.imgbuttonsrc = '../static/zb/img.png';
				// 	this.emojibuttonsrc = '../static/zb/smail.png';
				// 	this.imageshow = 0;
				// 	this.textshow = 1;
				// 	this.videoshow = 0;
				// }
			},
			showimg: function() {//展示评论图片上传窗口
				if (this.imageshow == 0) {
					this.imgbuttonsrc = '../static/zb/imged.png';
					this.emojibuttonsrc = '../static/zb/smail.png';
					this.imageshow = 1;
					this.textshow = 1;
					this.emojishow = 0;
				} else {
					this.imgbuttonsrc = '../static/zb/img.png';
					this.emojibuttonsrc = '../static/zb/smail.png';
					this.imageshow = 0;
					this.textshow = 1;
					this.emojishow = 0;
				}
			},
		choiceemoji:function(a){//选择表情符号 并添加到输入框中
			this.commenttext=this.commenttext+a;
		}	
		}
	}
</script>
<style>
	.alertmsg{
		position:absolute;
		bottom:28rpx;
		left:28rpx;
		color: gray;
	}
	image{
		border-radius: 0.4rem;
		overflow: hidden;
	}
	.del{
		position:absolute;
		width: 35rpx;
		height: 35rpx;
		right: -8rpx;
		top: -8rpx;
		display:flex;
		align-items: center;
		justify-content: center;
		border-radius: 100rpx;
		background-color:#dd0000;
	}
	.bottmbox{
		position: fixed;
		bottom: 0;
		width: 100%;
		height: 400rpx;
	}
	.emojiitem{
			position: relative;
			width: 80rpx;
			height:80rpx;
			display: inline-block;
			margin-left:10rpx;
			padding: 20rpx;
		}
	.emojibox{
		position: relative;
		width:100%;
		height:100%;
		overflow-y: scroll;
		background-color: #fff;
	}
	.textarea {
		position: relative;
		width: calc(100% - 48rpx);
		padding: 24rpx;
		height: 180rpx;
		font-size: 28rpx;
		border-radius: 10rpx;
		background-color: #fff;
		border: 1px solid #eee;
	}
	
	.imgbutton {
		position: relative;
		width: 80rpx;
		height: 80rpx;
		background-color: #fff;
		display: flex;
		align-items: center;
		justify-content: center;
	}
	.imgbutton img {
		width: 50rpx;
		height: 50rpx;
	}
	.videobutton {
		position: relative;
		width: 80rpx;
		height: 80rpx;
		background-color: #fff;
		display: flex;
		align-items: center;
		justify-content: center;
		margin-left: 20rpx;
	}
	.videobutton img {
		width: 50rpx;
		height: 50rpx;
	}
	
	.commentfootbox {
		position: absolute;
		bottom: 0;
		height: 80rpx;
		width: calc(100% - 48rpx);
		padding: 0 24rpx;
		display: flex;
		align-items: center;
		justify-content: left;
		background-color: #fff;
	}
	.imguploadbox{
	    position:absolute;
		right: 0;
		bottom: 0;
		padding: 10rpx;
	/* 	width: 90rpx;
		height: 90rpx; */
		background-color:#0090ff;
		border-radius:0.4rem 0 0 0;
		display: flex;
		align-items: center;
		justify-content: center;	
	}
	.imguploadbox img {
		width: 70rpx;
		height: 70rpx;
	}
	.videoinputbox img {
		width: 70rpx;
		height: 70rpx;
	}
	.videoinputbox {
		position: relative;
		width: 100%;
		height:100%;
		background-color: gray;
		border-radius: 20rpx;
		display: flex;
		align-items: center;
		justify-content: center;
	}
	.imginputbox{
		position: relative;
		width:100%;
		height:100%;
		background-color: #fff;
		display: flex;
		align-items: center;
		justify-content: center;
	}
	.inputbox {
		position: relative;
		width: calc(100% - 48rpx);
		margin-left: 24rpx;
		height: 228rpx;
		border-radius: 10rpx;
		background-color: #eee;
		display: flex;
		align-items: center;
		justify-content: center;
	}
    
	.button {
		position: relative;
		padding: 8rpx 20rpx;
		color: #fff;
		font-size: 30rpx;
		border-radius: 10rpx;
		display: inline-block;
		background-color: #afafaf;
	}
	.buttoncal {
		position: absolute;
		left: 0;
		padding: 8rpx 20rpx;
		color: #fff;
		font-size: 28rpx;
		border-radius: 10rpx;
		display: inline-block;
		background-color: #afafaf;
	}
	.buttonsub {
		position:absolute;
		right: 0;
		padding: 8rpx 20rpx;
		color: #fff;
		font-size: 28rpx;
		border-radius: 10rpx;
		display: inline-block;
		background-color: #afafaf;
	}
	.buttonbox {
		position: absolute;
		width:calc(100% - 48rpx);
		right: 24rpx;
		top: 18rpx;
	}
	.commentheadbox {
		position: relative;
		width:100%;
		padding: 24rpx;
		height: 90rpx;
		font-size: 30rpx;
	}
	.commentbox {
	position: fixed;
	bottom: 600rpx;
	width: calc(100% - 48rpx);
	margin-left: 24rpx;
	height: 440rpx;
	border-radius: 20rpx;
}
	.commentfloatbox {
		position: fixed;
		width: 100%;
		height: 100%;
		top: 0;
		left: 0;
		z-index: 100000000000;
		background-color: rgba(0, 0, 0, 0.4);
	}
	.commentrel {
		position: relative;
		width: calc(100% - 48rpx);
		margin-left: 24rpx;
		overflow: hidden;
		margin-top: 18rpx;
		border-radius: 20rpx;
		background-color: #fff;
		padding-bottom: 48rpx;
	}
	.bluebg{
		background-color: #0090FF;
	}
</style>


