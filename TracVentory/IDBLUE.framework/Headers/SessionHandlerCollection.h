
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "SessionHandler.h"
#import "ObjectCollection.h"

/**
 * A Collection of ISessionHandler objects
 */
@interface SessionHandlerCollection : ObjectCollection {
}

/**
 * Adds an object that will receive session open / close notifications
 * @param handler The object implementing ISessionHandler to receive
 * open / close notifications from the current IDBlueSession
 */
-(BOOL) addSessionHandler: (id<ISessionHandler>) handler;

/**
 * Remove the given ISessionHandler from the list of deelegaets
 * that are notified of session events (open, close, etc.)
 * @param handler The ISessionHandler to add
 * @return TRUE if the handler was removed, FALSE otherwise
 */
-(BOOL) removeSessionHandler: (id<ISessionHandler>) handler;

/**
 * Remove all session handlers
 */
-(int) removeAllSessionhandlers;

/**
 * Get whether the given ISessionHandler is contained in the list
 * of handlers that are notified of session events (open, close, etc.).
 * @param handler The handler to check for
 * @return TRUE if the handler is in the list of IDBLUeSessionDelegaets, 
 * FALSE otherwise.
 */
-(BOOL) hasSessionhandler: (id<ISessionHandler>) handler;

/**
 *
 */
-(id<ISessionHandler>) handlerAtIndex: (int) index;

@end
