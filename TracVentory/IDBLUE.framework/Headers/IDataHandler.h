
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>


/**
 * DataReceivedhandler is a protocol that is used to receive notifications
 * When data is received from and IDBLUE device by an IDBlueSession.
 */
@protocol IDataHandler <NSObject>

/**
 * onDataReceived should be called from within classes deriving from IDBlueSession 
 * when data is received from an IDBLUE device, so the IDBlueCommandSender can process responses.
 * @param data pointer to the byte array holding the data received
 * @param len the number of bytes received
 */
-(void) onDataReceived: (byte*) data withLen: (size_t) len;

@end
