//
//  Created by Jesse Squires on 2/12/13.
//  Copyright (c) 2013 Hexed Bits. All rights reserved.
//
//  http://www.hexedbits.com
//
//
//  Originally based on work by Sam Soffes
//  https://github.com/soffes
//
//  SSMessagesViewController
//  https://github.com/soffes/ssmessagesviewcontroller
//
//
//  The MIT License
//  Copyright (c) 2013 Jesse Squires
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//  associated documentation files (the "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
//  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#import <UIKit/UIKit.h>
#import "JSBubbleMessageCell.h"
#import "JSMessageInputView.h"
#import "JSMessageSoundEffect.h"


typedef NS_ENUM(NSUInteger, JSMessagesViewTimestampPolicy) {
    JSMessagesViewTimestampPolicyAll,
    JSMessagesViewTimestampPolicyAlternating,
    JSMessagesViewTimestampPolicyEveryThree,
    JSMessagesViewTimestampPolicyEveryFive,
    JSMessagesViewTimestampPolicyCustom
};


typedef NS_ENUM(NSUInteger, JSMessagesViewAvatarPolicy) {
    JSMessagesViewAvatarPolicyAll,
    JSMessagesViewAvatarPolicyIncomingOnly,
    JSMessagesViewAvatarPolicyOutgoingOnly,
    JSMessagesViewAvatarPolicyNone
};


typedef NS_ENUM(NSUInteger, JSMessagesViewSubtitlePolicy) {
    JSMessagesViewSubtitlePolicyAll,
    JSMessagesViewSubtitlePolicyIncomingOnly,
    JSMessagesViewSubtitlePolicyOutgoingOnly,
    JSMessagesViewSubtitlePolicyNone
};


@protocol JSMessagesViewDelegate <NSObject>

@required
- (void)didSendText:(NSString *)text;

- (JSBubbleMessageType)messageTypeForRowAtIndexPath:(NSIndexPath *)indexPath;
- (JSBubbleMessageStyle)messageStyleForRowAtIndexPath:(NSIndexPath *)indexPath;

- (JSMessagesViewTimestampPolicy)timestampPolicy;
- (JSMessagesViewAvatarPolicy)avatarPolicy;
- (JSMessagesViewSubtitlePolicy)subtitlePolicy;

@optional
- (BOOL)hasTimestampForRowAtIndexPath:(NSIndexPath *)indexPath;

- (UIButton *)sendButtonForInputView;

@end



@protocol JSMessagesViewDataSource <NSObject>

@required
- (NSString *)textForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSDate *)timestampForRowAtIndexPath:(NSIndexPath *)indexPath;
- (UIImage *)avatarForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSString *)subtitleForRowAtIndexPath:(NSIndexPath *)indexPath;

@end



@interface JSMessagesViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, UITextViewDelegate>

@property (weak, nonatomic) id<JSMessagesViewDelegate> delegate;
@property (weak, nonatomic) id<JSMessagesViewDataSource> dataSource;
@property (assign, nonatomic) BOOL preventScrollToBottomWhileUserScrolling;

#pragma mark - Messages view controller

- (BOOL)shouldHaveTimestampForRowAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)shouldHaveAvatarForRowAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)shouldHaveSubtitleForRowAtIndexPath:(NSIndexPath *)indexPath;

- (void)finishSend;
- (void)setBackgroundColor:(UIColor *)color;
- (void)scrollToBottomAnimated:(BOOL)animated;

#pragma mark - Scroll while respecting user interaction

- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath
			  atScrollPosition:(UITableViewScrollPosition)position
					  animated:(BOOL)animated;

@end