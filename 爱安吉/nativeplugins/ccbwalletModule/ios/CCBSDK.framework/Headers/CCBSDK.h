//
//  CCBSDK.h
//  CCBSDK
//
//  Created by Mr.Fn on 2018/9/29.
//  Copyright © 2018年 DCITS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ExtensionConfig.h"
#import "CCBBaseWebViewController.h"
#import "CCBNetworkErrorBaseView.h"

//! Project version number for CCBSDK.
FOUNDATION_EXPORT double CCBSDKVersionNumber;

//! Project version string for CCBSDK.
FOUNDATION_EXPORT const unsigned char CCBSDKVersionString[];

@interface CCBSDK : NSObject

@property (nonatomic, strong) NSOperationQueue *operationQueue;


/**
 *  @brief 创建SDK单例服务
 *
 *  @return 返回单例对象
 */
+ (CCBSDK *_Nonnull)shareInstance;


/**
 * @brief 注册SDK,使用SDK的第一步
 *
 * @param appkey          CCBSDK应用标识，可在https://open.ccb.com中登录并创建App后获得
 * @param bPublicUrl     用于发往APP服务端进行加密的URL
 * @param sPublicUrl     服务端入口URL
 * @param bPublicKey     商户端加密公钥，创建APPID后获得可在https://open.ccb.com中登录下载
 * @param sPublicKey     sPublicKey CCB服务器公钥
 */
+ (void)registerCCBSDKWithAppkey:(NSString *_Nonnull)appkey
                      bPublicUrl:(NSString *_Nonnull)bPublicUrl
                      sPublicUrl:(NSString *_Nonnull)sPublicUrl
                      bPublicKey:(NSString *_Nonnull)bPublicKey
                      sPublicKey:(NSString *_Nonnull)sPublicKey;


/**
 * @brief 验证开发者，获取SDK授权
 *
 * @param parameter      预留字段,为业务拓展使用。暂传nil
 * @param success        验证开发者成功回调信息
 * @param failure        验证开发者失败回调信息
 */
+ (void)approveDeveloperWithParameter:(id _Nullable )parameter
                              success:(void (^_Nullable)(id _Nullable responseObject))success
                              failure:(void (^_Nullable)(id _Nullable responseObject))failure;


+ (void)approveDeveloperWithParameter1:(id _Nullable )parameter
success:(void (^_Nullable)(id _Nullable responseObject))success
failure:(void (^_Nullable)(id _Nullable responseObject))failure;


/**SDK业务场景入口函数(自行配置WebView属性)
 * @param content        SDK运行当前上下文，即当前ViewController
 * @param productId      产品id （可在https://open.ccb.com产品文档中获得）
 * @param ScnId          业务场景标识
 * @param parameter      三方填写传给H5的数据
 * @param webVC          继承于《CCBBaseWebViewController》类的实例对象
 * @param success        成功回调信息
 * @param failure        失败回调信息
 */
+ (void)intoCustomizedH5Activity:(UIViewController *_Nonnull)content
                       productId:(NSString *_Nonnull)productId
                           ScnId:(NSString *_Nonnull)ScnId
                       parameter:(id _Nullable )parameter
                           webVC:(CCBBaseWebViewController *_Nonnull)webVC
                         success:(void (^_Nullable)(id _Nullable responseObject))success
                         failure:(void (^_Nullable)(id _Nullable error))failure;


/**SDK业务场景入口函数(自定义关闭按钮背景颜色)
 * @param content        SDK运行当前上下文，即当前ViewController
 * @param productId      产品id （可在https://open.ccb.com产品文档中获得）
 * @param ScnId          业务场景标识
 * @param parameter      三方填写传给H5的数据
 * @param hexColorStr    十六进制颜色字符串
 * @param success        成功回调信息
 * @param failure        失败回调信息
 */
+ (void)intoH5ActivityWithContent:(UIViewController *_Nonnull)content
                        productId:(NSString *_Nonnull)productId
                            ScnId:(NSString *_Nonnull)ScnId
                      hexColorStr:(NSString *_Nullable)hexColorStr
                        parameter:(id _Nullable)parameter
                          success:(void (^_Nullable)(id _Nullable responseObject))success
                          failure:(void (^_Nullable)(id _Nullable error))failure;


/**
 获得SDK版本号
 
 @return sdk版本号
 */
+ (NSString *_Nonnull)getSDKVersion;

/**调用其他SDK需要实现的方法
 * 注:此方法若使用,必须在"SDK业务场景入口函数"之前
 * @param block   在回调内实现调用其他SDK
 */
+ (void)invokeOtherSDKWithHandle:(tunnelBlock _Nullable)block;


/**为特定的产品设置调用的第三方SDK需要实现的方法
 * 注:此方法若使用,必须在"SDK业务场景入口函数"之前
 * @param block   在回调内实现调用其他SDK
 * @param productId      产品id （可在https://open.ccb.com产品文档中获得）
 * @param ScnId          业务场景标识
 * @param customVCBlock  在回调内实现创建自定义VC(继承于《CCBBaseWebViewController》)并return
 */
+ (void)invokeOtherSDKWithHandle:(tunnelBlock _Nullable)block
                         ForPdID:(NSString *_Nonnull)productId
                           ScnID:(NSString *_Nonnull)ScnId
                        customVC:(CCBCustomVCBlock _Nullable)customVCBlock;



/**设置发往商户端加签请求的自定义http header值
 * 注:此方法若使用,必须在"验证开发者函数"之前
 * @param dichttpHead   http head具体的键值对
 */
+ (void)setSignRequestHTTPHeader:(NSDictionary *_Nullable)dichttpHead;


/**设置第三方SDK初始化所需参数
  * @param extensionConfig   已经赋值过的值的ExtensionConfig实例对象
 */
+ (void)configureExtendFuncParam:(nonnull ExtensionConfig *)extensionConfig;


/**设置定制化参数
 * @param obj      不为nil的Object对象
 * @param objKey   想要赋值的Key
*/
+ (void)setSpecialRequirements:(id _Nullable )obj ForKey:(NSString *_Nullable)objKey;


@end
