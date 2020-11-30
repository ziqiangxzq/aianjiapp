<template>
	<view>
		<view style="display: flex;width: 100vw;justify-content: space-between;">
	<view  v-for="(item,index) in droparrs">
	<view class="drop">
	<view class="dropunit" @click="opendroplist(index)">
		<view>{{dropname[index]}}</view>
		<view class="dropicon"></view>
	</view>
	<view class="droplist" v-if="dropshow[index]==1">
		<view class="dropchoice" @click="choiceit(itam,index)" v-for="itam in item">{{ itam }}</view>
	</view>
	</view>
	</view>	
	   </view>
	</view>
</template>

<script>
	export default {
		props:["droparrs"],
		data() {
			return {
			dropshow:[0,0,0,0,0,0],
			dropname:[]
			};
		},
		created() {
			if(this.dropshow.length!=this.droparrs.length){//初始化展示数组
			var dropcopy=[];
			for(var i=0;i<this.droparrs.length;i++){				
					dropcopy.push(0);
					console.log(this.droparrs[i][0]);
					this.dropname.push(this.droparrs[i][0])
				}
			}
			this.dropshow=dropcopy;
		},
		methods:{
			opendroplist: function(a) {//使用等号运算符赋值无效 需重新遍历排列数组 否则数据改变视图无变化
				if(this.dropshow[a]==0){
				this.dropshow=[];
				for(var i=0;i<this.droparrs.length;i++){
					if(i==a){
						this.dropshow.push(1)
					}else{
						this.dropshow.push(0)
					}
				}					
				}else{
				this.dropshow=[];
				for(var i=0;i<this.droparrs.length;i++){
						this.dropshow.push(0)
				}	
				}
			},
			choiceit:function(a,b){
				console.log(a);
				console.log(b);
				this.dropname[b]=a;
			    this.dropshow=0;
			}
		}
	}
</script>

<style>
	.drop{position: relative;
	width: 100%;
	}
.droplist {
	position:absolute;
	width: 90%;
	left: 5%;
	background-color:#FFF;
	border: 1px solid #eee;
	z-index: 5;
	border-radius: 0 0 20rpx 20rpx;
	overflow: hidden;
	box-shadow: 0 15rpx 20rpx 10rpx rgba(0,0,0,0.1);
}
.dropchoice{
	position: relative;
	width: 100%;
	padding:15rpx 0;
	border-bottom: 1px solid #eee;
	background-color: #fff;
	text-align: center;
	line-height: 50rpx;
	font-size: 30rpx;
	color: #555;
}
.dropchoice:hover{
     background-color:#eee;	
}
.dropicon {
	width: 0;
	height: 0;
	border: 15rpx solid;
	margin-top: 15rpx;
	margin-left: 10rpx;
	border-color: #444 transparent transparent;
}
.dropunit {
	position: relative;
	padding: 30rpx 40rpx;
	font-size: 30rpx;
	display: flex;
	color: #444;
	align-items: center;
	justify-content: center;
}
</style>
