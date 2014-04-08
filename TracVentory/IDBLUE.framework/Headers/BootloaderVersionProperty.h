
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"

/**
 * BootloaderVersionProperty is a subclass of IDBlueProperty.
 * It is used to get the Bootloader version of the IDBLUE device.
 *
 * The bootloader is the onboard firmware of an IDBLUE device
 * that allows the IDBLUE device to be updated.
 */
@interface BootloaderVersionProperty : IDBlueProperty {
@private
	// The major part of the bootloader version
	byte _major;
	
	// The minor part of the bootloader version
	byte _minor;
	
	// The branch part of the bootloader version
	byte _branch;
	
	// The build part of the bootloader version
	ushort _build;
}

/**
 * Gets the major part of the bootloader version
 */
-(byte) major;

/**
 * Gets the minor part of the bootloader version
 */
-(byte) minor;

/**
 * Gets the branch part of the bootloader version
 */
-(byte) branch;

/**
 * Gets the build part of the bootloader version
 */
-(ushort) build;

/**
 * Get the bootloader version of the IDBLUE device.
 * @return the bootloader version, formatted as 'W.X.Y.Z'
 * where W is the major part, X is the minor part, Y is 
 * the branch part, and Z is the build part.
 */
-(NSString*) bootloaderVersion;

@end
