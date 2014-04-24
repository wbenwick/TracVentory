//
//  IDBlueSdk.h
//  iPhoneSampleApp
//
//  Copyright 2010-2011 Cathexis Innovations Inc. All rights reserved.
//
//  IDBlueSDK demonstrates how to use the IDBLUE iOS SDK
//

#import <Foundation/Foundation.h>

#import <IDBLUE/SessionHandler.h>
#import <IDBLUE/IDBlueCoreApi.h>
#import <IDBLUE/iOSSession.h>
#import <IDBLUE/IDBLUE.h>

// By subclassing IDBlueiOSSdk, IDBlueSdk is the only object from the IDBLUE
// iOS SDK you need to instantiate. 
@interface IDBlueSdk : IDBlueCoreApi {
    iOSSession* _iosSession;
}

// Methods that illustarte how to use the IDBlueiOSSdk
-(BOOL) openIDBlueSession;
-(BOOL) closeIDBlueSession;
-(BOOL) getTagId;
-(void) registerSessionHandler: (id<ISessionHandler>) handler;
-(void) registerIDBlueResponseHandler: (id<IResponseHandler>) handler;
@end
