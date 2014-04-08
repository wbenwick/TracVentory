
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlue.h"
#import "SessionHandler.h"
#import "IDataHandler.h"
#import "CByteArray.h"
#import "SessionHandlerCollection.h"
#import "ObjectCollection.h"

/**
 *  IDBlueSession is the base class for all sessions to an 
 *  IDBLUE device (IDBLUE supports Bluetooth and USB sessions).
 */
@interface IDBlueSession : NSObject <ISessionHandler> {
    
@protected
	// Array of handlers that will be notified when incoming data is received 
	ObjectCollection* _dataHandlers;
	
	// Array of handlers that will be notified of connect / disconnect notifications	
	SessionHandlerCollection* _sessionHandlers;
	
	// Whether the IDBlueSession is open
	BOOL _sessionOpen;
    
    // the current IDBLUE device
    NSObject* _idblueDevice;
    
    // Array of pending commands to be sent to IDBLUE
	ObjectCollection* _queuedCommands;
}

/**
 * Send any queued commands to IDBLUE, stopping when no space is available in the output buffer
 * @return The number of commands sent to IDBLUE.
 */
-(int) sendQueuedCommands;

/**
 * Send data directly to IDBLUE, not queuing the data. This should be called when space becomes
 * available in the output buffer.
 */
-(int) sendData: (CByteArray*) data;

/**
 * Get whether there is any space remaning in the output buffer
 */
-(BOOL) hasSpaceInOutputBuffer;

/**
 * Get wheter the output stream is available for writing
 */
-(BOOL) outputStreamAvailable;

/**
 * This method should be called by subclasses of IDBlueSession when space is available in the
 * output buffer. Calling this method will send queued commands to IDBLUE
 */
-(void) onSpaceAvailableInOutputBuffer;

/**
 * Get the current IDBLUE device
 */
-(NSObject*) idblueDevice;

/**
 * Set the current IDBLUE device
 */
-(void) setIDBlueDevice: (NSObject*) device;

/**
 * Send data to an IDBLUE device, or queues the data if there is no space available in the output buffer
 * @param data Byte array to send to IDBLUE
 * @return The number of bytes sent
 */
-(int) write: (CByteArray*) data;

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
 * Removes all session handlers from receiving notifications
 * @return The number of handlers removed
 */
-(int) removeAllSessionHandlers;

/**
 * Get whether the given ISessionHandler is contained in the list
 * of handlers that are notified of session events (open, close, etc.).
 * @param handler The handler to check for
 * @return TRUE if the handler is in the list of IDBLUeSessionDelegaets, 
 * FALSE otherwise.
 */
-(BOOL) hasSessionHandler: (id<ISessionHandler>) handler;

/**
 * Gets the collection of Session handlers
 */
-(SessionHandlerCollection*) sessionHandlers;

/**
 * Adds a DataReceivedhandler to be notified when data is received
 * from an IDBLUE device.
 * @param handler The DataReceivedhandler to receive notifications
 * when data is received.
 * @return TRUE if the handler was added, FALSE otherwise
 */
-(BOOL) addDataHandler: (id<IDataHandler>) handler;

/**
 * Remove the DataReceivedhandler from the list of handlers that are
 * notified when data is received from an IDBLUE device
 * @param handler The DataReceivedhandler to remove
 * @return TRUE if the handler was removed, FALSE otherwise
 */
-(BOOL) removeDataHandler: (id<IDataHandler>) handler;

/**
 * Remove all DataReceivedhandlers from receiving notifications
 * @return The number of handlers removed
 */
-(int) removeAllDataHandlers;

/**
 * Get whether the given DataReceivedhandler object is registered
 * @param handler The DataReceivedhandler to check for
 * @return TRUE if the handler was found, FALSE otherwise
 */
-(BOOL) hasDataHandler: (id<IDataHandler>) handler;

/**
 * Gets the collection of DataReceivedhandlers
 */
-(ObjectCollection*) dataHandlers;

/**
 * onDataReceived should be called from within classes deriving from
 * IDBlueSession when incoming data is received from an IDBLUE device.
 * onDataReceived forwards incoming data into the current IDBlueCommandSender object
 * of the IDBlueSession.
 * @param data The byte array containing the data received from IDBLUE
 * @param len The number of bytes in the data array.
 */
-(void) onDataReceived: (byte*) data withLen: (size_t) len;

/**
 * Gets if the current IDBlueSession is open
 * @return TRUE if open, FALSE otherwise
 */
-(BOOL) isOpen;

/**
 * Open a session to the attached IDBLUE device
 * @return TRUE if the session was started, FALSE otherwise.
 * @remarks This method is asynchronous. When the session is fully
 * established to an IDBLUE device, the opened notification will
 * be invoked on the session handler.
 */
-(BOOL) open;

/**
 * Close the session to the attached IDBLUE device
 * @return TRUE if the close was started, FALSE otherwise.
 * @remarks This method is asynchronous. When the session to the IDBLUE device
 * is fully closed, the closed notification will
 * be invoked on the session handler.
 */
-(BOOL) close;

/**
 * Notifies all ISessionHandlers that the session has been opened
 */
-(void) onOpened;

/**
 * Notifies all ISessionHandlers that the session is opening
 */
-(void) onOpening;

/**
 * Notifies all ISessionHandlers that opening the session has failed
 */
-(void) onOpenFailed;

/**
 * Notifies all ISessionHandlers that the session has been closed
 */
-(void) onClosed;

/**
 * Notifies all ISessionHandlers that the session is closing
 */
-(void) onClosing;

/**
 * Notifies all ISessionHandlers that the close session has failed
 */
-(void) onCloseFailed;

/**
 * Notifies all ISessionHandlers that an IDBLUE device is available
 * @param device The IDBLUE device that was added
 */
-(void) onIDBlueDeviceAdded: (id) device;

/**
 * Notifies all ISessionHandlers that an IDBLUE device was removed
 * @param device The IDBLUE device that was removed
 */
-(void) onIDBlueDeviceRemoved: (id) device;

@end
