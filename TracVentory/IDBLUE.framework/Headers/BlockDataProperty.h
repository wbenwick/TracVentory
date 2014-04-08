
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"
#import "CByteArray.h"

/**
 * BlockDataProperty is a sublcass of IDBlueProperty.
 * It is used to get / set the Block Data property of an IDBLUE
 * device.
 */
@interface BlockDataProperty : IDBlueProperty {
@private
	// The block data property value
	CByteArray* _blockData;
}

/**
 * Gets the block data byte array
 */
-(CByteArray*) blockData;
@end
