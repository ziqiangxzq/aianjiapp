<template>
	<view class="sheltermap" v-else>
		<map style="width: 100%; height: 1600upx;" :latitude="latitude" :longitude="longitude" :markers="covers" @markertap="openMap">
		</map>

	</view>
</template>

<script>
	export default {
		data() {
			return {
				shelterList: [],
				id: 0,
				title: 'map',
				latitude: 30.638,
				longitude: 119.680,
				covers: []
			}
		},
		onLoad() {
			this.get_shelter();
			this.get_location();
			this.openMap();
		},
		methods: {
			get_shelter: function() {
				let that = this;
				var url = '/broadcast/get_shelter.php';
				var data = {}
				that.globalRequest(url, data, 'POST', 'JSON', '', function(res) {
					console.log(res.data.data); 
					that.covers = res.data.data || [];
				})
			},
			get_location: function() {
				uni.getLocation({
					type: 'wgs84',
					geocode: true,
					success: function(res) {
						console.log('当前位置的经度：' + res.longitude);
						console.log('当前位置的纬度：' + res.latitude);
					}
				})
			},

			openMap: function(res) { //打开地图
				var url = "";
				//  // #ifdef H5
				// var appid = plus.runtime.appid;
				// console.log('应用的 appid 为：' + appid);
				// // #endif
				if (plus.os.name == "Android") {
					var hasBaiduMap = plus.runtime.isApplicationExist({
						pname: 'com.baidu.BaiduMap',
						action: 'baidumap://'
					});
					var hasAmap = plus.runtime.isApplicationExist({
						pname: 'com.autonavi.minimap',
						action: 'androidamap://'
					});
					var urlBaiduMap = "baidumap://map/direction?origin=" + uni.getStorageSync("res.latitude") + "," + uni.getStorageSync(
							"res.longitude") +
						"&destination=latlng:" + res.latitude + "," + res.longitude + "|name:" + encodeURI(res.shop_name) +
						"&mode=driving";
					var urlAmap =
						"androidamap://route?sourceApplication=www.NanJingJiangNing.com&slat=" + uni.getStorageSync("gcj02_latitude") +
						"&slon=" + uni.getStorageSync("gcj02_longitude") +
						"&sname=" + encodeURI("当前位置") + "&dlat=" + res.latitude + "&dlon=" + res.longitude +
						"&dname=" + encodeURI(res.shop_name) + "&dev=0&m=0&t=2"
					if (hasAmap && hasBaiduMap) {
						plus.nativeUI.actionSheet({
							title: "选择地图应用",
							cancel: "取消",
							buttons: [{
								title: "百度地图"
							}, {
								title: "高德地图"
							}]
						}, function(e) {
							switch (e.index) {
								case 1:
									plus.runtime.openURL(urlBaiduMap); //百度地图
									break;
								case 2:
									plus.runtime.openURL(urlAmap); //高德地图
									break;
							}
						})
					} else if (hasAmap) {
						plus.runtime.openURL(urlAmap);
					} else if (hasBaiduMap) {
						plus.runtime.openURL(urlBaiduMap);
					}
					// else {
					//  url = "geo:39.96310,116.340698?q=%e6%95%b0%e5%ad%97%e5%a4%a9%e5%a0%82";
					//  plus.runtime.openURL(url); //如果是国外应用，应该优先使用这个，会启动google地图。这个接口不能统一坐标系，进入百度地图时会有偏差  
					// }
				} else {
					// iOS上获取本机是否安装了百度高德地图，需要在manifest里配置，在manifest.json文件app-plus->distribute->apple->urlschemewhitelist节点下添加（如urlschemewhitelist:["iosamap","baidumap"]）  
					plus.nativeUI.actionSheet({
						title: "选择地图应用",
						cancel: "取消",
						buttons: [{
							title: "Apple地图"
						}, {
							title: "百度地图"
						}, {
							title: "高德地图"
						}]
					}, function(e) {
						console.log("e.index: " + e.index);
						switch (e.index) {
							case 1:
								url =
									"https://maps.apple.com/?saddr=" + uni.getStorageSync("gcj02_latitude") + "," + uni.getStorageSync(
										"gcj02_longitude") + "&daddr=" + res.latitude + "," + res.longitude;
								break;
							case 2:
								// url = "baidumap://map/direction?origin=latlng:"+uni.getStorageSync("latitude")+","+uni.getStorageSync("longitude")+"|name:当前位置"
								//+"&destination=latlng:"+res.latitude+","+res.longitude+"|name:"+res.shop_name+"&mode=driving";
								url = "baidumap://map/direction?origin=" + uni.getStorageSync("latitude") + "," + uni.getStorageSync(
										"longitude") +
									"&destination=" + res.latitude + "," + res.longitude + "&mode=driving";
								console.log("baidumap " + url);
								break;
							case 3:
								url =
									"iosamap://path?sourceApplication=www.NanJingJiangNing.com&sid=BGVIS1&slat=" + uni.getStorageSync(
										"gcj02_latitude") + "&slon=" + uni.getStorageSync("gcj02_longitude") + "&sname=" + encodeURI("当前位置") +
									"&did=BGVIS2&dlat=" + res.latitude + "&dlon=" + res.longitude + "&dname=" + encodeURI(res.shop_name) +
									"&dev=0&m=0&t=0";
								break;
							default:
								break;
						}
						if (url != "") {
							plus.runtime.openURL(url, function(e) {
								plus.nativeUI.alert("本机未安装指定的地图应用");
							});
						}
					})
				}
			}
		},
	}
</script>

<style>
</style>
