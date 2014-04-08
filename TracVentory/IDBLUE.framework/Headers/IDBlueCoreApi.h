
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueSession.h"
#import "SessionHandler.h"
#import "ResponseHandler.h"
#import "IDBlueResponseProcessor.h"
#import "CommandQueue.h"
#import "PacketQueue.h"
#import "ObjectCollection.h"
#import "SessionHandlerCollection.h"
#import "CommandQueue.h"
#import "GetPropertyClassInfo.h"

/** The current version number of the IDBLUE (iOS / OSX) SDK */
#define IDBLUE_SDK_VERSION_NUMBER @"0.7"

/** 
 *  IDBlueCoreApi is the subset of functionality common to both HF and UHF.
 */
@interface IDBlueCoreApi : ResponseHandler <ISessionHandler> {
@private
	// The IDBlueSession object that can establish a communication channel 
	// with an IDBLUE device, and send and receive (binary) data.
	IDBlueSession* _session;
	
	// The IDBlueResponseProcessor is used to form IDBlueResponses out of data
	// received from IDBLUE via the IDBlueSession object. When responses are 
	// received, the IDBlueResposneProcessor notifies all registered ResponseHandleres
	// of the response.
	IDBlueResponseProcessor* _processor;
	
	// The list of IDBlueCommands that have been sent to IDBLUE that are awaiting
	// responses from IDBLUE.
	CommandQueue* _commandQueue;
	
	// The byte array that will receive the incoming data from IDBLUE, that is used
	// by the IDBlueResponseProcessor.
	PacketQueue* _receiveBuffer;
    
    // Whether the event handlers for the current IDBlueCoreApi have been hooked up or not.
    BOOL _enabled;
    
    // Temporary collection of data eeceived handlers that is used during firmware updating
	ObjectCollection* _dataHandlers;
	
    // Temporary collection of session delegats that is used during firmware updating
	SessionHandlerCollection* _sessionHandlers;
    
    // The asynchronous response callback method
	ResponseHandlerCollection* _responseHandlers;
    
    // PropertyGenerator is used to create IDBlueProperty objects from incoming IDBluePackets
    PropertyGenerator* _propertyGenerator;
    
    // ResponseFactory is used to create IDBlueResponses from incoming IDBluePackets
    ResponseFactory* _responseFactory;
    
    // GetPropertyClassInfo is used to dynamically create IDBlueProperty responses
    GetPropertyClassInfo* _supportedProperties;
    
    // The number of commands sent to IDBLUE
	int _commandsSent;
}

/**
 * Get the version of the IDBLUE SDK
 * @return An NSString containing the IDBLUE SDK Version
 */
-(NSString*) sdkVersion;

/**
 * Initialize the IDBlueCoreApi with the given IDBlueSession
 * @param session The IDBlueSession to use to communicate with an IDBLUE device
 */
-(id) initWithSession: (IDBlueSession*) session;

/**
 * Gets the current IDBlueSession
 */
-(IDBlueSession*) session;

/**
 * Adds the given IResponseHandler to listen for responses
 * from an IDBLUE device.
 * @param handler The IResponseHandler to receive response notifications
 */
-(void) addResponseHandler: (id<IResponseHandler>) handler;

/**
 * Remove the given IResponseHandler from receiving response notifications
 * from IDBLUE devices.
 * @param handler The IResponseHandler to remove 
 */
-(void) removeResponseHandler: (id<IResponseHandler>) handler;

/**
 * Adds the given ISessionHandler to receive notifications of session
 * events (open / close,  lost / restored, etc).
 * @param handler The ISessionHandler to receive session events
 */
-(void) addSessionHandler: (id<ISessionHandler>) handler;

/**
 * Removes the given ISessionHandler from receiving notifications of
 * session events.
 * @param handler The ISessionHandler to remove from receiving 
 * session events
 */
-(void) removeSessionHandler: (id<ISessionHandler>) handler;

/**
 * Determines if the given IResponseHandler is contained in the list of
 * handlers that are notified of responses received from an IDBLUE device.
 */
-(BOOL) hasResponseHandler: (id<IResponseHandler>) handler;

/**
 * Get whether the current IDBlueSession is open.
 * @return TRUE if the communication channel is open.
 */
-(BOOL) isSessionOpen;

/**
 * Open a session to the current IDBLUE device. You must use one of the platform
 * specific setDevice methods before calling openSession.
 * @return TRUE if the session open was started, FALSE otherwise.
 */
-(BOOL) openSession;

/**
 * Close the current IDBlueSession
 * @return TRUE if the session close was started, FALSE otherwise
 */
-(BOOL) closeSession;

/**
 * Disable the current IDBlueCoreApi
 * @return TRUE if the IDBlueCoreApi was disabled, false otherwise
 */
-(BOOL) disable;


/**
 * Enable the current IDBlueCoreApi
 * @return TRUE if the IDBlueCoreApi was enabled, false otherwise
 */
-(BOOL) enable;

/**
 * Get whether the current IDBlueCoreApi is enabled
 * @return TRUE if the IDBlueCoreApi is enabled, false otherwise
 */
-(BOOL) enabled;

/**
 *
 * @remarks Internal method of IDBlueCoreApi. Do not call externally.
 */
-(BOOL) addSupportedCommand: (CommandIdentifier) commandIdentifier 
              withClassInfo: (Class) classInfo;

/**
 *
 * @remarks Internal method of IDBlueCoreApi. Do not call externally.
 */
-(BOOL) addSupportedProperty: (PropertyIdentifier) property 
               withClassInfo: (Class) classInfo;

/**
 *
 * @remarks Internal method of IDBlueCoreApi. Do not call externally.
 */
-(SendStatus*) getProperty: (PropertyIdentifier) property 
			   withHandler: (id<IResponseHandler>) handler;

/**
 *
 * @remarks Internal method of IDBlueCoreApi. Do not call externally.
 */
-(SendStatus*) setProperty: (id<IResponseHandler>) handler
				   withProperty: (PropertyIdentifier) property 
                       withArgs: (void*) args;

/**
 * sendCommand - 
 *
 * Sends a command to the connected IDBLUE device. When a response is received,
 * the command's callback method will be invoked.
 *
 * @param command the command to be sent to IDBLUE
 * @param handler An object implementing IResponseHandler
 *
 * The callback method defined by handler/selector will be called when a 
 * response is received from IDBLUE. The parameter will be an IDBlueCommand 
 * object containing an IDBlueResponse
 * 
 * @return TRUE if the data was buffered successfully, FALSE otherwise.
 * @remarks If sendCommand fails, no data is sent. This method should not
 * be used - instead use one of the specific commands (e.g. noOp).
 */
-(SendStatus*) sendCommand: (IDBlueCommand*) command 
				   withHandler: (id<IResponseHandler>) handler;

/**
 * noOp -
 *
 * Sends a NO-OP command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) noOp {
 *     SendStatus status = nil;
 *     status = [api noOp: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) noOpResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) noOpFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) noOp: (id<IResponseHandler>) handler;

/**
 * noOp -
 *
 * Sends a NO-OP command to IDBLUE. 
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) noOp {
 *     SendStatus status = nil;
 *     status = [api noOp];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) noOpResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) noOpFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) noOp;

/**
 * beginCommands - 
 *
 * Sends a BEGIN-COMMANDS command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 *
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) beginCommands {
 *     SendStatus status = nil;
 *     status = [api beginCommands: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) beginCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) beginCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks BEGIN-COMMANDS causes the front LED of IDBLUE to light up, 
 * indicating that a command is being executed. Send a END-COMMANDS to turn 
 * off the LED, and provide a success / failure notification to the user.
 */
-(SendStatus*) beginCommands: (id<IResponseHandler>) handler;

/**
 * beginCommands - 
 *
 * Sends a BEGIN-COMMANDS command to IDBLUE
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) beginCommands {
 *     SendStatus status = nil;
 *     status = [api beginCommands];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) beginCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) beginCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks BEGIN-COMMANDS causes the front LED of IDBLUE to light up, 
 * indicating that a command is being executed. Send a END-COMMANDS to turn 
 * off the LED, and provide a success / failure notification to the user.
 */
-(SendStatus*) beginCommands;

/**
 * endCommands - 
 *
 * Sends a END-COMMANDS command to IDBLUE
 *
 * @param success Whether to indicate success or failure
 * @param handler An object implementing IResponseHandler that will receive response notifications.
 *
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) endCommands: (BOOL) success {
 *     SendStatus status = nil;
 *     status = [api endCommands: success
 *                        withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) endCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) endCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 *
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks END-COMMANDS is used to turn off the front LED of IDBLUE (turned 
 * on with BEGIN-COMMANDS) and to provide success / failure feedback to the user.
 */
-(SendStatus*) endCommands: (BOOL) success 
				   withHandler: (id<IResponseHandler>) handler;

/**
 * endCommands - 
 *
 * Sends a END-COMMANDS command to IDBLUE
 *
 * @param success Whether to indicate success or failure
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) endCommands: (BOOL) success {
 *     SendStatus status = nil;
 *     status = [api endCommands: success
 *                        withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) endCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) endCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 *
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks END-COMMANDS is used to turn off the front LED of IDBLUE (turned 
 * on with BEGIN-COMMANDS) and to provide success / failure feedback to the user.
 */
-(SendStatus*) endCommands: (BOOL) success;

/**
 * beep -
 *
 * Sends a BEEP command to IDBLUE
 *
 * @param bt The BeepType for the beep to be emitted.
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 *
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) beep: (BeepType) bt {
 *     SendStatus status = nil;
 *     status = [api beep: bt
 *                 withHandler: self)];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) beepResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) beepFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks - BEEP causes IDBLUE to emit one of several beeps from it's 
 * onboard buzzer. Beeps are used to provide feedback to the user (e.g. connected, 
 * disconnected, tag scans, etc.).
 */
-(SendStatus*) beep: (BeepType) bt 
			withHandler: (id<IResponseHandler>) handler;

/**
 * beep -
 *
 * Sends a BEEP command to IDBLUE
 *
 * @param bt The BeepType for the beep to be emitted.
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) beep: (BeepType) bt {
 *     SendStatus status = nil;
 *     status = [api beep: bt];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) beepResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) beepFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks - BEEP causes IDBLUE to emit one of several beeps from it's 
 * onboard buzzer. Beeps are used to provide feedback to the user (e.g. connected, 
 * disconnected, tag scans, etc.).
 */
			
-(SendStatus*) beep: (BeepType) bt;

/**
 * clearEntries - 
 *
 * Sends a CLEAR-ENTRIES command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 *
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) clearEntries {
 *     SendStatus status = nil;
 *     status = [api clearEntries: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) clearEntriesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) clearEntriesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CLEAR-ENTRIES erases all stored tags from
 * onboard memory.
 */
-(SendStatus*) clearEntries: (id<IResponseHandler>) handler;

/**
 * clearEntries - 
 *
 * Sends a CLEAR-ENTRIES command to IDBLUE
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) clearEntries {
 *     SendStatus status = nil;
 *     status = [api clearEntries];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) clearEntriesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) clearEntriesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CLEAR-ENTRIES erases all stored tags from
 * onboard memory.
 */
-(SendStatus*) clearEntries;

/**
 * factoryReset - 
 *
 * Sends a FACTORY-RESET command to IDBLUE
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) factoryReset {
 *     SendStatus status = nil;
 *     status = [api factoryReset];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks FACTORY-RESET is used to reset all settings of IDBLUE back to the
 * factory defaults. All stored tags will be cleared, and all settings will be 
 * set to their defaults. Any sessions to a host will be terminated, so the
 * FACTORY-RESET command will not receive a response from IDBLUE.
 */
-(SendStatus*) factoryReset;

/**
 * powerDown - 
 *
 * Sends a POWER-DOWN command to IDBLUE
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) powerDown {
 *     SendStatus status = nil;
 *     status = [api powerDown];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks POWER-DOWN turns off IDBLUE. Since the session to the host is 
 * severed, no response will be sent back to the host from IDBLUE.
 */
-(SendStatus*) powerDown;

/**
 * saveProperties - 
 *
 * Sends a SAVE-PROPERTIES command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) saveProperties {
 *     SendStatus status = nil;
 *     status = [api saveProperties: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) savePropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) savePropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * } 
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks SAVE-PROPERTIES causes any changes to IDBLUE settings to be 
 * persisted to onboard memory. SAVE-PROPERTIES should be called after making
 * changes to IDBLUE that need to be saved before powering off - otherwise, the
 * changes will be lost.
 */
-(SendStatus*) saveProperties: (id<IResponseHandler>) handler;

/**
 * saveProperties - 
 *
 * Sends a SAVE-PROPERTIES command to IDBLUE
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) saveProperties {
 *     SendStatus status = nil;
 *     status = [api saveProperties: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) savePropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) savePropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * } 
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks SAVE-PROPERTIES causes any changes to IDBLUE settings to be 
 * persisted to onboard memory. SAVE-PROPERTIES should be called after making
 * changes to IDBLUE that need to be saved before powering off - otherwise, the
 * changes will be lost.
 */
-(SendStatus*) saveProperties;

/**
 * loadProperties - 
 *
 * Sends a LOAD-PROPERTIES command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) loadProperties {
 *     SendStatus status = nil;
 *     status = [api loadProperties: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) loadPropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) loadPropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks LOAD-PROPERTIES loads the last saved settings from onboard memory. 
 * Any changes to settings that have not been saved will be lost.
 */
-(SendStatus*) loadProperties: (id<IResponseHandler>) handler;

/**
 * loadProperties - 
 *
 * Sends a LOAD-PROPERTIES command to IDBLUE
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) loadProperties {
 *     SendStatus status = nil;
 *     status = [api loadProperties];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) loadPropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) loadPropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks LOAD-PROPERTIES loads the last saved settings from onboard memory. 
 * Any changes to settings that have not been saved will be lost.
 */
-(SendStatus*) loadProperties;

/**
 * turnOffBluetooth - 
 *
 * Sends a TURN-OFF-BLUETOOTH command to IDBLUE
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) turnOffBluetooth {
 *     SendStatus status = nil;
 *     status = [api turnOffBluetooth];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks TURN-OFF-BLUETOOTH causes the Bluetooth module of IDBLUE to power off, 
 * causing any Bluetooth sessions to be severed - if a session is opeded to IDBLUE via 
 * Bluetooth, no response will be returned.
 */
-(SendStatus*) turnOffBluetooth;

/**
 * setScanning - 
 *
 * Sends a SET-SCANNING command to IDBLUE
 *
 * @param enable Whether set scanning is to be enabled or disabled.
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setScanning: (BOOL) enabled {
 *     SendStatus status = nil;
 *     status = [api setScanning: enabled 
 *                        withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setScanningResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setScanningFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks SET-SCANNING is a means to simulate pressing the front 
 * button of an IDBLUE device. When set scanning is enabled, IDBLUE will perform 
 * the connected mode action. If SET-SCANNING is disabled and IDBLUE is 
 * currently performing a continuous scan, the continuous scan will be terminated.
 */
-(SendStatus*) setScanning: (BOOL) enable 
				   withHandler: (id<IResponseHandler>) handler;
				   
/**
 * setScanning - 
 *
 * Sends a SET-SCANNING command to IDBLUE
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setScanning: (BOOL) enabled {
 *     SendStatus status = nil;
 *     status = [api setScanning: enabled];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setScanningResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setScanningFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks SET-SCANNING is a means to simulate pressing the front 
 * button of an IDBLUE device. When set scanning is enabled, IDBLUE will perform 
 * the connected mode action. If SET-SCANNING is disabled and IDBLUE is 
 * currently performing a continuous scan, the continuous scan will be terminated.
 */
-(SendStatus*) setScanning: (BOOL) enable;

/**
 * getEntry -
 *  
 * Sends a GET-ENTRY command to IDBLUE
 *
 * @param index An index between 0 and n-1 (n being the number of entries)
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEntry: (int) index {
 *     SendStatus status = nil;
 *     status = [api getEntry: index 
 *                     withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEntryResponse: (IDBlueCommand*) command withResponse: (GetEntryResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte data = [response blockData];
 * }
 *
 * -(void) getEntryFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-ENTRY retrieves a tag entry stored in onboard memory
 * of IDBLUE (timestamp, tag id, and a single byte of data).
 */
-(SendStatus*) getEntry: (int) index 
				withHandler: (id<IResponseHandler>) handler;
	
/**
 * getEntry -
 *  
 * Sends a GET-ENTRY command to IDBLUE
 *
 * @param index An index between 0 and n-1 (n being the number of entries)
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEntry: (int) index {
 *     SendStatus status = nil;
 *     status = [api getEntry: index];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEntryResponse: (IDBlueCommand*) command withResponse: (GetEntryResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte data = [response blockData];
 * }
 *
 * -(void) getEntryFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-ENTRY retrieves a tag entry stored in onboard memory
 * of IDBLUE (timestamp, tag id, and a single byte of data).
 */	
-(SendStatus*) getEntry: (int) index;

/**
 * getEntryCount - 
 *
 * Sends a GET-ENTRY-COUNT command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEntryCount {
 *     SendStatus status = nil;
 *     status = [api getEntryCount: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEntryCountResponse: (IDBlueCommand*) command withResponse: (GetEntryCountResponse*) response {
 *     int entryCount = [response entryCount];
 * }
 *
 * -(void) getEntryCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-ENTRY-COUNT retrieves the number of tag entries stored in on board 
 * memory of IDBLUE. Each entry can be retrieved using the GET-ENTRY command.
 */
-(SendStatus*) getEntryCount: (id<IResponseHandler>) handler;

/**
 * getEntryCount - 
 *
 * Sends a GET-ENTRY-COUNT command to IDBLUE
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEntryCount {
 *     SendStatus status = nil;
 *     status = [api getEntryCount];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEntryCountResponse: (IDBlueCommand*) command withResponse: (GetEntryCountResponse*) response {
 *     int entryCount = [response entryCount];
 * }
 *
 * -(void) getEntryCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-ENTRY-COUNT retrieves the number of tag entries stored in on board 
 * memory of IDBLUE. Each entry can be retrieved using the GET-ENTRY command.
 */
-(SendStatus*) getEntryCount;

/**
 * getBluetoothName - 
 *
 * Sends a GET-BLUETOOTH-NAME command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBluetoothName {
 *     SendStatus status = nil;
 *     status = [api getBluetoothName: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBluetoothNameResponse: (IDBlueCommand*) command withResponse: (GetBluetoothNameResponse*) response {
 *     NSString* btName = [response bluetoothName];
 * }
 * 
 * -(void) getBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-BLUETOOTH-NAME is used to get the name of the IDBLUE device that 
 * will be found during a Bluetooth discovery.
 */
-(SendStatus*) getBluetoothName: (id<IResponseHandler>) handler;

/**
 * getBluetoothName - 
 *
 * Sends a GET-BLUETOOTH-NAME command to IDBLUE
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBluetoothName {
 *     SendStatus status = nil;
 *     status = [api getBluetoothName];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBluetoothNameResponse: (IDBlueCommand*) command withResponse: (GetBluetoothNameResponse*) response {
 *     NSString* btName = [response bluetoothName];
 * }
 * 
 * -(void) getBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-BLUETOOTH-NAME is used to get the name of the IDBLUE device that 
 * will be found during a Bluetooth discovery.
 */
-(SendStatus*) getBluetoothName;

/**
 * getStatus - 
 * 
 * Sends a GET-STATUS command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *  
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     status = [api getStatus: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getStatusResponse: (IDBlueCommand*) command withResponse: (GetStatusResponse*) response {
 *     byte batteryLevel = [response batteryLevel];
 *     NSString* hardwareVersion = [response hardwareVersion];
 *     NSString* firmwareVersion = [response firmwareVersion];
 * }
 *
 * -(void) getStatusFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-STATUS is used to get the battery level, hardware & firmware 
 * versions of IDBLUE.
 */
-(SendStatus*) getStatus: (id<IResponseHandler>) handler;

/**
 * getStatus - 
 * 
 * Sends a GET-STATUS command to IDBLUE
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *  
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     status = [api getStatus];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getStatusResponse: (IDBlueCommand*) command withResponse: (GetStatusResponse*) response {
 *     byte batteryLevel = [response batteryLevel];
 *     NSString* hardwareVersion = [response hardwareVersion];
 *     NSString* firmwareVersion = [response firmwareVersion];
 * }
 *
 * -(void) getStatusFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-STATUS is used to get the battery level, hardware & firmware 
 * versions of IDBLUE.
 */
-(SendStatus*) getStatus;

/**
 * readTagId - 
 *
 * Sends a GET-TAG-ID command to IDBLUE
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     status = [api readTagId: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) readTagIdResponse: (IDBlueCommand*) command withResponse: (ReadTagIdResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 * }
 *
 * -(void) readTagIdFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-TAG-ID causes IDBLUE to retrieve the ID of the first RFID 
 * tag in the read field.
 */
-(SendStatus*) readTagId: (id<IResponseHandler>) handler;

/**
 * readTagId - 
 *
 * Sends a GET-TAG-ID command to IDBLUE
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 * 
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     status = [api readTagId];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) readTagIdResponse: (IDBlueCommand*) command withResponse: (ReadTagIdResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 * }
 *
 * -(void) readTagIdFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks GET-TAG-ID causes IDBLUE to retrieve the ID of the first RFID 
 * tag in the read field.
 */
-(SendStatus*) readTagId;

/**
 * setBluetoothName - 
 *
 * Sends a STORE-BLUETOOTH-NAME command to IDBLUE
 *
 * @param btName
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBtName {
 *     SendStatus status = nil;
 *     status = [api setBluetoothName: @"My IDBLUE Device" 
 *                      withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothNameResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBluetoothName: (NSString*) btName 
				 withHandler: (id<IResponseHandler>) handler;

/**
 * setBluetoothName - 
 *
 * Sends a STORE-BLUETOOTH-NAME command to IDBLUE
 *
 * @param btName
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBtName {
 *     SendStatus status = nil;
 *     status = [api setBluetoothName: @"My IDBLUE Device"];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothNameResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBluetoothName: btName;
				 
/**
 * setBluetoothPin - 
 *
 * Sends a STORE-BLUETOOTH-PIN command to IDBLUE
 *
 * @param pin
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBtPin {
 *     SendStatus status = nil;
 *     status = [api setBluetoothPin: @"1234" 
 *                     withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothPinResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothPinFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBluetoothPin: (NSString*) pin 
				withHandler: (id<IResponseHandler>) handler;

/**
 * setBluetoothPin - 
 *
 * Sends a STORE-BLUETOOTH-PIN command to IDBLUE
 *
 * @param pin
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBtPin {
 *     SendStatus status = nil;
 *     status = [api setBluetoothPin: @"1234"];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothPinResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothPinFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBluetoothPin: (NSString*) pin;
				
/**
 * getTimestamp - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Timestamp property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getTimestamp {
 *     SendStatus status = nil;
 *     status = [api getTimestamp: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getTimestampResponse: (IDBlueCommand*) command withResponse: (TimestampProperty*) response;
 *     IDBlueTimestamp* ts = [response idblueTimestamp];
 * }
 *
 * -(void) getTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getTimestamp: (id<IResponseHandler>) handler;

/**
 * getTimestamp - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Timestamp property
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getTimestamp {
 *     SendStatus status = nil;
 *     status = [api getTimestamp];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getTimestampResponse: (IDBlueCommand*) command withResponse: (TimestampProperty*) response;
 *     IDBlueTimestamp* ts = [response idblueTimestamp];
 * }
 *
 * -(void) getTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getTimestamp;

/**
 * getDuplicateElimination - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Duplicate Elimination 
 * property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDupElim {
 *     SendStatus status = nil;
 *     status = [api getDuplicateElimination: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (DuplicateEliminationProperty*) response {
 *     ushort dupElim = [response duplicateElimination];
 * }
 *
 * -(void) getDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDuplicateElimination: (id<IResponseHandler>) handler;

/**
 * getDuplicateElimination - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Duplicate Elimination 
 * property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDupElim {
 *     SendStatus status = nil;
 *     status = [api getDuplicateElimination];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (DuplicateEliminationProperty*) response {
 *     ushort dupElim = [response duplicateElimination];
 * }
 *
 * -(void) getDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDuplicateElimination;

/**
 * getRfidTimeout - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the RFID timeout property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getRfidTimeout {
 *     SendStatus status = nil;
 *     status = [api getRfidTimeout: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (RfidTimeoutProperty*) response {
 *     byte timeout = [response rfidTimeout];
 * }
 *
 * -(void) getRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getRfidTimeout: (id<IResponseHandler>) handler;

/**
 * getRfidTimeout - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the RFID timeout property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getRfidTimeout {
 *     SendStatus status = nil;
 *     status = [api getRfidTimeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (RfidTimeoutProperty*) response {
 *     byte timeout = [response rfidTimeout];
 * }
 *
 * -(void) getRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getRfidTimeout;

/**
 * getBluetoothTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Bluetooth Timeout property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBluetoothTimeout {
 *     SendStatus status = nil;
 *     status = [api getBluetoothTimeout: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (BluetoothTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 *
 * -(void) getBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBluetoothTimeout: (id<IResponseHandler>) handler;

/**
 * getBluetoothTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Bluetooth Timeout property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBluetoothTimeout {
 *     SendStatus status = nil;
 *     status = [api getBluetoothTimeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (BluetoothTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 *
 * -(void) getBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */

-(SendStatus*) getBluetoothTimeout;

/**
 * getConnectToHost - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Connect to Host 
 * property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getConnectToHost {
 *     SendStatus status = nil;
 *     status = [api getConnectToHost: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getConnectToHostResponse: (IDBlueCommand*) command withResponse: (ConnectToHostProperty*) response {
 *     BOOL connectToHost = [response connectToHost];
 * }
 *
 * -(void) getConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getConnectToHost: (id<IResponseHandler>) handler;

/**
 * getConnectToHost - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Connect to Host 
 * property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getConnectToHost {
 *     SendStatus status = nil;
 *     status = [api getConnectToHost];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getConnectToHostResponse: (IDBlueCommand*) command withResponse: (ConnectToHostProperty*) response {
 *     BOOL connectToHost = [response connectToHost];
 * }
 *
 * -(void) getConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getConnectToHost;

/**
 * getActionButtonEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Action Button Enabled 
 * property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getActionButtonEnabled {
 *     SendStatus status = nil;
 *     status = [api getActionButtonEnabled: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (ActionButtonEnabledProperty*) response {
 *     BOOL actionButtonEnabled = [response actionButtonEnabled];
 * }
 *
 * -(void) getActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getActionButtonEnabled: (id<IResponseHandler>) handler;

/**
 * getActionButtonEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Action Button Enabled 
 * property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getActionButtonEnabled {
 *     SendStatus status = nil;
 *     status = [api getActionButtonEnabled];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (ActionButtonEnabledProperty*) response {
 *     BOOL actionButtonEnabled = [response actionButtonEnabled];
 * }
 *
 * -(void) getActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */

-(SendStatus*) getActionButtonEnabled;

/**
 * getContinuousScanTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Continuous Scan Timeout 
 * property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getContinuousScanTimeout {
 *     SendStatus status = nil;
 *     status = [api getContinuousScanTimeout: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (ContinuousScanTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 *
 * -(void) getContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getContinuousScanTimeout: (id<IResponseHandler>) handler;

/**
 * getContinuousScanTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Continuous Scan Timeout 
 * property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getContinuousScanTimeout {
 *     SendStatus status = nil;
 *     status = [api getContinuousScanTimeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (ContinuousScanTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 *
 * -(void) getContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getContinuousScanTimeout;

/**
 * getDeviceTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Device Timeout property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDeviceTimeout {
 *     SendStatus status = nil;
 *     status = [api getDeviceTimeout: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (DeviceTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 * 
 * -(void) getDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDeviceTimeout: (id<IResponseHandler>) handler;

/**
 * getDeviceTimeout - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Device Timeout property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDeviceTimeout {
 *     SendStatus status = nil;
 *     status = [api getDeviceTimeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (DeviceTimeoutProperty*) response {
 *     byte timeout = [response timeout];
 * }
 * 
 * -(void) getDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDeviceTimeout;

/**
 * getHoldToScan - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Hold to Scan property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getHoldToScanEnabled {
 *     SendStatus status = nil;
 *     status = [api getHoldToScan: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getHoldToScanResponse: (IDBlueCommand*) command withResponse: (HoldToScanEnabledProperty*) response {
 *     BOOL enabled = [response holdToScanEnabled];
 * }
 *
 * -(void) getHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getHoldToScan: (id<IResponseHandler>) handler;

/**
 * getHoldToScan - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Hold to Scan property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getHoldToScanEnabled {
 *     SendStatus status = nil;
 *     status = [api getHoldToScan];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getHoldToScanResponse: (IDBlueCommand*) command withResponse: (HoldToScanEnabledProperty*) response {
 *     BOOL enabled = [response holdToScanEnabled];
 * }
 *
 * -(void) getHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getHoldToScan;

/**
 * getBuzzerEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Buzzer Enabled property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBuzzerEnabled {
 *     SendStatus status = nil;
 *     status = [api getBuzzerEnabled: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (BuzzerEnabledProperty*) response {
 *     BOOL enabled = [response buzzerEnabled];
 * }
 *
 * -(void) getBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBuzzerEnabled: (id<IResponseHandler>) handler;

/**
 * getBuzzerEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Buzzer Enabled property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBuzzerEnabled {
 *     SendStatus status = nil;
 *     status = [api getBuzzerEnabled];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (BuzzerEnabledProperty*) response {
 *     BOOL enabled = [response buzzerEnabled];
 * }
 *
 * -(void) getBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBuzzerEnabled;

/**
 * getContinuousScanEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Continuous Scan Eanbled 
 * property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getContinuousScanEnabled {
 *     SendStatus status = nil;
 *     status = [api getContinuousScanEnabled: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (ContinuousScanEnabledProperty*) response {
 *     BOOL enabled = [response continuousScanEnabled];
 * }
 *
 * -(void) getContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getContinuousScanEnabled: (id<IResponseHandler>) handler;

/**
 * getContinuousScanEnabled - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Continuous Scan Eanbled 
 * property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getContinuousScanEnabled {
 *     SendStatus status = nil;
 *     status = [api getContinuousScanEnabled];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (ContinuousScanEnabledProperty*) response {
 *     BOOL enabled = [response continuousScanEnabled];
 * }
 *
 * -(void) getContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getContinuousScanEnabled;

/**
 * getEnforceTimestamp - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Enforce Timestamp property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEnforceTimestamp {
 *     SendStatus status = nil;
 *     status = [api getEnforceTimestamp: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (EnforceTimestampProperty*) response {
 *     BOOL enforce = [response enforceTimestamp];
 * }
 * 
 * -(void) getEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getEnforceTimestamp: (id<IResponseHandler>) handler;

/**
 * getEnforceTimestamp - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Enforce Timestamp property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getEnforceTimestamp {
 *     SendStatus status = nil;
 *     status = [api getEnforceTimestamp];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (EnforceTimestampProperty*) response {
 *     BOOL enforce = [response enforceTimestamp];
 * }
 * 
 * -(void) getEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */

-(SendStatus*) getEnforceTimestamp;

/**
 * getConnectedMode - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Connected Mode property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getConnectedMode {
 *     SendStatus status = nil;
 *     status = [api getConnectedMode: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getConnectedModeResponse: (IDBlueCommand*) command withResponse: (ConnectedModeProperty*) response {
 *     ConnectedMode mode = [response connectedMode];
 * }
 *
 * -(void) getConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getConnectedMode: (id<IResponseHandler>) handler;

/**
 * getConnectedMode - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Connected Mode property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getConnectedMode {
 *     SendStatus status = nil;
 *     status = [api getConnectedMode];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getConnectedModeResponse: (IDBlueCommand*) command withResponse: (ConnectedModeProperty*) response {
 *     ConnectedMode mode = [response connectedMode];
 * }
 *
 * -(void) getConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getConnectedMode;

/**
 * getDisconnectedMode - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Disconnected Mode property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDisconnectedMode {
 *     SendStatus status = nil;
 *     status = [api getDisconnectedMode: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (DisconnectedModeProperty*) response {
 *     DisconnectedMode mode = [response disconnectedMode];
 * }
 *
 * -(void) getDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDisconnectedMode: (id<IResponseHandler>) handler;

/**
 * getDisconnectedMode - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Disconnected Mode property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getDisconnectedMode {
 *     SendStatus status = nil;
 *     status = [api getDisconnectedMode];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (DisconnectedModeProperty*) response {
 *     DisconnectedMode mode = [response disconnectedMode];
 * }
 *
 * -(void) getDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getDisconnectedMode;

/**
 * getRfidProtocol - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the RFID Protocol property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getRfidProtocol {
 *     SendStatus status = nil;
 *     status = [api getRfidProtocol: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getRfidProtocolResponse: (IDBlueCommand*) command withResponse: (RfidProtocolProperty*) response {
 *     RfidProtocol protocol = [response rfidProtocol];
 * }
 *
 * -(void) getRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getRfidProtocol: (id<IResponseHandler>) handler;

/**
 * getRfidProtocol - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the RFID Protocol property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getRfidProtocol {
 *     SendStatus status = nil;
 *     status = [api getRfidProtocol];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getRfidProtocolResponse: (IDBlueCommand*) command withResponse: (RfidProtocolProperty*) response {
 *     RfidProtocol protocol = [response rfidProtocol];
 * }
 *
 * -(void) getRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getRfidProtocol;

/**
 * getBootloaderVersion - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Bootloader Version property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBootloaderVersion {
 *     SendStatus status = nil;
 *     status = [api getBootloaderVersion: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBootloaderVersionResponse: (IDBlueCommand*) command withResponse: (BootloaderVersionProperty*) response {
 *      NSString* version = [response bootloaderVersion];
 * }
 *
 * -(void) getBootloaderVersionFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBootloaderVersion: (id<IResponseHandler>) handler;

/**
 * getBootloaderVersion - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Bootloader Version property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBootloaderVersion {
 *     SendStatus status = nil;
 *     status = [api getBootloaderVersion];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBootloaderVersionResponse: (IDBlueCommand*) command withResponse: (BootloaderVersionProperty*) response {
 *      NSString* version = [response bootloaderVersion];
 * }
 *
 * -(void) getBootloaderVersionFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */

-(SendStatus*) getBootloaderVersion;

/**
 * getVersionInfo - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Version Info property
 *
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getVersionInfo {
 *     SendStatus status = nil;
 *     status = [api getVersionInfo: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getVersionInfoResponse: (IDBlueCommand*) command withResponse: (VersionInfoProperty*) response {
 *      NSString* version = [response firmwareVersion];
 * }
 *
 * -(void) getVersionInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getVersionInfo: (id<IResponseHandler>) handler;

/**
 * getVersionInfo - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Version Info property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getVersionInfo {
 *     SendStatus status = nil;
 *     status = [api getVersionInfo];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getVersionInfoResponse: (IDBlueCommand*) command withResponse: (VersionInfoProperty*) response {
 *      NSString* version = [response firmwareVersion];
 * }
 *
 * -(void) getVersionInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getVersionInfo;

/**
 * setTimestamp - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the timestamp property
 *
 * @param timestamp
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setTimestamp {
 *     SendStatus status = nil;
 *     NSDate* now = [[NSDate alloc] init]];
 *     IDBlueTimestamp* ts = [IDBlueTimestamp alloc] initFromNSDate: now];
 
 *     status = [api setTimestamp: ts
 *                         withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [ts release];
 *     [date release];
 * }
 *
 * -(void) setTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setTimestamp: (IDBlueTimestamp*) timestamp
					withHandler: (id<IResponseHandler>) handler;

/**
 * setTimestamp - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the timestamp property
 *
 * @param timestamp
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setTimestamp {
 *     SendStatus status = nil;
 *     NSDate* now = [[NSDate alloc] init]];
 *     IDBlueTimestamp* ts = [IDBlueTimestamp alloc] initFromNSDate: now];
 
 *     status = [api setTimestamp: ts];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [ts release];
 *     [date release];
 * }
 *
 * -(void) setTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */					
-(SendStatus*) setTimestamp: (IDBlueTimestamp*) timestamp;

/**
 * setDuplicateElimination - 
 *
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the duplicate elimination 
 * property.
 * 
 * @param dupElim
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDuplicateElimination: (ushort) dupElim {
 *     SendStatus status = nil;
 *     status = [api setDuplicateElimination: dupElim
 *                                    withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setDuplicateElimination: (ushort) dupElim
							   withHandler: (id<IResponseHandler>) handler;

/**
 * setDuplicateElimination - 
 *
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the duplicate elimination 
 * property.
 * 
 * @param dupElim
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDuplicateElimination: (ushort) dupElim {
 *     SendStatus status = nil;
 *     status = [api setDuplicateElimination: dupElim];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setDuplicateElimination: (ushort) dupElim;

/**
 * setRfidTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the RFID timeout property.
 *
 * @param timeout
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setRfidTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setRfidTimeout: timeout
 *                           withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setRfidTimeout: (byte) timeout
					  withHandler: (id<IResponseHandler>) handler;

/**
 * setRfidTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the RFID timeout property.
 *
 * @param timeout
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setRfidTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setRfidTimeout: timeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setRfidTimeout: (byte) timeout;

/**
 * setBluetoothTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Bluetooth timeout property.
 *
 * @param timeout
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBluetoothTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setBluetoothTimeout: timeout
 *                                withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBluetoothTimeout: (byte) timeout
						   withHandler: (id<IResponseHandler>) handler;

/**
 * setBluetoothTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Bluetooth timeout property.
 *
 * @param timeout
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBluetoothTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setBluetoothTimeout: timeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */						   
-(SendStatus*) setBluetoothTimeout: (byte) timeout;

/**
 * setContinuousScanTimeout - 
 *
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the continuous scan timeout 
 * property.
 *
 * @param timeout
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setContinuousScanTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setContinuousScanTimeout: timeout
 *                                     withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setContinuousScanTimeout: (byte) timeout
								withHandler: (id<IResponseHandler>) handler;

/**
 * setContinuousScanTimeout - 
 *
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the continuous scan timeout 
 * property.
 *
 * @param timeout
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setContinuousScanTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setContinuousScanTimeout: timeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setContinuousScanTimeout: (byte) timeout;

/**
 * setDeviceTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the device timeout property.
 *
 * @param timeout
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDeviceTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setDeviceTimeout: timeout
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setDeviceTimeout: (byte) timeout
						withHandler: (id<IResponseHandler>) handler;
		
/**
 * setDeviceTimeout - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the device timeout property.
 *
 * @param timeout
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDeviceTimeout: (byte) timeout {
 *     SendStatus status = nil;
 *     status = [api setDeviceTimeout: timeout];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */		
-(SendStatus*) setDeviceTimeout: (byte) timeout;

/**
 * setHoldToScan - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Hold to Scan property.
 *
 * @param enabled
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setHoldToScanEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setHoldToScan: enable
 *                          withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setHoldToScanResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setHoldToScan: (BOOL) enabled
					 withHandler: (id<IResponseHandler>) handler;
	
/**
 * setHoldToScan - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Hold to Scan property.
 *
 * @param enabled
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setHoldToScanEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setHoldToScan: enable];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setHoldToScanResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setHoldToScan: (BOOL) enabled;

/**
 * setBuzzerEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Buzzer Enabled property.
 *
 * @param enabled
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBuzzerEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setBuzzerEnabled: enable
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBuzzerEnabled: (BOOL) enabled
						withHandler: (id<IResponseHandler>) handler;
	
/**
 * setBuzzerEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Buzzer Enabled property.
 *
 * @param enabled
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBuzzerEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setBuzzerEnabled: enable];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setBuzzerEnabled: (BOOL) enabled;

/**
 * setConnectToHost - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Connect to Host property.
 *
 * @param connectToHost
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setConnectToHost: (BOOL) connectToHost {
 *     SendStatus status = nil;
 *     status = [api setConnectToHost: connectToHost
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setConnectToHostResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setConnectToHost: (BOOL) connectToHost
						withHandler: (id<IResponseHandler>) handler;
	
/**
 * setConnectToHost - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Connect to Host property.
 *
 * @param connectToHost
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setConnectToHost: (BOOL) connectToHost {
 *     SendStatus status = nil;
 *     status = [api setConnectToHost: connectToHost
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setConnectToHostResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setConnectToHost: (BOOL) connectToHost;


/**
 * setActionButtonEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Action Button Enabled property.
 *
 * @param actionButtonEnabled
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setActionButtonEnabled: (BOOL) actionButtonEnabled {
 *     SendStatus status = nil;
 *     status = [api setActionButtonEnabled: actionButtonEnabled
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setActionButtonEnabled: (BOOL) actionButtonEnabled
						withHandler: (id<IResponseHandler>) handler;
	
/**
 * setActionButtonEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Action Button Enabled property.
 *
 * @param actionButtonEnabled
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setActionButtonEnabled: (BOOL) actionButtonEnabled {
 *     SendStatus status = nil;
 *     status = [api setActionButtonEnabled: actionButtonEnabled];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setActionButtonEnabled: (BOOL) actionButtonEnabled;


/**
 * setContinuousScanEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Continuous Scan Enabled property.
 *
 * @param enabled
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setContinuousScanEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setContinuousScanEnabled: enable
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setContinuousScanEnabled: (BOOL) enabled
								withHandler: (id<IResponseHandler>) handler;
	
/**
 * setContinuousScanEnabled - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Continuous Scan Enabled property.
 *
 * @param enabled
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setContinuousScanEnabled: (BOOL) enable {
 *     SendStatus status = nil;
 *     status = [api setContinuousScanEnabled: enable];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setContinuousScanEnabled: (BOOL) enabled;

/**
 * setEnforceTimestamp -
 * 
 * Sets the enforce timestamp property of an IDBLUE device.
 * 
 * @param enforce Whether to enforce a timestamp be required when storing tags 
 * to onboard memory of an IDBLUE device.
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setEnforceTimestamp: (BOOL) enforce {
 *     SendStatus status = nil;
 *     status = [api setEnforceTimestamp: enforce
 *                                withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks Enforce timestamp only applies to the DM_TAG_STORE disconnected mode 
 * operation. If enabled, tag scans will only be stored in onboard memory if the 
 * onboard clock of the IDBLUE device has been set.
 */
-(SendStatus*) setEnforceTimestamp: (BOOL) enforce
						   withHandler: (id<IResponseHandler>) handler;
	
/**
 * setEnforceTimestamp -
 * 
 * Sets the enforce timestamp property of an IDBLUE device.
 * 
 * @param enforce Whether to enforce a timestamp be required when storing tags 
 * to onboard memory of an IDBLUE device.
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setEnforceTimestamp: (BOOL) enforce {
 *     SendStatus status = nil;
 *     status = [api setEnforceTimestamp: enforce];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks Enforce timestamp only applies to the DM_TAG_STORE disconnected mode 
 * operation. If enabled, tag scans will only be stored in onboard memory if the 
 * onboard clock of the IDBLUE device has been set.
 */	
-(SendStatus*) setEnforceTimestamp: (BOOL) enforce;

/**
 * setConnectedMode - 
 * 
 * Sets the connected mode operation of the IDBLUE device.
 * 
 * @param mode The connected mode to bet set.
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setConnectedMode: (ConnectedMode) mode {
 *     SendStatus status = nil;
 *     status = [api setConnectedMode: mode
 *                             withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setConnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks The connected mode property determines what action IDBLUE will take 
 * when the front button of the IDBLUE device is pressed, while the IDBLUE device 
 * is connected to a host. For example, IDBLUE can be configured to scan an RFID 
 * tag and return thet tag ID back to the host, or it can be configured to just 
 * notify the host that the button was pressed. See ConnectedMode in IDBlue.h 
 * for more information.
 */
-(SendStatus*) setConnectedMode: (ConnectedMode) mode
						withHandler: (id<IResponseHandler>) handler;
	
/**
 * setConnectedMode - 
 * 
 * Sets the connected mode operation of the IDBLUE device.
 * 
 * @param mode The connected mode to bet set.
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setConnectedMode: (ConnectedMode) mode {
 *     SendStatus status = nil;
 *     status = [api setConnectedMode: mode];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setConnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks The connected mode property determines what action IDBLUE will take 
 * when the front button of the IDBLUE device is pressed, while the IDBLUE device 
 * is connected to a host. For example, IDBLUE can be configured to scan an RFID 
 * tag and return thet tag ID back to the host, or it can be configured to just 
 * notify the host that the button was pressed. See ConnectedMode in IDBlue.h 
 * for more information.
 */	
-(SendStatus*) setConnectedMode: (ConnectedMode) mode;

/**
 * setDisconnectedMode - 
 *
 * Sets the disconnected mode operation of the IDBLUE device.
 *
 * @param mode The disconnected mode to be set
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDisconnectedMode: (DisconnectedMode) mode {
 *     SendStatus status = nil;
 *     status = [api setDisconnectedMode: mode
 *                                withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks The disconnected mode determines if a tag scan will be stored in 
 * onboard memory of an IDBLUE device. Set to DM_TAG_STORE to store tag scans 
 * when not connected to a host, DM_TAG_VERIFY to only verify the tag is 
 * compatible with IDBLUE and not store the tag in onboard memory. See 
 * DisconnectedMode in IDBlue.h for more information.
 */
-(SendStatus*) setDisconnectedMode: (DisconnectedMode) mode
						   withHandler: (id<IResponseHandler>) handler;
	
/**
 * setDisconnectedMode - 
 *
 * Sets the disconnected mode operation of the IDBLUE device.
 *
 * @param mode The disconnected mode to be set
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setDisconnectedMode: (DisconnectedMode) mode {
 *     SendStatus status = nil;
 *     status = [api setDisconnectedMode: mode];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks The disconnected mode determines if a tag scan will be stored in 
 * onboard memory of an IDBLUE device. Set to DM_TAG_STORE to store tag scans 
 * when not connected to a host, DM_TAG_VERIFY to only verify the tag is 
 * compatible with IDBLUE and not store the tag in onboard memory. See 
 * DisconnectedMode in IDBlue.h for more information.
 */	
-(SendStatus*) setDisconnectedMode: (DisconnectedMode) mode;

/**
 * setRfidProtocol - 
 *
 * Sets the RFID protocol property of an IDBLUE device.
 *
 * @param protocol The RfidProtocol to be set
 * @param handler An object implementing IResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setRfidProtocol: (RfidProtocol) protocol {
 *     SendStatus status = nil;
 *     status = [api setRfidProtocol: protocol
 *                            withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setRfidProtocolResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful.
 * @remarks See RfidProtocol in IDBlue.h for more information.
 */
-(SendStatus*) setRfidProtocol: (RfidProtocol) protocol
					   withHandler: (id<IResponseHandler>) handler;
		
/**
 * setRfidProtocol - 
 *
 * Sets the RFID protocol property of an IDBLUE device.
 *
 * @param protocol The RfidProtocol to be set
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setRfidProtocol: (RfidProtocol) protocol {
 *     SendStatus status = nil;
 *     status = [api setRfidProtocol: protocol];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setRfidProtocolResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful.
 * @remarks See RfidProtocol in IDBlue.h for more information.
 */		
-(SendStatus*) setRfidProtocol: (RfidProtocol) protocol;

@end
