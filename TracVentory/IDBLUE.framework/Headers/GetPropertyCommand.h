
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "UShortCommand.h"

@interface GetPropertyCommand : UShortCommand {
    
}

-(id) initWithProperty:(PropertyIdentifier) property;
-(PropertyIdentifier) property;

@end
