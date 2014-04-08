
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface GetTagInfoCommand : IDBlueCommand {
    
}

-(id) initWithTagId:(byte*) tagId withLen:(int) len;

@end
