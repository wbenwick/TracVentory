
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"
#import "ObjectCollection.h"
#import "CommandIdentifierClassInfo.h"

/**
 *  ResponseFactory is responsible for creating IDBlueResponses from 
 *  IDBluePackets
 */
@interface ResponseFactory : NSObject {
@private
    // List of CommandIdentifierClassInfo objects that maps
    // command identifiers into classes for handling responses for the
    // associated command identifier
    ObjectCollection* _responseMap;
}

/**
 * Add the given CommandIdentifierClassInfo to the response map
 * @param classInfo The CommandIdentifierClassInfo object to add
 * @return TRUE if the classInfo was added, FALSE otherwise
 */
-(BOOL) addResponseMap: (CommandIdentifierClassInfo*) classInfo;

/**
 * Add the given command identifier / Class to the response map
 * @param commandIdentifier The identifier of the command
 * @param classInfo Class for the IDBlueResponse subclass that handles responses for the given 
 * command identifier
 * @return TRUE if the response map was added, FALSE otherwise
 */
-(BOOL) addResponseMap:(int) commandIdentifier withClassInfo:(Class) classInfo;

/**
 * Gets a new IDBlueResponse object from the given response packet.
 * @param packet A response from an IDBLUE device
 * @param async Whether the response packet was sent asynchronously or not. An asynchronous packet
 * is a response packet sent from IDBLUE without a corresponding request being sent to IDBLUE asking
 * for the response. Asynchronous responses are sent from an IDBLUE device when the front button
 * of the IDBLUE device is pressed while connected to a host.
 * @return an instance of (or subclass of) IDBlueResponse that is used to process the data contained
 * in the response packet. Typically, the response will be a NackResponse if a synchronous command
 * was sent to IDBLUE and that command failed (or returned a warning), otherwise an instance of
 * IDBlueResponse containing the requested data is returned. The return value is marked with autorelease
 */
-(IDBlueResponse*) getResponse: (IDBluePacket*) packet withAsync: (BOOL) async;
@end
