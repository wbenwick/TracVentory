
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueResponse.h"
#import "IDBlueCommand.h"

/**
 *  SendStatus is a subclass of IDBlueResponse.
 *  It is returned from all methods of IDBlueCommandSender that send
 *  IDBlueCommand packets to an IDBLUE device. It contains the 
 *  IDBlueCommand packet sent to IDBLUE, whether the data was sent to 
 *  IDBLUE, and if not, the error details
 */
@interface SendStatus : IDBlueResponse {
@private
	// The IDBlueCommand packet sent to IDBLUE
	IDBlueCommand* _commandSent;
}

/**
 * Initialize a SendStatus object, for the specified command
 * @param command the CommandIdentifier of the command sent
 * @param success Whether the command was sent successfully
 * @return an initialized SendStatus object
 */
-(id) initWithHeader: (CommandIdentifier) command withSuccess: (BOOL) success;

/**
 * Gets the IDBlueCommand packet that was sent to IDBLUE
 */
-(IDBlueCommand*) commandSent;

/**
 * Set the IDBlueCommand packet that was sent to IDBLUE.
 */
-(void) setCommandSent: (IDBlueCommand*) command;
@end
