
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * BluetoothTimeout property is a subclass of ByteProperty.
 * It is used to get / set the Bluetooth Timeout property of an
 * IDBLUE device.
 *
 * The Bluetooth tiimeout is the amount of idle time (in minutes) 
 * before the Bluetooth radio of the IDBLUE device is powered off
 * (to conserve battery life). Setting the Bluetooth Timeout
 * to zero disables automatically turning off the Bluetooth radio.
 *  
 * This only applies when the device does not have an active
 * Bluetooth session. Once the Bluetooth radio is turned off,
 * it can be turned on again by pressing and releasing the rear
 * button of the IDBLUE device. Ater the Bluetooth radio is turned
 * back on, the host must re-establish a session with the IDBLUE
 * device in order to communicate (the Bluetooth session is not
 * automatically established).
 */
@interface BluetoothTimeoutProperty : ByteProperty {
	
}

-(byte) timeout;

@end
