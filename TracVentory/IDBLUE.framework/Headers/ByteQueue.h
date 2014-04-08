
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlue.h"

/** BufferState is used to distinguish between the buffer being full and the buffer being empty */
typedef enum _BufferState {
	BS_BufferEmpty,
	BS_BufferNormal,
	BS_BufferFull
} BufferState;

/** 
 * ByteQueue is a fast circular byte buffer, for pushing and poping bytes
 * quickly. Typically would be used to prcessing IDBLUE responses.
 */
@interface ByteQueue : NSObject {
	
@private
	byte* _data;
	int _capacity;
	int _size;
	
	/**
	 * Pointer to the next available memory space containing data
	 * (the start of the queue)
	 */	
	byte* _pStart;
	
	/**
	 * Pointer to the next available memory space in the buffer 
	 * in which to write (the end of the queue)
	 */	
	byte* _pEnd;
	
	BufferState _state;
}

/**
 * Initialize a ByteQueue
 * @param capacity The capacity of the ByteQueue
 * @return The ByteQueue if initialized, nil otherwise
 */
-(id) initWithMaxCapacity: (int) capacity;

/**
 * Push len bytes from data into the ring buffer.  If the 
 * buffer has insufficient capacity to continue writing, 
 * write up to the amount of space available.
 *
 * @param data Pointer to an initialized data buffer of at least length len
 * @param len The length of the data buffer to write
 * @return The number of bytes written to the buffer
 */
-(int) push: (byte*) data withLen: (int) len;

/**
 * Pop maxlen bytes from the ring buffer into the dest array.  Dest must
 * be an initialized buffer of at least maxlen bytes.
 *
 * @param dest An initialized buffer of at least maxlen bytes.
 * @param maxlen The number of bytes requested from the ring buffer.
 * @return The number of bytes written into the dest buffer.
 */
-(int) pop: (byte*) dest withMaxLen: (int) maxlen;

/**
 * Pop the given number of bytes from the ByteQueue
 * @param toRemove The number of bytes to remove
 * @return The number of bytes actually removed
 */
-(int) pop: (int) toRemove;

/**
 * Get the value in the queue at the specified index.
 *
 * @param val The location of the byte that will be assigned the value
 * @param index The index in the queue to retrieve the value of
 * @return True if the byte was read, FALSE otherwise
 */
-(BOOL) peek: (byte*) val withIndex: (int) index;

/**
 * Retrieve a range of bytes from the ByteQueue, without removing them
 * from the ByteQueue
 * @param dest The pointer to the byte array to copy the bytes into
 * @param index The index within the ByteQueue to start reading from
 * @param count The number of bytes to read
 * @return The number of bytes read
 */
-(int) peekRange: (byte*) dest withIndex: (int) index withCount: (int) count;

-(byte) computeChecksum: (int) index withCount: (int) count;

/**
 * Get the number of bytes held in the queue.
 */
-(int) size;

/**
 * Get the maximum number of bytes that can be held in the queue
 */
-(int) capacity;

/**
 * Get the number of bytes that can be added before the queue is full 
 */
-(int) available;

/**
 * Whether the queue is full or not
 */
-(BOOL) full;

/**
 * Whether the queue is empty or not
 */
-(BOOL) empty;

/**
 * Brings the ringbuffer back to the default state.
 * @return RC_SUCCESS successfully flushed.
 * @return RC_LOCK_ERROR error obtaining the mutex lock.
 * @return RC_UNLOCK_ERROR error releasing the mutex lock.
 */
-(int) flush;

/**
 * Get the hex string representation of the ByteQueue
 * @return a string containing each byte represented in hex.
 */
-(NSString*) toString;
@end
