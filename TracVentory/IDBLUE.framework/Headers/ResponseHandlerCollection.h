
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ResponseHandler.h"
#import "IDBlueResponse.h"
#import "IDBlueCommand.h"
#import "ObjectCollection.h"

/**
 * A collection of ResponseHandler objects
 */
@interface ResponseHandlerCollection : ObjectCollection {
}

/**
 * Add an ResponseHandler to the list of handlers that are notified of 
 * respones received from an IDBLUE device.
 */
-(BOOL) addHandler: (id<IResponseHandler>) handler;

/**
 * Removes an ResponseHandler from the list of handlers that are notified of
 * responses received from an IDBLUE device.
 */
-(BOOL) removeHandler: (id<IResponseHandler>) handler;

/**
 * Remove all ResponseHandlers from the list of handlers that are notified
 * of responses received from an IDBLUE device.
 */
-(int) removeAllHandlers;

/**
 * Determines if the given ResponseHandler is contained in the list of
 * handlers that are notified of responses received from an IDBLUE device.
 */
-(BOOL) hasHandler: (id<IResponseHandler>) handler;

/**
 * Returns the handler at the specified index
 * @param index the index to retrieve the handler from
 * @return the ResponseHandler found
 * @remarks will return nil if index is out of the collections range
 */
-(id<IResponseHandler>) handlerAtIndex: (int) index;

/**
 * Notifies all listeners that a command was sent to IDBLUE
 * @param command the command that was sent
 */
-(void) commandSent: (IDBlueCommand*) command;

/**
 * Notifies all listeners that a asynchronous response was received
 * @param resopnse the resopnse that was received
 */
-(void) asynchronousResponseReceived: (IDBlueResponse*) response;

/**
 * Notifies all listeners that a synchronous resopnse was received
 * @param command the command that initiaited the synchronous response
 */
-(void) synchronousResponseReceived: (IDBlueCommand*) command;

@end
