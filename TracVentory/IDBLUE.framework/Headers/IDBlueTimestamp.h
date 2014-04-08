
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlue.h"
#import "CByteArray.h"

/**
 *  IDBlueTimestamp represents a date / time retrieved from an IDBLUE
 *  device. It contains year, month, day, hour, minute and second stored
 *  as bytes, where the year is relative to the year 2000.
 */
@interface IDBlueTimestamp : NSObject {
@private	
	// The year byte - number of years since 2000.
	byte _year;
	byte _month;
	byte _day;
	byte _hour;
	byte _minute;
	byte _second;
}

-(byte) year;
-(byte) month;
-(byte) day;
-(byte) hour;
-(byte) minute;
-(byte) second;
-(void) setYear: (byte) year;
-(void) setMonth: (byte) month;
-(void) setDay: (byte) day;
-(void) setHour: (byte) hour;
-(void) setMinute: (byte) minute;
-(void) setSecond: (byte) second;

/**
 * Gets an NSDate object that represents the current IDBlueTimestamp
 */
-(NSDate*) toNSDate;

/**
 * Initialize the IDBlueTimestamp object from an NSDate object
 * @param date the date to create the IDBlueTimestamp from
 * @return The IDBlueTimestamp
 */
-(id) initFromNSDate: (NSDate*) date;

/**
 * Initialize the IDBlueTimestamp object from an array of bytes,
 * ordered as year, month, day, hour, minute, second.
 * @param data the byte array containing the date components
 * @param index the index in the byte array to start copying data from.
 * @return the IDBlueTimestamp if successful, nil otherwise
 */
-(id) initFromByteArray: (CByteArray*) data withIndex: (int) index;

/**
 * Convert the current IDBlueTimestamp object to a string representation
 * of the form 'yyyy-MM-dd HH:mm:ss'
 */
-(NSString*) toString;

/**
 * Initialize an IDBlueTimestamp from a string
 * @param s The timestamp as a string. Must be of the form 
 *		yyyy-MM-dd HH:mm:ss
 * @return An initialized IDBlueTimestamp object if successful,
 * nil otherwise.
 * @remarks The string passed into initFromString needs to be
 * formatted exactly as the string returned from the toString method.
 */
-(id) initFromString: (NSString*) s;

@end
