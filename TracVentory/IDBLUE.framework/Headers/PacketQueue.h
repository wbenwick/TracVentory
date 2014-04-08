
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ByteQueue.h"
#import "IDBluePacket.h"
#import "ResponseFactory.h"

/**
 *  PacketQueue is a subclass of ByteQueue that is used to convert from
 *  raw bytes into IDBluePacket objects.
 */
@interface PacketQueue : ByteQueue {
@private
    ResponseFactory* _responseFactory;
}

/**
 *
 */
-(ResponseFactory*) responseFactory;

/**
 *
 */
-(void) setResponseFactory: (ResponseFactory*) factory;

/**
 * Create an IDBluePacket from a ByteQueue
 * @return The IDBluePacket if the ByteQueue starts with a valid IDBluePacket, 
 * nil otherwise.
 */
-(IDBluePacket*) popNextPacket;

/**
 * Create an IDBLuePacket from the ByteQueue at the given index
 * @param index The index in the ByteQueue to check for a packet
 * @return An IDBluePacket if the data starting at index is a valid
 * packet. Otherwise, returns nil.
 */
-(IDBluePacket*) peekPacket: (int) index;

/**
 * In the event the ByteQueue contains invalid data (i.e. data is not formatted
 * as proper IDBLUE packets), remove data from the start of the ByteQueue
 * so that the ByteQueue contains only valid IDBLUE packets.
 * @return The number of bytes removed from the start of the ByteQueue.
 */
-(int) recover;

/**
 * Determine if the given packet is a valid IDBLUE packet
 * @param packet The packet to validate
 * @return TRUE if the packet is valid, FALSE otherwise
 */ 
-(BOOL) isValidPacket: (IDBluePacket*) packet;
@end
