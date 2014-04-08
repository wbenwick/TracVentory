
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface WriteBlockCommand : IDBlueCommand {
    
}

-(id) initWithInfo: (byte*) tagId withLen: (byte) len 
    withBlockIndex: (byte) blockIndex 
     withBlockData: (byte*) block 
      withBlockLen: (byte) blockLen;

@end
