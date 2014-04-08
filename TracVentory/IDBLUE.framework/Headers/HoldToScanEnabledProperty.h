
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanProperty.h"

/**
 * HoldToScanEnabledProperty is a subclass of BooleanProperty.
 * It is used to get / set the hold to scan property of an IDBLUE device.
 *
 * Enabling hold to scan of an IDBLUE device allows scanning of
 * RFID tags, repeatedly, when the front button of IDBLUE is pressed and
 * held. If both Continuous Scan Enabled and Hold To Scan Enabled are
 * are both set to FALSE, pressing the front button if IDBLUE will
 * result in a single tag scan.
 */
@interface HoldToScanEnabledProperty : BooleanProperty {

}

-(BOOL) holdToScanEnabled;
@end
