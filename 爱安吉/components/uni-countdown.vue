<template name="uni-countdown">
	<view class="uni-countdown">
		<view class="uni-countdown-numbers" @click="click" :id="id" :style="{borderColor:borderColor, color:fontColor, background:bgrColor}">{{text}} {{s}}</view>
	</view>
</template>
<script>
	import MD5 from '../common/MD5.js';
	export default {
		name: "uni-countdown",
		props: {
			bgrColor: {
				type: String,
				default: "#FFFFFF"
			},
			borderColor: {
				type: String,
				default: "#000000"
			},
			fontColor: {
				type: String,
				value: "#ec4e47" 
			},
			splitorColor: {
				type: String,
				default: "#000000"
			},
			timer: {
				type: String,
				default: ""
			},
			phone: {
				type: String,
				default: ""
			}
		},
		data() {
			return {
				setTime: null,
				h: '00',
				i: '00',
				s: '',
				leftTime: 0,
				text:'获取验证码',
				id:1
			}
		},
		created: function(e) {	
			var reg = /^([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})$/;
			var res = this.timer;
			// console.log(this.timer)
			if (res == null) {
				console.log('时间格式错误');
				return false;
			} else {
				var s = parseInt(res);
				if (s < 0 || s > 60) {
					console.log('时间格式错误');
					return false;
				}
				// var leftTime = new Date(i, s);
				this.leftTime = '60';
				this.countDown(this);
				this.setInterValFunc(this);
			}
		},
		beforeDestroy() {
			clearInterval(this.setTime)
		},
		methods: {
			setInterValFunc: function(obj) {
				this.setTime = setInterval(function() {
					obj.countDown(obj);
				}, 1000);
			},
			click:function(){
				var that = this;
				if(this.s == '') {
					this.text = '重新获取'
					this.s = '60';
					this.bgrColor = '#a8a8a8';
					
					var url = '/sms/sendPhoneCode';
					var data = {
						"phone": this.phone,
					}
					that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
						if(res.data.ret == 200) {
						   	uni.showToast({
						   	    title: res.data.msg,
						   	    duration: 1200,
						   		icon: 'none'
						   	});
						} else {
							that.s = '';
							uni.showToast({
							    title: res.data.msg,
							    duration: 1200,
								icon: 'none'
							});
						}
					}, "globalUrlNew");
				} else {
					uni.showToast({
						icon: 'none',
					    title: '请勿重复提交',
					    duration: 2000
					});
				}
			},
			countDown: function(self) {
				
				if(self.text == '重新获取'){
					if(self.s > 0) {
						self.s -= 1;
					}else if(self.s == 0){
						self.s = '';
						self.text = '获取验证码';
						self.bgrColor = '#0090ff';
					}
				}
			},
			clearVerify: function() {
				this.s = '';
			}
		}
	}
</script>
<style>
	.uni-countdown {
		display: flex;
		padding: 2upx 0;
		flex-wrap: nowrap;
		justify-content: center;
	}
 
	.uni-countdown-splitor {
		width: auto !important;
		justify-content: center;
		line-height: 50upx;
		padding: 0 5upx;
	}
 
	.uni-countdown-numbers {
		line-height: 50upx;
		width: auto !important;
		padding: 0 10upx;
		justify-content: center;
		height: 50upx;
		border-radius: 8upx;
		margin: 0 5upx;
		/* border: 1px solid #000000; */
		font-size: 22upx;
	}
</style>