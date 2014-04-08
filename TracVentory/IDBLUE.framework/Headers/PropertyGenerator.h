
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"
#import "IDBlueResponse.h"
#import "SetPropertyCommand.h"
#import "IDBlueProperty.h"
#import "GetPropertyClassInfo.h"

/**
 *  PropertyGenerator is used to create SET_PROPERTY commands to be 
 *  sent to an IDBLUE device, and to process GET_PROPERTY responses
 *  from an IDBLUE device.
 *  
 *  GET_PROPERTY commands are not handled by the PropertyGenerator since
 *  they are fairly easy to create (most commands only have one or 2 
 *  parameters). 
 *
 *  SET_PROPERTY responses are not handled by the PropeertyGenerator either,
 *  since the response to a set property command is a response packet,
 *  with the property identifier that was set contained in the payload.
 */
@interface PropertyGenerator : NSObject {
@private
    // List of GetPropertyClassInfo objects that maps property identifiers
    // into Classes that process responses for IDBlue properties.
    GetPropertyClassInfo* _supportedProperties;
}

/**
 * Gets the supported IDBLUE properties
 */
-(GetPropertyClassInfo*) supportedProperties;

/**
 * Sets the supported IDBLUE properties 
 */
-(void) setSupportedProperties: (GetPropertyClassInfo*) properties;

/**
 * Create an IDBlueCommand to be sent to an IDBLUE device that will set the
 * specified property using the specified arguments.
 * @param property The property identifier of the property to be set
 * @param args The value of the property to be set
 * @return The IDBlueCommand if the set request could be generated, nil otherwise.
 */
-(SetPropertyCommand*) buildSetRequest: (PropertyIdentifier) property withArgs: (void*) args;

/**
 * Create an instance (or subclass) of IDBlueResponse from the given packet that 
 * is a response to the GET_PROPERTY command.
 * @param packet A response packet to the GET_PROPERTY command
 * @return An allocated (but not initialized) IDBlueResponse object. initFromPacket
 * needs to be called on the returned value.
 */
-(IDBlueResponse*) allocResponse: (IDBluePacket*) packet;

/**
 * Create an instance (or subclass) of IDBlueResponse from the given property identifier.
 * @param property The property to create a response for
 * @return An allocated (but not initialized) IDBlueResponse object. initFromPacket
 * needs to be called on the returned value.
 */
-(IDBlueResponse*) allocResponseByProperty: (PropertyIdentifier) property;

@end
