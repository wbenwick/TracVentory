
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteArrayCommand.h"

@interface EpcLockCommand : ByteArrayCommand {
    
}


-(id) initWithLockBits: (uint) lockbits;
@end
