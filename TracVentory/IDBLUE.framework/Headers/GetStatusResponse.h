
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 * GetStatusResponse is a subclass of IDBlueResponse.
 * It's purpose is to be a return value for the GET_STATUS command,
 * and returns battery level, hardware version and firmware version
 * of an IDBLUE device.
 */
@interface GetStatusResponse : IDBlueResponse {
@private
	// the battery level, as a percentage (0 - 100)
	byte _batteryLevel;
	
	// Major part of the hardware version
	byte _majorHardwareVersion;
	
	// Minor part of the hardware version
	byte _minorHardwareVersion;
	
	// Major part of the firmware version
	byte _majorFirmwareVersion;
	
	// Minor part of the firmware version
	byte _minorFirmwareVersion;
	
	// Branch part of the firmware version
	byte _branchFirmwareVersion;
	
	// Build part of the firmware version
	ushort _buildFirmwareVersion;
}

/**
 * Get the battery level of the IDBLUE device
 * @return the battery level as a percentage (0 - 100)
 */
-(byte) batteryLevel;

/**
 * Get the major part of the hardware version
 */
-(byte) majorHardwareVersion;

/**
 * Get the minor part of the hardware version
 */
-(byte) minorHardwareVersion;

/**
 * Get the hardware version of the IDBLUE device
 * @return the hardware version, formatted as 'X.Y', where 
 * 'X' is the major part and 'YY' is the minor part.
 */
-(NSString*) hardwareVersion;

/**
 * Get the major part of the firmware version
 */
-(byte) majorFirmwareVersion;

/**
 * Get the minor part of the firmware version
 */
-(byte) minorFirmwareVersion;

/**
 * Get the branch part of the firmware version
 */
-(byte) branchFirmwareVersion;

/**
 * Get the build part of the firmware version
 */
-(ushort) buildFirmwareVersion;

/**
 * Get the firmware version of the IDBLUE device.
 * @return the firmware version, formatted as 'W.X.Y.Z'
 * where W is the major part, X is the minor part, Y is 
 * the branch part, and Z is the build part.
 */
-(NSString*) firmwareVersion;

@end
