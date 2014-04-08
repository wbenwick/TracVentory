
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface StringCommand : IDBlueCommand {
    
}

-(id) initWithCommandIdentifier: (CommandIdentifier) cmd withString: (NSString*) s;

@end
