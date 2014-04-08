
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * BlockCountProperty is a sublcass of ByteProperty.
 * It is used to get / set the Block Count property of an IDBLUE
 * device.
 *
 * When an IDBLUE device is connected to a host and it's Connected
 * Mode propert is set to CM_READ_BLOCKS, the block count property 
 * is used to determine how many blocks of data to read.
 * (The Block Index property determines at which block to start
 * reading from).
 */
@interface BlockCountProperty : ByteProperty {

}

-(byte) blockCount;

@end
