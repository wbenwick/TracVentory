
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "BooleanProperty.h"

/**
 * EnforceTimestampProperty is a subclass of BooleanProperty.
 * It is used to get / set the Enforce Timestamp property of an IDBLUe device.
 *
 * Enforce Timestamp is used to only store tag scans (in disconnecte mode)
 * into onboard memory only if the the IDBLUE device has it's onboard clock
 * initialized. If the onboard clock is not initialized, scanning a tag in
 * disconnected mode (with the disconnected mode property set to DM_TAG_STORE)
 * will not store the tag into onboard memory.
 */
@interface EnforceTimestampProperty : BooleanProperty {

}

/**
 * Gets the enforceTimestamp property value.
 */
-(BOOL) enforceTimestamp;

@end
