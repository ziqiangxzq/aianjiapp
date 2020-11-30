<template>
	<view>
		<view class="goodslistbox">
			<view class="nocontent" v-if="goodarr.length==0">暂无商品敬请期待~</view>
			<view class="gooditem" v-if="goodarr.length!=0" v-for="item in goodarr">
				<view class="goodsimg">
					<img :src="item.pic_uri" style="width: 100%;height: 100%;position: relative;">
				</view>
				<view class="goodmsgbox">
					<view >{{item.goods_name}}</view>
					<view >剩余：{{item.numbers}}</view>
					<view class="fontpoint">积分:{{item.consume_points}}</view>
				</view>
				<view  v-if="item.numbers==0" class="goodschange gray">已兑完</view>
				<view  v-if="item.numbers!=0" class="goodschange" @click="exchange(item.goods_id,item.consume_points)">兑 换</view>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
			goodarr:[1,2,3],
			nocontent:0	,
			page:1
			}
		},
		onLoad(){
			this.getgoodarr()
		}
		,
		methods: {
			//https://www.meilianji.cn/web/points/get_points_goods_list.php?page=1&recs=10&type=0
			exchange:function(a,b){
				
				uni.showModal({
				    title: '提示',
				    content: '本次兑换需花费'+b+'积分,是否进行兑换？',
				    success: function (res) {
				        if (res.confirm) {
                          uni.request({
                          	url:"https://www.meilianji.cn/web/points/exchange_points_goods.php",
							data:{
								goods_id:23,
								user_id:63714
							},
							dataType:"JSON",
							method:"POST",
							header:{
								"content-type":"application/x-www-form-urlencoded"
							},
							success: (res) => {
								if(res.data.resultid==0){
									uni.showToast({
										icon:'none',
										title:res.data.msg
									})
								}else{
									uni.showToast({
										icon:"none",
										title:"兑换成功,请于工作日前往指定地点凭兑换码兑换！"
									})
								}
								console.log(res.data)
							}
							
                          })
				        } else if (res.cancel) {
				            console.log('用户点击取消');
				        }
				    }
				});
			},
			getgoodarr: function(){
				uni.request({
					url:"https://www.meilianji.cn/web/points/get_points_goods_list.php?",
					data:{
					page:this.page,
					recs:10,
					type:0	
					},
					dataType:'JSON',
					method:"GET",
					header:{
						"content-type":"application/x-www-form-urlencoded"
					},
					success: (res) => {
						if(this.page==1){
						if(res.data.length!=0){
							this.goodarr=res.data
						}else{
							this.nocontent=1
						}
						console.log(res.data)	
						}else{
						if(res.data.length==0){
							uni.showToast({
								icon:'none',
								title:'暂无更多内容~'
							})
						}else{
							for(var i=0;i<res.data.length;i++){
								this.goodarr.push(res.data[i]);
							}
						}	
						}

					}
				})
			}
		},onReachBottom() {//滑动到底部加载更多新闻或显示提示信息
		  console.log("滑动到底部了");
		  this.page++;
		  this.getgoodarr()	},
		  onNavigationBarButtonTap(e) {
		  	console.log(e.index)
		  	if(e.index==0){
		  	uni.navigateTo({
		  		url:"../pointshop-rechanglist/pointshop-rechanglist"
		  	})
		  	}
		  }
	}
</script>

<style>
	.nocontent{
		position: relative;
		width: 100%;
		text-align: center;
		color: gray;
		padding: 50rpx;
	}
	.fontpoint{
		font-size:20rpx;
		color: #0090FF;
	}
.gooditem{
	position: relative;
	display: flex;
	align-items: center;
	border-bottom: 1px solid #eee;
	width: 100%;
	background-color: #fff;
	padding: 24rpx;
}
.goodsimg{
	position: relative;
	width: 100rpx;
	height:100rpx;
	background-color: #f8f8f8;
	border-radius: 100rpx;
}
.goodmsgbox{
	position: relative;
	width: 300rpx;
	height: 100rpx;
	margin-left: 50rpx;
	display: flex;
	flex-direction: column;
	justify-content: space-between;
	background-color: #fff;
	color: #444;
}
.goodschange{
	position:absolute;
	right:24rpx;
	width:120rpx;
	height:55rpx;
	font-size: 26rpx;
	border-radius:30rpx;
	background-color: #0090ff;
	text-align: center;
	line-height:55rpx;
	color: #fff;
}
	.gray{
	background-color:gray;	
	}
</style>
