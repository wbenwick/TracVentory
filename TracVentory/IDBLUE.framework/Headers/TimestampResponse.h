
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"
#import "IDBlueTimestamp.h"

@interface TimestampResponse : IDBlueResponse {
    // The time the RFID tag was scanned on the IDBLUE device.
	IDBlueTimestamp* _scanTime;
}


/**
 * Get the date / time on the IDBLUE device when the RFID tag was scanned. 
 */
-(IDBlueTimestamp*) scanTime;

@end
