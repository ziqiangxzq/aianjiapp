<template>
	<view>
	     <view class="rechangehead">
			<view class="title">兑换对象</view>
			<view class="title">消耗</view>
			<view class="title">兑换码</view>
		</view>
		<view class="rechangebox">
			<view class="nocontent" v-if="rechangelist.length==0">暂无兑换记录~</view>
			<view class="rechangeitem" v-if="rechangelist.length!=0"  v-for="item in rechangelist">
			<view class="item itemtitle">{{item.goods_names}}</view>
			<view class="item itempoint">{{item.points}}</view>
			<view class="item itemcode" v-if="item.is_end==1">已过期</view>
			<view class="item itemcode" v-if="item.if_send==1">已兑换</view>
			<view class="item itemcode" v-if="item.is_end==0&&item.if_send==0">{{item.sent_code}}</view>
			<view class="rechangeaddress">兑换地点：{{item.address}}</view>
			<view class="uptotime">兑换截至日期：{{item.end_time}}</view>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				rechangelist:[1,1,1]
			}
		},
		onLoad() {
			this.getrechangemssage()
		},
		methods: {
		getrechangemssage:function(){
			uni.request({
				url:"https://www.meilianji.cn/web/points/get_user_goods_consume_detail.php",
				dataType:"json",
				method:"POST",
				data:{
					user_id:63714,
					page:1,
					recs:10
				},
				header:{
					'content-type': 'application/x-www-form-urlencoded',
				},
				success: (res) => {
					for(var i=0;i<res.data.length;i++){
						var star=res.data[i].sent_code.indexOf("：");
						var end=res.data[i].sent_code.indexOf("，");
						var laststar=res.data[i].sent_code.lastIndexOf("请到");
						var lastend=res.data[i].sent_code.lastIndexOf("兑奖");
						console.log(laststar+" "+lastend);
						var string=res.data[i].sent_code;
						res.data[i].sent_code=string.substring(star+1,end);
						res.data[i].address=string.substring(laststar+2,lastend);
						console.log(res.data[i].address);
					}
					this.rechangelist=res.data
					console.log(res.data)
				}
			})
		}	
		}
	}
</script>

<style>
	.nocontent{
		position: relative;
		width: 100%;
		padding: 50rpx;
		text-align:center;
		color: gray;
	}
	.uptotime{
		position: absolute;
		bottom:18rpx;
		color:gray;
		font-size: 20rpx;
		right: 24rpx;
	}
	.rechangeaddress{
		position: absolute;
		bottom:58rpx;
		color:gray;
		font-size: 20rpx;
		right: 24rpx;
	}
	.item{
		position: relative;
		width: 30%;
		color: #444;
		text-align: center;
	}
	.itemtitle{
	    width: 35%;
		padding-left: 24rpx;
	}
	.itempoint{
	   color: #0090FF;
	}
	.itemcode{
		padding-right: 24rpx;
	}
	.rechangeitem{
		position: relative;
		width: 100%;
		padding:40rpx 0 120rpx 0;
		border-bottom: 1px solid #f8f8f8;
		display: flex;
		align-items: center;
		justify-content:space-between;
	}
.rechangehead{
	position: relative;
	width: 100%;
	padding: 20rpx 0;
	display: flex;align-items: center;
	justify-content: space-between;
	border-bottom: 1px solid #eee;
}
.title{
	position: relative;
	flex: 1;
	color: #0090FF;
	text-align: center;
}
</style>
