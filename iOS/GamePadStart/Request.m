//
//  Request.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/29/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "Request.h"
#import "UserData.h"

@implementation Request

-(id) initWithOp:(int)op
{
    if(self = [super init]){
        _data = [NSMutableDictionary dictionary];
        
        _data[@"op"] = [NSNumber numberWithInt:op];
        _data[@"ts"] = [NSNumber numberWithInt:time(0)];
        
        
        if(op == 0)
        {
            _data[@"id"] = [UserData getUserData];
            _data[@"APIVersion"] = @1;
            
            NSMutableDictionary *capablities = [[NSMutableDictionary alloc] init];
            NSMutableDictionary *resolution = [[NSMutableDictionary alloc] init];
            resolution[@"h"] = @([UIScreen mainScreen].bounds.size.height);
            resolution[@"w"] = @([UIScreen mainScreen].bounds.size.width);
            capablities[@"resolution"] = resolution;
            _data[@"capabilities"] = capablities;
        }
    }
    return self;
}


-(NSData*) serializeToJSON
{
    NSMutableData* json = [NSMutableData data];
    NSError* err;
    
    // Dictionary convertable to JSON ?
    if ([NSJSONSerialization isValidJSONObject:_data])
    {
        // Serialize the dictionary
        [json appendData:[NSJSONSerialization dataWithJSONObject:_data options:NSJSONWritingPrettyPrinted error:&err]];
        
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

@end
