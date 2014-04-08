
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 *  NackResponse is an IDBlueResponse that represents a NACK 
 *  sent from an IDBLUE device.
 */
@interface NackResponse : IDBlueResponse {
@private
	// the command identifier of the command sent to IDBLUE that failed
	CommandIdentifier _failedCommand;
	
	// Byte array containing the variable data that can be contained in a 
	// NACK response.
	CByteArray* _info;
	
	// Number of bytes in the info byte array
	int _infoLen;
}

/**
 * Get the command identifier of the command sent to IDBLUE that resulted in the NACK
 */
-(CommandIdentifier) failedCommand;

/**
 * Get the variable data that may have been returned in the NACK response
 */
-(CByteArray*) info;

/**
 * Get the number of bytes in the info byte array
 */
-(int) infoLen;

@end
