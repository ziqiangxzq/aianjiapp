<template>
	<view>
		<view>
			<image :src="desc_data[0].pic_uri" class="desc_img" mode="widthFix">
			<view class="title_txt" v-html="desc_data[0].news_title"></view>
			<view class="desc_txt" v-html="desc_data[0].news_content"></view>
		</view>
		
		<view>
			<radio-group @change="radioChange" style="width: 100%;">
				<label class="category_wrapper" v-for="(item, index) in category_data" :key="item.news_category_id">
					<view>
						<radio :value="item.news_category_id" :checked="index === current" class="radio_icon" />
					</view>
					<view class="radio_wrap" :class="{'radio_checked': item.isActive, 'radio_un_checked': item.noActive}" >{{item.category_name}}</view>
				</label>
			</radio-group>
		</view>
		
		<news-list class="clear-both" :newsListData="news_data"></news-list>
		
		<uni-load-more :status="status" :content-text="contentText" />
	</view>
</template>

<script>
	import newsList from '../../components/news-list.vue'
	import uniLoadMore from '../../components/uni-load-more/uni-load-more.vue'
	
	export default {
		components: {
		 	newsList
		},
		data() {
			return {
				news_id: '',
				
				desc_data: [{
					"news_title":"",
					"news_content":"",
					"pic_uri":""
				}],
				
				category_data: [],
				current: 0,
				
				news_data: [],
				
				last_id: false,
				reload: false,
				status: 'more',
				contentText: {
					contentdown: '上拉加载更多',
					contentrefresh: '加载中',
					contentnomore: '没有更多内容了'
				},
				
				page: 1,
				recs: 10,
				
				news_category_id: '',
			};
		},
		onLoad(options) {
			uni.setNavigationBarTitle({
			　　title: options.module_name
			})
			this.news_id = options.news_id;
			this.get_special_news_title();
			this.get_special_news_category();
		},
		onReachBottom() {
			this.status = 'more';
			this.get_special_news_list(this.news_category_id);  //新闻
		},
		methods: {
			get_special_news_title: function() { //获取专题简介
				var that = this;
				var url = '/news/get_special_news_title.php';
				var data = {
					special_news_id: this.news_id,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					var data = res.data;
					that.desc_data = data;
				});
			},
			get_special_news_category: function() {  //获取专题类别
				var that = this;
				var url = '/news/getNewsCategoryByNews';
				var data = {
					news_id: this.news_id
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					var data = res.data.data;
					for(var i=0; i<data.length; i++) {
						if(i!=0) {
							data[i]['isActive'] = false;
							data[i]['noActive'] = true;
						} else {
							data[i]['isActive'] = true;
							data[i]['noActive'] = false;
							that.news_category_id = data[i].news_category_id;
							that.get_special_news_list(data[i].news_category_id)
						}
						that.category_data.push(data[i]);
					}
				}, "globalUrlNew");
		    },
			radioChange: function(evt) {  //切换类别
				for (var i = 0; i < this.category_data.length; i++) {
					this.category_data[i].isActive = false;
					this.category_data[i].noActive = true;
					if (this.category_data[i].news_category_id === evt.target.value) {
						this.current = i;
						this.category_data[i].isActive = true;
						this.category_data[i].noActive = false;
						this.news_category_id = this.category_data[i].news_category_id;
						
						this.status = 'more';
						this.last_id = false;
						this.page = 1;
						this.news_data = [];
						
						this.get_special_news_list(this.news_category_id);
					}
				}
			},
			get_special_news_list: function(news_category_id) { //获取专题类别下的新闻
				var that = this;
				
				if (that.last_id) {
					//说明已有数据，目前处于上拉加载
					that.status = 'loading';
					that.page++;
				}
				
				var url = '/news/getNews';
				var data = {
					special_news_id: this.news_id,
					news_category_id: news_category_id,
					page: that.page,
					recs: that.recs,
				}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					var data = res.data.data;
					for(var i=0; i<data.length; i++) {
						that.news_data.push(data[i]);
					}
					
					that.last_id = true;
					that.reload = false;
					if(data.length < that.recs) {
						that.status = '';
					}
				}, "globalUrlNew");
			},
		}
	}
</script>

<style>
	.desc_img {
		width: 100%;
	}
	
	.title_txt {
		font-size: 36upx;
		padding: 19.2upx;
	}
	
	.desc_txt {
		font-size: 28.8upx;
		padding:0 19.2upx 0 19.2upx;
		color:#464646;
	}
	
	.radio_icon {
		transform: scale(0)
	}
	
	.radio_checked {
		font-size: 25.6upx;
		background-color: #0090ff;
		color: #FFFFFF;
		border: 1upx solid #0090ff;
	}
	
	.radio_un_checked {
		font-size: 25.6upx;
		background-color: #FFFFFF;
		color: #000;
		border: 1upx solid #000;
	}
	
	.radio_wrap {
		padding: 19.2upx 9.6upx;
	}
	
	.category_wrapper {
	   float: left;
	   padding: 0 1.5% 0 3%;
    }
</style>
