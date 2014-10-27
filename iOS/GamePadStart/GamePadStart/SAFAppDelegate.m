//
//  SAFAppDelegate.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/20/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "SAFAppDelegate.h"

@implementation SAFAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window setRootViewController:[[TestLoginViewController alloc] init]];
    [self.window makeKeyAndVisible];
    
    
    for (int x = START_PORT; x <= START_PORT+NUM_PORTS; x++) {
        self.socket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
        
        NSError *err = nil;
        if (![self.socket connectToHost:@"localhost" onPort:x error:&err]) // Asynchronous!
        {
            // If there was an error, it's likely something like "already connected" or "no delegate set"
            NSLog(@"I goofed: %@", err);
        }else{
            
            NSData *test = [@"Test" dataUsingEncoding:NSUTF8StringEncoding];//[[NSData alloc] initWithBytes:@"Test" length:4];
            
            [self.socket writeData:test withTimeout:-1 tag:1];
            break;
        }
        
    }
    return YES;
}



- (void)socket:(GCDAsyncSocket *)sender didConnectToHost:(NSString *)host port:(UInt16)port
{
    NSLog(@"Cool, I'm connected! That was easy.");
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
