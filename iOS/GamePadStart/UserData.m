//
//  UserData.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/23/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "UserData.h"
#import "PersistentDictionary.h"

@implementation UserData

static NSMutableDictionary *userData;

+ (NSMutableDictionary *) getUserData
{
    NSMutableDictionary* temp = [PersistentDictionary dictionaryWithName:@"userData"].dictionary;
    [PersistentDictionary saveAllDictionaries];
    return temp;
}


@end
