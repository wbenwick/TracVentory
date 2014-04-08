
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueProperty.h"

/**
 *  UShortProperty is a subclass of IDBlueProperty
 *  It's purpose to process GET_PROPERTY responses that contain
 *  a 2 bytes of data (i.e. ushort) in the payload, as well as to create 
 *  SET_PROPERTY commands that accept a ushort as a parameter. 
 */
@interface UShortProperty : IDBlueProperty {
@private
	// The ushort value of the property
	ushort _val;
}

/**
 * Get the ushort value of the IDBlueProperty
 */
-(ushort) val;
@end
