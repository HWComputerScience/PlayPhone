//
//  GameConnection.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/24/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "GameConnection.h"
#import <BlocksKit/BlocksKit+UIKit.h>

@implementation GameConnection

-(id) initWithSock:(GCDAsyncSocket *)sock {
    if(self = [super init]){
        _socket = sock;
        _resp = [[NSMutableData alloc] init];
    }
    return self;
}

-(void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    while (YES)
    {
        const char * temp = [_resp bytes];
        int zeroIndex = -1;
        for (int x = 0; x < _resp.length; x++) {
            if(!temp[x])
            {
                zeroIndex = x;
                break;
            }
        }
        if (zeroIndex < 0) break;
        
        /* Operate on buffer w/ zero at zeroIndex */
        NSData* tempData = [_resp subdataWithRange:NSMakeRange(0, zeroIndex)];
        
        /* Process tempdata */
        [self processData:tempData];
        
        /* resp reset */
        _resp = [NSMutableData dataWithData:[_resp subdataWithRange:NSMakeRange(zeroIndex+1, _resp.length - zeroIndex - 1)]];
    }
    
    [_socket readDataWithTimeout:-1 buffer:_resp bufferOffset:0 tag:0];
}

-(NSData *)toJSON: (NSDictionary *)dic
{
    NSMutableData* json = [NSMutableData data];
    NSError* err;
    
    // Dictionary convertable to JSON ?
    if ([NSJSONSerialization isValidJSONObject:dic])
    {
        // Serialize the dictionary
        [json appendData:[NSJSONSerialization dataWithJSONObject:dic options:0 error:&err]];
        
        // If no errors, let's view the JSON
        if (json != nil && err == nil)
        {
            NSString *jsonString = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
            
            NSLog(@"JSON: %@", jsonString);
            
            char end = 0;
            
            [json appendBytes:&end length:1];
            return json;
        }
    }
    return nil;
}

-(void)processData: (NSData*) toProc
{
    NSDictionary* temp = [NSJSONSerialization JSONObjectWithData:toProc options:NSJSONReadingAllowFragments error:nil];
    
    
    //If its a request...
    if (temp[@"op"]) {
        
        //If it is a Game Refresh Request...
        if ([(NSNumber *) temp[@"op"] isEqualToNumber:[NSNumber numberWithInt:1]]) {
            _game = temp[@"game"];
#warning update tableview
            NSMutableDictionary* resp = [[NSMutableDictionary alloc] initWithCapacity:1];
            NSMutableDictionary* sts = [[NSMutableDictionary alloc] initWithCapacity:2];
            resp[@"sts"] = sts;
            sts[@"code"] = [[NSNumber alloc] initWithInt:200];
            sts[@"msg"] = @"Updated game status";
            
            [_socket writeData:[self toJSON:resp] withTimeout:-1 tag:4];
            return;
        }
        
        //If it is a Disconnect Request...
        
        NSString* x = [[NSString alloc] initWithFormat:@"%@", temp[@"sts"][@"msg"]];
        
        if ([(NSNumber *) temp[@"op"] isEqualToNumber:[NSNumber numberWithInt:3]]) {
            [UIAlertView bk_showAlertViewWithTitle:@"Disconnected by  Server" message:x cancelButtonTitle:@"Okay" otherButtonTitles:nil
                                handler:^(UIAlertView *alertView, NSInteger buttonIndex) {  NSLog(@"Disconnected by server alert showed");}];
#warning go back to discovery mode
            return;
        }
        
        //If it is a Update Pad Config Request...
        if ([(NSNumber *) temp[@"op"] isEqualToNumber:[NSNumber numberWithInt:4]]) {
            _padconfig = temp[@"padconfig"];
#warning update control view
            NSMutableDictionary* resp = [[NSMutableDictionary alloc] initWithCapacity:1];
            NSMutableDictionary* sts = [[NSMutableDictionary alloc] initWithCapacity:2];
            resp[@"sts"] = sts;
            sts[@"code"] = [[NSNumber alloc] initWithInt:200];
            sts[@"msg"] = @"Updated pad config";
    
            [_socket writeData:[self toJSON:resp] withTimeout:-1 tag:4];
            return;
        }
    }
    
    //If its a response...
    else if (temp[@"sts"]) {
        
        //If its a discovery response
        if(temp[@"game"])
        {
            _sts = temp[@"sts"];
            _game = temp[@"game"];
            _banned = temp[@"banned"];
            
            
            [[SocketManager manager].gamesViewController.tableView reloadData];
            //NSLog(@"%@ %@",[SocketManager manager].gamesViewController.tableView, [SocketManager manager].gamesViewController.tableView.delegate );
            
            
            return;
        }
        
        //If its a join response
        if(temp[@"accepted"])
        {
            //take in "accepted" and "padconfig"
        }
        
        //finish this
        
        
        
        
    }
    else
    {
        NSLog(@"Something went wrong processing data");
    }
}

@end
