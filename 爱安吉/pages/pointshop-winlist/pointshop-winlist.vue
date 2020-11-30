<template>
	<view>
		<view style="margin-top:20rpx;" v-for="item in winlist">
		<lab :name="item.title"></lab>
		<view class="winlistbox">
			<view class="winitem" v-for="itam in item.award_info">
				<view style="width: 80%;">
				<view class="itemtitle">{{itam.award_name}}</view>
				<view class="itemdesc">{{itam.award_level_desc}}</view>
				<view class="itemtime">兑奖截止日期：<span class="blue">{{itam.award_end_time}}</span></view>
				</view>
				<view v-if="itam.if_used==0">未兑换</view>
				<view v-if="itam.if_used==1">已兑换</view>
				<view v-if="itam.if_used==2">已过期</view>
			</view>
		</view>
		</view>
	</view>
</template>

<script>
	import lab from "../../components/lab.vue"
	export default {
		components:{lab},
		data() {
			return {
			winlist:[]	
			}
		},
		onLoad() {
			this.getwinlist()
		},
		methods: {
		getwinlist:function(){
			uni.request({
				url:"https://www.meilianji.cn/web/points/get_activity_user_record2.php",
				data:{
				user_id:1,
				page:1,
				recs:100000	
				},
				dataType:"JSON",
				method:"POST",
				header:{
				'content-type': 'application/x-www-form-urlencoded',
				},
				success: (res) => {
					this.winlist=res.data
					console.log(res.data)
				}
			})
		}	
		}
	}
</script>

<style>
	.blue{
		color: #0090FF;
	}
	.itemtitle{
		position: relative;
		font-size: 32rpx;
	}
	.itemdesc{
		font-size: 28rpx;
		margin-top: 5rpx;
		color: gray;
	}
	.itemtime{
		position: relative;
		color: gray;
		font-size: 28rpx;
		margin-top: 5rpx;
	}
	.winlistbox{
		margin-top: -24rpx;
	}
.winitem{
	position: relative;
	width: 100%;
	padding:40rpx;
	color: #444;
	border-bottom: 1px solid #f8f8f8;
	display: flex;
	align-items: center;
	justify-content: space-between;
}
</style>
