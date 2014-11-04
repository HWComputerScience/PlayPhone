//
//  Request.h
//  GamePadStart
//
//  Created by Jake Saferstein on 10/29/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Request : NSObject

//@property int op;
//@property int ts;
@property NSMutableDictionary* data;

-(id)initWithOp:(int)op;
-(NSData*)serializeToJSON;

@end
