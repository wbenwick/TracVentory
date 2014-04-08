
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "CByteArray.h"

/**
 *  RfidTag is a class that represents an RfidTag as an array of bytes.
 */
@interface RfidTag : CByteArray {
@private
    Endianness _byteOrder;
}

/**
 * Initialize an RfidTag object from the given tag id as a string.
 * @param tagId the string containing the tag id
 * @param byteOrder
 * @return the RfidTag if successful, nil otherwise.
 * @remarks The given tag id contains the bytes of the RFID tag,
 * stored as 2 character hex bytes in reverse order.
 */
-(id) initFromString: (NSString*) tagId withByteOrder: (Endianness) byteOrder;

/**
 * Initialize an RfidTag object from the given byte array
 * @param data a byte array where the first byte contains the number
 * of bytes in the tag id, followed by the tag id.
 * @param index the index of the tag id length byte
 * @param byteOrder 
 * @return The RfidTag object if successful, nil otherwise
 */
-(id) initFromByteArray: (CByteArray*) data withIndex: (int) index withByteOrder: (Endianness) byteOrder;

/**
 * Get the length of the tag id
 * @return the length of the tag id, in bytes
 */
-(int) tagIdLength;

/**
 *
 */
-(Endianness) byteOrder;

/**
 *
 */
-(void) setByteOrder:(Endianness) byteOrder;

@end
