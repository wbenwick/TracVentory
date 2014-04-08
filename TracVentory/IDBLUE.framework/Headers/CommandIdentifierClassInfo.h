
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBluePacket.h"
#import "IDBlueResponse.h"

/**
 * CommandIdentifierClassInfo is used to dynamically create IDBlueResponse
 * classes (at runtime). 
 */
@interface CommandIdentifierClassInfo : NSObject {
@private
    // The command identifier
    int _commandIdentifier;
    
    // The Class that represents the instance of the IDBlueResponse
    // associated with the command identifier
    Class _classInfo;
}

/**
 * Gets the command identifier
 */
-(int) commandIdentifier;

/**
 * Sets the command identifier
 */
-(void) setCommandIdentifier: (int) commandIdentifier;

/**
 * Gets the Class that is used to create the IDBlueResponse object
 */
-(Class) classInfo;

/**
 * Sets the Class that is used to create the IDBlueResponse object
 */
-(void) setClassInfo: (Class) classInfo;

/**
 * Get an IDBlueResponse object from the given IDBluePacket
 * @param packet The IDBluePacket containing the response data
 * @param async Whether the response is asynchronous or not
 * @return The IDBlueResponse from the IDBluePacket
 */
-(IDBlueResponse*) getResponse: (IDBluePacket*) packet withAsync: (BOOL) async;

/**
 * Create an instance of CommandIdentifierClassInfo for the given command identifier and Class
 * @param commandIdentifier The command identifier
 * @param classInfo The Class of the IDBlueResponse
 * @return The CommandIdentifierClassInfo, marked as autorelease
 */
+(CommandIdentifierClassInfo*) create:(int) commandIdentifier withClassInfo:(Class) classInfo;

@end
