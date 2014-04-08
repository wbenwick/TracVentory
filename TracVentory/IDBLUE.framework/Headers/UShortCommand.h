
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface UShortCommand : IDBlueCommand {
    
}

-(id) initWithCommandIdentifier: (CommandIdentifier) cmd withVal: (ushort) i;
@end
