import Vue from 'vue'
import App from './App'
import uView from 'uview-ui';
import globalRequest from './common/request.js'
import MD5 from './common/MD5.js'
// http拦截器，此为需要加入的内容，如果不是写在common目录，请自行修改引入路径
//import httpInterceptor from '@/common/http.interceptor.js'

Vue.config.productionTip = false
Vue.prototype.globalUrl = "https://www.meilianji.cn/web2"
Vue.prototype.globalUrl2 = "https://www.meilianji.cn"
Vue.prototype.globalRequest = globalRequest
Vue.prototype.apiKey = '32dd3c0eb6340a932a990e5832a0d2cf'
Vue.prototype.version = 5 //plus.runtime.version;  //app版本号

Vue.prototype.globalUrlNew = "https://www.meilianji.cn/api/v1"

App.mpType = 'app'
Vue.use(uView);

//这里需要写在最后，是为了等Vue创建对象完成，引入"app"对象(也即页面的"this"实例)
//Vue.use(httpInterceptor, app)

Vue.prototype.openWebview = function(url) {
	uni.navigateTo({
		url: '/pages/webview/webview?url=' + url
	})
}

//获取当前时间戳
Vue.prototype.getTimestamp = function() {
	var timestamp = Date.parse(new Date()) / 1000;
	return timestamp;
}

//获取签名
Vue.prototype.getSign = function(timestamp) {
	var s = timestamp + this.apiKey;
	var signature = MD5(s);
	return signature;
}

//获取上传图片地址
Vue.prototype.getUploadImgUrl = function(timestamp) {
	var timestamp = this.getTimestamp();
	var signature = this.getSign(timestamp);
	var action = this.globalUrl + '/upload/uploadImg.php?imgName=' + timestamp + '_' + uni.getStorageSync("user_id") +
		'&imgPath=user' +
		'&timestamp=' + timestamp +
		'&sign=' + signature
	return action;
}

//统计点击模块
Vue.prototype.submitClickInfo = function(module_num) {
	var that = this;
	var url = '/click/click_info_submit_new.php';
	var data = {
		module_num: module_num,
	}
	var header = {
		'content-type': 'application/json'
	}

	that.globalRequest(url, data, 'POST', 'JSON', header, function(res) {

	});
}

//处理main表数据点击事件(首页中部，应用，个人中心上下部)
Vue.prototype.handleMainModuel = function(arr) {
	var module_URI2 = arr.module_URI2;
	if (arr.notice_type == 1) { //电话
		this.callPhone(arr.notice);
	} else {
		if (module_URI2 != '') {
			uni.navigateTo({
				url: module_URI2
			})
		}
	}
	this.submitClickInfo(arr.module_num);
}

//拨打电话
Vue.prototype.callPhone = function(tel) { //打电话
	if (tel != '') {
		uni.makePhoneCall({
			// 手机号
			phoneNumber: tel,
			// 成功回调
			success: (res) => {
				console.log('调用成功!')
			},
			// 失败回调
			fail: (res) => {
				alert('调用失败!')
			}
		});
	}
}

//预览图片
Vue.prototype.previewImage = function(urls, current) {
	uni.previewImage({
		urls: urls,
		current: current
	});
}

//打开新闻详情
Vue.prototype.open_news_detail = function(arr) {
	var jump_url = ''
	if(arr.jump_url == null || arr.jump_url == '') {
		jump_url = arr.module_url
	} else {
		jump_url = arr.jump_url
	}
	uni.navigateTo({
		url: jump_url
	})
}

//获取经纬度start
Vue.prototype.getLocation = function() {
	var that = this;
	uni.getLocation({
		type: 'gcj02',
		success: function(res) {
			console.log("longitude ", res.longitude)
			uni.setStorageSync("gcj02_longitude", res.longitude);
			uni.setStorageSync("gcj02_latitude", res.latitude);

			that.gcj02tobd09(res.longitude, res.latitude)
			console.log('当前位置的经度：' + res.longitude);
			console.log('当前位置的纬度：' + res.latitude);
		}
	});
}
var x_PI = 3.14159265358979324 * 3000.0 / 180.0;
/**
 *火星坐标系（GCJ-02）与百度坐标系（BD-09）的转换
 *即谷歌、高德 转 百度
 *
 */
Vue.prototype.gcj02tobd09 = function gcj02tobd09(lng, lat) {
	var lat = +lat;
	var lng = +lng;
	var z = Math.sqrt(lng * lng + lat * lat) + 0.00002 * Math.sin(lat * x_PI);
	var theta = Math.atan2(lat, lng) + 0.000003 * Math.cos(lng * x_PI);
	var bd_lng = z * Math.cos(theta) + 0.0065;
	var bd_lat = z * Math.sin(theta) + 0.006;
	console.log("bd_lat ", bd_lat)
	console.log("bd_lng ", bd_lng)
	uni.setStorageSync("longitude", bd_lng);
	uni.setStorageSync("latitude", bd_lat);
	return [bd_lng, bd_lat];
};

/*
 *百度坐标系（BD09）与火星坐标系（GCJ-02）的转换
 *即 百度 转 高德 、谷歌
 */
Vue.prototype.bd09togcj02 = function bd09togcj02(bd_lon, bd_lat) {
	var bd_lon = +bd_lon;
	var bd_lat = +bd_lat;
	var x = bd_lon - 0.0065;
	var y = bd_lat - 0.006;
	var z = Math.sqrt(x * x + y * y) - 0.00002 * Math.sin(y * x_PI);
	var gg_lng = z * Math.cos(theta);
	var gg_lat = z * Math.sin(theta);
	return [gg_lng, gg_lat];
};
//获取经纬度end


const app = new Vue({
	...App
})
app.$mount()
