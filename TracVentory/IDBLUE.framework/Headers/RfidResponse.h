
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"
#import "IDBlue.h"
#import "RfidTag.h"
#import "TimestampResponse.h"

/**
 *  RfidResponse is a subclass of IDBlueResponse. It is used
 *  when the payload of an IDBluePacket contains a timestamp,
 *  tag id length, followed by the tag id bytes. RfidResponse
 *  can be used as response class directly (providing tag id 
 *  and timestamp) or can be overridden to process other information
 *  from the payload of an IDBluePacket (all responses from 
 *  IDBLUE that contain RFID tag info, alwyas contain a timestamp,
 *  tag id length, and tag id).
 */
@interface RfidResponse : TimestampResponse {
@private
	// The RfidTag that was returned from IDBLUE
	RfidTag* _rfidTag;
	
@protected
	// The number of bytes in the tag id.
	byte _tagIdLen;
}

/**
 * Get the RfidTag object returned from IDBLUE
 */
-(RfidTag*) rfidTag;

/**
 * Get the number of bytes in the tag id.
 */
-(byte) tagIdLen;

@end
