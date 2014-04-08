
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"

@protocol IResponseHandler;
@class PropertyGenerator;

/**
 *  IDBlueCommand derives from the IDBluePacket interface. IDBlueCommand
 *  Represents an IDBluePacket that can be sent to an IDBLUE device.
 * 
 *  IDBlueCommand objects should not be created from outside the IDBLUE
 *  iOS SDK. Instead, use the appropriate method on the IDBlueCommandSender object
 *  that will create the appropriate IDBlueCommand object, and notify the 
 *  calling application via the ResponseHandler interface.
 */
@interface IDBlueCommand : IDBluePacket {
@private
	// The object that will get notified of a response
	id<IResponseHandler> _handler;
	
	// The response received for the current IDBlueCommand
	IDBlueResponse* _response;
}

/**
 * Determine if the specified response is valid for the current IDBlueCommand.
 * A valid response would be a response having the same command header, or
 * a NACK response with the failedCommand matching the current IDBlueCommand header.
 * @return TRUE if the response is valid for the current IDBlueCommand, FALSE otherwise
 */
-(BOOL) isValidResponse: (IDBlueResponse*) response;

/**
 * Get the command identifier of the current IDBlueCommand
 */
-(CommandIdentifier) command;

/**
 * Gets the ResponseHandler that is assigned to the current IDBlueCommand
 */
-(id<IResponseHandler>) handler;

/**
 * Sets the callback method to be executed when a response to the current IDBlueCommand is received
 * from an IDBLUE device.
 * @param handler the object implementing the ResponseHandler protocol. When a response is 
 * received to the current IDBlueCommand, the corresponding method will be invoked on the handler.
 */
-(void) sethandler: (id<IResponseHandler>) handler;

/**
 * Gets the IDBlueResponse for the current IDBlueCommand
 */
-(IDBlueResponse*) response;

/**
 * Sets the IDBlueResponse for the current IDBlueCommand
 * @param response The IDBlueResponse received for the current IDBlueCommand
 */
-(void) setResponse: (IDBlueResponse*) response;

/**
 *
 */
-(BOOL) notifySynchronousResponse: (id<IResponseHandler>) handler 
            withPropertyGenerator: (PropertyGenerator*) generator;

@end
