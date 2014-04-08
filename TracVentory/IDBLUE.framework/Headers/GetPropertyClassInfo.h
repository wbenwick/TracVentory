
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "CommandIdentifierClassInfo.h"
#import "ObjectCollection.h"

/**
 * GetPropertyClassInfo is an instance of CommandIdentifierClassInfo,
 * that is used to dynamically create IDBlueProperty objects (at runtime)
 */
@interface GetPropertyClassInfo : CommandIdentifierClassInfo {
@private
    // List of supported IDBLUE properties
    ObjectCollection* _propertyMap;
}

/**
 * Adds a supported IDBLUE property, represented as a CommandIdentifierClassInfo
 * @param classInfo A CommandIdentifierClassInfo for the supported property,
 * where the commandIdentifier represents the property identiifer, and
 * the class is an instance of IDBlueProperty
 * @return TRUE if the classInfo was added, FALSE otherwise
 */
-(BOOL) addResponseMap: (CommandIdentifierClassInfo*) classInfo;

/**
 * Addas a supported IDBLUE property
 * @param propertyIdentifier The PropertyIdentifier of the supported IDBLUE property
 * @param classInfo the Class of the sublcass of IDBlueProperty associated with the property identifier
 * @return TRUE if the IDBLUE property was added, FALSE otherwise
 */
-(BOOL) addResponseMap: (int) propertyIdentifier withClassInfo: (Class) classInfo;

/**
 * Gets the CommandIdentifierClassInfo associated with the given propertyIdentifier
 * @param propertyIdentifier The id of the IDBLUE property
 * @return A CommandIdentifierClassInfo associated with the propertyIdentifier
 */
-(CommandIdentifierClassInfo*) getClassInfo:(int) propertyIdentifier;

/**
 * Creates an instance of GetPropertyClassInfo, that is marked as autorelease
 */
+(GetPropertyClassInfo*) create;

@end
