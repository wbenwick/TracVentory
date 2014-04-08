
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * ConnectedModeProperty is a subclass of ByteProperty.
 * It is used to get / set the ConnectedMode property of an IDBLUE
 * device.
 * 
 * The ConnectedMode of an IDBLUE device determines what operation
 * will occur when the user presses the front button of the IDBLUE
 * device while the device is connected to a host. 
 *  
 * See IDBlue.h for a list of ConnectedMode properties.
 */
@interface ConnectedModeProperty : ByteProperty {

}

-(ConnectedMode) connectedMode;

@end
