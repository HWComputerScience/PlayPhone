//
//  SAFAppDelegate.h
//  GamePadStart
//
//  Created by Jake Saferstein on 10/20/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GCDAsyncSocket.h"
#import "TestLoginViewController.h"

@interface SAFAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic) GCDAsyncSocket *socket;



@end