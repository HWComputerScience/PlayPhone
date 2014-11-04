//
//  TestLoginViewController.m
//  GamePadStart
//
//  Created by Jake Saferstein on 10/21/14.
//  Copyright (c) 2014 Jake Saferstein. All rights reserved.
//

#import "TestLoginViewController.h"
#import "GameListViewController.h"
#import "SocketManager.h"

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
    [self.view setBackgroundColor:[UIColor blueColor]];
    
    _firstLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 120, 100, 20)];
    _firstLbl.text = @"First Name";
    _lastLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 150, 100, 20)];
    _lastLbl.text = @"Last Name";
    _userLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 180, 100, 20)];
    _userLbl.text = @"Username";
    
    [self.view addSubview:_firstLbl];
    [self.view addSubview:_lastLbl];
    [self.view addSubview:_userLbl];
    
    _firstName = [[UITextField alloc] initWithFrame:CGRectMake(100, 120, self.view.frame.size.width-50, 20)];
    _lastName = [[UITextField alloc] initWithFrame:CGRectMake(100, 150, self.view.frame.size.width-50, 20)];
    _username = [[UITextField alloc] initWithFrame:CGRectMake(100, 180, self.view.frame.size.width-50, 20)];
    _firstName.placeholder = @"John";
    _lastName.placeholder = @"Doe";
    _username.placeholder = @"XxX_$w@gYo1o420_XxX";
    
    
    [self.view addSubview:_firstName];
    [self.view addSubview:_lastName];
    [self.view addSubview:_username];
    
    UIButton *submit = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    submit.frame = CGRectMake(self.view.frame.size.width/2 - 100, 210, 200, 20);
    submit.backgroundColor = [UIColor redColor];
    [submit setTitle:@"PRESS HERE" forState:UIControlStateNormal];
    [submit addTarget:self action:@selector(submitted:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:submit];
}

-(void)submitted:(UIButton *) button
{
    if(!_firstName.text.length || !_lastName.text.length || !_username.text.length)
    {
        [UIAlertView bk_showAlertViewWithTitle:@"Missing Fields"
                                       message:@"Fill in all fields to continue"
                             cancelButtonTitle:@"Try again"
                             otherButtonTitles:nil
                                       handler:^(UIAlertView *alertView, NSInteger buttonIndex) {
                                           NSLog(@"yay!");
                                       }];
        return;
    }
    NSMutableDictionary* temp = [UserData getUserData];
    temp[@"username"] = _username.text;
    temp[@"firstname"] = _firstName.text;
    temp[@"lastname"] = _lastName.text;
    NSString *uuid = [[NSUUID UUID] UUIDString];
    temp[@"phoneID"] = uuid;
    temp[@"fbuid"] = @"";

    [SocketManager manager].gamesViewController = [[GameListViewController alloc] initWithStyle:UITableViewStyleGrouped];
    [self presentViewController:[SocketManager manager].gamesViewController animated:YES completion:^{
        NSLog(@"Switched viewcontrollers");
    }];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)presentViewController:(UIViewController *)viewControllerToPresent animated:(BOOL)flag completion:(void (^)(void))completion
{
    [super presentViewController:viewControllerToPresent animated:flag completion:completion];
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
