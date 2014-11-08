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

@interface SAFAppDelegate : UIResponder <UIApplicationDelegate, GCDAsyncSocketDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic) GCDAsyncSocket *socket;


#define JAMES_IP 169.254.47.29
#define START_PORT 47810
#define NUM_PORTS 10

@end