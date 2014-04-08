
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 *  SimpleResponse is a class used to processing Packets that have no 
 *  payload. A simple response is a command 4 bytes long, with the first
 *  and last bytes set to the command header and the middle 2 bytes 
 *  set to zero.
 */
@interface SimpleResponse : IDBlueResponse {

}

@end
