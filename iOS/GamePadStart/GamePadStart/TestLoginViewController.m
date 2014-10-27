//
//  TestLoginViewController.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/21/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "TestLoginViewController.h"

@interface TestLoginViewController ()

@end

@implementation TestLoginViewController

- (id)init
{
    self = [super init];
    if (self) {
        // Custom initialization
        
        
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    UILabel *firstLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 120, 100, 20)];
    firstLbl.text = @"First Name";
    UILabel *lastLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 150, 100, 20)];
    lastLbl.text = @"Last Name";
    UILabel *userLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 180, 100, 20)];
    userLbl.text = @"Username";
    
    [self.view addSubview:firstLbl];
    [self.view addSubview:lastLbl];
    [self.view addSubview:userLbl];
    
    UITextField *firstName = [[UITextField alloc] initWithFrame:CGRectMake(100, 120, self.view.frame.size.width-50, 20)];
    UITextField *lastName = [[UITextField alloc] initWithFrame:CGRectMake(100, 150, self.view.frame.size.width-50, 20)];
    UITextField *userName = [[UITextField alloc] initWithFrame:CGRectMake(100, 180, self.view.frame.size.width-50, 20)];
    firstName.placeholder = @"John";
    lastName.placeholder = @"Doe";
    userName.placeholder = @"XxX_$w@gYo1o420_XxX";
    
    
    [self.view addSubview:firstName];
    [self.view addSubview:lastName];
    [self.view addSubview:userName];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
