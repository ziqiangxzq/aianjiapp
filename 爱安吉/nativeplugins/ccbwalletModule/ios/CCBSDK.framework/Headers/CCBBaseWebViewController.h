//
//  CCBBaseWebViewController.h
//  CCBSDK
//
//  Created by 樊亮 on 2019/11/14.
//  Copyright © 2019 Mr.Fn. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CCBNewProductInfo.h"

NS_ASSUME_NONNULL_BEGIN


@interface CCBBaseWebViewController : UIViewController

@property (nonatomic, copy)   tunnelBlock  _block;

@property (nonatomic, copy) void (^_closePage)(id param);

@property (nonatomic, strong) NSString    *_sign;

- (void)_setPdID:(NSString *)pdID ScnID:(NSString *)scnID;




/**
 * @brief set webview custom frame
 * @param frame    webView load html url string
 */
- (void)setWebViewFrame:(CGRect )frame;

/**
 * @brief set webView.scrollView.backgroundColor
 * @param bgColor    UIColor*
 */
- (void)setWebScrollerViewbgColor:(UIColor *)bgColor;


@end

NS_ASSUME_NONNULL_END
