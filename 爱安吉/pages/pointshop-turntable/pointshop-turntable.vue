<template>
	<view>
		<!--logo-->
		<image src="../../static/points/bg-1.png" class="bg-1" mode="widthFix"></image>

		<!-- <image src="../../static/points/bg-2.png" class="bg-2" mode="widthFix"></image> -->
		<div class="ub-img7 ub ub-ver ub-ac ub-pc" style="background-image: url(../../static/points/bg-2.png);width: 100%;">
			<div class="ub-img7 ub ub-ac ub-pc" style="background-image: url(../../static/points/circle-4.png);width: 280px; height: 280px;">
				<canvas canvas-id="canvas" :animation="animationData" style="width: 250px; height: 250px;"></canvas>
				<image src="../../static/points/GO.png" class="GO" mode="widthFix" style="" @click="GoingClick();"></image>
			</div>
			<view style="margin-top: 10upx;">您还有<span style="color: #FC7800;">{{chance_num}}</span>次抽奖机会
			</view>
		</div>

		<!--积分规则start-->
		<view v-if="activity_data != ''">
			<image src="../../static/points/bg-3.png" class="bg-3" mode="widthFix"></image>
			<view class="content_wrap">
				<view v-html="activity_data[0].content">
				</view>
			</view>
		</view>
		<!--积分规则end-->

		<!--我的中奖记录start-->
		<image src="../../static/points/bg-4.png" class="bg-4" mode="widthFix"></image>
		<view class="user_record_txt">我的中奖</view>
		<view class="user_record" v-for="(arr, index) in user_record_data" :key="index">
			<view class="award_level_desc">{{arr.award_level_desc}}</view>
			<view class="change_btn" v-if="arr.if_used == 0" @click="go_convertibility(index);">去兑换</view>
			<view class="change_btn_over" v-if="arr.if_used == 1">已兑换</view>
			<view class="change_btn_over" v-if="arr.if_used == 2">已过期</view>
		</view>
		<!--我的中奖记录end-->

		<!--所有中奖记录start-->
		<view class="user_record_txt">中奖记录</view>
		<view class="record">
			<swiper vertical="true" autoplay="true" circular="true" interval="3000">
				<swiper-item>
					<view v-for="(arr, index) in award_record_data" :key="index">
						{{arr.create_date}}{{arr.phone}}获得{{arr.award_name}}
					</view>
				</swiper-item>
			</swiper>
		</view>
		<!--所有中奖记录end-->

		<!--底部分享弹窗start-->
		<uni-popup ref="share" :type="type" :custom="true" @change="change">
			<view class="uni-share">
				<view class="uni-share-title">分享到</view>
				<view class="uni-share-content">
					<view v-for="(item, index) in bottomData" :key="index" class="uni-share-content-box" @click="share_wx(item.name);">
						<view class="uni-share-content-image">
							<image :src="item.icon" class="image" />
						</view>
						<view class="uni-share-content-text">{{ item.text }}</view>
					</view>
				</view>
				<view class="uni-share-btn" @click="cancel('share')">取消分享</view>
			</view>
		</uni-popup>
		<!--底部分享弹窗end-->
	</view>
</template>

<script>
	import uniPopup from '@/components/uni-popup/uni-popup.vue';

	export default {
		components: {
			uniPopup
		},
		data() {
			return {
				activity_id: '',
				activity_data: [],
				award_data: [],
				list: [],

				bRotate: false,

				ctx: '',

				animationData: {},

				bottomData: [{
					text: '微信',
					icon: 'https://www.waxcapp.com/upload_pics/sharing_type/img20190918/share2.png',
					name: 'hy'
				}, {
					text: '朋友圈',
					icon: 'https://www.waxcapp.com/upload_pics/sharing_type/img20190918/share3.png',
					name: 'pyq'
				}],
				type: '',

				user_record_data: [],
				award_record_data: [],

				chance_num: '',
				user_share_num: '',
				user_points_num: '',
			}
		},
		onLoad() {
			this.get_activity();
		},
		onShow() {},
		methods: {
			get_activity: function() {
				var that = this;
				var url = that.globalUrl + '/points/get_activity.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						version: this.version,
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						that.activity_id = data[0].activity_id;
						that.activity_data = data;
						that.get_activity_award();
						that.get_activity_user_record();
						that.get_activity_award_record();
						that.get_activity_user_chance();
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			get_activity_user_chance() {
				var that = this;
				var url = that.globalUrl + '/points/get_activity_user_chance.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						version: this.version,
						activity_id: that.activity_id
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						console.log('chance_num = ' + data.chance_num)
						that.chance_num = data.chance_num;
						that.user_points_num = data.user_points_num;
						that.user_share_num = data.user_share_num;
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			get_activity_award: function() { //获取奖项
				var that = this;
				var url = that.globalUrl + '/points/get_activity_award.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						version: this.version,
						activity_id: that.activity_id
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');

						for (var i = 0; i < data.length; i++) {
							that.award_data.push(data[i]);
						}

						that.list = data;
						that.initZhuanPan();
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			initZhuanPan: function() {

				this.ctx = uni.createCanvasContext('canvas')
				var data = this.award_data;

				//屏幕系数
				var ratio = uni.getSystemInfoSync().pixelRatio;
				var r = 250;

				var c_r1 = parseFloat(r * 0.5);
				var c_r2 = parseFloat(r * 0.1);
				var font_size = ratio * 0.7 * 16;

				// 计算每块占的角度，弧度制
				var baseAngle = Math.PI * 2 / (data.length);

				//在给定矩形内清空一个矩形
				this.ctx.clearRect(0, 0, r, r);

				//strokeStyle 绘制颜色
				this.ctx.strokeStyle = "#FFBE04"; // 红色
				//font 画布上文本内容的当前字体属性
				this.ctx.font = '12px Microsoft YaHei';

				// 注意，开始画的位置是从0°角的位置开始画的。也就是水平向右的方向。
				// 画具体内容
				for (var index = 0; index < data.length; index++) {
					// 当前的角度
					var angle = 0 + index * baseAngle,
						rotate = angle + baseAngle / 2 + Math.PI / 2;

					// 填充颜色
					this.ctx.fillStyle = data[index].bg_clr;
					// 开始画内容
					// ---------基本的背景颜色----------
					this.ctx.beginPath();

					/*
					 * 画圆弧，和IOS的Quartz2D类似
					 * context.arc(x,y,r,sAngle,eAngle,counterclockwise);
					 * x :圆的中心点x
					 * y :圆的中心点x
					 * sAngle,eAngle :起始角度、结束角度
					 * counterclockwise : 绘制方向,可选，False = 顺时针，true = 逆时针
					 * */
					this.ctx.arc(c_r1, c_r1, c_r1, angle, angle + baseAngle, false);
					this.ctx.arc(c_r1, c_r1, c_r2, angle + baseAngle, angle, true);
					this.ctx.stroke();
					this.ctx.fill();
					//保存画布的状态，和图形上下文栈类似，后面可以Restore还原状态（坐标还原为当前的0，0），
					this.ctx.save();

					/*----绘制奖品内容----重点----*/
					// 红色字体
					this.ctx.fillStyle = data[index].font_clr;
					this.ctx.setFontSize = "20px 黑体";
					var rewardName = data[index].award_name;
					var line_height = 1;
					// translate方法重新映射画布上的 (0,0) 位置
					// context.translate(x,y);
					// 见PPT图片，
					var translateX = r * 0.5 + Math.cos(angle + baseAngle / 2) * r * 0.4;
					var translateY = r * 0.5 + Math.sin(angle + baseAngle / 2) * r * 0.4;
					this.ctx.translate(translateX, translateY);

					// rotate方法旋转当前的绘图，因为文字适合当前扇形中心线垂直的！
					// angle，当前扇形自身旋转的角度 +  baseAngle / 2 中心线多旋转的角度  + 垂直的角度90°
					this.ctx.rotate(rotate);

					/** 下面代码根据奖品类型、奖品名称长度渲染不同效果，如字体、颜色、图片效果。(具体根据实际情况改变) **/
					// canvas 的 measureText() 方法返回包含一个对象，该对象包含以像素计的指定字体宽度。
					// fillText() 方法在画布上绘制填色的文本。文本的默认颜色是黑色. fillStyle 属性以另一种颜色/渐变来渲染文本
					/*
					 * context.fillText(text,x,y,maxWidth);
					 * 注意！！！y是文字的最底部的值，并不是top的值！！！
					 * */
					//在画布上绘制填色的文本。文本的默认颜色是黑色
					this.ctx.fillText(rewardName, -25, 0, 100);
					//	this.ctx.fillText(rewardName, -this.ctx.measureText(rewardName).width, 0);
					this.ctx.restore();

					var imgx = r * 0.5 + Math.cos(angle + baseAngle / 2) * r * 0.3;
					var imgy = r * 0.5 + Math.sin(angle + baseAngle / 2) * r * 0.3;
					var img_size = 25;

					this.ctx.save();
					this.ctx.translate(imgx, imgy);
					this.ctx.rotate(rotate);
					this.ctx.translate(-(imgx), -(imgy));
					this.ctx.drawImage(data[index].award_pic, imgx - img_size / 2, imgy - img_size / 2, img_size, img_size);
					this.ctx.restore();

					//this.loadImages(ctx,rotate,data[index].award_pic,imgx,imgy);
					//还原画板的状态到上一个save()状态之前
					this.ctx.restore();
					/*----绘制奖品结束----*/
				}
				this.ctx.draw()
			},
			canvasIdErrorCallback: function(e) {
				console.error(e.detail.errMsg)
			},
			GoingClick: function() {
				uni.showToast({
					duration: 1000,
					title: '请稍等',
					icon: 'none'
				})
				// 正在转动，直接返回
				if (this.bRotate) return;
				this.bRotate = true;
				this.judge_part_points();
			},
			judge_part_points: function() {
				var that = this;
				if (this.user_share_num == 0 && this.user_points_num > 0) {
					uni.showModal({
						title: '提示',
						content: '您确定消耗100积分来抽奖吗?',
						success: function(res) {
							if (res.confirm) {
								console.log('用户点击确定');
								that.part_points_activity();
							} else if (res.cancel) {
								console.log('用户点击取消');
								that.bRotate = false;
								return;
							}
						}
					});
				} else {
					this.part_points_activity();
				}
			},
			part_points_activity: function() {
				var that = this;
				var url = that.globalUrl + '/points/part_points_activity.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						version: this.version,
						activity_id: that.activity_id
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						if (data.resultid == 1) {
							for (var i = 0; i < that.award_data.length; i++) {
								if (that.award_data[i].award_id == data.award_id) {
									that.rotateFunc(i, data.award_name);
									that.get_activity_user_record();
									that.get_activity_award_record();
									that.get_activity_user_chance();
									break;
								}
							}
						} else if (data.resultid == 2) {
							var _that = that;
							this.bRotate = false;
							uni.showModal({
								title: '提示',
								content: data.msg,
								success: function(res) {
									if (res.confirm) {
										console.log('用户点击确定');
										for (var i = 0; i < _that.award_data.length; i++) {
											if (_that.award_data[i].award_id == data.award_id) {
												_that.rotateFunc(i, data.award_name);
												_that.get_activity_user_record();
												_that.get_activity_award_record();
												_that.get_activity_user_chance();
												break;
											}
										}
									} else if (res.cancel) {
										console.log('用户点击取消');
									}
								}
							});
						} else {
							this.bRotate = false;
							uni.showModal({
								content: data.msg,
								showCancel: false
							});
						}
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			rotateFunc: function(item, award_name) {
				this.bRotate = false;
				var count = this.award_data.length;
				// 应该旋转的角度，旋转插件角度参数是角度制。
				var baseAngle = 360 / count;

				// 旋转角度 == 270°（当前第一个角度和指针位置的偏移量） - 奖品的位置 * 每块所占的角度 - 每块所占的角度的一半(指针指向区域的中间)
				var angles = 360 * 3 / 4 - (item * baseAngle) - baseAngle / 2; // 因为第一个奖品是从0°开始的，即水平向右方向
				// $("#canvas").stopRotate();
				// 注意，jqueryrotate 插件传递的角度不是弧度制。
				var time = this.randomNum(1000, 5000);

				// 哪个标签调用方法，旋转哪个控件
				var animation = uni.createAnimation({
					duration: time,
				})

				setTimeout(function() {
					animation.rotate(angles + 360 * 6).step()
					this.animationData = animation.export()

					setTimeout(function() {
						uni.showModal({
							content: award_name,
							showCancel: false
						});
					}, time)
				}.bind(this), 200)
			},
			randomNum: function(n, m) {
				/* Math.floor(Math.random()*10);时，可均衡获取0到9的随机整数。 */
				var random = Math.floor(Math.random() * (m - n)) + n;
				return random;
			},
			shareFriend: function() {
				var that = this;
				//分享到微信朋友
				uni.share({
					provider: "weixin",
					scene: "WXSceneSession", //分享到聊天界面
					type: 0, //type==0图文分享
					href: this.globalUrl2 + "/m.web/points/slyder_Adventures.php?activity_id=" + this.activity_id,
					title: this.removeHTMLTag(this.activity_data[0].title),
					summary: this.removeHTMLTag(this.activity_data[0].title),
					imageUrl: "../../static/share_wx.png", //推荐使用小于20Kb的图片
					success: function(res) {
						console.log("success:" + JSON.stringify(res));
						that.shareCall(0);

						that.cancel('share');
					},
					fail: function(err) {
						console.log("fail:" + JSON.stringify(err));
					}
				});
			},
			//分享到微信朋友圈
			shareFriendcricle: function() {
				var that = this;
				uni.share({
					provider: "weixin",
					scene: "WXSenceTimeline", //分享到朋友圈
					type: 0,
					href: this.globalUrl2 + "/m.web/points/slyder_Adventures.php?activity_id=" + this.activity_id,
					title: this.removeHTMLTag(this.activity_data[0].title),
					summary: this.removeHTMLTag(this.activity_data[0].title),
					imageUrl: "../../static/share_wx.png", //推荐使用小于20Kb的图片
					success: function(res) {
						console.log("success:" + JSON.stringify(res));
						that.shareCall(1);

						that.cancel('share');
					},
					fail: function(err) {
						console.log("fail:" + JSON.stringify(err));
					}
				});
			},
			share_wx: function(name) {
				if (name == 'hy') {
					this.shareFriend();
				} else if (name == 'pyq') {
					this.shareFriendcricle();
				}
			},
			togglePopup: function(type, open) {
				switch (type) {
					case 'top':
						this.content = '顶部弹出 popup'
						break;
					case 'bottom':
						this.content = '底部弹出 popup'
						break;
					case 'center':
						this.content = '居中弹出 popup'
						break;
				}
				this.type = type
				if (open === 'tip') {
					this.show = true
				} else {
					this.$refs[open].open()
				}
			},
			cancel(type) {
				if (type === 'tip') {
					this.show = false
					return
				}
				this.$refs[type].close()
			},
			change(e) {
				console.log(e.show)
			},
			shareCall: function(type) {
				var that = this;
				var url = that.globalUrl + '/main/add_share_record.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						module_id: '10',
						category: that.activity_id,
						relation_id: that.activity_id,
						type: type,
						user_id: uni.getStorageSync("user_id"),
					},
					success: (res) => {
						that.get_activity_user_chance();
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			onNavigationBarButtonTap(e) {
				if (e.float == 'right') {
					this.togglePopup('bottom', 'share');
				}
			},
			removeHTMLTag: function(str) {
				str = str.replace(/<\/?[^>]*>/g, '');
				//去除HTML tag
				str = str.replace(/[ | ]*\n/g, '\n');
				//去除行尾空白
				//str = str.replace(/\n[\s| | ]*\r/g,'\n'); //去除多余空行
				str = str.replace(/&nbsp;/ig, '');
				//去掉&nbsp;
				return str;
			},
			get_activity_user_record: function() {
				var that = this;
				var url = that.globalUrl + '/points/get_activity_user_record.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						page: 1,
						recs: 1000,
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						that.user_record_data = data;
					},
					fail: (err) => {},
					complete: () => {}
				});
			},
			go_convertibility: function(index) {
				var that = this;
				uni.showModal({
					title: '兑换码',
					content: that.user_record_data[index].used_code,
					showCancel: false,
					complete: function() {}
				});
			},
			get_activity_award_record: function() {
				var that = this;
				var url = that.globalUrl + '/points/get_activity_award_record.php';
				uni.request({
					url: url,
					dataType: 'text',
					method: "POST",
					header: {
						'content-type': 'application/x-www-form-urlencoded'
					},
					data: {
						user_id: uni.getStorageSync("user_id"),
						activity_id: that.activity_id,
						page: 1,
						recs: 1000,
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						that.award_record_data = data;
					},
					fail: (err) => {},
					complete: () => {}
				});
			}
		}
	}
</script>

<style scoped>
	.ub-img7
	{
		-webkit-background-size:100% 100%;
		background-size:100% 100%;
		background-repeat:no-repeat;
		background-position:center;
	}
	.ub
	{
		display: -webkit-box !important;
		display: box !important;
		position:relative;
	}
	.ub-ac
	{
		-webkit-box-align:center;
		box-align:center;
	}
	.ub-pc
	{
		-webkit-box-pack:center;
		box-pack:center;
	}
	.bg-1 {
		width: 100%;
		display: block;
	}

	.bg-2 {
		width: 100%;
		display: block;
	}

	.bg-3 {
		width: 100%;
		display: block;
	}

	.bg-4 {
		width: 100%;
		display: block;
	}

	.content_wrap {
		background-color: #f9f9ed;
		padding: 30upx 30upx;
		color: #545454;
	}

	/*转盘*/
	.GO {
		width: 80px;
		height: 80px;
		position: absolute;
		top: 95px;
		left: 100px;
	}

	/*转盘*/

	/*中奖记录start*/
	.user_record_txt {
		background-color: #ed304e;
		color: #FBBF09;
		font-size: 32upx;
		font-weight: bold;
		padding: 0 30upx 30upx 30upx;
	}

	.user_record {
		display: flex;
		flex-direction: row;
		background-color: #ed304e;
		color: #FFFFFF;
		font-size: 28upx;
		padding: 0 60upx 30upx 60upx;
	}

	.change_btn {
		background-color: #fbbf09;
		color: #FFFFFF;
		padding: 10upx 30upx;
		font-size: 26upx;
		border-radius: 30upx;
	}

	.change_btn_over {
		background-color: #d6d6d6;
		color: #848484;
		padding: 10upx 30upx;
		font-size: 26upx;
		border-radius: 30upx;
	}

	.award_level_desc {
		flex: 1;
	}

	.record {
		background-color: #ed304e;
		color: #FFFFFF;
		font-size: 28upx;
		padding: 0 0 30upx 0;
		margin: 0 auto;
		text-align: center;
		align-items: center;
	}

	/*中奖记录end*/
</style>
