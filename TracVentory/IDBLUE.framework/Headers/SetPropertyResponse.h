
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 * SetPropertyResponse is used process the response to a CI_SET_PROPERTY
 * command.
 */
@interface SetPropertyResponse : IDBlueResponse {
    
}

-(PropertyIdentifier) property;

@end
