
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "ResponseHandler.h"
#import "EpcReadTagResponse.h"
#import "EpcWriteTagResponse.h"
#import "EpcLockResponse.h"
#import "EpcKillResponse.h"
#import "EpcSetKillPasswordResponse.h"

@protocol IUhfResponseHandler <IResponseHandler, NSObject>
@optional

-(void) epcReadResponse: (IDBlueCommand*) command withResponse: (EpcReadTagResponse*) response;
-(void) epcReadFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

-(void) epcWriteResponse: (IDBlueCommand*) command withResponse: (EpcWriteTagResponse*) response;
-(void) epcWriteFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

-(void) epcLockResponse: (IDBlueCommand*) command withResponse: (EpcLockResponse*) response;
-(void) epcLockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

-(void) epcKillResponse: (IDBlueCommand*) command withResponse: (EpcKillResponse*) response;
-(void) epcKillFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

-(void) epcSetKillPasswordResponse: (IDBlueCommand*) command withResponse: (EpcSetKillPasswordResponse*) response;
-(void) epcSetKillPasswordFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;

@end

@interface UhfResponseHandler : ResponseHandler <IUhfResponseHandler> {
}
@end
