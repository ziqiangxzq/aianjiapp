<template> 
    <view> 
        <view class="cpt-mask">
			<view class="btn_mask">
				<view class="cancel btn_snap" @click="cancel()">取消</view>
				<view style="flex: 1;"></view>
				<view class="sub btn_snap" @click="write_news_comment()">提交</view>
			</view>
			<view>
				<textarea placeholder="请输入..." class="area" v-model="comment" auto-focus="true"></textarea>
			</view>
        </view> 
    </view> 
</template> 
 
<script> 
    export default {
		props: ["mask", "news_id"],
		data() {
			return {
				comment: '',
			}
		},
		methods: {
			cancel: function() {
				this.$emit("changes");
			},
			write_news_comment: function() {
				var that = this;
				var url = that.globalUrl+'/news/write_news_comment.php';
				uni.request({
					url: url,
					dataType: 'text',
					method:"POST",
					header : {'content-type':'application/x-www-form-urlencoded'},
					data: {
						user_id: uni.getStorageSync("user_id"),
						news_id: that.news_id,
						comment: that.comment,
					},
					success: (res) => {
						var data = eval('(' + res.data + ')');
						if(data.resultid == 1) {
							uni.showModal({
								content: data.msg,
								showCancel: false,
								complete: function() {
									that.$emit("changes");
								}
							});
						} else {
							uni.showModal({
								content: data.msg,
								showCancel: false,
							});
						}
					},
					fail: (err) => {
					},
					complete: () => {
					}
				});
			}
		}
	} 
</script> 
 
<style> 
    .cpt-mask { 
        position: fixed;
        top: 15%;
        left: 0;
        width: 100%;
        background-color: #FFFFFF;
        z-index: 21474836489;
		padding: 50upx 0;
    }
	
	.area {
		background: #F8F8F8;
		opacity: 1;
		width: 90%;
		margin-left: 5%;
		padding: 30upx;
	}
	
	.btn_mask {
		display: flex;
		flex-direction: row;
		margin-bottom: 50upx;
	}
	
	.btn_snap {
		padding: 10upx 40upx;
		border-radius: 5upx;
		font-size: 32upx;
	}
	
	.cancel {
		background: #EEEEEE;
		color: #A8A8A8;
		margin-left: 5%;
	}
	
	.sub {
		background: #3d86bd;
		color: #FFFFFF;
		margin-right: 5%;
	}
</style>