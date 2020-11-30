//
//  ExtensionConfig.h
//  CCBSDK
//
//  Created by 樊亮 on 2019/7/20.
//  Copyright © 2019年 Mr.Fn. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ExtensionConfig : NSObject

/**人脸SDK需商户传入的appSecretS*/
@property (nonatomic, copy) NSString    *faceSDK_appSecretS;

/**人脸SDK测试环境URL*/
@property (nonatomic, copy) NSString    *faceSDK_safeConsoleAddr;


/// 渠道号
@property(nonatomic, strong) NSString *faceRecognitionChnlID;


/// 渠道交易码
@property(nonatomic, strong) NSString *faceRecognitionChnlTxnCD;
 
@end

NS_ASSUME_NONNULL_END
