
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "IDBlue.h"

/**
 * CByteArray is used to encapsulate a C pointer to an array of bytes (byte*),
 * handling dynamically creating memory for the array, and freeing the allocated
 * array when the class is dealllocated.
 */
@interface CByteArray : NSObject {
	// The nuber of bytes allocated in the array
	int _length;
	// The byte array 
	byte* _data;
}

/**
 * Initialize the current CByteArray
 * @param length the number of bytes to allocate for the byte array
 * @return the initialized CByteArray
 */
-(id) initWithArrayLength:(int)length;

/**
 * Initialize a CByteArray with an array of bytes
 * @param data The pointer to the data to be set
 * @len The number of bytes to copy
 */
-(id) initWithData:(const byte*) data withLen:(int) len;

/**
 * Creates a byte array of ascii characters
 * @param s An NSString containing all ASCII characters
 */
-(id) initWithAsciiString: (NSString*) s;

/**
 * Initialize a CByteArray from a string of hex bytes
 * @param hex A string containing hex values, that may contain spaces. Each hex value must
 * be stored in 2 characters. (e.g. 00 FF 00 FF).
 * @return The CByteArray containing each hex value in byte format if successful,
 * nil otherwise.
 */
-(id) initWithHexString: (NSString*) hex;

/**
 * Gets the length of the byte array
 */ 
-(int) arrayLength;

/**
 * Gets the pointer to the byte array
 */
-(byte*) data;

/**
 * Copy the given data into the current CByteArray 
 * replacing the old data with the new data and length
 * @param data The data to be copied
 * @param dataLen The number of bytes in the specified byte array
 * @return The number of bytes copied into the current CByteArray
 */
-(int) setData: (const byte*) data withDataLen: (int) dataLen;

/**
 * Copy a portion of the given data array into the current CByteArray
 * replacing the old data with the new data and length
 * @param data The data to be copied
 * @param dataLen The length of the byte array
 * @param index The index to start copying from
 * @param count The number of bytes to copy
 * @return the number of bytes copied
 */ 
-(int) setData: (const byte*) data withDataLen: (int) dataLen withIndex: (int) index withCount: (int) count;

/**
 * Copy data from another CByteArray into the current CByteArray
 * @param data The CByteArray to copy data from
 * @return the number of bytes copied.
 */
-(int) setData: (CByteArray*) data;

/**
 * Convert to the current CByteArray to a string, where each byte is represented as it's 2 character 
 * hex equivalent, separated by spaces.
 * @return An NSString object containing the bytes of the byte array, displayed in hex format.
 */
-(NSString*) toString;

/**
 * Convert the current CByteArray to a string, the same as toString, except the string is in reverse order.
 * @remarks Equivalet to calling reverse on the CByteArray followed by a toString
 */
-(NSString*) toStringReversed;

/**
 * Reverse the bytes in the CByteArray
 */
-(void) reverse;


@end
