
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanProperty.h"

/**
 * ContinuousScanEnabledProperty is a subclas of BooleanProperty.
 * It is used to get / set the Continuous Scan enabled property
 * of an IDBLUE device.
 *
 * In continuous scanning mode, pressing and releasing of the 
 * front button of an IDBLUE device will cause the device to
 * keep reading tags continuously until no tag is found withing
 * the Continuous Scan Timeout period. This behaviour is similar
 * to pressing the front button if IDBLUE repeatedly.
 */
@interface ContinuousScanEnabledProperty : BooleanProperty {

}

-(BOOL) continuousScanEnabled;

@end
