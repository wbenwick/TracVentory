
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"

/**
 * VersionInfoProperty is a subclass of IDBlueProperty.
 * It is used to get the Bootloader version of the IDBLUE device.
 *
 * The bootloader is the onboard firmware of an IDBLUE device
 * that allows the IDBLUE device to be updated.
 */
@interface VersionInfoProperty : IDBlueProperty {
@private
	// The major part of the hardare version
	byte _hardwareMajor;
	
	// The minor part of the hardware version
	byte _hardwareMinor;

	// The major part of the firmware version
	byte _firmwareMajor;
	
	// The minor part of the firmware version
	byte _firmwareMinor;
	
	// The branch part of the firmware version
	byte _firmwareBranch;
	
	// The build part of the firmware version
	ushort _firmwareBuild;
}

/**
 * Gets the major part of the hardware version
 */
-(byte) hardwareMajor;

/**
 * Gets the minor part of the hardware version
 */
-(byte) hardwareMinor;

/**
 * Gets the major part of the firmware version
 */
-(byte) firmwareMajor;

/**
 * Gets the minor part of the firmware version
 */
-(byte) firmwareMinor;

/**
 * Gets the branch part of the firmware version
 */
-(byte) firmwareBranch;

/**
 * Gets the build part of the firmware version
 */
-(ushort) firmwareBuild;

/**
 * Get the hardware version of the IDBLUE device.
 * @return the hardware version, formatted as 'X.Y'
 * where X is the major part, Y is the minor part.
 */
-(NSString*) hardwareVersion;

/**
 * Get the firmware version of the IDBLUE device.
 * @return the firmware version, formatted as 'W.X.Y.Z'
 * where W is the major part, X is the minor part, Y is 
 * the branch part, and Z is the build part.
 */
-(NSString*) firmwareVersion;

@end
