<template>
	<view class="container">
		<!-- 浮动窗口开始 -->
		<view class="addpassengerfloatbox" v-if="floatshow==1">
			<view class="msgbox">
				<view class="headbox">
					<view class="button cancelbutton" v-on:click="canceladd">取消</view>
					<view class="button" v-on:click="enter">确定</view>
				</view>
				<view class="unitbox" v-for="(item,index) in passengerlist">
					<view class="choiceit" v-on:click="choiceit(index)">
						<image :src="item.imgsrc" style="width: 100%;height: 100%;">
					</view>
					<view class="usermsg">
						<view class="person-message-box">
							<view class="msg">{{item.user_name}}<span class="grayS" v-if="item.ticker_type==0">(成人票)</span><span class="grayS"
								 v-if="item.ticker_type==1">(儿童票)</span></view>
							<view class="idcard">{{item.id_card}}</view>
						</view>
					</view>
					<view class="delete-text" @click="delete_personmessage(item.contactor_id)">
						删除
					</view>
				</view>
				<view class="addbox" v-on:click="addpassenger"><span class="iconbox">
						<image src="../../static/bus/add.png" style="width: 100%;height: 100%;">
					</span>新增乘客</view>
			</view>
		</view>
		<!-- 浮动窗口结束 -->
		<view class="ordermsg">
			<view class="ordermsgbox">
				<view class="headextramsg"><span class="day">{{BusDate}}</span> {{Time}}发车</view>
				<view class="trickmessage">安吉<span style="font-weight:normal;margin: 0 0.4rem;">----</span>{{EndStationName}}</view>
			</view>
			<view class="bottombox">
				<view class="bleft">
					<view><span style="color: gray;margin-right: 0.4rem;">车型</span> {{VehicleModel}}</view>
					<view class="explain" @click="gotoillustrate">售票，取票，退改签说明 ></view>
				</view>
				<view class="bright">￥{{FullPrice}}</view>
			</view>
		</view>
		<view class="passenger unit">
			<view><span class="title">乘客</span><span class="grayS">（一个用户最多可代购五张票）</span></view>
			<view class="addpassenger" v-on:click="addpass">添加乘客</view>
		</view>
		<view class="unitbox" v-for="(item,index) in relpassengerlist">
			<view class="delete-box" @click="delete_list(index)">
				<image src="../../static/bus/delete.png" class="delete-img"></image>
			</view>
			<view class="usermsg-out">
				<view class="msg-out" style="font-size: 30rpx;">{{item.user_name}}<span class="grayS" v-if="item.ticker_type==0">(成人票)</span><span
					 class="grayS" v-if="item.ticker_type==1">(儿童票)</span></view>
				<view class="idcard-out" style="font-size: 26rpx;">{{item.id_card}}</view>
			</view>
		</view>

		<view class="gettickper unit">
			<view class="flexcenter"><span class="title">取票人</span><input type="text" placeholder="请选择" v-model="contactsname"
				 disabled="true" class="people" /></view>
			<view v-on:click="showqupiao()" class="xiala">
				<image src="../../static/bus/xiala.png" style="width: 100%;height: 100%;">
			</view>
		</view>
		<view class="taketrick" v-if="choicequpiao==1 && relpassengerlist!=''">
			<view class="unittrick" v-for="(item,index) in relpassengerlist" :style="{'background-color':item.if_contacts==1?'#0090FF':'#c7c7c7'}"
			 @click="selectperson(index)">{{item.user_name}}</view>

		</view>
		<view class="phone unit">
			<view class="flexcenter"><span class="title">手机号</span><input placeholder="用于接收取票信息" v-model="phonenum" style="width: 500rpx;" type="number"></view>
		</view>
		<view class="floatbox">
			<view class="preice">￥{{TotalPrice}}</view>
			<view class="submitorder" @click="submit_order">提交订单</view>
		</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				// 订单内容start
				EndStationName: '',
				BusDate: '',
				Time: '',
				VehicleModel: '',
				FullPrice: '',
				// 订单内容end
				busID: '',
				BusDateLong: '',
				SellStationID: '',
				SellStationName: '',
				EndStationID: '',
				HalfPrice: '',
				halfTicketCount: '',
				fullTicketCount: '',

				floatshow: 0,
				choicequpiao: 0,
				passengerlist: [],
				relpassengerlist: [],
				TotalPrice: '0.00',

				contacts: [],
				contactsname: '请选择',

				phonenum: '',
			}
		},
		onShow() {
			this.getpassengerlist()
		},
		onLoad(options) {
			this.EndStationName = options.EndStationName
			this.BusDate = options.BusDate.substr(5)
			this.BusDateLong = options.BusDate
			this.Time = options.Time
			this.VehicleModel = options.VehicleModel
			this.FullPrice = options.FullPrice
			this.busID = options.busID
			this.SellStationID = options.SellStationID
			this.SellStationName = options.SellStationName
			this.EndStationID = options.EndStationID
			this.HalfPrice = options.HalfPrice
		},
		methods: {
			addpass: function() { //打开添加乘客界面
				this.floatshow = 1;
				// this.getpassengerlist()
			},
			canceladd: function() { //点击取消 隐藏添加乘客界面
				this.floatshow = 0
			},
			addpassenger: function() { //打开新增乘客界面
				uni.navigateTo({
					url: "../busTicket-addpassenger/busTicket-addpassenger"
				})
			},
			enter: function() { //确认选择乘客
				for (var i = 0, length = this.passengerlist.length; i < length; i++) {
					if (this.passengerlist[i].checkstatic == 1) {
						var obj = this.passengerlist[i];
						this.relpassengerlist.push(obj)
					} else {}
				}
				// 去掉数组里重复的对象start
				var result = [];
				var obj = {};
				for (var i = 0; i < this.relpassengerlist.length; i++) {
					if (!obj[this.relpassengerlist[i].contactor_id]) {
						result.push(this.relpassengerlist[i]);
						obj[this.relpassengerlist[i].contactor_id] = true;
					}
				}
				// 去掉数组里重复的对象end
				this.relpassengerlist = result
				this.calculation_total(); //计算总价
				this.floatshow = 0
			},
			choiceit: function(a) {
				if (this.passengerlist[a].checkstatic == 0) {
					this.passengerlist[a].imgsrc = '../../static/bus/checkpassenger.png';
					this.passengerlist[a].checkstatic = 1
				} else if (this.passengerlist[a].checkstatic == 1) {
					this.passengerlist[a].imgsrc = '../../static/bus/notpassenger.png';
					this.passengerlist[a].checkstatic = 0;
				}
			},
			showqupiao: function() {
				if (this.choicequpiao == 0) {
					this.choicequpiao = 1
				} else {
					this.choicequpiao = 0
				}
			},
			getpassengerlist: function() {
				var url = this.globalUrl + '/ticket/get_contactor_info.php';
				uni.request({
					url: url,
					data: {
						user_id: uni.getStorageSync("user_id")
					},
					dataType: 'json',
					method: 'post',
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					success: (res) => {
						for (var i = 0, length = res.data.length; i < length; i++) {
							res.data[i] = {
								imgsrc: '../../static/bus/notpassenger.png',
								if_contacts: 0,
								checkstatic: 0,
								contactor_id: res.data[i].contactor_id,
								id_card: res.data[i].id_card,
								ticker_type: res.data[i].ticker_type,
								user_name: res.data[i].user_name,
							}
							// res.data[i].imgsrc='../../static/bus/checked.png';
							// res.data[i].checkstatic=0;
						}
						this.passengerlist = res.data;
					}
				})
			},
			// 删除添加乘客里的乘客
			delete_personmessage: function(a) {
				var url = this.globalUrl + '/ticket/delete_ticket_contactor.php';
				uni.request({
					url: url,
					data: {
						contactor_id: a,
					},
					dataType: 'json',
					method: 'post',
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					success: (res) => {
						if (res.data[0].resultid == 1) {
							uni.showToast({
								icon: "none",
								title: '删除成功'
							})
						}

						this.getpassengerlist()
					}
				})
			},
			// 删除外面显示的乘客
			delete_list: function(a) {
				if (this.relpassengerlist[a].if_contacts = 1) {
					this.relpassengerlist[a].if_contacts = 0
					this.contacts = []
					this.contactsname = ''
				}
				//外面去掉时里面也变化
				for (var i = 0; i < this.passengerlist.length; i++) {
					if (this.passengerlist[i].contactor_id == this.relpassengerlist[a].contactor_id) {
						this.choiceit(i)
					}
				}

				//删除
				this.relpassengerlist.splice(a, 1);
				this.calculation_total(); //计算总价

			},
			// 选择取票人
			selectperson: function(a) {
				for (var i = 0; i < this.relpassengerlist.length; i++) {
					this.relpassengerlist[i].if_contacts = 0
				}
				this.relpassengerlist[a].if_contacts = 1
				this.contacts = this.relpassengerlist[a]
				console.log(this.contacts)
				this.contactsname = this.contacts.user_name
				this.choicequpiao = 0
			},
			// 计算总金额和成人票与儿童票的数量
			calculation_total: function() {
				var k = 0;
				var t = 0;
				for (var i = 0; i < this.relpassengerlist.length; i++) {
					if (this.relpassengerlist[i].ticker_type == 0) {
						k++
					} else {
						t++
					}
				}
				this.halfTicketCount = t
				this.fullTicketCount = k
				this.TotalPrice = this.halfTicketCount * this.HalfPrice + this.fullTicketCount * this.FullPrice
			},
			submit_order: function() {
				var idCards = []
				var names = []
				var contactor_ids = []
				for (var i = 0; i < this.relpassengerlist.length; i++) {
					if (this.relpassengerlist[i].ticker_type == 0) {
						idCards.push(this.relpassengerlist[i].id_card + '=0')
					} else {
						idCards.push(this.relpassengerlist[i].id_card + '=1')
					}

					names.push(this.relpassengerlist[i].user_name)
					contactor_ids.push(this.relpassengerlist[i].contactor_id)
				}
				var that = this;
				var url = that.globalUrl + '/ticket/web_MakeOrder2_new.php';
				var json = [{
					user_id: uni.getStorageSync("user_id"),
					unitID: uni.getStorageSync("unitid"),
					busID: that.busID,
					busDate: that.BusDateLong + ' ' + that.Time,
					beginStationID: that.SellStationID,
					start_station: that.SellStationName,
					end_station: that.EndStationName,
					endStationID: that.EndStationID,
					fullTicketCount: that.fullTicketCount,
					fullTicketPrice: that.FullPrice,
					halfTicketCount: that.halfTicketCount,
					halfTicketPrice: that.HalfPrice,
					idCard: that.contacts.id_card,
					contactor_id: that.contacts.contactor_id,
					name: that.contacts.user_name,
					mobile: that.phonenum,
					amount: that.TotalPrice,
					idCards: idCards.join(","),
					names: names.join(","),
					contactor_ids: contactor_ids.join(","),


				}];
				uni.request({
					url: url,
					method: 'GET',
					dataType: 'JSON',
					data: {
						json: JSON.stringify(json)
					},
					success: res => {

						if (res.data[0].resultid == 1) {
							uni.setStorageSync('openway', 'orderdetail')
							uni.navigateTo({
								url: '../busTicket-orderpay/busTicket-orderpay?buyed_id=' + res.data[0].buyed_id
							})

						} else {
							uni.showToast({
								icon: "none",
								title: res.data[0].str,
							});
						}

					},
					fail: () => {},
					complete: () => {}
				})
			},
			gotoillustrate: function() {
				uni.navigateTo({
					url: '../busTicket-illustrate/busTicket-illustrate'
				})
			}
		}
	}
</script>

<style lang="scss">
	$theme-color:#0090ff;
	$bottom-line:1px solid #f8f8f8;

	page {
		color: #444;
		background-color: #fff;
	}

	.container {
		padding-bottom: 100rpx;
	}

	.unittrick {
		position: relative;
		width: 4rem;
		background-color: #a4a4a4;
		color: #fff;
		display: flex;
		border-radius: 0.4rem;
		padding: 0.3rem 0;
		align-items: center;
		justify-content: center;
		float: left;
		margin-right: 0.65rem;
		margin-bottom: 0.3rem;
	}

	.taketrick {
		position: relative;
		width: 100%;
		background-color: #fff;
		padding: 25rpx 24rpx;
	}


	.headextramsg {
		position: relative;
		font-size: 0.8rem;
		font-weight: normal;
		margin-bottom: 0.4rem;
	}

	.xiala {
		position: relative;
		width: 1.3rem;
		height: 1.3rem;
	}

	.xiala img {
		width: 100%;
	}

	.trickmessage {
		position: relative;

	}

	.day {
		position: relative;
		margin-right: 1rem;
	}

	.ordermsgbox {
		position: relative;
		width: 100%;
		height: 4rem;
		background-color: #fff;
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
		font-size: 1rem;
		font-weight: bold;
	}

	.explain {
		position: relative;
		font-size: 0.6rem;
		color: $theme-color;
		padding-left: 0.1rem;
		margin-top: 0.2rem;
	}

	.bright {
		position: relative;
		font-size: 1rem;
		color: $theme-color;
	}

	.bleft {
		font-size: 0.6rem;
	}

	.bottombox {
		position: relative;
		width: 100%;
		padding: 30rpx 24rpx;
		background-color: #fff;
		display: flex;
		align-items: center;
		justify-content: space-between;
		border-bottom: 1px solid #eee;
	}

	.choiceit {
		// position:absolute;
		width: 50rpx;
		height: 50rpx;
		// right: 0.5rem;
		display: flex;
		align-items: center;
		justify-content: center;
		background-color: #fff;
		overflow: hidden;
		border-radius: 25rpx;
	}

	.choiceit img {
		width: 100%;
	}

	.idcard {
		font-size: 0.7rem;
		color: gray;
		margin-top: 0.2rem;
	}

	.delete-text {
		position: absolute;
		right: 40rpx;
		color: #ff0000;
		line-height: 140rpx;
	}

	.person-message-box {
		margin-left: 40rpx;
		margin-top: 20rpx;
		height: 100rpx;
	}

	.msg {
		position: relative;
		font-size: 32rpx;
	}

	.usermsg {
		position: relative;
		display: flex;
		/* width:50%; */
		background-color: #fff;
	}

	.unitbox {
		position: relative;
		width: 100%;
		padding: 24rpx 40rpx 24rpx 40rpx;
		height: 4rem;
		// border-bottom: 1px solid #f8f8f8;
		display: flex;
		align-items: center;
		// justify-content:space-between;
	}

	.iconbox {
		position: relative;
		width: 1rem;
		height: 1rem;
		background-color: #fff;
		margin-right: 0.2rem;
	}

	.iconbox img {
		position: relative;
		width: 100%;
		height: 100%;
	}

	.addbox {
		position: relative;
		width: 80%;
		margin: 0 auto;
		margin-bottom: 20rpx;
		// margin-left:30%;
		padding: 20rpx 30rpx;
		color: $theme-color;
		display: flex;
		border-radius: 0.4rem;
		align-items: center;
		justify-content: center;
		border: 1px solid $theme-color;
	}

	.button {
		position: relative;
		font-size: 30rpx;
		color: $theme-color;
	}

	.cancelbutton {
		color: #7c7c7c;
	}

	.headbox {
		position: relative;
		width: 100%;
		display: flex;
		align-items: center;
		color: #fff;
		padding: 24rpx 40rpx;
		border-bottom: 1px solid #eee;
		justify-content: space-between;
	}

	.msgbox {
		position: fixed;
		width: 100%;
		/* left: 24rpx; */
		bottom: 100rpx;
		background-color: #fff;
		animation: openwin 0.4s;
	}
	@keyframes openwin
	{
	    0%   {bottom: -800rpx;}
	    100% {bottom: 100rpx;}
	}
	.addpassengerfloatbox {
		position: fixed;
		width: 100%;
		height: 100%;
		z-index: 20;
		background-color: rgba(0, 0, 0, 0.4);
	}

	.flexcenter {
		position: relative;
		display: flex;
		align-items: center;
	}

	.unit input {
		font-size: 0.7rem;
		display: inline-block;
		margin-left: 0.6rem;
	}

	.title {
		position: relative;
		font-weight: bold;
	}

	.addpassenger {
		position: relative;
		width: 4rem;
		padding: 0.3rem 0.1rem;
		font-size: 0.7rem;
		color: #fff;
		text-align: center;
		border-radius: 0.8rem;
		background-color: $theme-color;
	}

	.unit {
		position: relative;
		width: 100%;
		height: 100rpx;
		background-color: #fff;
		border-bottom: 1px solid #eee;
		display: flex;
		font-size: 0.8rem;
		padding: 24rpx;
		align-items: center;
		justify-content: space-between;
	}

	.grayS {
		position: relative;
		font-size: 0.6rem;
		color: gray;
		margin-left: 0.4rem;
	}

	.preice {
		position: relative;
		color: #fff;
		font-weight: bold;
		font-size: 0.8rem;
	}

	.floatbox {
		position: fixed;
		bottom: 0;
		width: 100%;
		height: 100rpx;
		z-index: 30;
		background-color: rgba(0, 0, 0, 0.7);
		padding: 24rpx;
		display: flex;
		align-items: center;
		justify-content: space-between;
	}

	.submitorder {
		position: relative;
		width: 4rem;
		padding: 0.3rem 0.1rem;
		font-size: 0.7rem;
		color: #fff;
		text-align: center;
		border-radius: 0.2rem;
		background-color: $theme-color;
	}

	.ordermsg {
		position: relative;
		width: 100%;
	}

	.delete-img {

		width: 50rpx;
		height: 50rpx;
	}

	.delete-box {
		position: absolute;
		width: 50rpx;
		height: 50rpx;
		right: 30rpx;
		display: flex;
		align-items: center;
		justify-content: center;
		background-color: #fff;
		overflow: hidden;
		border-radius: 25rpx;
	}
</style>
