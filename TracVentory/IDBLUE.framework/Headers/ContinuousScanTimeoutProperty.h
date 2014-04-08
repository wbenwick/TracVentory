
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * ContinuousScanTimeoutProperty is a subclass of ByteProperty.
 * It's purpose is to get / set the Continuous Scan Timeout
 * property of an IDBLUE device.
 *
 * In continuous scanning mode, this property controls how long
 * the device will scan without finding an RFID tag before
 * ceasing continuous operations.
 */
@interface ContinuousScanTimeoutProperty : ByteProperty {

}

-(byte) timeout;

@end
