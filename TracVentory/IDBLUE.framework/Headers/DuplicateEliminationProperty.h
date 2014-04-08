
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "UShortProperty.h"

/**
 * DuplicateEliminationProperty is a sublcass of UShortProperty.
 * It is used to get / set the Duplicate Elimination property of an
 * IDBLUE device.
 * 
 * The duplicate elimination property is a timeout value (in milliseconds).
 * It is used to reduce the number of tags that get stored into onboard memory,
 * when IDBLUE is in disconnected mode (i.e. not connected to a host).
 * Setting this property to a value other than zero will only allow the tag
 * scan to be stored in onboard memory if that tag has not been scanned within
 * duplicate elimination timeout. Scans of the same tag within the duplicate
 * elimination timeout period will just be ignored.
 * 
 * Setting the duplicate elimination property to zero disables the duplicate 
 * elimination check, and allows all tags scans.
 */
@interface DuplicateEliminationProperty : UShortProperty {

}

/**
 * Gets the duplicate elimination property
 * @return the duplicate elimination, in milliseconds.
 */
-(ushort) duplicateElimination;

@end
