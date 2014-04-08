
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface ReadBlockCommand : IDBlueCommand {
    
}

-(id) initWithInfo: (byte*) tagId 
           withLen: (byte) len 
    withBlockIndex: (byte) blockIndex;
@end
