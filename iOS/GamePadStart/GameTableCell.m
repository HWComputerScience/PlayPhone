//
//  GameTableCell.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/28/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "GameTableCell.h"

@implementation GameTableCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

-(void)setConn:(GameConnection *)conn {
    _conn = conn;
    self.textLabel.text = _conn.game[@"name"];
    self.detailTextLabel.text = _conn.game[@"desc"];
    
//    NSData* temp = [NSData dataFromBase64String:_conn.game[@"icon"]];
//    UIImage* icon = [UIImage imageWithData:temp];
//    self.imageView.image = icon;
}


@end
