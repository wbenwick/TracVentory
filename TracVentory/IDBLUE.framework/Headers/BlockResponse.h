
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "RfidResponse.h"

/**
 * BlockResponse is a subclass of RfidResponse, that also contains
 * block data. BlockResponse defaults to 1 block of data. 
 * BlocksResponse is a BlockResponse that deals with multiple blocks
 * of data.
 *  
 * (data stored in user memory of an RFID tag.   Block 
 * is an ISO15693 term - ISO15693 tags user memory is broken up 
 * into blocks. The size of the user memory is the number of blocks
 * times the number of bytes per block. Block size and block count vary
 * from tag to tag)
 */
@interface BlockResponse : RfidResponse {
	// The index of the starting block read from user memory of an RFID tag 
	byte _blockIndex;
	
	// The number of blocks read from an RFID tag
	byte _blockCount;
	
	// The number of bytes ready from user memory
	int _blockDataLen;
	
	// The byte array of data read from user memory.
	CByteArray* _blockData;
}

/**
 * Gets the block index of the first block read from user memory of an RFID tag
 */
-(byte) blockIndex;

/**
 * Gets the number of blocks read from user memory of an RFID tag
 */
-(byte) blockCount;

/**
 * Gets the number of bytes of user memory read from an RFID tag
 */
-(int) blockDataLen;

/**
 * Gets the block data ready from user memory of an RFID tag
 */
-(CByteArray*) blockData;

/**
 * Gets the offset, relative to the payload, of where the block data is read from an IDBluePacket
 */
-(int) blockDataOffset;
@end
