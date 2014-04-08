
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * DisconnectedModeProperty is a subclass of ByteProperty.
 * It's purpose is to get / set the disconnected mode operation 
 * of an IDBLUE device. The DisconnectedMode is stored as a 
 * sigle byte of data in the payload of an IDBluePacket.
 *
 * In disconnected mode, scanning a tag can either just verify the 
 * tag is a valid tag, or can store the tag, with timestamp and a 
 * single byte of tag data, into onboard memory. When tags are 
 * stored tags into onboard memory, they can be retrieved by the 
 * GET_ENTRY command. The number of tags stored in onboard memory 
 * can be retrieved with the GET_ENTRY_COUNT command.
 */
@interface DisconnectedModeProperty : ByteProperty {

}

/**
 *
 */
-(DisconnectedMode) disconnectedMode;
@end
