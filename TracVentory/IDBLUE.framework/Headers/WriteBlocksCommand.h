
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface WriteBlocksCommand : IDBlueCommand {
    
}

-(id) initWithInfo: (byte*) tagId withLen: (byte) len 
    withBlockIndex: (byte) blockIndex 
    withBlockCount: (byte) blockCount 
     withBlockData: (byte*) block 
      withBlockLen: (byte) blockLen;

@end
