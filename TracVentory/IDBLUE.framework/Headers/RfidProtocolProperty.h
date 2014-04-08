
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 *  RfidProtocolProperty is a subclass of ByteProperty.
 *  It is used to get / set the RFID Protocol property of an IDBLUE
 *  device.
 *
 *  The RFID protocol property of an IDBLUE device determines 
 *  what type of RFID tags can be read or written. IDBLUE can only 
 *  read / write to RFID tags that match the current RFID Protocol
 *  of the IDBLUE device.
 *
 *  Currently, the only supported RFID Prootcol is ISO15693.
 */
@interface RfidProtocolProperty : ByteProperty {

}

-(RfidProtocol) protocol;

@end
