
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "CByteArray.h"

/**
 *  IDBluePacket represents a command / response for IDBLUE devices.
 *  A packet can be between 4 and 256 bytes. An IDBluePacket starts with
 *  a header byte, followed by 2 data length bytes, then the payload, 
 *  and finally a checksum byte (xor of all other bytes).
 
 *  0        - header byte
 *  1        - data len (MSB)
 *  2        - data len (LSB)
 *  3        - 
 *  ...      - payload
 *  [n - 2]  -
 *  [n - 1]  - checksum
 *
 *  An example of the simplest packet would be the NO_OP command
 *  [0x00 0x00 0x00 0x00], and the ASYNC packet [0x70 0x00 0x00 0x70].
 *  An example of a packet with a payload would be the beep command:
 *  [0x03 0x00 0x01 0x01 0x03]
 */
@interface IDBluePacket : CByteArray {
@private	
	// The header byte
	byte _header;
	
	// The checksum byte
	byte _checksum;
		
	// The date / time when the IDBluePacket was created
	NSDate* _timestamp;
}

/**
 * Initialize an IDBluePacket with the specified number of bytes
 * @param packetSize the length of the packet, in bytes.
 * @return the initialized packet if successful, nil otherwise
 */
-(id) initWithPacketSize: (int)packetSize;

/**
 * Initialize an IDBluePacket with the specified number of bytes 
 * and the given header byte.
 * @param packetSize the length of the packet, in bytes
 * @param header the header byte of the IDBluePacket
 * @return the initialized packet if successful, nil otherwise
 */
-(id) initWithHeader: (int) packetSize withHeader: (byte) header;

/**
 * Get the timestamp of the IDBluePacket
 * @return the date / time the IDBluePacket was created
 */
-(NSDate*) timestamp;

/**
 * Get the length of the payload
 * @return the number of bytes that can be stored in the payload
 * of the IDBluePacket
 */
-(int) payloadSize;

/**
 * The total length of the IDBluePacket
 * @return the number of bytes contained in the IDBluePacket,
 * including the header byte, 2 payload size bytes, payload size 
 * and checksum.
 */
-(int) packetSize;

/**
 * Get a pointer to the payload of the IDBluePacket
 * @return the pointer to the start byte of the payload. Modifying 
 * the data stored in payload will modify the data in the IDBluePacket.
 */
-(byte*) payload;

/**
 * Determine if the current IDBluePacket is the async packet (0x70 0x00 0x00 0x70).
 @return TRUE if the current IDBluePacket is the async packet, FALSE otherwise.
 */
-(BOOL) isAsyncPacket;

/**
 * Gets the header byte
 */
-(byte) header;

/**
 * Sets the header byte
 * @param header the header byte to be set
 */
-(void) setHeader: (byte) header;

/**
 * Gets the checksum
 */
-(byte) checksum;

/**
 * Sets the checksum
 * @param checksum the checksum to be set
 */
-(void) setChecksum: (byte) checksum;

/**
 * Xor all the bytes in the IDBluePacket to compute the checksum
 * and store the results in the last byte of the packet.
 * @return the computed checksum.
 */
-(byte) computeChecksum;

/**
 * Computes the payload size (i.e. packet size - 4), and stores
 * the payload size in the payload size bytes (index 1 and 2) of
 * the current IDBluePacket.
 * @return the payload size
 */
-(int) computePayloadSize;

/**
 * Calls computePayloadSize followed by computeChecksum. This method
 * should be called after modifying the payload.
 */
-(void) computePayloadSizeAndChecksum;

@end
