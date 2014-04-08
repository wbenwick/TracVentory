
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanProperty.h"

/**
 * ConnectToHostProperty is a BooleanProperty. It is used to 
 * get the Connect to Host Property from an IDBLUE. If this
 * property is set to TRUE, the IDBLUE device will attempt to 
 * connect to the last known host on power up.
 */
@interface ConnectToHostProperty : BooleanProperty {

}

/**
 * Gets whether connectToHost is enabled
 */
-(BOOL) connectToHost;

@end
