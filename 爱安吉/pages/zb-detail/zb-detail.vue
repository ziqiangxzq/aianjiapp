<template>
	<view style="display: flex;flex-direction:column">
		
		<view class="outbox">
			<view class="zbtitle" style="margin-top: 3rem;" v-html="newstitle"></view>
			<view class="zbreadnum"><span class="blue">{{ click_num }}</span>阅读</view>
<!-- 			<view class="zbtime">{{ release_data }}</view> -->
			
			<view class="zbdaojishi" v-if="zbtype == 0">
				<view class="dajishititle">距离直播开始还有</view>
				<view class="daojishitime">
					<span class="blue">{{daojishiDay}}</span>
					天
					<span class="blue">{{daojishiHour}}</span>
					小时
					<span class="blue">{{daojishiMinute}}</span>
					分
					<span class="blue">{{daojishiSecond}}</span>
					秒
				</view>
			</view>
			<u-sticky>
			<view class="zbdesc" v-if="zbtype == 1" v-html="news_content"></view>
			<!-- <view class="mediabox"></view> -->

			<u-tabs ref="tabs" :list="typearr" :is-scroll="false" :current="current" @change="choiceit"></u-tabs>
			</u-sticky>
<!-- 			<view class="zbtypeshawnbox">
				<view class="zbtypebox">
					<view v-for="item in typearr" :class="item.classname" @click="choiceit(item.index)">{{ item.name }}</view>
				</view>
			</view> -->
		</view>
		<view class="innerbox">
			<!-- 图文直播内容框开始 -->

			<view class="zbcontent" v-if="zbshow == 1">
				<view class="textcontent">
					    <view class="changeiconF" @click="changeorder()"></view>
<!-- 					<view class="texthead">
						<view class="changeicon" @click="changeorder()"></view>
						<view class="littletitle" @click="changeorder()">顺序改变</view>
						<view class="littledesc">
							已发布
							<span class="blue">{{ newsnum }}</span>
							条新闻
						</view>
					</view> -->
					<view class="textbodybox">
						<view class="nocontent" v-if="contentarr.length == 0">暂无内容 敬请期待~</view>
						<view class="textbody" v-for="item in contentarr">
							<view class="bodyhead">
								<view class="cirle"></view>
								<view class="bodysendtime">{{ item.create_date }}</view>
							</view>
							<view class="bodybody">
								<view class="line"></view>
								<view class="realcontent">
									<view v-html="item.live_news_title"></view>
									<img v-if="item.live_pic.length != 0" v-for="itam in item.live_pic" class="contentimg" :src="itam.pic_uri" />
								</view>
							</view>
						</view>
					</view>
				</view>
			</view>
			<!-- 图文直播内容框结束 -->
			<!-- 互动内容框开始 -->
			<view class="hdcontent" v-if="hdshow == 1">
				<!-- <view class="commentbuttonbox"><view class="commentbutton" @click="showcommentfloatbox()"><img style="width: 1rem;margin: 0 0.5rem;" src="../../static/zb/comment.png">点击参与互动</view></view> -->
				<!-- <commentbox ref="commentbox" opemjo="1" opimage="1" ajaxname="json" ajaxurl="https://www.meilianji.cn/web/news/write_news_comment.php" newsid="news_id" userid="user_id" textname="comment" picname="pic_url"  newsidvalue="53720" useridvalue="63714"></commentbox> -->
				<!-- 评论浮动窗口开始 -->
                  <comment fun="releasecomment" @releasecomment="releasecomment"></comment>				
 				<!-- 评论浮动窗口结束 -->
				<view class="nocontent" v-if="commentarr.length == 0">暂无内容 敬请期待~</view>
				<view class="communit" v-for="(item, index) in commentarr">
					<view class="hdheadbox">
						<view class="hdheadimage"><img style="width:100%;height:100%" :src="item.pics" /></view>
						<view class="hdusername">{{ item.user_nick }}</view>
						<view class="hdsogood">
							<img style="width: 100%;height: 100%;" @click="changegoodtype(index, item.comment_id)" v-if="item.record_num == 0" src="../../static/zb/zan_gray.png" />
							<img style="width: 100%;height: 100%;" @click="changebadtype(index, item.comment_id)" v-if="item.record_num == 1" src="../../static/zb/zan_blue.png" />
							<view class="goodnum">{{ item.good_num }}</view>
						</view>
					</view>
					<view class="hdcomment" >
						<image @click="seeimage(itam.pic)" mode="aspectFill" style="width: 30%;overflow: hidden;height:150rpx;margin-right:3%;border-radius:10rpx;display: inline-block;" v-for="itam in item.pic_url" :src="itam.pic">
					</view>
					<view class="hdcomment" v-html="item.comment"></view>
					<view class="hdtime">{{ item.create_date }}</view>
				</view>
			</view>
			<!-- 互动内容框结束 -->
			  <!-- 表情界面 -->
			            <div id="emojiView"  class="emojiView ub-f1 ub-ver bc-head" style="width:100%;z-index:2;overflow:hidden;display:none;position: fixed;bottom: 0;">
			                <div id="sliderItem" class="sliderItem ub ub-ver" style="width:100%;overflow-y:scroll;width:100%;-webkit-overflow-scrolling:touch;position:relative;padding-bottom:.4em;"> </div>
			                <!-- <div id="pagePoint" class="pagePoint ub ub-ac ub-pc " style="height:1em;width:100%;"> </div> -->
			                
			            </div>
		</view>
	</view>
</template>

<script>
import commentbox from '../../components/commentbox.vue';
import comment from '../../components/comment.vue'
export default {
	components:{commentbox,
	comment
	},
	data() {
		return {
			newsid:0,//新闻id
			zbtype:1, //0直播未开始 1直播已开始
			daojishiDay: 0,
			daojishiHour: 0,
			daojishiMinute: 0,
			daojishiSecond: 0,
			typearr: [{ index: 0, name: '直播', classname: 'typeunit typeunited' }, { index: 1, name: '互动', classname: 'typeunit' }],
			contentarr: [''],
			commentarr: [''],
			current:0,
			sort: 1,
			newsnum: '',
			newstitle: '',
			click_num: '',
			release_data: '',
			news_content: '',
			zbpage: 1,
			hdpage: 1,
			zbshow: 1,
			hdshow: 0,
			floatboxshow:0,
			sogoodimaged: '../../static/zb/zan_blue.png',
			sogoodimage: '../../static/zb/zan_gray.png',
		};
	},
	onLoad(e) {
		this.newsid=e.news_id;
		console.log(this.newsid)
		this.getzblist();
		this.gethdlist();

	},
	onReachBottom() {
		//滑动到底部加载更多新闻或显示提示信息
		if (this.zbshow == 1) {
			//直播加载下一页
			this.zbpage++;
			this.getzblist();
		} else if (this.hdshow == 1) {
			this.hdpage++;
			this.gethdlist();
		}
		console.log('滑动到底部了');
		this.page++;
		this.gethdlist();
	},
	methods: {
		releasecomment:function(e){//上传
		var that=this;
		var json=[{
			news_id:that.newsid,
			user_id:uni.getStorageSync("user_id"),
			comment:e
		}];
		json=JSON.stringify(json);
		console.log(json)
				var url="https://www.meilianji.cn/web/news/write_news_comment.php?comment_json="+json;
		uni.request({
			url: url,
			dataType: 'json',
			method: "POST",
			header: {
				'content-type': 'application/x-www-form-urlencoded'
			},
			data: {
							
			},
			success: (res) => {
				console.log(res.data);
				if(res.data[0].resultid==1){
					uni.showToast({
						icon:"none",
						title:res.data[0].message
					})
					
				}else{
				uni.showToast({
					icon:"none",
					title:res.data[0].message
				})	
				}
			}})	
			
		},
		seeimage:function(image){
				var imgArr = [];
				imgArr.push(image);
				//预览图片
				uni.previewImage({
					urls: imgArr,
					current: imgArr[0]
				});
		},
		showcommentfloatbox: function() {
			this.$refs.commentbox.showcommentfloatbox()
			console.log(this.floatboxshow);
			//this.floatboxshow = 1;
		},
        emojiBtn:function(){
		//emojiBtn.emojiBtn()	
		},

		choiceimage: function() {
			//选择图片
		},
		changegoodtype: function(index, id) {
			console.log('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx' + index);
			uni.request({
				url: 'https://www.meilianji.cn/web/news/update_news_comment_good_num.php',
				data: {
					comment_id: id,
					user_id: 63714
				},
				method: 'POST',
				dataType: 'json',
				header: {
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: res => {
					if (res.data[0].resultid == 1) {
						this.commentarr[index].record_num = 1;
						this.commentarr[index].good_num++;
					} else {
						uni.showToast({
							icon: 'none',
							title: '网络不佳 请稍后再试'
						});
					}
				}
			});
		},
		changebadtype: function(index, id) {
			console.log('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx' + index);
			uni.request({
				url: 'https://www.meilianji.cn/web/news/update_news_comment_good_num.php',
				data: {
					comment_id: id,
					user_id: 63714
				},
				method: 'POST',
				dataType: 'json',
				header: {
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: res => {
					//console.log(res.data.resultid);
					if (res.data[0].resultid == -1) {
						this.commentarr[index].record_num = 0;
						this.commentarr[index].good_num--;
					} else {
						uni.showToast({
							icon: 'none',
							title: '网络不佳 请稍后再试'
						});
					}
				}
			});
		},
		changeorder: function() {
			if (this.sort == 0) {
				this.sort = 1;
				this.getzblist();
			} else {
				this.sort = 0;
				this.getzblist();
			}
		},
		gethdlist: function() {
			var that=this;
			uni.request({
				url: 'https://www.meilianji.cn/web/news/get_news_comment_list_new.php',
				data: {
					news_id:that.newsid,
					user_id: 63714,
					page: that.hdpage,
					recs: 100
				},
				method: 'POST',
				dataType: 'json',
				header: {
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: res => {
					if (this.hdpage == 1) {
						this.commentarr = res.data;
						console.log(res.data);
					} else {
						if (res.data.length != 0) {
							for (var i = 0; i < res.data.length; i++) {
								this.commentarr.push(res.data);
							}
						} else {
							uni.showToast({
								icon: 'none',
								title: '暂无更多评论~'
							});
						}
					}
				}
			});
		},
		daojishistart:function(){
			var that=this;
			var daojishistart=setInterval(function(){
				if(that.daojishiSecond!=0){
					that.daojishiSecond--
				}else{
					if(that.daojishiMinute!=0){
						that.daojishiMinute--;
						that.daojishiSecond=59;
					}else{
						if(that.daojishiHour!=0){
							that.daojishiHour--;
							that.daojishiMinute=59;
							that.daojishiSecond=59;
						}else{
							if(that.daojishiDay!=0){
								that.daojishi--;
								that.daojishiHour=23;
								that.daojishiMinute=59;
								that.daojishiSecond=59;
							}else{
								//直播开始
								clearInterval(daojishistart);
								that.zbtype=1;
							}
						}
					}
				}
			},1000)
		}
		,
		getzblist: function() {
			var that=this;
			//获取直播信息
			uni.request({
				url: 'https://www.meilianji.cn/web/news/get_live_news_list.php',
				data: {
					news_id:that.newsid,
					sort_type: that.sort, //1正序0倒序
					page: that.zbpage,
					recs: 20
				},
				method: 'POST',
				dataType: 'json',
				header: {
					'content-type': 'application/x-www-form-urlencoded'
				},
				success: res => {
					// res.data.start_time =1500000010 ;
					// res.data.now_time = 1500000000;
					if (res.data.start_time > res.data.now_time) {
						//直播未开始 开启倒计时
						this.zbtype=0
						var time=res.data.start_time - res.data.now_time;
						var day=parseInt(time/86400);
						time=time%86400;
						var hour=parseInt(time/3600);
						time=time%3600;
						var minute=parseInt(time/60);
						time=time%60;
						var second=time;
						this.daojishiDay=day;
						this.daojishiHour=hour;
						this.daojishiMinute=minute;
						this.daojishiSecond=second;
						this.daojishistart()
					} else {
						//直播已开始
						this.zbtype=1
					}
					console.log(res.data);
					if (this.zbpage == 1) {
						console.log("直播已开始")
						this.contentarr = res.data.live_list;
						this.newsnum = res.data.live_news_num;
						this.newstitle = res.data.news_title;
						this.click_num = res.data.click_num;
						this.release_data = res.data.release_date;
						this.news_content = res.data.news_content;
					} else {
						console.log("直播已结束")
						if (res.data.live_list.length != 0) {
							for (var i = 0; i < res.data.live_list.length; i++) {
								this.contentarr.push(res.data.live_list[i]);
							}
						} else {
							uni.showToast({
								icon: 'none',
								title: '暂无更多内容~'
							});
						}
					}
				}
			});
		},
		choiceit: function(a) {
			this.current=a;
			for (var i = 0; i < this.typearr.length; i++) {
				this.typearr[i].classname = 'typeunit';
			}
			this.typearr[a].classname = 'typeunit typeunited';
			if (a == 0) {
				//展示直播
				this.zbshow = 1;
				this.hdshow = 0;
			} else {
				//展示互动
				this.zbshow = 0;
				this.hdshow = 1;
			}
			uni.pageScrollTo({
				scrollTop: 0,
				duration: 200
			});
		}
	}
};
</script>

<style>
.zbdaojishi {
	position: relative;
	font-size: 30rpx;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	background-color: #eee;
	min-height: 380rpx;
	margin-top: 10rpx;
	display: flex;
	justify-content: center;
	flex-direction: column;
}
.dajishititle {
	position: relative;
	width: 100%;
	text-align: center;
	font-size: 42rpx;
	font-weight: bolder;
	color: #444;
}
.daojishitime {
	position: relative;
	width: 100%;
	text-align: center;
	font-size: 50rpx;
	color: #444;
	margin-top: 40rpx;
	font-weight: bolder;
}
.blue {
	color: #0090ff;
	margin: 0 10rpx;
}
.innerbox {
	position: relative;
/* 	margin-top: 600rpx; */
}
.nocontent {
	position: relative;
	font-size: 28rpx;
	width: 100%;
	text-align: center;
	color: gray;
	padding: 2rem 0;
}
.outbox {
	/* position: fixed; */
	position: relative;
	width: 100%;
	height: auto;
	z-index:10;
	background-color: #fff;
}

.red {
	background-color: #cb3034;
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
	z-index: 10;
	left: 0;
	
	box-shadow: 0rpx -10rpx 20rpx 10rpx rgba(100, 100, 100, 0.1);
}
.hdheadbox {
	position: relative;
	display: flex;
	align-items: center;
}
.hdheadimage {
	position: relative;
	width: 60rpx;
	height: 60rpx;
	overflow: hidden;
	border-radius: 100rpx;
	background-color: #000000;
}
.hdsogood {
	position: absolute;
	right: 40rpx;
	width: 56rpx;
	background-color: #fff;
	display: flex;
	align-items: center;
}
.goodnum {
	position: absolute;
	right: -30rpx;
	font-size: 30rpx;
	color: gray;
}
.hdusername {
	position: relative;
	color: gray;
	margin-left: 28rpx;
	font-size: 30rpx;
}
.hdcomment {
	position: relative;
	font-size: 26rpx;
	margin-top: 10rpx;
	color: #444;
	margin-left: 90rpx;
}
.hdtime {
	position: relative;
	font-size: 24rpx;
	color: gray;
	margin-top: 20rpx;
	margin-left: 90rpx;
}
.contentimg {
	width: 100%;
	margin: 10rpx 0;
}
.communit {
	position: relative;
	width:100%;
	padding:30rpx 20rpx;
	margin-left: 10rpx;
	background-color: #fff;
	border-bottom: 1px solid #eee;
	margin-top: 10rpx;
}
.realcontent {
	position: relative;
	background-color: #fff;
	width: 90%;
	border-radius: 10rpx;
	font-size: 30rpx;
	color: #444;
	padding: 20rpx;
	margin-left: 50rpx;
	margin-top: 18rpx;
}
.line {
	position: absolute;
	z-index: 5;
	height: 100%;
	width: 2rpx;
	background-color: #8a8a8a;
	left: 14rpx;
	top: 24rpx;
}
.cirle {
	position: absolute;
	z-index: 10;
	width: 28rpx;
	height: 28rpx;
	border-radius: 50rpx;
	background-color: #0091e9;
}
.bodysendtime {
	position: relative;
	color: #444;
	font-size: 25rpx;
	margin-left: 48rpx;
}
.bodyhead {
	position: relative;
	display: flex;
	align-items: center;
}
.textbody {
	position: relative;
	width: calc(100% - 48rpx);
	margin-left: 24rpx;
	margin-top: 24rpx;
}
.textbodybox {
	margin-top: 10rpx;
}
.littletitle {
	position: relative;
	font-size: 30rpx;
	color: #444;
}
.littledesc {
	position: relative;
	font-size: 20rpx;
	color: #555;
	margin-left: 50rpx;
}
.changeiconF{
	position: fixed;
	width: 80rpx;
	height: 60rpx;
	z-index: 10;
    bottom: 40rpx;
	right:0rpx;
	background: url(../../static/zb/pym1.png) no-repeat center;
	background-size: 38rpx 38rpx;
	background-color: #eee;
	border-radius: 100rpx 0 0 100rpx;
}
.changeicon {
	position: relative;
	width: 70rpx;
	height: 70rpx;
	background: url(../../static/zb/pym1.png) no-repeat center;
	background-size: 38rpx 38rpx;
}
.texthead {
	position: relative;
	width: 100%;
	height: 2rem;
	display: flex;
	align-items: center;
}
.textcontent {
	position: relative;
	width: calc(100% - 48rpx);
	margin-left: 24rpx;
}
.zbcontent {
	position: relative;
	width:100%;
	padding: 10rpx;
	padding-bottom: 50rpx;
	background-color: #f8f8f8;
}
.hdcontent {
	position: relative;
	width: calc(100% - 20rpx);
	padding: 10rpx;
	padding-bottom: 50rpx;
	background-color: #fff;
}
.zbtypebox {
	position: relative;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	color: #000000;
	display: flex;
	margin-top: 20rpx;
	justify-content: left;
}
.zbtypeshawnbox {
	position: relative;
	width: 100%;
	height: auto;
	/* 	border-bottom:50rpx solid #eee;
	border-image: linear-gradient(rgba(0,0,0,0.1),rgba(0,0,0,0)) 50 50; */
}
.typeunit {
	padding: 15rpx 20rpx;
	font-size: 30rpx;
	margin-right: 10rpx;
}
.typeunited {
	border-bottom: 13rpx solid #0090ff;
}
.zbtitle {
	position: relative;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	font-size:36rpx;
	font-weight: bolder;
	background-color: #fff;
}
.zbreadnum {
	position: relative;
	font-size: 20rpx;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	text-align: right;
	color: gray;
	margin-top: 20rpx;
	margin-bottom: 20rpx;
}
.blue {
	color: #019eff;
}
.zbtime {
	position: relative;
	font-size: 30rpx;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	text-align: right;
	color: gray;
	margin-top: 10rpx;
}

.zbdesc {
	position: relative;
	font-size: 30rpx;
	width:100%;
	background-color: #fff;
    padding:10rpx 48rpx;
	color: #444;
}
.mediabox {
	position: relative;
	width: calc(100% - 96rpx);
	margin-left: 48rpx;
	height: 300rpx;
	margin-top: 10rpx;
	background-color: #199bff;
}
</style>
