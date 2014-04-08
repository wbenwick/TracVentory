
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import "ResponseHandler.h"

@protocol IHfResponseHandler <IResponseHandler, NSObject>
@optional
	-(void) getTagInfoResponse: (IDBlueCommand*) command withResponse: (GetTagInfoResponse*) response;
	-(void) getTagInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	
	-(void) readBlockResponse: (IDBlueCommand*) command withResponse: (ReadBlockResponse*) response;
	-(void) readBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) readBlocksResponse: (IDBlueCommand*) command withResponse: (ReadBlocksResponse*) response;
	-(void) readBlocksFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) writeBlockResponse: (IDBlueCommand*) command withResponse: (WriteBlockResponse*) response;
	-(void) writeBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) writeBlocksResponse: (IDBlueCommand*) command withResponse: (WriteBlocksResponse*) response;
	-(void) writeBlocksFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	
	-(void) getBlockIndexResponse: (IDBlueCommand*) command withResponse: (BlockIndexProperty*) response;
	-(void) getBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBlockCountResponse: (IDBlueCommand*) command withResponse: (BlockCountProperty*) response;
	-(void) getBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) getBlockDataResponse: (IDBlueCommand*) command withResponse: (BlockDataProperty*) response;
	-(void) getBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBlockIndexResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBlockCountResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
	
	-(void) setBlockDataResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response;
	-(void) setBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response;
@end

@interface HfResponseHandler : ResponseHandler <IHfResponseHandler> {
} 
@end