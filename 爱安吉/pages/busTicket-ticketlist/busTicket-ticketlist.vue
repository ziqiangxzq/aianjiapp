<template>
	<view>
		<view class="listbox">
			<view class="nocontent" v-if="tricklist.length==0">
				{{tips}}
			</view>
			<view class="listunit" v-on:click="openorderdetail(item)" v-if="tricklist.length!=0" v-for="item in tricklist">
				<view class="headbox">
					<view class="time">{{item.Time}}<span class="grayS">发车</span></view>
					<view class="price">￥{{item.FullPrice}}</view>
				</view>
				<view class="bodybox">
					<view class="address"><span class="pointicon">起</span>{{item.SellStationName}} <view class="ticknum">剩<span class="blue">{{item.SeatRemain}}</span>张</view></view>
					<view class="address"><span class="pointicon">终</span>{{EndStationName}} <view class="bustype">{{item.VehicleModel}}</view></view>
				</view>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
			page:1,
			tricklist:[],
			tips:'加载中...',
			EndStationName:'',
			}
		},onLoad() {
			this.getticklist()
		},
		methods: {
			getticklist:function(){
				
				var url = this.globalUrl + '/ticket/get_Bus4.php';
				uni.request({
					url:url+'?unitID='+uni.getStorageSync("unitid")+'&busDate='+uni.getStorageSync("trickdate")+'&desStationID='+uni.getStorageSync("station")+'&pageSize=10&pageSerial='+this.page,
					data:{
					// unitID:uni.getStorageSync("unitid"),
					// busDate:uni.getStorageSync("trickdate"),
					// desStationID:uni.getStorageSync("station"),
					// pageSize:"10",
					// pageSerial:this.page
					},
					dataType:'json',
					method:'GET',
					header:{
						"contentr-type":"application/x-www-form-urlencoded"
					},
					success: (res) => {
					if(this.page==1){//第一页
						if(res.data.length!=0){
						this.tricklist=res.data;
						}else{
						this.tricklist=[];
						}
					}else{
						if(res.data.length!=0){
						for(var i=0,length=res.data.length;i<length;i++){
							var obj=res.data[i];
							this.tricklist.push(obj);
						}	
						}else{
							uni.showToast({
								icon:'none',
								title:'暂无更多车次信息~'
							})
						}
					}
					console.log(res.data)
						this.tips='很遗憾，暂无符合要求的车次信息~'
						this.EndStationName=uni.getStorageSync("unitname")
					}
				})
			},
			openorderdetail:function(arr){//打开订单详情
			var that = this
				uni.navigateTo({
					url:'../busTicket-orderdetail/busTicket-orderdetail?EndStationName='+that.EndStationName+'&BusDate='+uni.getStorageSync("trickdate")+'&Time='+arr.Time+'&VehicleModel='+arr.VehicleModel+'&FullPrice='+arr.FullPrice+'&busID='+arr.ID+'&SellStationID='+arr.SellStationID+'&SellStationName='+arr.SellStationName+'&EndStationID='+arr.EndStationID +'&HalfPrice='+arr.HalfPrice 
				})
			}
		},
		onReachBottom() {
			this.page++;
			this.getticklist()
		}
	}
</script>

<style>
	.nocontent{
		position: relative;
		width: 100%;
		text-align: center;
		padding: 2rem 0;
		color: gray;
	}
	.blue{
		color: #0090ff;
		margin: 0 0.1rem;
	}
	.bustype{
		position:absolute;
		right:0;
	    top: 0.2rem;
		color: gray;
		font-size: 0.7rem;		
	}
	.ticknum{
		position:absolute;
		top: 0.2rem;
		right:0;
		color: gray;
		font-size: 0.7rem;
	}
	.address{
		position: relative;
		display: flex;
		align-items: center;
		margin-top: 0.4rem;
	}
	.pointicon{
		position: relative;
		width: 1.3rem;
		height: 1.3rem;
		background-color: #2ba3ff;
		display: flex;
		align-items: center;
		font-size: 0.65rem;
		justify-content: center;
		color: #fff;
		border-radius: 1rem;
		margin-right: 0.4rem;
	}
	.bodybox{
		position: relative;
		width:100%;
	/* 	background-color: #060F53; */
	}
	.time{
		position: relative;
		font-size: 0.9rem;
		color: #444;
		font-weight: bold;
	}
	.price{
		position: relative;
		font-size: 0.9rem;
		color: #2ba3ff;	
		font-weight: bold;
	}
	.grayS{
		position: relative;
		font-size: 0.8rem;
		color:gray;
		margin-left: 0.2rem;
		font-weight:normal;
	}
.listunit{
	position: relative;
	width: 100%;
	padding: 24rpx;
	border-bottom: 1rpx solid #eee;
}
.headbox{
	position: relative;
	width: 100%;
	display: flex;
	margin-bottom: 0.6rem;
	justify-content:space-between;
}
</style>
