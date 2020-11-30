# uni 插件使用说明

插件共提供两个接口

- initSDK
- intoCustomizedH5Activity

## 1.initSDk

入参示例

```JSON
{
    "appKey":"",
    "bPublicUrl ":"",
    "bPublicKey":"",
    "sPublicUrl ":"",
    "sPublicKey ":""
}
```

具体参数含义参考中国建设银行开放银行管理平台Android 基础SDK开发者使用手册5.1章节

---

## 2.intoCustomizedH5Activity

入参示例

```json
{
    "productId":"",
    "scnId":"",
    "wvEntrance":"",
    "thirdParametersMapJson":{
        "TrdPt_Cst_OrCd":"",
        "WalletTitle":"",
        "Crdt_No":"",
        "Cst_Nm":"",
        "Theme":""
    }
}
```



具体参数含义参考电子银行钱包Android SDK开发者使用手册 2.1章节

---

调用代码实例

```vue
<template>
	<view>
		<button v-on:click="init()">初始化</button>
		<button v-on:click="intoCustomizedH5Activity()">跳转界面</button>
	</view>
</template>

<script>
	var ccbwalletModule = uni.requireNativePlugin('ccbwalletModule');

	var productId = 'ShrWlt';
	var scnId = 'Main_Standard';
	var wvEntrance = 'com.open.ccb.ccbdemo.CCBH5CustomActivity';
	var hexColorStr = '';
	var thirdParametersMap = {
		TrdPt_Cst_OrCd: '1000003',
		WalletTitle: 'cs',
		Crdt_No: '210105199602134936',
		Cst_Nm: '刘宇轩',
		Theme: '0001'
	};
	export default {
		data() {
			return {};
		},
		methods: {
			init: function(e) {
				let platform = uni.getSystemInfoSync().platform
				if (platform == 'ios') {
					var appKey = 'c22868f0_142c_47c6_aa9d_e187894d2c42';
					var bPublicUrl = 'http://121.40.107.145:465/getMerchantSign';
					var bPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApHAYzvsxIC2G5rA2lP2y7IogtRd2WpMZxFWPhq9IfRWgPpDtvOyKgLiD72L/BmdMFN9uAcoEdLaLy0U2ffzrRScpE1m0JFgNerlsDGoeEdG5J5YQkeSXyuwOvhBbknk2tOTuLQYAY9EVXf17WHwd/cZTjx277Iyk1TzuVUdj3HiQcuIFECnZYylhdM+mra0ERJNxo1eUoSA5qzup6X5jo/JHlrov72cAp8czlXBSzFl5Cc1Re1eRSPJbvZUow8CsTe+8Hd9xx1Gyl6lLj49aDSI2BWWnK3/ZNN7zAi3n+dHAdanEWaQQw4x5OsKrAR/4zhl0VOLwQdjEPZkMMHqFKwIDAQAB';
					var sPublicUrl = 'https://sandbox.open.ccb.com/api/ios/';
					var sPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjVdGe8P2JumYU4sB1Zywioxw1+HaZB/KmzrzlClj2m2e4ZPqS5cYe2FCiCwBmyizZrVYGfECugszj7e+OjbrFeqOpCgOYnXrbX0me0YdqLAowELbI4cqRxGciFlbgkjJXLoTHX/ZPPKAaF8VCNfQJrfpAqYZBeGPHWiODu4m3P8lGG5U+kHsjemdFf+5iwBabtm8IKvvE3fIfboXjnsdLSW3xxWjFK2A7iubUA8U0jA9UCCJp61qDnjmMC4hfW5QEWQMchW2D6vRYyZZStKGYxKto60jj5qnqm0+xyX9X5pBz9hTWTIqCHpzbyeLTOeG3l2jQ4ut9ZgVXP9IRj1IzwIDAQAB';
				} else if (platform == 'android') {
					var appKey = '20761e0b_2abb_442b_b66e_e99f3eb20a4f';
					var bPublicUrl = 'http://121.40.107.145:465/getMerchantSign';
					var bPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjBLDRPolWFvKxbVlFIJm/WBKo6IIFhZeES1H/D+0Oudq8Vg1zsKk6CiWxGMIc9DWV8jkabobsWeVQFOW5IPe9dXUANlA2W9p22QpzexTEoUYKXcGhq3McK9Sw5JEObFYFlK5H+GX1H0xfm0649KXrPtt647rpTNBr1Ke8PxQPbGGNExT57oJioc9ShK0Izk6J4iQGZFW5R+z1hST6//qRRKva94Wd0iB0mlr2hvcqEDEwOAnu+/lhzEu4ylHI+3ru0oTK4XoTace6SRQviTaXDUvQh9rZeJLFATM5v+32ipJdiWnD/TydY7nFrdaK3eZp2G5tvKZ1BiHFSKaKOO9XQIDAQAB';
					var sPublicUrl = 'https://sandbox.open.ccb.com/api/andriod/';
					var sPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjVdGe8P2JumYU4sB1Zywioxw1+HaZB/KmzrzlClj2m2e4ZPqS5cYe2FCiCwBmyizZrVYGfECugszj7e+OjbrFeqOpCgOYnXrbX0me0YdqLAowELbI4cqRxGciFlbgkjJXLoTHX/ZPPKAaF8VCNfQJrfpAqYZBeGPHWiODu4m3P8lGG5U+kHsjemdFf+5iwBabtm8IKvvE3fIfboXjnsdLSW3xxWjFK2A7iubUA8U0jA9UCCJp61qDnjmMC4hfW5QEWQMchW2D6vRYyZZStKGYxKto60jj5qnqm0+xyX9X5pBz9hTWTIqCHpzbyeLTOeG3l2jQ4ut9ZgVXP9IRj1IzwIDAQAB';
				}
				console.log('init');
				ccbwalletModule.initSDK({
						appKey: appKey,
						bPublicUrl: bPublicUrl,
						bPublicKey: bPublicKey,
						sPublicUrl: sPublicUrl,
						sPublicKey: sPublicKey
					},
					ret => {
						console.log(ret);
					}
				);
			},
			intoCustomizedH5Activity: function(e) {
				console.log('intoCustomizedH5Activity');
				ccbwalletModule.intoCustomizedH5Activity({
						productId: productId,
						scnId: scnId,
						thirdParametersMap: thirdParametersMap,
						wvEntrance: wvEntrance,
						hexColorStr: hexColorStr
					},
					ret => {
						console.log(ret);
					}
				);
			}
		}
	};
</script>

<style></style>


```

----

### android 测试数据

```javascript
var appKey = 'c22868f0_142c_47c6_aa9d_e187894d2c42';
					var bPublicUrl = 'http://121.40.107.145:465/getMerchantSign';
					var bPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApHAYzvsxIC2G5rA2lP2y7IogtRd2WpMZxFWPhq9IfRWgPpDtvOyKgLiD72L/BmdMFN9uAcoEdLaLy0U2ffzrRScpE1m0JFgNerlsDGoeEdG5J5YQkeSXyuwOvhBbknk2tOTuLQYAY9EVXf17WHwd/cZTjx277Iyk1TzuVUdj3HiQcuIFECnZYylhdM+mra0ERJNxo1eUoSA5qzup6X5jo/JHlrov72cAp8czlXBSzFl5Cc1Re1eRSPJbvZUow8CsTe+8Hd9xx1Gyl6lLj49aDSI2BWWnK3/ZNN7zAi3n+dHAdanEWaQQw4x5OsKrAR/4zhl0VOLwQdjEPZkMMHqFKwIDAQAB';
					var sPublicUrl = 'https://sandbox.open.ccb.com/api/ios/';
					var sPublicKey =
						'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjVdGe8P2JumYU4sB1Zywioxw1+HaZB/KmzrzlClj2m2e4ZPqS5cYe2FCiCwBmyizZrVYGfECugszj7e+OjbrFeqOpCgOYnXrbX0me0YdqLAowELbI4cqRxGciFlbgkjJXLoTHX/ZPPKAaF8VCNfQJrfpAqYZBeGPHWiODu4m3P8lGG5U+kHsjemdFf+5iwBabtm8IKvvE3fIfboXjnsdLSW3xxWjFK2A7iubUA8U0jA9UCCJp61qDnjmMC4hfW5QEWQMchW2D6vRYyZZStKGYxKto60jj5qnqm0+xyX9X5pBz9hTWTIqCHpzbyeLTOeG3l2jQ4ut9ZgVXP9IRj1IzwIDAQAB';
```



----

### ios测试数据

```javascript
				var appKey = '20761e0b_2abb_442b_b66e_e99f3eb20a4f';
				var bPublicUrl = 'http://121.40.107.145:465/getMerchantSign';
				var bPublicKey =
					'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjBLDRPolWFvKxbVlFIJm/WBKo6IIFhZeES1H/D+0Oudq8Vg1zsKk6CiWxGMIc9DWV8jkabobsWeVQFOW5IPe9dXUANlA2W9p22QpzexTEoUYKXcGhq3McK9Sw5JEObFYFlK5H+GX1H0xfm0649KXrPtt647rpTNBr1Ke8PxQPbGGNExT57oJioc9ShK0Izk6J4iQGZFW5R+z1hST6//qRRKva94Wd0iB0mlr2hvcqEDEwOAnu+/lhzEu4ylHI+3ru0oTK4XoTace6SRQviTaXDUvQh9rZeJLFATM5v+32ipJdiWnD/TydY7nFrdaK3eZp2G5tvKZ1BiHFSKaKOO9XQIDAQAB';
				var sPublicUrl = 'https://sandbox.open.ccb.com/api/andriod/';
				var sPublicKey =
					'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAjVdGe8P2JumYU4sB1Zywioxw1+HaZB/KmzrzlClj2m2e4ZPqS5cYe2FCiCwBmyizZrVYGfECugszj7e+OjbrFeqOpCgOYnXrbX0me0YdqLAowELbI4cqRxGciFlbgkjJXLoTHX/ZPPKAaF8VCNfQJrfpAqYZBeGPHWiODu4m3P8lGG5U+kHsjemdFf+5iwBabtm8IKvvE3fIfboXjnsdLSW3xxWjFK2A7iubUA8U0jA9UCCJp61qDnjmMC4hfW5QEWQMchW2D6vRYyZZStKGYxKto60jj5qnqm0+xyX9X5pBz9hTWTIqCHpzbyeLTOeG3l2jQ4ut9ZgVXP9IRj1IzwIDAQAB';
```