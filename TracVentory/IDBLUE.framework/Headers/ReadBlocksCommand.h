
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface ReadBlocksCommand : IDBlueCommand {
    
}

-(id) initWithInfo: (byte*) tagId 
           withLen: (byte) len 
    withBlockIndex: (byte) blockIndex 
    withBlockCount: (byte) blockCount;
@end
