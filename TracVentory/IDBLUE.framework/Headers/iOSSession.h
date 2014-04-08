
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueSession.h"
#import <ExternalAccessory/ExternalAccessory.h>
#import <ExternalAccessory/EASession.h>
#import "ObjectCollection.h"

/**
 *  iOSSession implements IDBlueSession, that manages searching for and
 *  connecting to IDBLUE devices using the EAAccessory Framework.
 */
@interface iOSSession : IDBlueSession <NSStreamDelegate> {
@private
	// The current IDBLUE device
	EAAccessory* _accessory;
	
	// The current session to the IDBLUE device
	EASession* _session;
	
@private
	BOOL _inputStreamOpen;
	BOOL _outputStreamOpen;
}

/**
 * Sets the current IDBLUE device
 * @param device The EAAccessory object of the IDBLUE device to connect to.
 * @return Whether the set device was successful
 * @remarks Use getDevices to get the list of IDBLUE devices that are
 * paired with the iPhone.
 */
-(BOOL) setDevice: (EAAccessory*) device;

/**
 * Callback method that is invoked when an EAAccessory is connected 
 * to the iPhone.
 */
-(void) eaAccessoryDidConnectNotification:(NSNotification*) notification;

/**
 * Callback method that is invoked whne an EAAccessory is disconnected
 * from the iPHone.
 */
-(void) eaAccessoryDidDisconnectNotification:(NSNotification*) notification;

/**
 * Read all bytes available in the input stream
 * @param input The stream to read from
 * @param flush Wheter to flush the data (i.e. don't process it), or process it as 
 * a response from IDBLUE.
 * @return The number of bytes read
 */
-(unsigned int) readIncomingData: (NSInputStream*) input withFlush: (BOOL) flush;

/**
 * Get the current IDBLUE device
 * @return The EAAccessory representing the current IDBLUE device
 */
-(EAAccessory*) getDevice;

/**
 * Gets an array of EAAccerrory objects representing IDBLUE devices connected to the
 * iPhone.
 * @return an NSArray containing EAAccessory objects
 * @remarks Only IDBLUE devices that are connected to the iPhone are returned.
 * You must manually connect the IDBLUE device (via Settings->General->Bluetooth
 * on the iPhone) before calling getDevices.
 */
+(ObjectCollection*) getDevices;

/**
 * Open a session to the first IDBLUE device found using getFirstIDBlueDevice
 * @return TRUE if the device was set and a session was opened, FALSE otherwise
 */
-(BOOL) openFirstIDBlueDevice;

/**
 * Get the first IDBLUE device from the list of connected EAAccessories.
 * @return The first EAAccessory that is an IDBLUE device from the 
 * list returned from getDevices if an IDBLUE device exists, nil otherwise.
 */
+(EAAccessory*) getFirstIDBlueDevice;

/**
 * Get whether an EAAccessory is an IDBLUE device or not.
 * @return TRUE if the accessory is an IDBLUE device, false otherwise
 */
+(BOOL) isIDBlueDevice: (EAAccessory*) accessory;
@end
