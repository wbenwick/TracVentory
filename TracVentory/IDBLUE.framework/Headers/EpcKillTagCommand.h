
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteArrayCommand.h"

@interface EpcKillTagCommand : ByteArrayCommand {
    
}

-(id) initWithPassword: (byte*) pwd withLen:(int) len;
@end
