
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"
#import "IDBlueTimestamp.h"

/**
 *  TimestampProperty is a subclass of IDBlueProperty
 *  It's purpose is process respones to the GET_PROPERTY for the
 *  PI_Timestamp property, and to create SET_PROPERTY commands.
 * 
 *  The payload of a GET_PROPERTY / SET_PROPERTY for PI_Timestamp
 *  has the first 2 bytes of the payload the property identifier,
 *  and the next 6 bytes the timestamp information.
 */
@interface TimestampProperty : IDBlueProperty {
@private
	// The date / time set on the IDBLUE device.
	IDBlueTimestamp* _idblueTimestamp;
}

/**
 * Get the date / time set on the IDBLUE device.
 */
-(IDBlueTimestamp*) idblueTimestamp;

@end
