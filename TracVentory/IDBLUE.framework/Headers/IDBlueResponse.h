
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBluePacket.h"

@protocol IResponseHandler;
@class IDBlueCommand;
@class NackResponse;

/**
 *  IDBlueResponse represents a response from an IDBLUE device.
 *  It can be used as a response to simple commands (i.e. commands that
 *  don't return any data in the payload), or it can be subclassed to 
 *  process the data in the payload of an IDBluePacket.
 */
@interface IDBlueResponse : NSObject {
@protected
	// The error code of the sent command
	CommandStatus _status;
	
	// The command identifier of the response. This may be different
	// than the command sent to IDBLUE, in the case of a NACK (failure)
	// response.
	CommandIdentifier _command;
	
@private
	// A message that desribes the response
	NSString* _message;
	
	// The date / time the response was created
	NSDate* _timestamp;
	
	// Whether the current IDBlueResponse was sent asynchronously from
	// an IDBLUE device (i.e. the response was sent from IDBLUE without
	// being requested by the host, such as pressing the front button
	// resulting in a tag scan).
	BOOL _async;
	
	// The IDBluePacket the current IDBlueResponse was created from
	IDBluePacket* _packet;
}

/**
 * Gets whether the command that the current IDBlueResponse belongs to
 * is successful or not.
 */
-(BOOL) successful;

/**
 * Get the error code returned from the command snet to IDBLUE that resulted in the NACK
 */
-(CommandStatus) status;

/**
 * Sets the status of the current IDBlueResponse object, indicating the error code (or CS_Ok if successful).
 */
-(void) setStatus: (CommandStatus) status;

/**
 * Get the message of the current IDBlueResponse 
 */
-(NSString*) message;

/**
 * Set the message of the current IDBlueResponse
 */
-(void) setMessage: (NSString*) message;

/**
 * Get the date / time the current IDBlueResponse was created
 */
-(NSDate*) timestamp;

/**
 * Get the command identifier of the current IDBlueResponse.
 * This may be different that the command identifier of the command
 * sent to IDBLUE that resulted in the current response, in the event
 * of a NACK response.
 */
-(CommandIdentifier) command;

/**
 * Sets the command identifier of the response
 */
-(void) setCommand: (CommandIdentifier) command;

/**
 * Get the IDBluePacket the current IDBlueResponse was created from
 */
-(IDBluePacket*) packet;

/**
 * Get whether the current response is a response for the giveen command identifier
 * @param command The command identifier to check
 * @return TRUE if the current IDBlueResponse is a valid response for the given
 * command identifier, FALSE otherwise.
 */
-(BOOL) isResponseFor: (CommandIdentifier) command;

/**
 * Gets whether the current IDBlueResponse was sent asynchronously
 */
-(BOOL) async;

/**
 * Set the async property
 */
-(void) set: (BOOL) async;

/**
 * Initialize the current IDBlueResponse from the given IDBluePacket.
 * Override this method when sublcassing IDBlueResponse to process
 * the payload of the IDBluePacket.
 * @param packet The response sent from an IDBLUE device
 * @param async Whether the response was sent asynchronously
 * @return The initialized IDBlueResponse object, or nil if initialization failed.
 */
-(id) initFromPacket: (IDBluePacket*) packet withAsync: (BOOL) async;

/**
 * Notify the given ResponseHandler of an asynchronous response
 * @param handler The handler to be notified of the asynchronous response
 * @return TRUE if the handler was notified, FALSE otherwise
 */
-(BOOL) notifyAsynchronousResponse: (id<IResponseHandler>) handler;

@end
