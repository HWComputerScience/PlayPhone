//
//  GameConnection.h
//  GamePadStart
//
//  Created by Jake Saferstein on 10/24/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GCDAsyncSocket.h"
#import "SocketManager.h"

@interface GameConnection : NSObject <GCDAsyncSocketDelegate>

@property (nonatomic) GCDAsyncSocket* socket;
@property (nonatomic,strong) NSMutableData* resp; //The buffer that holds all data from the socket

//For all responses
@property (nonatomic) NSMutableArray* sts;

//For discovery response
@property (nonatomic,strong) NSMutableDictionary* game;
@property (nonatomic) NSMutableArray* banned;

//For Join response and update config requests
@property (nonatomic) NSMutableDictionary* padconfig;




-(id)initWithSock: (GCDAsyncSocket *) sock;

@end
