//
//  CCBNewProductInfo.h
//  CCBSDKDemo
//
//  Created by 樊亮 on 2020/3/26.
//  Copyright © 2020 Mr.Fn. All rights reserved.
//

#import <UIKit/UIKit.h>
@class CCBBaseWebViewController;

typedef CCBBaseWebViewController *_Nonnull(^CCBCustomVCBlock)(void);

typedef void(^CCBBlock)(id _Nullable  data);

typedef void(^tunnelBlock)(NSString* _Nullable eventID,id _Nullable param,UIViewController* _Nullable vc,CCBBlock _Nullable ccbblock);


NS_ASSUME_NONNULL_BEGIN



@interface CCBNewProductInfo : NSObject


/**custom create viewController Block*/
@property (nonatomic, copy) CCBCustomVCBlock    customVCBlock;


/**Tunnel data*/
@property (nonatomic, copy) tunnelBlock    tunnelBlock;


@end

NS_ASSUME_NONNULL_END
