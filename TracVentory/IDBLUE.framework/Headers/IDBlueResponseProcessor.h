
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlue.h"
#import "IDataHandler.h"
#import "ResponseHandlerCollection.h"
#import "PacketQueue.h"
#import "IDBluePacket.h"
#import "IDBlueCommand.h"
#import "CommandQueue.h"
#import "IDBlueTimestamp.h"
#import "CByteArray.h"
#import "SendStatus.h"
#import "RfidTag.h"
#import "ResponseHandler.h"
#import "ResponseFactory.h"
#import "PropertyGenerator.h"

/**
 *  IDBlueResponseProcessor is responsible for converting incoming 
 *  data from IDBLUE into IDBlueResponse objects and notifing listeners
 *  of received responses
 */
@interface IDBlueResponseProcessor : NSObject <IDataHandler> {
@private
	// The circular byte queue that holds the incoming data from IDBLUE
	PacketQueue* _receiveBuffer;
	
	// The CommandQueue object that maps commands sent to IDBLUE
	// to responses received from IDBLUE
	CommandQueue* _commandQueue;
	
	// The asynchronous response callback method
	ResponseHandlerCollection* _handlers;
	
	// Indicates that the next response from IDBLUE is asynchronous
	// (e.g. the user presses the front button of the IDBLUE device,
	// IDBLUE scans a tag then sends the result back to the host).
	BOOL _nextPacketAsync;
	
	// The number of synchronous responses received from IDBLUE
	int _synchronousResponsesReceived;
	
	// The number of asynchronous responses received from IDBLUE
	int _asynchronousResponsesReceived;
    
    // ResponseFactory is used to create responses from IDBluePackets
    ResponseFactory* _responseFactory;
    
    // PropertyGenerator is used to create IDBlueProperty objects from IDBluePackets
    PropertyGenerator* _propertyGenerator;
}

/**
 * Gets the ResponseFactory
 */
-(ResponseFactory*) responseFactory;


/**
 * Gets the PropertyGenerator
 */
-(PropertyGenerator*) propertyGenerator;

/**
 * Initialize an IDBlueResponseProcessor with the given CommandQueue
 * @param queue The CommandQueue that will hold commands sent to IDBLUE, 
 * awaiting responses
 * @param receiveBuffer The PacketQueue that will be used to store 
 * incoming data, and convert the bytes into IDBluePackets.
 * @param factory The ResponseFactory that creates IDBleuResponse objects
 * @param generator The PropertyGenerator that creates IDBlueProeprty objets
 */
-(id) initWithCommandQueue: (CommandQueue*) queue 
         withReceiveBuffer: (PacketQueue*) receiveBuffer 
       withResponseFactory: (ResponseFactory*) factory 
     withPropertyGenerator: (PropertyGenerator*) generator;

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
 * Determines if the given ResponseHandler is contained in the list of
 * handlers that are notified of responses received from an IDBLUE device.
 */
-(BOOL) hasHandler: (id<IResponseHandler>) handler;

/**
 * Gets the array of ResponseHandler objects
 */
-(ResponseHandlerCollection*) handlers;

/**
 * Gets the data in the incoming buffer, in hex format
 */
-(NSString*) incomingBufferContents;

/**
 * Gets the number of bytes in the incoming buffer
 */
-(int) incomingBufferCount;

/**
 * Notifies the given ResponseHandler that an IDBluePacket has been received from IDBLUE.
 * onPacketReceived is called from within IDBlueCommandSender. It should not be called externally.
 * @param packet the IDBluePacket received from IDBLUE
 * @param handler the ResponseHandler object to notify
 */
-(void) onPacketReceived:(IDBluePacket*) packet withHandler: (id<IResponseHandler>) handler;

/**
 * Notifies all ResponseHandler objects (registered with addHandler or 
 * passed into the constructor) of an asynchronous response from an IDBLUE device.
 * notifyAsyncResponse is called from within IDBlueCommandSender afer a call to 
 * onDataReceived if the incoming data is an asynchronous response (e.g. a
 * the user presses the front button of IDBLUE, resulting in a tag scan being
 * sent back to the host).
 * @param response the asynchronous response received from an IDBLUE device.
 * @return TRUE if an ResponseHandler was notified of the response, FALSE otherwise.
 */
-(BOOL) notifyAsyncResponse: (IDBlueResponse*) response;

/**
 * Notifies the ResponseHandler assigned to the IDBlueCommand sent to IDBLUE that
 * a synchronous response has been received (a synchronous response is a response
 * sent from an IDBLUE device in response to an IDBlueCommand).
 * @param command The IDBlueCommand object that was sent to IDBLUE that received
 * the response (use the method [command response] to get the IDBlueResponse). 
 * @return TRUE if an IDBLUE handler was notified, FALSE otherwise
 */
-(BOOL) notifySyncResponse: (IDBlueCommand*) command;

@end
