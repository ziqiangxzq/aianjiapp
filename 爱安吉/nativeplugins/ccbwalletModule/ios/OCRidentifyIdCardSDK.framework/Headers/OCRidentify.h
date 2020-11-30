//
//  OCRidentify.h
//  CCBOpenBankDemo
//
//  Created by zuowending on 2019/10/18.
//  Copyright © 2019 陈裕贵. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, OcrCardSide) {
    CARD_SIDE_FONT_t = 1, //身份证正面
    CARD_SURFACE_BACK_t, //身份证反面
    CARD_BANK_positive//银行卡正面
};
typedef void(^CCBDataBlock)(id data);


@interface OCRidentify : NSObject
/**
 * @brief 填入CCBSDK invokeOtherSDKWithHandle方法回调传过来的ccbblock
 */
@property(nonatomic,copy) CCBDataBlock ccbdatablock;

@property(nonatomic,strong) UIImage *images;

/**
 * @brief 调起OCR
 *
 * @param ViewController      填入CCBSDK invokeOtherSDKWithHandle方法回调传过来的VC
 * @param OcridCardSurface    判断OCR正反面
 * @param success             成功回调信息
 * @param failure             失败回调信息
 */
- (void)TunedupOCRFrontofcardActivity:(UIViewController *)ViewController OcridCardSurface:(OcrCardSide)OcridCardSurface success:(void (^)(id responseObject))success failure:(void (^)(id error))failure;

/**
 *  获取版本号
 */
+(NSString *)getVersion;

@end

NS_ASSUME_NONNULL_END
