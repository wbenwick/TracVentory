
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"

/**
 * ByteProperty is a subclass of IDBlueProperty
 * It's purpose to process GET_PROPERTY responses that contain
 * a singe byte of data in the payload, as well as to create 
 * SET_PROPERTY commands that accept a single byte as a parameter. 
 */
@interface ByteProperty : IDBlueProperty {
@private
	// The value stored in the first byte of the payload of the IDBluePacket response
	byte _val;
}

/**
 * Get the byte value of the property
 */
-(byte) val;
@end
