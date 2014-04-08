
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

/**
 * GetBluetoothNameResponse is a subclass of IDBlueResponse.
 * It's purpose is a return value for the GET_BT_NAME command, and
 * returns the name configured in the Bluetooth Radio of the IDBLUE device
 * (i.e. the name that shows up when you search for the IDBLUE device).
 */
@interface GetBluetoothNameResponse : IDBlueResponse {
@private
	// The Bluetooth Name of the IDBLUE device
	NSString* _bluetoothName;
}

/**
 * Get the Bluetooth name of the IDBLUE device.
 */
-(NSString*) bluetoothName;

@end
