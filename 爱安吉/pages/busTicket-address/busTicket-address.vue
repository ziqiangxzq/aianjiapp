<template>
	<view>
		<view class="selectbox">
			<view class="inputbox">
				<view class="iconbox">
				<image src="../../static/bus/select.png" style="width: 100%;height:100%;">	
				</view>
				<input placeholder="杭 /杭州 /HZ" v-on:input="selectaddresslist()" v-model="addresstext">
			</view>
		</view>
		<view class="listbox">
			<view class="listunit" v-on:click="choiceit(item.UnitID,item.Name,item.ID)" v-for="item in addresslist">
			{{item.Name}}
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
			fulladdresslist:[],
			addresslist:[],
			addresstext:""
			}
		},
		onLoad() {
			this.getcitylist()
		},
		onBackPress() {
			uni.redirectTo({
				url: '../busTicket-index/busTicket-index'
			})
			return true
		},
		methods: {
			choiceit:function(a,b,c){
				uni.setStorageSync("unitid",a);//缓存地区id
				uni.setStorageSync("unitname",b);//缓存地区名
				uni.setStorageSync("station",c);//缓存车站id
				uni.redirectTo({
					url:'../busTicket-index/busTicket-index'
				})
			}
			,
			getcitylist:function(){
				uni.request({
					url:this.globalUrl+ '/ticket/get_EndStations2.php',
					data:{
						unitID:'330572010',
						},
					dataType:'json',
					method:'post',
					header:{
					//"content-type":"application/x-www-form-urlencoded"
					"content-type":"application/x-www-form-urlencoded"	
					},
					success: (res) => {
					this.addresslist=res.data;
					this.fulladdresslist=res.data;	
					console.log(res.data.length);	
					}
				})
			},
			selectaddresslist:function(){
				console.log("selectaddresslist");
				this.addresslist=[];
				for(var i=0,length=this.fulladdresslist.length;i<length;i++){
					// console.log(this.addresstext);
					// console.log(this.fulladdresslist[i].Name);
					// console.log(this.fulladdresslist[i].Name.indexOf(this.addresstext));
					
					if(this.fulladdresslist[i].Name.indexOf(this.addresstext)!=-1||this.fulladdresslist[i].InputCode.indexOf(this.addresstext)!=-1){//this.addresstext
				    console.log("have");
					var obj=this.fulladdresslist[i];
					this.addresslist.push(obj)	 	
					}else{
					console.log("nothave");	
					}
				}
			}
		}
	}
</script>

<style>
	.listunit{
		position: relative;
		width: 100%;
		padding: 30rpx;
		color: #444;
		border-bottom: 1px solid #f8f8f8;
	}
	.listbox{
		/* margin-top:100rpx ; */
		padding-top: 100rpx;
	}
.selectbox{
	position:fixed;
	/* top:0rpx; */
	left: 0;
	z-index: 10;
	width: 100%;
	padding:30rpx;
	height: 100rpx;
	display: flex;
	align-items:center;
	justify-content: center;
	background-color:#eee;
}
.inputbox{
	position:relative;
	width: 100%;
	height:60rpx;
	border-radius: 10rpx;
	background-color: #fff;
	display: flex;
	align-items:center;
}
.inputbox input{
	font-size: 0.75rem;
	width: 80%;
}
.iconbox{
    position: relative;
	width:40rpx;
	height: 40rpx;
	margin-left: 10rpx;
	margin-right:10rpx;
}
</style>
