
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

@class GetPropertyCommand;
@class SetPropertyCommand;
@class IDBlueCommand;
@protocol IResponseHandler;

/**
 *  IDBlueProperty overrides the initFromPacket command, and
 *  sets it's property identifier from the payload of the packet
 *  passed as a parameter (property identifier is stored in the
 *  first 2 bytes of the payload).
 */
@interface IDBlueProperty : IDBlueResponse {
@private
	// The property identifier of the current IDBlueProperty
	PropertyIdentifier _property;
}

/**
 * Initialize the IDBlueProeprty, setting the property identifier to the 
 * specified value.
 * @param property The property identifier for the current IDBlueProperty
 * @return The initialized IDBlueProperty object
 */
-(id) initWithPropertyId: (PropertyIdentifier) property;

/**
 * Gets the property identifier of the current IDBlueProperty
 */
-(PropertyIdentifier) property;

/**
 * Create an IDBlueCommand that will set the current property of an IDBLUE device
 * @param args The value of the property to be set
 * @return an IDBlueCommand that will set the property corresponding to the 
 * property identifier of the current IDblueProperty.
 */
-(SetPropertyCommand*) buildSetRequest: (void*) args;

/**
 * Creates an instance of the GetPropertyCommand that (when sent to IDBLUE)
 * is used to set the current IDBLueProperty
 */
-(GetPropertyCommand*) buildGetRequest;

/**
 * Notify the given handler of a response to a get property command
 * @param command The request (GetPropertyCommand) that resulted in the response 
 * @param response The response (IDBlueProperty) containing the value of the property
 * @param handler The handler to be notified
 * @return TRUE if the handler was notified, FALSE otherwise
 */
-(BOOL) notifySynchronousGetResponse:(IDBlueCommand*) command 
                        withResponse:(IDBlueResponse*) response 
                        withHandler:(id<IResponseHandler>) handler;

/**
 * Notify the given handler of a response to a set property command
 * @param command The request (SetPropertyCommand) that resulted in the response
 * @param response The response to the set property command
 * @param handler The handler to be notified
 * @return TRUE if the handler was notified, FALSE otherwise
 */
-(BOOL) notifySynchronousSetResponse:(IDBlueCommand*) command 
                        withResponse:(IDBlueResponse*) response 
                        withHandler:(id<IResponseHandler>) handler;

@end
