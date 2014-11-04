//
//  SocketManager.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/22/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "SocketManager.h"

#include <ifaddrs.h>
#import "UserData.h"
#include <arpa/inet.h>

@implementation SocketManager

static SocketManager* instance;

+(SocketManager*)manager{
    if(!instance){
        instance = [[SocketManager alloc] init];
    }
    return instance;
}

-(id)init{
    if(self = [super init]){
        instance = self;
    }
    return self;
}

//Initial Method: Ping everyone on Wi-Fi to find server IP/Port
-(void)discoverServers
{
    GCDAsyncUdpSocket* temp = [[GCDAsyncUdpSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    NSError* err;
    if(![temp enableBroadcast:YES error:&err]){
        NSLog(@"error enabling broadcast: %@", err);
    }
    char c = 'a';
    NSData * pingData = [NSData dataWithBytes:&c length:1];
    
    for (int i = 0; i < 10; i++)
    {
        [temp sendData:pingData toHost:@"255.255.255.255" port:9999 withTimeout:-1 tag:0];
    }
    [temp beginReceiving:&err];
}

//Process UDP Responses
-(void)udpSocket:(GCDAsyncUdpSocket*)socket didReceiveData:(NSData *)data fromAddress:(NSData *)address withFilterContext:(id)filterContext{
//    NSLog(@"Received data from %@", address);
    const char* arr = [address bytes];
    if(arr[2] == 0x27 && arr[3] == 0x0f)
    {
        const unsigned char* arr2 = [data bytes];
        int port = (arr2[0])*256+(arr2[1]);
        char addr[100];
        sprintf(addr, "%0d.%0d.%0d.%0d", arr[4], arr[5], arr[6], arr[7]);
//        NSLog(@"ip = %s, port = %d", addr, port);
        
        [self joinGame:[NSString stringWithUTF8String:addr] onPort:port];
    }
}

//Connect to games found with UDP using TCP
-(void) joinGame: (NSString *) ip onPort: (int) port
{
    
    NSString* temp = [NSString stringWithFormat:@"%@:%d", ip, port];
    if(!_addresses)_addresses = [NSMutableArray array];
    if([_addresses containsObject:temp])
    {
        return;
    }
    [_addresses addObject:temp];
    
    GCDAsyncSocket* curSock = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    
    
    if(!_attemptedSockets)_attemptedSockets = [NSMutableArray array];

    [self.attemptedSockets addObject:curSock];
        
    NSError *err = nil;
    NSLog(@"Connecting to address: %@ : %d", ip, port);
    if(![curSock connectToHost:ip onPort:port error:&err])
    {
        NSLog(@"I goofed: %@", err);
    }
}

//If connected, send data and start to read
- (void)socket:(GCDAsyncSocket *)sender didConnectToHost:(NSString *)host port:(UInt16)port
{
    NSLog(@"A socket connected");
    
    Request* r = [[Request alloc] initWithOp:0];
    
    
    GameConnection* newGame = [[GameConnection alloc] initWithSock:sender];
    [sender setDelegate:newGame];
    
    [sender writeData:[r serializeToJSON] withTimeout:-1 tag:0];

    if(!_connections) _connections = [NSMutableArray array];
    [_connections addObject:newGame];
    
    [sender readDataWithTimeout:-1 buffer:newGame.resp bufferOffset:0 tag:0];
}

//Get Data Response SEE GAME CONNECTION


@end
