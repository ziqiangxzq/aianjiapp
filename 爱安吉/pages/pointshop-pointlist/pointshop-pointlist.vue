<template>
	<view>
		<u-tabs style="position: fixed;width: 100%;background-color: #fff;top:42px;z-index: 50;border-bottom:1px solid #f8f8f8 ;" ref="tabs" :list="typearr" :is-scroll="false" :current="current" @change="choiceit"></u-tabs>
		<view class="listbox">
			<view v-if="addlistbox==1">
			<view class="listnocontent" v-if="addarr.length==0">暂无内容~</view>
			<view class="listitem" v-for="item in addarr">
				<view class="itemimage">
					<img style="width: 100%;height: 100%;" :src="item.category_icon">
				</view>
				<view class="itemtitle">{{item.category_name}}</view>
				<view style="display: none;" class="itemtime">{{item.create_time}}</view>
				<view class="pointnum">+{{item.points}}</view>
			</view>
			</view>
			<view v-if="dellistbox==1">
			<view class="listnocontent" v-if="delarr.length==0">暂无内容~</view>
			<view class="dellistitem" v-for="item in delarr">
				<view class="delitemtitle">{{item.goods_names}}<view class="delpointnum">-{{item.points}}</view></view>
				<view  class="delitemtime">{{item.create_time}}</view>
				
			</view>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				addlistbox:1,
				dellistbox:0,
				addarr:[],
				delarr:["0",2,3,4],
				current:0,
				typearr:[{ index: 0, name: '积分奖励', classname: 'typeunit typeunited' }, { index: 1, name: '积分扣除', classname: 'typeunit' }]
			}
		},
		onLoad(){
		this.getpointaddlist();	
		this.getpointdellist();
		},
		methods: {
			//积分奖励
			//https://www.meilianji.cn/web/points/get_user_points_award_detail.php?user_id=63714&page=1&recs=10&_=1596176330508
			//积分扣除
			//https://www.meilianji.cn/web/points/get_user_points_consume_detail.php?user_id=63714&page=1&recs=10
			getpointaddlist:function(){
			uni.request({
				url:"https://www.meilianji.cn/web/points/get_user_points_award_detail.php",
				data:{
					user_id:63714,
					page:1,
					recs:10
				},
				dataType:"JSON",
				method:"GET",
				header:{
				'content-type':'application/x-www-form-urlencoded'		
				},
				success:(res)=>{
					this.addarr=res.data;
				}
			})	
			},
			getpointdellist:function(){
				uni.request({
					url:"https://www.meilianji.cn/web/points/get_user_points_consume_detail.php",
					data:{
					user_id:63714,
					page:1,
					recs:10	
					},
					dataType:"JSON",
					method:"GET",
					header:{
						"content-type":"application/x-www-form-urlencoded"
					},
					success:(res)=>{
						this.delarr=res.data;
					}
				})
			}
			,
			choiceit:function(a){
				this.current=a;
				if(a==0){
				this.addlistbox=1,
				this.dellistbox=0;	
				}else{
				this.addlistbox=0,
				this.dellistbox=1;						
				}
			}
		}
	}
</script>
<style>
	.listnocontent{
		position: relative;
		width: 100%;
		text-align:center;
		color:gray;
		padding:50rpx 0;
	}
	.listbox{
		position: relative;
		top:70rpx;
	}
	.pointnum{
		position:absolute;
		color: #444;
		font-size: 40rpx;
		right:24rpx;
	}
	.blue{
	    color: #0090ff;	
	}
	.delpointnum{
		position:relative;
		color: #0090ff;
		font-size: 30rpx;
		display: inline-block;		
	}
	 .itemimage{
		 position: relative;
		 width: 80rpx;
		 height:80rpx;
		 border-radius: 40rpx;
		 background-color:#f8f8f8;
		 display: flex;
		 background-color: #eee;
		 align-items: center;
		 justify-content: center;
	 }	
	 .itemtime{
		 position: absolute;
		 font-size: 25rpx;
		 right:24rpx;
		 top: 4rpx;
		 color:#aaa;
	 }
	 .delitemtime{
		 position: absolute;
		 font-size: 25rpx;
		 right:24rpx;
		 color:#666;		 
	 }
	 .itemtitle{
		 position: relative;
		 margin-left: 40rpx;
		 font-size: 30rpx;
	 }
	 .delitemtitle{
		 color: #444;
		 position: relative;
		 font-size: 30rpx;		 
	 }
	  .listitem{
		  position: relative;
		  width: 100%;
		  padding: 24rpx;
		  display: flex;
		  align-items: center;
		  border-bottom: 1rpx solid #f8f8f8;
	  }
	  .dellistitem{
		  position: relative;
		  width: 100%;
		  padding:40rpx 24rpx;
		  display: flex;
		  align-items: center;
		  border-bottom: 1rpx solid #f8f8f8;		  
	  }
</style>
