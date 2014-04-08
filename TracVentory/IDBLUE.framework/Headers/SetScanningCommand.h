
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanCommand.h"

@interface SetScanningCommand : BooleanCommand {
    
}

-(id) initWithScanningEnabled:(BOOL) enabled;

@end
