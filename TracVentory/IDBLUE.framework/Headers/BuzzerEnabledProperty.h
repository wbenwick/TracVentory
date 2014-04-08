
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanProperty.h"

/**
 * BuzzerEnabledProperty is a sublcass of BooleanProperty.
 * It is used to get / set the buzzer enabled property of an IDBLUE
 * device.
 *
 * Setting Buzzer Enabled to FALSE will cause IDBLUE to not emmitt
 * any beeps (the CM_BEEP command will fail and return a NACK).
 */
@interface BuzzerEnabledProperty : BooleanProperty {

}

/**
 * Gets the buzzer enabled property value
 */
-(BOOL) buzzerEnabled;

@end
