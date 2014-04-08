
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 *  RfidTimeout is a subclass of ByteProperty.
 *  It's purpose is to get / set the RfidTimeout property of an 
 *  IDBLUE device.
 */
@interface RfidTimeoutProperty : ByteProperty {

}

/**
 * Get the RFID timeout
 */
-(byte) rfidTimeout;
@end
