
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 * The GetEntryCountResponse class is a subclass of IDBlueResponse.
 * It's purpose is a return value for the GET_ENTRY_COUNT command,
 * which returns  the number of RFID tags stored in the 
 * onboard memory of an IDBLUE device.
 */
@interface GetEntryCountResponse : IDBlueResponse {
@private
	// The number of entires stored in onboard memory of an IDBLUE device
	ushort _entryCount;
}


/**
 * Get the number of entires (i.e. RFID tags) stored in the onboard memory
 * of an IDBLUE device.
 */ 
-(ushort) entryCount;

@end
