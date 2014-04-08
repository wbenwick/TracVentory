
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "ByteProperty.h"

/**
 * BooleanProperty is a subclass of ByteProperty
 * It's purpose to process GET_PROPERTY responses that contain
 * a singe byte of data (BOOLean) in the payload, as well as to create 
 * SET_PROPERTY commands that accept a BOOLean as a parameter. 
 * The byte value of the ByteProperty is treated like a C BOOL
 * (zero returns FALSE, anything else returns TRUE).
 */
@interface BooleanProperty : ByteProperty {

}

/**
 * Get the boolean value
 */
-(BOOL) boolVal;

@end
