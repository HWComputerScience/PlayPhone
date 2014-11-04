//
//  GameTableCell.h
//  GamePadStart
//
//  Created by Jake Saferstein on 10/28/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GameConnection.h"

@interface GameTableCell : UITableViewCell

@property(nonatomic, strong) GameConnection* conn;

@end
