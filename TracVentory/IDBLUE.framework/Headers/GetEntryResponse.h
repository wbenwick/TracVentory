
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "RfidResponse.h"

/**
 * GetEntryResponse is a subclass of RfidResponse.
 * It's purpose is a return value for the GET_ENTRY command.
 * It returns the timestamp, tag id, and block data stored
 * in a memory bank in onboard memory of IDBLUE.
 */
@interface GetEntryResponse : RfidResponse {
@private
	// The block data stored in a memory bank of the IDBLUE device.
	byte _blockData;
}

/**
 * Get the block data stored in a memory bank of the IDBLUE device.
 */
-(byte) blockData;

@end
