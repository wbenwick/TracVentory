
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface SetPropertyCommand : IDBlueCommand {
    
}

-(id) initWithPacketSize:(int)packetSize;
-(PropertyIdentifier) property;

@end
