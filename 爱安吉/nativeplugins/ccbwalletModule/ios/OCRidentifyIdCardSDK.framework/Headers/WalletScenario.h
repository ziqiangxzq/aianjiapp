
//
//  walletscenario.h
//  OCRidentifyIdCardSDK
//
//  Created by zuowending on 2020/3/3.
//  Copyright © 2020 zuowending. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CCBSDK/CCBSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface WalletScenario : NSObject

/**SDK业务场景入口函数(自定义关闭按钮背景颜色)
* @param content        SDK运行当前上下文，即当前ViewController
* @param productId      产品id （可在https://open.ccb.com产品文档中获得）
* @param ScnId          业务场景标识
* @param parameter      三方填写传给H5的数据
* @param hexColorStr    十六进制颜色字符串
* @param success        成功回调信息
* @param failure        失败回调信息
*/

+ (void)OpenH5ActivityWithContent:(UIViewController *)content          productId:(NSString*)productId
                            ScnId:(NSString*)ScnId hexColorStr:(NSString*)hexColorStr parameter:(NSDictionary*)parameter success:(void (^)(id responseObject))success
                          failure:(void (^)(id responseObject))failure;

/**SDK业务场景入口函数(自行配置WebView属性)
 * @param content        SDK运行当前上下文，即当前ViewController
 * @param productId      产品id （可在https://open.ccb.com产品文档中获得）
 * @param ScnId          业务场景标识
 * @param parameter      三方填写传给H5的数据
 * @param webVC          继承于《CCBBaseWebViewController》类的实例对象
 * @param success        成功回调信息
 * @param failure        失败回调信息
 */
+(void)intoCustomizedOpenH5ActivityWithContent:(UIViewController *)content
                       productId:(NSString *)productId
                           ScnId:(NSString *)ScnId
                       parameter:(id)parameter
                           webVC:(CCBBaseWebViewController *)webVC
                         success:(void (^)(id responseObject))success
                         failure:(void (^)(id error))failure;
@end

NS_ASSUME_NONNULL_END
