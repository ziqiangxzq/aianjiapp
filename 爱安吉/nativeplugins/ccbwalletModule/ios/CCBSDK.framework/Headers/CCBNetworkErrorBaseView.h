//
//  CCBNetworkErrorBaseView.h
//  CCBSDKDemo
//
//  Created by 樊亮 on 2019/11/12.
//  Copyright © 2019 Mr.Fn. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CCBNetworkErrorBaseView : UIView

/**刷新*/
- (void)action_FuncionRefresh;

/**关闭*/
- (void)action_FuncionClose;


- (void)setErrorPageWithWebView:(WKWebView *)webView urlString:(NSString *)urlString closePage:(void (^)(id data))closePage;


@end

NS_ASSUME_NONNULL_END
