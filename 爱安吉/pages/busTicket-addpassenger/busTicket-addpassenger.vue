<template>
	<view>
		<view class="unit"><span class="title">乘客类型</span>
		<radio-group name="gender" @change="openradiogroup">
			<label style="width: 20rpx;font-size:0.7rem">
				<radio value="0"    color="#0081FF" checked=""/><text style="margin-left: 10rpx;">成人</text>
			</label>
			<label style="width: 20rpx;font-size:0.7rem;margin-left:40rpx;">
				<radio value="1" color="#0081FF"/><text style="margin-left: 10rpx;">儿童</text>
			</label>
		</radio-group>
		</view>
		<view class="unit"><span class="title">姓名</span><input  v-model="name"  placeholder="与证件姓名一致"></view>
		<view class="unit"><span class="title">身份证</span><input  v-model="code"  placeholder="乘客身份证号"></view>
		<view class="submitbutton" v-on:click="sunmitusermessage()">完成</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				name:'',
				code:'',
				trick:'0'
			}
		},
		methods: {
			openradiogroup:function(e){
				console.log(e.detail.value)
				this.trick=e.detail.value
			},

			sunmitusermessage:function(){//提交乘客信息
			var obj=[{"user_id":uni.getStorageSync("user_id"),"user_name":this.name,"id_card":this.code,"ticker_type":this.trick}];
			// var obj=[{"user_id":75756,"user_name":this.name,"id_card":this.code,"ticker_type":this.trick}];
			obj=JSON.stringify(obj)
			console.log(obj)
				uni.request({
					url:this.globalUrl+ '/ticket/add_ticket_contactor_new.php?json='+obj,
					data:{
					},
					method:'post',
					dataType:'json',
					header:{
						"content-type":"application/x-www-from-urledcoded"
					},
					success: (res) => {
						console.log(res.data[0].resultid)
						if(res.data[0].resultid==1){
							uni.showToast({
								icon:'none',
								title:res.data[0].message
							})
							setTimeout(function(){
								uni.navigateBack({})
							},1000)
						}else{
							uni.showToast({
								icon:'none',
								title:res.data[0].message
							})
						}
						console.log(res.data)
					}
				})
			}
		}
	}
</script>

<style>
	.unit input{
		position: relative;
	    font-size: 0.7rem;	
	}
	.title{
		position: relative;
		width: 4rem;
	}
.unit{
	position: relative;
	width: 100%;
	height: 100rpx;
	background-color: #fff;
	border-bottom: 1px solid #eee;
	padding: 24rpx;
	display: flex;
	align-items: center;
}
.submitbutton{
	position: relative;
	width: calc(100% - 48rpx);
	margin-left: 24rpx;
	padding:20rpx 0;
	margin-top: 40rpx;
	background-color: #0081FF;
	color: #fff;
	text-align: center;
	border-radius: 0.4rem;
}
</style>
