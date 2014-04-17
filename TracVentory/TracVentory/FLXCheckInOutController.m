//
//  FLXCheckInOutController.m
//  TracVentory
//
//  Created by Administrator on 4/16/14.
//  Copyright (c) 2014 FileLogix. All rights reserved.
//

#import "FLXCheckInOutController.h"
#import "IDBlueSdk.h"

@interface FLXCheckInOutController () <ISessionHandler, IResponseHandler>
@property (weak, nonatomic) IBOutlet UITextField *textField;
@property (strong, nonatomic) IDBlueSdk * idBlue;
@end

@implementation FLXCheckInOutController

- (id)initWithStyle:(UITableViewStyle)style
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
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;

    self.idBlue = [[IDBlueSdk alloc] init];
    
    if ([self.idBlue openIDBlueSession]) {
        NSLog(@"ID Blue Session Opened");
        [self.idBlue addResponseHandler:self];
        
    }
    else {
        NSLog(@"ID Blue Session Not Found");
    }

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




-(void) readTagIdResponse: (IDBlueCommand*) command withResponse: (ReadTagIdResponse*) response {

    NSLog(@"ReadTagIDResponse");
    
    if (!response) {
        return;
    }
    
    RfidTag* tag = [response rfidTag];
    if (!tag) {
        return;
    }
    
    NSString* tagId = [tag toString];
    [[self textField] setText:tagId];
}

-(void) readTagIdFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
    NSLog(@"ReadTagIDFailed");
    [[self textField] setText:@""];
}

@end
