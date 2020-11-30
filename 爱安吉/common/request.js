function globalRequest(url, data, method, dataType, header, fn, which_url) {
	if (header == '') {
		header = {
			'content-type': 'application/x-www-form-urlencoded'
		}
	}
	
	var timestamp = this.getTimestamp();
	var signature = this.getSign(timestamp);
	
	data['timestamp'] = timestamp;
	data['sign'] = signature;
	
	data['user_id'] = uni.getStorageSync("user_id");
	data['user_token'] = uni.getStorageSync("user_token");
	
	data['platformName'] = uni.getStorageSync("platform"); //android、ios
	data['model'] = uni.getStorageSync("model"); //手机型号
	data['version'] = this.version; //app版本号
	
	
	data['deviceInfo'] = {
		"OS": uni.getStorageSync("platform"), //android、ios
		"Manufacturer": "",
		"IMEI": "",
		"MobileOperatorName": "",
		"Model": uni.getStorageSync("model"), //手机型号
	}
	
	var global = '';
	if(which_url == "globalUrlNew") {
		global = this.globalUrlNew;
	} else {
		global = this.globalUrl;
	}
	
	// uni.showLoading({
	//     title: '加载中'
	// });
	
	uni.request({
		url: global + url,
		method: method,
		dataType: dataType,
		header: header,
		data: data,
		success: fn,
		beforeSend: () => {

		},
		fail: () => {
			uni.showModal({
			    title: '提示',
			    content: '请求失败,请检查您的网络环境。',
				showCancel: false,
			    success: function (res) {
			        if (res.confirm) {
			            //console.log('用户点击确定');
			        } else if (res.cancel) {
			            //console.log('用户点击取消');
			        }
			    }
			});
		},
		complete: () => {
			//uni.hideLoading();
		}
	});
}

export default globalRequest
