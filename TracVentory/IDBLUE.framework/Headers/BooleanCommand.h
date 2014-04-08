
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteCommand.h"

@interface BooleanCommand : ByteCommand {
    
}

-(id) initWithBooleanValue:(CommandIdentifier) ci withVal:(BOOL) val;
@end
