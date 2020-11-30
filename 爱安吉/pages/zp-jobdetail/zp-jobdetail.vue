<template>
	<view>
		<view class="msgheadbox">
	    <view class="pay">{{data.salary}}</view>
		<view class="maintitle">{{data.name}}</view>
		<view class="desc">{{data.edution}} &nbsp; {{data.exp_require}}</view>
		<view class="companydes">{{data.company}}</view>
		</view>
		<view class="company">
			<view class="title">公司简介</view>
			<view class="content" v-html="data.intr">
			</view>
		</view>
		<view class="job">
			<view class="title">岗位要求</view>
			<view class="content">
                  <view class="message">年龄：{{data.age}}</view>
				  <view class="message">性别：{{data.sex}}</view>
				  <view class="message">工作性质:{{data.way}}</view>
				  <view class="message">学历：{{data.edution}}</view>
				  <view class="message">工作地点：{{data.place}}</view>
				  <view class="message">招聘人数：{{data.num}}人</view>
			</view>
		</view>
		<!-- @click="hidefloatbox()"  隐藏浮动窗口-->
<!-- 		<view class="floatbox" v-if="floatshow==1">
			<view class="submitbox">
				<view class="personmsg"><view class="pertitle">姓名</view><input type="text" placeholder="请输入姓名" value="吴晓野"></view>
			    <view class="personmsg"><view class="pertitle">身份证号</view><input type="text" placeholder="请输入身份证号" value="3304**********5221"></view>
			    <view class="personmsg"><view class="pertitle">出生年月</view>
				<picker mode="date" :value="date" :start="startDate" :end="endDate" @change="bindDateChange">
					<view class="uni-input" style="font-size: 24rpx;">{{date}}</view>
				</picker>
				</view>
				<view class="personmsg"><view class="pertitle">性别</view>
				<radio-group name="gender">
					<label style="width: 30rpx;font-size: 30rpx;">
						<radio value="男" /><text style="margin-left: 10rpx;">男</text>
					</label>
					<label style="width: 30rpx;font-size: 30rpx;margin-left:40rpx;">
						<radio value="女"  /><text style="margin-left: 10rpx;">女</text>
					</label>
				</radio-group>
				</view>
				<view class="personmsg"><view class="pertitle">手机号</view><input type="radio" placeholder="请输入手机号"><view class="sendcode">点击获取</view></view>
				<view class="personmsg"><view class="pertitle">验证码</view><input type="radio" placeholder="请输入验证码"></view>
			    <view class="submitbuttonbox">
					<view class="submitpermsg cancel" @click="cancel()">取消</view>
					<view class="submitpermsg enter">提交</view>
				</view>
			</view>
		</view> -->
		<view class="submitbutton"  @click="submitpermsg()">投简历</view>
	</view>
</template>

<script>
	function getDate(type) {
		const date = new Date();
	
		let year = date.getFullYear();
		let month = date.getMonth() + 1;
		let day = date.getDate();
	
		if (type === 'start') {
			year = year - 60;
		} else if (type === 'end') {
			year = year + 2;
		}
		month = month > 9 ? month : '0' + month;;
		day = day > 9 ? day : '0' + day;
	
		return `${year}-${month}-${day}`;
	}
	
	import MD5 from '../../common/MD5.js'
	export default {
		data() {
			return {
			floatshow:0, 	
			date: getDate({
				format: true
			}),
			startDate:getDate('start'),
			endDate:getDate('end'),
				
			jobid:'',
			data:[],
			}
		},
		onLoad(options) {
			this.jobid = options.jobid
			this.get_detail_content()
		},
		methods: {
			get_detail_content: function() {
				var that = this;
				var url = that.globalUrl + '/ajzp/recruit_information_detail.php';
				var timestamp = Date.parse(new Date())/1000;
				var s = timestamp+"32dd3c0eb6340a932a990e5832a0d2cf";
				var signature = MD5(s);
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						job_id:that.jobid,
						timestamp: timestamp,
						sign: signature,
					},
					success: (res) => {
						that.data = eval('(' + res.data + ')').data[0];

					},
					fail: (err) => {}, 
					complete: () => {}
				});
			},
			
        submitpermsg:function(){//投简历
				var that = this;
				var url = that.globalUrl + '/ajzp/resume_send.php';
				var timestamp = Date.parse(new Date())/1000;
				var s = timestamp+"32dd3c0eb6340a932a990e5832a0d2cf";
				var signature = MD5(s);
				uni.request({
					url: url,
					method: 'GET',
					
					data: {
						job_id:that.jobid,
						user_id: uni.getStorageSync("user_id"),
						timestamp: timestamp,
						sign: signature,
					},
					success: res => {
						// console.log(that.addressidlist[that.addressindex])
						// console.log(that.industryidlist[that.industryindex])
						// console.log(that.natureidlist[that.natureindex])
						// console.log(that.scaleidlist[that.scaleindex])
						// console.log(this.locationAddress)
				     uni.showToast({
				     	icon:"none",
						title:res.data.msg,
				     });
					 if(res.data.ret==200){
						 setTimeout(function(){
					 },500); 
					 }
					
					},
					fail: () => {},
					complete: () => {}
				})
		}
			
		}
	}
</script>

<style>
	.cancel{
		background-color:gray !important;
	}
	.enter{
		
	}
	.submitbuttonbox{
		position: relative;
		width: 100%;
		display: flex;
		align-items: center;
		justify-content: space-between;
	}
	.uni-radio .uni-radio-input{
		width: 30rpx !important;
		height: 30rpx !important;
	}
	.sendcode{
		position: absolute;
		z-index: 10;
		right:24rpx;
		font-size: 24rpx;
		color: #0090FF;
		border: 1px solid #0090FF;
		border-radius:10rpx;
		padding: 10rpx;
	}
	.personmsg{
	display: flex;
	align-items: center;
	padding: 24rpx 0;
	justify-content: left;
	border-bottom: 1px solid #eee;
	}
	.personmsg input{
	position: relative;
	font-size:24rpx;
	}
	.pertitle{
		width:200rpx;
		font-size:24rpx;
	}
	.submitbox{
		position:fixed;
		/* margin-left: 5%; */
	    background-color: #fff;
		height: 50%;
		/* bottom:200rpx; */
		padding:24rpx  48rpx;
		border-radius:25rpx;
	}
	.submitpermsg{
	position:relative;
	color:#fff;
	font-size:30rpx;
	background-color: #0090FF;
	bottom:50rpx;
	width: 80%;
	margin-left:5%;
	margin-right: 5%;
	margin-top:80rpx;
	text-align: center;
	padding: 15rpx 0;
	border-radius:50rpx;		
	}
	.floatbox{
		position:fixed;
		width: 100%;
		height: 100%;
		z-index: 5;
		top: 0;
		display: flex;
		justify-content: center;
		align-items: center;
		background-color: rgba(0,0,0,0.5);
	}
	.content{
		position: relative;
		width:calc(100% - 96rpx);
		padding:24rpx 48rpx;
	    font-size:28rpx;
		color: #555;
	}
	.title{
		position: relative;
		font-size: 30rpx;
		margin-left: 48rpx;
		margin-top: 20rpx;
	}
	.content .message{
		margin-top:5rpx;
	}
	.pay{
		position:absolute;
		font-size:30rpx;
		right:24rpx;
		top:24rpx;
		color: #d92323;
	}
	.maintitle{
		position: relative;
		font-size:35rpx;
		color: #444;
	}
	.desc{
		position: relative;
		font-size: 26rpx;
		margin-top:10rpx;
		color: gray;
	}
	.company{
		border-bottom: 1px solid #eee;
	}
	.companydes{
		position: relative;
		margin-top:20rpx;
		font-size:28rpx;
	}
.msgheadbox{
	padding:24rpx 48rpx;
	border-bottom: 1px solid #eee;
}
.submitbutton{
	position:fixed;
	color:#fff;
	font-size:30rpx;
	background-color: #0090FF;
	bottom:50rpx;
	width: 80%;
	margin-left:10%;
	text-align: center;
	padding: 20rpx 0;
	border-radius:50rpx;
}
</style>
