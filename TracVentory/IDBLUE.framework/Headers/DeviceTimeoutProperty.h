
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * DeviceTimeoutProperty is a subclass of ByteProperty.
 * It is used to get / set the Device Timeout property of an IDBLUE
 * device.
 *
 * The device timeout (in minutes) is used to turn off the IDBLUE device
 * after a period if inactivity (i.e. the front button not being pressed,
 * or no commands sent to the IDBLUE device). Setting the device timeout
 * to zero disables automatically turning off IDBLUE.
 */
@interface DeviceTimeoutProperty : ByteProperty {

}

-(byte) timeout;

@end
