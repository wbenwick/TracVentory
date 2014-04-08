
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * ISessionHandler is a protocol that is used by IDBlueSession
 * to notify callers that an IDBLUE session has been opened or closed.
 */
@protocol ISessionHandler <NSObject>

/**
 * onOpened is called after the session is opened
 */
-(void) onSessionOpened: (id) session;

/**
 * onClosed is called after a session is closed
 */
-(void) onSessionClosed: (id) session;

@optional
/**
 * onOpening is called when the session is opening, but not yet opened
 */
-(void) onSessionOpening: (id) session;

/**
 * onOpenFailed is called when a session fails to open
 */
-(void) onSessionOpenFailed: (id) session;

/**
 * onClosing is called when a session is closing, but before 
 * the session is closed
 */
-(void) onSessionClosing: (id) session;

/**
 * onCloseFailed is called when a session fails to close
 */
-(void) onSessionCloseFailed: (id) session;

/**
 * onIDBlueDeviceAdded is called when an IDBLUE device is added to the list
 * of availabe IDBLUE devices (e.g. when an IDBLUE device is paired with 
 * an iPhone).
 * @param device The IDBLUE device that was added
 */
-(void) onIDBlueDeviceAdded: (id) device;

/**
 * onIDBlueDeviceRemoved is called when an IDBLUE device is removed from the 
 * list of available IDBLUE devices (e.g. when an IDBLUE device is unpaired
 * with an iPhone).
 * @param device The IDBLUE device that was removed
 */
-(void) onIDBlueDeviceRemoved: (id) device;
@end
