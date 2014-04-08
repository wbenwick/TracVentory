
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDblueCommand.h"
#import "IDBlueResponse.h"
#import "ObjectCollection.h"

/**
 * CommandQueue is a queue of IDBlueCommand objects that are sent 
 * to an IDBLUE device that are waiting for a response from IDBLUE.
 */
@interface CommandQueue : ObjectCollection {
}

/**
 * Queue a command
 * @param command the command that was sent to IDBLUE and now  
 * waiting for a response.
 */ 
-(void) push: (IDBlueCommand*) command;

/**
 * Get the number of queued commands
 * @return the number of commands that are awaiting respones
 */
-(int) commandCount;

/**
 * Get the first queued command for which the given response is valid,
 * and remove the command from the queue.
 * @return The first command for which response is a valid response - 
 * command is also removed from the queue.
 */
-(IDBlueCommand*) getCommand: (IDBlueResponse*) response;

/**
 * Remove the given command from the CommandQueue
 */
-(void) remove: (IDBlueCommand*) command;

/**
 * Clears all pending commands from the CommandCueue
 * @return the number of commands removed.
 */
-(int) clear;

@end
