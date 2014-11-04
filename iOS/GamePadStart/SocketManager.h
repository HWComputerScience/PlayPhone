//
//  SocketManager.h
//  GamePadStart
//
//  Created by Jake Saferstein on 10/22/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GCDAsyncSocket.h"
#import "GameConnection.h"
#import "GCDAsyncUdpSocket.h"
#import "Request.h"

@interface SocketManager : NSObject <GCDAsyncSocketDelegate>

@property (nonatomic, strong) NSMutableArray* connections; //Successful GameConnection objects
@property (nonatomic, strong) NSMutableArray* addresses; //Ensures that you don't repeat UDP addresses
@property (nonatomic, strong) NSMutableArray* attemptedSockets; //Keeps a strong reference so sockets persist until they are created


@property(nonatomic, strong) UITableViewController* gamesViewController;

+(SocketManager*)manager;

-(void)discoverServers;

@end
