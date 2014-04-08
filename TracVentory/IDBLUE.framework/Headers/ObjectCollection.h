
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>

/**
 *  An ObjectCollection is a mutable array of objects. ObjectCollection does not
 *  allow the same object to be added more than once.
 */
@interface ObjectCollection : NSObject {
	// Array to hold the objects
	NSMutableArray* _objects;
}

/**
 * Add the given object
 * @param object The object to add
 * @return TRUE if the object was added, FALSE otherwise
 */
-(BOOL) addObject: (id) object;

/**
 *
 */
-(int) addObjects: (ObjectCollection*) objects;

/**
 * Remove the object
 * @param object The object to remove
 * @return TRUE if the object was removed, FALSE otherwise
 */
-(BOOL) removeObject: (id) object;

/**
 * Remove the object at the given index
 * @param index The index of the object to remove
 * @return TRUE if the object was removed, FALSE otherwise
 */
-(BOOL) removeObjectAtIndex: (int) index;

/**
 * Remove all objects from the ObjectCollection
 */
-(int) removeAllObjects;

/**
 * Determine if the given object exists in the ObjectCollection
 * @param object The object to check for
 * @return TRUE if the object exists, false otherwise
 */
-(BOOL) hasObject: (id) object;

/**
 * Get the index of the object in the ObjectCollection
 * @param object The object to retrieve the index of
 * @return The index of the object if found, -1 otherwise
 */
-(int) indexOfObject: (id) object;

/**
 * Get the number of objects in the ObjectCollection
 * @return The number of objects in the ObjectCollection
 */
-(int) count;

/**
 * Get the object at the given index
 * @param index The index of the object to check for
 * @return The object if index is within the bounds of the
 * ObjectCollection, nil otherwise.
 */
-(id) objectAtIndex: (int) index;

@end
