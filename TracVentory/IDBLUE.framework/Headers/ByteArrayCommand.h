
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface ByteArrayCommand : IDBlueCommand {
    
}

-(id) initWithCommandIdentifier: (CommandIdentifier) cmd 
                       withByte: (byte*) data 
                    withDataLen: (byte) len;
@end
