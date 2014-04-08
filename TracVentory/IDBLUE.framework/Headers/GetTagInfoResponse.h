
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "RfidResponse.h"
#import "IDBlueTimestamp.h"

/**
 * The GetTagInfoResponse class is a subclass of RfidResponse.
 * It's purpose is to be a return value for the GET_TAG_INFO command.
 * Along with timestamp and tag id data, GetTagInfoResponse
 * contains the number of blocks and bytes per block of an RFID tag.
 */
@interface GetTagInfoResponse : RfidResponse {
@private
	// the number of blocks of user memory of the scanned RFID tag
	byte _blockCount;
	
	// The number of bytes per block in user memory of the scanned RFID tag
	byte _bytesPerBlock;
}

/**
 * Get the number of blocks of user memory of the scanned RFID tag
 */
-(byte) blockCount;

/**
 * Get the number of bytes per block in user memory of the scanned RFID tag
 */
-(byte) bytesPerBlock;
@end
