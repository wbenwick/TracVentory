
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * BlockIndexProperty is a sublcass of ByteProperty.
 * It is used to get / set the Block Count property of an IDBLUE
 * device.
 *
 * When an IDBLUE device is connected to a host and it's Connected
 * Mode propert is set to CM_READ_BLOCK, CM_READ_BLOCKS, or 
 * CM_WRITE_BLOCK, the block index property is used to determine 
 * at what block index to start reading / writing data from. 
 *  
 * (The Block Count property determines how many blocks to ready
 * when the Connected Mode is set to CM_READ_BLOCKS. Only one block
 * of data is read when the Connected Mode is set to CM_READ_BLOCK.
 * When the Connected Mode is set to CM_WRITE_BLOCK, a single block is
 * written at the block index, where the block data comes from the
 * Block Data property).
 */
@interface BlockIndexProperty : ByteProperty {

}

-(byte) blockIndex;
@end
