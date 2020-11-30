<template>
	<view>
		<!-- 头部积分模块和签到模块开始 -->
		<view class="headbox">
			<view class="headbackground">
				<view class="personpoint">623积分</view>
				<view class="pointmessagebox">
					<!-- <view class="pointmessageunit" @click="openpointrule()">积分说明</view> -->
					<view class="pointmessageunit" @click="openpointlist()">积分明细</view>
				</view>
			</view>
			<view class="headsignbox">
				<view class="tittext">
					您已连续签到
					<span style="color:#d75a25;">1</span>
					天
				</view>
				<view class="signbox">
					<view :class="item.classname" v-for="item in signarr">
						{{ item.index }}
						<view :class="item.daytextclass">{{ item.day }}</view>
					</view>
				</view>
			</view>
		</view>
		<!-- 头部积分模块和签到模块结束 -->
		<!-- 试手气 积分大转盘模块开始 -->
		<view style="position: relative;">
			<lab name="试手气"></lab>
			<view class="getmore" @click="openwinlist()">中奖记录 ></view>
		</view>
		<view class="swiperbox">
			<view class="swiperitem" @click="openturntable()" v-for="item in slidearr">
				<view class="swiperimg"><image mode="aspectFill" style="width: 100%;height: 100%;" :src="item.activity_pic"></view>
				<view class="swipertext">{{item.title}}</view>
			</view>
		</view>
		<!-- 试手气 积分大转盘模块结束 -->
		<!-- 做任务 积分任务模块开始 -->
		<view style="position: relative;">
			<lab name="做任务"></lab>
			<view class="getmore">
				每日最多可获得积分
				<span style="color: red;">{{date_pointsum}}</span>
				分，今日已获得
				<span style="color: red;">{{date_pointfinish}}</span>
				分
			</view>
		</view>
		<view class="taskbox">
			<view class="taskitem" v-for="item in taskarr">
				<view class="taskicon">
					<img :src="item.category_icon" style="width: 100%;height: 100%;">
				</view>
				<view class="taskmessagebox">
					<view class="tasktitle">{{ item.category_name }}</view>
					<view class="taskdesc">{{ item.category_desc }}</view>
				</view>
				<view class="taskdonum">{{ item.finish_num}}/{{ item.limit_num}}</view>
			</view>
		</view>
		<!-- 做任务 积分任务模块结束 -->
		<!-- 兑奖品 奖品模块开始 -->
		<view style="position: relative;">
			<lab name="兑奖品"></lab>
			<view class="getmore" @click="opengoodslist()">更多 ></view>
		</view>
		<view class="goodsbox">
			<view class="gooditem" @click="opengoodslist()" v-for="item in goodsarr">
				<view class="goodimg">
					<img :src="item.pic_uri" style="width: 100%;height: 100%;">
				</view>
				<view class="goodtitle">{{ item.goods_name }}</view>
				<view class="goodmessagebox">
					<view class="goodpointnum">{{ item.consume_name}}</view>
					<view class="goodsnum">剩余： {{ item.numbers }}</view>
				</view>
			</view>
		</view>
		<!-- 兑奖品 奖品模块结束 -->
	</view>
</template>

<script>
import slideshowHead from '../../components/slideshow-head.vue';
import slideshowNav from '../../components/slideshow-nav.vue';
import lab from '../../components/lab.vue';
export default {
	components: { lab, slideshowHead, slideshowNav },
	data() {
		return {
			date_pointsum:"",
			date_pointfinish:"",
			slidearr: [
			],
			signarr: [
				// { index: '√', day: '7/3', classname: 'sign signed', daytextclass: 'signday black ' },
				// { index: '+1', day: '7/5', classname: 'sign', daytextclass: 'signday gray' },
				// { index: '+2', day: '7/6', classname: 'sign', daytextclass: 'signday gray' },
				// { index: '+3', day: '7/7', classname: 'sign', daytextclass: 'signday gray' },
				// { index: '+4', day: '7/8', classname: 'sign', daytextclass: 'signday gray' },
				// { index: '+5', day: '7/9', classname: 'sign', daytextclass: 'signday gray' },
				// { index: '+6', day: '7/10', classname: 'sign', daytextclass: 'signday gray' }
			],
			taskarr: [
				// { tasktitle: '订单评价', taskdesc: '完成订单评价可获得3积分的奖励', num: '3', donenum: '1' },
				// { tasktitle: '看新闻', taskdesc: '完成订单评价可获得3积分的奖励', num: '8', donenum: '5' },
				// { tasktitle: '转发新闻', taskdesc: '完成订单评价可获得3积分的奖励', num: '3', donenum: '1' },
				// { tasktitle: '看安吉', taskdesc: '完成订单评价可获得3积分的奖励', num: '4', donenum: '4' }
			],
			goodsarr: [
				// { title: '中华铅笔', point: '500积分', goodnum: '50' },
				// { title: '超市环保袋', point: '200积分', goodnum: '150' },
				// { title: '圆规多功能套装', point: '100积分', goodnum: '50' },
				// { title: '手持小风扇', point: '600积分', goodnum: '01' }
			]
		};
	},
	onLoad() {
		this.sign();//签到
		this.getturntablelist();
		this.getpointtask();
		this.getgoodlist();
	},
	methods: {
		sign:function(){
		uni.request({
			url:"https://www.meilianji.cn/web/points/insert_points2.php?user_id="+uni.getStorageSync("user_id")+"&module=12&category=01",
			dataType:"json",
			data:{
			},
			header:{
				'content-type': 'application/x-www-form-urlencoded',
			},
			method:"POST",
			success: (res) => {
			// this.goodsarr=res.data;
		 //    console.log(res.data)
		 if(res.data.resultid==1){
			uni.showToast({
				icon:'none',
				title:'签到成功！'
			}) 
		 }
			}
		})			
		},
		openwinlist:function(){
			console.log('openwinlistxxxxxxxxxxxxxxxxxxxx');
			uni.navigateTo({
				url:"../pointshop-winlist/pointshop-winlist"
			})
			console.log('openwinlistvvvvvvvvvvvvvvvvvvv')
		}
		,
		opengoodslist:function(){
		uni.navigateTo({
			url:"../pointshop-goodslist/pointshop-goodslist"
		})	
		},
		getgoodlist:function(){//获取奖品清单
		//https://www.meilianji.cn/web/points/get_points_goods_list.php?type=1
		uni.request({
			url:"https://www.meilianji.cn/web/points/get_points_goods_list.php",
			dataType:"json",
			data:{
				type:1
			},
			header:{
				'content-type': 'application/x-www-form-urlencoded',
			},
			method:"POST",
			success: (res) => {
				this.goodsarr=res.data;
		     console.log(res.data)
			}
		})
		}
		,
		changedaytype:function(a){//修改时间格式
		 var startstr=a.indexOf("/");
		 var changea=a.slice(startstr + 1,startstr + 6);
		 console.log(changea)
		 return changea
		},
		getpointtask:function(){//获取积分任务积分信息及签到情况
			//https://www.meilianji.cn/web/points/get_points_date_task2.php?user_id=63714
		uni.request({
			url:"https://www.meilianji.cn/web/points/get_points_date_task2.php",
			dataType:"json",
			data:{user_id:uni.getStorageSync("user_id")},
			header:{
				'content-type': 'application/x-www-form-urlencoded',
			},
			method:"POST",
			success: (res) => {
			if(res.data!=''){
			  this.date_pointsum=res.data.date_points_sum;
			  this.date_pointfinish=res.data.date_points_finish;
              this.taskarr=res.data.date_category_info;
			  var classname;
			  var daytextclass;
			  var day;
			  var index;
			  for(var i=0;i<res.data.week_sign_info.length;i++){
				  if(res.data.week_sign_info[i].is_sign==1){
					 index="√";
					 classname="sign signed"; 
					 daytextclass="signday black"
				  }else{
					 index="+"+res.data.week_sign_info[i].award_points
					 classname="sign" ;
					 daytextclass="signday gray"
				  }
				  var obj={
					  index:index,
					  day:this.changedaytype(res.data.week_sign_info[i].award_time), 
					  classname:classname, 
					  daytextclass:daytextclass
					  
				  }
				  this.signarr.push(obj)
			  }
			  console.log(this.signarr)				
			}else{
				uni.showToast({
					title:"网络不佳,稍后再试~",
					icon:"none"
				})
			}

			}
		})
		}
		,getturntablelist:function(){//获取大转盘抽奖活动
		//https://www.meilianji.cn/web/points/get_activity_list.php?user_id63714
			uni.request({
				url:"https://www.meilianji.cn/web/points/get_activity_list.php",
				dataType:"json",
				data:{},
				header:{
					'content-type': 'application/x-www-form-urlencoded',
				},
				method:"POST",
				success: (res) => {
					if(res.data!=''){
					console.log(res.data)
					this.slidearr=res.data	
					}else{
						uni.showToast({
							icon:"none",
							title:"暂无抽奖活动"
						})
					}
					
				}
			})
		},
		openturntable:function(){//打开大转盘
			uni.navigateTo({
				url:"../pointshop-turntable/pointshop-turntable"
			})
		},
		openpointrule:function(){//打开积分说明
		
			uni.navigateTo({
				url:"../personpoint-pointrule/personpoint-pointrule"
			})
		},
		openpointlist:function(){//打开积分明细
		    console.log("xxxxxxxxxxx");
			uni.navigateTo({
				url:"../pointshop-pointlist/pointshop-pointlist"
			})			
		},
		onNavigationBarButtonTap(e) {
			console.log(e.index)
			if(e.index==0){
			uni.navigateTo({
				url:"../pointshop-pointrule/pointshop-pointrule"
			})
			}
		}
	}
};
</script>

<style>
.pointmessagebox {
	position: absolute;
	color: #f8f8f8;
	right: 50rpx;
	top: 90rpx;
}
.goodimg {
	position: relative;
	width: 100%;
	height: 300rpx;
	background-color: #f8f8f8;
	border-radius: 20rpx;
	overflow: hidden;
}
.goodtitle {
	font-size: 35rpx;
	margin: 20rpx 0;
}
.goodmessagebox {
	position: relative;
	width: 100%;
	height: 40rpx;
}
.goodpointnum {
	position: absolute;
	left: 0;
	color: #29a2ff;
}
.goodsnum {
	position: absolute;
	right: 0;
	color: gray;
}
.gooditem {
	padding: relative;
	width: 50%;
	padding: 24rpx;
	display: inline-block;
}
.personpoint {
	position: relative;
	color: #fff;
	font-size: 40rpx;
	font-weight: bolder;
	width: 100%;
	top: 80rpx;
	padding: 0 50rpx;
}

.tasktitle {
	position: relative;
	font-size: 30rpx;
	color: #444;
}
.taskdesc {
	color: gray;
	font-size: 20rpx;
	margin-top: 4rpx;
}
.taskitem {
	position: relative;
	width: 100%;
	height: 180rpx;
	padding: 48rpx 24rpx;
	display: flex;
	align-items: center;
	border-bottom: 1rpx solid #eee;
}
.taskicon {
	position: relative;
	width: 70rpx;
	height: 70rpx;
	display: flex ;
	align-items: center;
	justify-content: center;
	border-radius: 40rpx;
}
.taskmessagebox {
	position: relative;
	width: 80%;
	height: 90rpx;
	display: flex;
	flex-direction: column;
	justify-content: space-between;
	margin-left: 24rpx;
}
.taskdonum {
	position: absolute;
	height: 30rpx;
	right: 24rpx;
	color: #000000;
}
.signday {
	position: absolute;
	width: 67rpx;
	text-align: center;
	bottom: -50rpx;
	left: 0;
	color: #444;
}
.black {
	color: #444;
}
.gray {
	color: gray;
}
.signbox {
	position: relative;
	display: flex;
	justify-content: space-between;
}
.sign {
	position: relative;
	width: 67rpx;
	height: 67rpx;
	margin-top: 20rpx;
	display: flex;
	align-items: center;
	color: #fff;
	justify-content: center;
	background-color: #d0d0d0;
	border: 2px solid #f6faec;
	border-radius: 100%;
}
.signed {
	background-color: #f3cb45;
	border: 2px solid #f9e898;
}
.tittext {
	position: relative;
	width: 100%;
	text-align: center;
	font-size: 35rpx;
	font-weight: bolder;
}
.headsignbox {
	position: absolute;
	width: calc(100% - 48rpx);
	height: 230rpx;
	background-color: #fff;
	top: 200rpx;
	padding: 24rpx;
	box-shadow: 0 10rpx 20rpx 10rpx rgba(50, 50, 50, 0.1);
	margin-left: 24rpx;
	border-radius: 20rpx;
}
.headbox {
	position: relative;
	padding-bottom: 200rpx;
}
.headbackground {
	position: relative;
	height: 8rem;
	width: 100%;
	border-radius: 0 0 50% 50% / 0 0 18rpx 18rpx;
	background-image: linear-gradient(to bottom, #6cb2f4, #6284f3);
}
.getmore {
	position: absolute;
	right: 24rpx;
	top: 30rpx;
	color: gray;
	font-size: 24rpx;
}
.swiperbox {
	position: relative;
	width: 100%;
	height: 9rem;
	overflow: scroll;
	white-space: nowrap;
	padding: 0 12px 1rem 12px;
}
.swiperimg {
	position: relative;
	width: 100%;
	height: 5rem;
	background-color: #444;
	border-radius: 0.5rem;
    border: 1px solid #f4f5f6;
}
.swipertext {
	white-space: normal;
	margin-top: 5rpx;
}
.swiperitem {
	position: relative;
	width: 8rem;
	height: 7rem;
	display: inline-block;
	margin-right: 0.5rem;
}
</style>
