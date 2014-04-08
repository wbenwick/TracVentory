
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import "IDBlueCommand.h"
#import "IDBlueResponse.h"
#import "NackResponse.h"
#import "GetEntryResponse.h"
#import "GetEntryCountResponse.h"
#import "GetBluetoothNameResponse.h"
#import "GetStatusResponse.h"
#import "ReadTagIdResponse.h"
#import "GetTagInfoResponse.h"
#import "ReadBlockResponse.h"
#import "ReadBlocksResponse.h"
#import "WriteBlockResponse.h"
#import "WriteBlocksResponse.h"

#import "TimestampProperty.h"
#import "DuplicateEliminationProperty.h"
#import "RfidTimeoutProperty.h"
#import "BluetoothTimeoutProperty.h"
#import "ContinuousScanTimeoutProperty.h"
#import "DeviceTimeoutProperty.h"
#import "BlockIndexProperty.h"
#import "BlockCountProperty.h"
#import "HoldToScanEnabledProperty.h"
#import "BuzzerEnabledProperty.h"
#import "ContinuousScanEnabledProperty.h"
#import "EnforceTimestampProperty.h"
#import "ConnectedModeProperty.h"
#import "DisconnectedModeProperty.h"
#import "RfidProtocolProperty.h"
#import "BlockDataProperty.h"
#import "BootloaderVersionProperty.h"
#import "VersionInfoProperty.h"
#import "ConnectToHostProperty.h"
#import	"ActionButtonEnabledProperty.h"

@protocol IResponseHandler <NSObject>
@optional
	-(void) commandSent: (IDBlueCommand*) command;
	
	-(void) packetReceived: (IDBluePacket*) packet;
	
    -(void) responseReceived: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	
	-(void) buttonPressResponse: (IDBlueResponse*) response;
	
	
	-(void) noOpResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) noOpFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) heartBeatResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) heartBeatFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) beginCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) beginCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) endCommandsResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) endCommandsFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) beepResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) beepFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) clearEntriesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) clearEntriesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) savePropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) savePropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) loadPropertiesResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) loadPropertiesFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) enableChannelResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) enableChannelFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setScanningResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setScanningFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getEntryResponse: (IDBlueCommand*) command withResponse: (GetEntryResponse*) response;
	-(void) getEntryFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getEntryCountResponse: (IDBlueCommand*) command withResponse: (GetEntryCountResponse*) response;
	-(void) getEntryCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBluetoothNameResponse: (IDBlueCommand*) command withResponse: (GetBluetoothNameResponse*) response;
	-(void) getBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getStatusResponse: (IDBlueCommand*) command withResponse: (GetStatusResponse*) response;
	-(void) getStatusFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) readTagIdResponse: (IDBlueCommand*) command withResponse: (ReadTagIdResponse*) response;
	-(void) readTagIdFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBluetoothNameResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBluetoothNameFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBluetoothPinResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBluetoothPinFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	
	
	-(void) getTimestampResponse: (IDBlueCommand*) command withResponse: (TimestampProperty*) response;
	-(void) getTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (DuplicateEliminationProperty*) response;
	-(void) getDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (RfidTimeoutProperty*) response;
	-(void) getRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (BluetoothTimeoutProperty*) response;
	-(void) getBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (ContinuousScanTimeoutProperty*) response;
	-(void) getContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (DeviceTimeoutProperty*) response;
	-(void) getDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getHoldToScanResponse: (IDBlueCommand*) command withResponse: (HoldToScanEnabledProperty*) response;
	-(void) getHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (BuzzerEnabledProperty*) response;
	-(void) getBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getConnectToHostResponse: (IDBlueCommand*) command withResponse: (ConnectToHostProperty*) response;
	-(void) getConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

	-(void) getActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (ActionButtonEnabledProperty*) response;
	-(void) getActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (ContinuousScanEnabledProperty*) response;
	-(void) getContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (EnforceTimestampProperty*) response;
	-(void) getEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getConnectedModeResponse: (IDBlueCommand*) command withResponse: (ConnectedModeProperty*) response;
	-(void) getConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (DisconnectedModeProperty*) response;
	-(void) getDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getRfidProtocolResponse: (IDBlueCommand*) command withResponse: (RfidProtocolProperty*) response;
	-(void) getRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBootloaderVersionResponse: (IDBlueCommand*) command withResponse: (BootloaderVersionProperty*) response;
	-(void) getBootloaderVersionFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

	-(void) getVersionInfoResponse: (IDBlueCommand*) command withResponse: (VersionInfoProperty*) response;
	-(void) getVersionInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	
	
	-(void) setTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setDuplicateEliminationResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setDuplicateEliminationFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setRfidTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setRfidTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBluetoothTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBluetoothTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setContinuousScanTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setContinuousScanTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setDeviceTimeoutResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setDeviceTimeoutFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setHoldToScanResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setHoldToScanFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBuzzerEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBuzzerEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setConnectToHostResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setConnectToHostFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

	-(void) setActionButtonEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setActionButtonEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

	-(void) setContinuousScanEnabledResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setContinuousScanEnabledFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setEnforceTimestampResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setEnforceTimestampFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setConnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setConnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setDisconnectedModeResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setDisconnectedModeFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setRfidProtocolResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setRfidProtocolFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
@end

/**
 *  ResponseHandler is used to notify calling applications of responses
 *  from an IDBLUE device. Calling applications should create a subclass
 *  of ResponseHandler, and pass the ResponseHandler subclass into the 
 *  methods of IDBlueCommandSender. 
 *
 *  For example, here's an example of the beepAsync command
 * 
 *  // Myhandler.h
 *  @interface Myhandler : ResponseHandler {
 *  }
 *  @end
 * 
 *  // Myhandler.m
 *  @implementation Myhandler
 *      // Override beepResponse to process successsful beep responses
 *      -(void) beepResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 *          // TODO - beep succeeded
 *      }
 * 
 *      // Override beepFailed to process failed beep response
 *      -(void) beepFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 *          // TODO - beep failed
 *      }
 *  @end
 *
 *  // SomeFile.m
 *  -(void) beep {
 *      IDBlueCommandSender* controller; // TODO - initialize
 *      Myhandler* handler; // TODO - initialize
 *      BeepType bt = BT_Low;
 *      SendStatus* status = [controller beepAsync: bt withHandler: handler];
 *      if ([status successful]) {
 *          // Beep command sent successfully
 *      }
 *      else {
 *          // Beep failed
 *      }
 *  } 
 *
 */
@interface ResponseHandler : NSObject <IResponseHandler> {
} 
@end