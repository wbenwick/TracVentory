
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface ByteCommand : IDBlueCommand {
    
}

-(id) initWithByteValue:(CommandIdentifier) ci withByte:(byte) b;
@end
