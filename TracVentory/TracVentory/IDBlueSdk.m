//
//  IDBlueSdk.m
//  iPhoneSampleApp
//
//  Copyright 2010-2011 Cathexis Innovations Inc. All rights reserved.
//

#import "IDBlueSdk.h"

@implementation IDBlueSdk
-(id) init {
    _iosSession = [[iOSSession alloc] init];
    if (!_iosSession) {
        return nil;
    }
    
    self = [super initWithSession:_iosSession];
    if (self) {
        // Log the current version of the SDK we are using
        NSLog(@"%@", [self sdkVersion]);
        // add custom initialization here
    }
    return self;
}



// This method illustrates one method for opening a session to an IDBLUE device.
-(BOOL) openIDBlueSession {
    // The External Accessory Framework only allows for one accessory to be 
    // connected to the iOS based device (e.g. iPhone) at a time. So when
    // we want to connect, we can just try to connect to the first IDBLUE
    // device found (if one exists). That's exactly what the openFirstIDBlueDeice
    // does.
    BOOL sessionStarted = [_iosSession openFirstIDBlueDevice];
    if (sessionStarted) {
        NSLog(@"A session was started.");
        // The session was started. We will be notified when the session is
        // open via the onSessionOpened callback method of IDBlueSessionDelegate.
    }
    else {
        NSLog(@"Failed to open a session. Is an IDBLUE device paired with the iPhone?");
    }
    return sessionStarted;
}

// This method illustrates how to close a session once it has been opened
-(BOOL) closeIDBlueSession {
    BOOL closeStarted = [self closeSession];
    if (closeStarted) {
        // Closing the session was started. We will be notified when the session is
        // closed via the onSessionClosed callback method of IDBlueSessionDelegate.
    }
    else {
        NSLog(@"Failed to close the session. We're we even connected?");
    }
    return closeStarted;
}

// Illustrates how to get IDBLUE to scan an RFID tag and give us back the tag id.
// If IDBLUE finds a tag, the scanTagIdResponse callback method will be invoked.
// If no RFID tag was found or an error occurred, the scanTagIdFailed callback 
// method will be invoked.
-(BOOL) getTagId {
	SendStatus* status = [self readTagId:self];
	if ([status successful]) {
		NSLog(@"get tag id command sent to IDBLUE");
		return TRUE;
	}
	else {
		NSLog(@"failed to send get tag id command to IDBLUE");
		return FALSE;
	} 
}

// You can use the IDBlueiOSSdk without subclassing it. If you do this,
// your application has no way of receiving session events (e.g. open, 
// close, etc.) unless you register a session delegate with the IDBlueiOSSdk
// first. This method illustrates the use of addSessionDelegate.
-(void) registerSessionHandler: (id<ISessionHandler>) handler {
	[self addSessionHandler:handler];
}

// You can use the IDBlueiOSSdk without subclassing it. If you do this,
// your application has no way of receiving responses from IDBLUE unless you 
// register a receiver delegate with the IDBlueiOSSdk first. This method 
// illustrates the use of addDelegate.
-(void) registerIDBlueResponseHandler: (id<IResponseHandler>) handler {
	[self addResponseHandler:handler];
}

// IDBlueSessionDelegate callback methods we are overriding
-(void) onSessionOpened: (id) session {
	[super onSessionOpened:session];
	NSLog(@"IDBLUE session opened");
}

-(void) onSessionClosed: (id) session {
	[super onSessionClosed:session];
	NSLog(@"IDBLUE session closed");
}

-(void) onIDBlueDeviceAdded: (id) device {
	if ([self isSessionOpen] == FALSE) {
		[self openIDBlueSession];
	}
}

-(void) onIDBlueDeviceRemoved: (id) device {

}

// IDBlueReceiverDelegate callback methods we are overriding
-(void) readTagIdResponse: (IDBlueCommand*) command 
			 withResponse: (ReadTagIdResponse*) response {
	[super readTagIdResponse:command withResponse:response];
	RfidTag* tag = [response rfidTag];
	NSString* tagId = [tag toString];
	NSLog(@"Got tag id: %@", tagId);
}

-(void) readTagIdFailed: (IDBlueCommand*) command 
		   withResponse: (NackResponse*) response {
	[super readTagIdFailed:command withResponse:response];
	NSLog(@"Get tag id failed");
}

@end
