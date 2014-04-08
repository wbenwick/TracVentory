
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCoreApi.h"
#import "HfResponseHandler.h"

@interface IDBlueHfApi : IDBlueCoreApi <IHfResponseHandler> {
    
}

/**
 * getTagInfo - 
 *
 * Sends a CI_GET_TAG_INFO command to IDBLUE
 *
 * @param tag The RfidTag of the RFID tag to get tag info for
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueHfApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     status = [api getTagInfo: tag 
 *                       withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 * }
 *
 * -(void) getTagInfoResponse: (IDBlueCommand*) command withResponse: (GetTagInfoResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockCount = [response blockCount];
 *     byte blockSize = [response bytesPerBlock];
 * }
 *
 * -(void) getTagInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CI_GET_TAG_INFO is used to get information about the tag structure 
 * (tag id, block count, block size).
 */
-(SendStatus*) getTagInfo: (RfidTag*) tag
              withHandler: (id<IHfResponseHandler>) handler;
			  
/**
 * getTagInfo - 
 *
 * Sends a CI_GET_TAG_INFO command to IDBLUE
 *
 * @param tag The RfidTag of the RFID tag to get tag info for
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueHfApi* api;
 * -(void) getStatus {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     status = [api getTagInfo: tag];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 * }
 *
 * -(void) getTagInfoResponse: (IDBlueCommand*) command withResponse: (GetTagInfoResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockCount = [response blockCount];
 *     byte blockSize = [response bytesPerBlock];
 * }
 *
 * -(void) getTagInfoFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CI_GET_TAG_INFO is used to get information about the tag structure 
 * (tag id, block count, block size).
 */
-(SendStatus*) getTagInfo: (RfidTag*) tag;

/**
 * readBlock - 
 * 
 * Sends a CI_READ_BLOCK command to IDBLUE
 *
 * @param tag The tag id of the tag to read the block from. Set to all zeros to 
 * read from any tag.
 * @param blockIndex the index of the block to read from, between 0 and n-1 
 * (where n is the number of blocks on the tag).
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) readBlock: (byte) blockIndex {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     status = [api readBlock: tag
 *                    withBlockIndex: blockIndex
 *                      withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 * }
 *
 * -(void) readBlockResponse: (IDBlueCommand*) command withResponse: (ReadBlockResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     CByteArray* blockData = [response blockData];
 *     byte blockIndex = [response blockIndex];
 * }
 *
 * -(void) readBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CI_READ_BLOCK is used to read a single block from user memory of 
 * an RFID tag.
 */
-(SendStatus*) readBlock: (RfidTag*) tag
			   withBlockIndex: (byte) blockIndex
				 withHandler: (id<IHfResponseHandler>) handler;
		
/**
 * readBlock - 
 * 
 * Sends a CI_READ_BLOCK command to IDBLUE
 *
 * @param tag The tag id of the tag to read the block from. Set to all zeros to 
 * read from any tag.
 * @param blockIndex the index of the block to read from, between 0 and n-1 
 * (where n is the number of blocks on the tag).
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) readBlock: (byte) blockIndex {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     status = [api readBlock: tag
 *                    withBlockIndex: blockIndex];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 * }
 *
 * -(void) readBlockResponse: (IDBlueCommand*) command withResponse: (ReadBlockResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     CByteArray* blockData = [response blockData];
 *     byte blockIndex = [response blockIndex];
 * }
 *
 * -(void) readBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * 
 * @return A SendStatus indicating if the send was successful
 * @remarks CI_READ_BLOCK is used to read a single block from user memory of 
 * an RFID tag.
 */		
-(SendStatus*) readBlock: (RfidTag*) tag
			   withBlockIndex: (byte) blockIndex;

/**
 * readBlocks - 
 * 
 * Sends a CI_READ_BLOCKS command to IDBLUE
 * 
 * @param tag The tag id of the tag to read the block from. Set to all zeros to 
 * read from any tag.
 * @param blockIndex the start index of the block to read from, between 0 and n-1 
 * (where n is the number of blocks on the tag).
 * @param blockCount the number of blocks to read
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) readBlocks: (byte) blockIndex withBlockCount: (byte) blockCount {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     status = [api readBlocks: tag
 *                     withBlockIndex: blockIndex
 *                     withBlockCount: blockCount];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 * }
 *
 * -(void) readBlocksResponse: (IDBlueCommand*) command withResponse: (ReadBlocksResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     CByteArray* blockData = [response blockData];
 *     byte blockIndex = [response blockIndex];
 *     byte blockCount = [response blockCount];
 * }
 *
 * -(void) readBlocksFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 * @remarks CI_READ_BLOCKS is used to read multiple blocks of user memory from 
 * an RFID tag.
 */
-(SendStatus*) readBlocks: (RfidTag*) tag
				withBlockIndex: (byte) blockIndex
				withBlockCount: (byte) blockCount
				  withHandler: (id<IHfResponseHandler>) handler;
				  
-(SendStatus*) readBlocks: (RfidTag*) tag
				withBlockIndex: (byte) blockIndex
				withBlockCount: (byte) blockCount;

/**
 * writeBlock - 
 *
 * Sends a CI_WRITE_BLOCK command to IDBLUE
 *
 * @param tag The RfidTag to write to
 * @param blockIndex The block index to start writing at
 * @param block The block data to write to the tag
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) writeBlock: (byte) blockIndex {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: 4];
 *     status = [api writeBlock: tag
 *                     withBlockIndex: blockIndex
 *                      withBlockData: blockData
 *                       withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 *     [blockData release];
 * }
 *
 * -(void) writeBlockResponse: (IDBlueCommand*) command withResponse: (WriteBlockResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockIndex = [response blockIndex];
 * }
 *
 * -(void) writeBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) writeBlock: (RfidTag*) tag
				withBlockIndex: (byte) blockIndex
				 withBlockData: (CByteArray*) block
				  withHandler: (id<IHfResponseHandler>) handler;
			
/**
 * writeBlock - 
 *
 * Sends a CI_WRITE_BLOCK command to IDBLUE
 *
 * @param tag The RfidTag to write to
 * @param blockIndex The block index to start writing at
 * @param block The block data to write to the tag
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) writeBlock: (byte) blockIndex {
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: 4];
 *     status = [api writeBlock: tag
 *                     withBlockIndex: blockIndex
 *                      withBlockData: blockData];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 *     [blockData release];
 * }
 *
 * -(void) writeBlockResponse: (IDBlueCommand*) command withResponse: (WriteBlockResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockIndex = [response blockIndex];
 * }
 *
 * -(void) writeBlockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */			
-(SendStatus*) writeBlock: (RfidTag*) tag
				withBlockIndex: (byte) blockIndex
				 withBlockData: (CByteArray*) block;

/**
 * writeBlocks - 
 *
 * Sends a CI_WRITE_BLOCKS command to IDBLUE
 *
 * @param tag The RfidTag to write to
 * @param blockIndex The block index to start writing at
 * @param blockCount The number of blocks to write
 * @param blocks The block data to write to the tag
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) writeBlocks: (byte) blockIndex withBlockCount: (byte) blockCount{
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     int bytesPerBlock = 4;
 *     int blockDataLen = bytesPerBlock * blockCount;
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: blockDataLen];
 *     status = [api writeBlocks: tag
 *                      withBlockIndex: blockIndex
 *                      withBlockCount: blockCount
 *                       withBlockData: blockData
 *                        withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 *     [blockData release];
 * }
 *
 * -(void) writeBlocksResponse: (IDBlueCommand*) command withResponse: (WriteBlocksResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockIndex = [response blockIndex];
 *     byte blockCount = [response blockCount];
 * }
 *
 * -(void) writeBlocksFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) writeBlocks: (RfidTag*) tag
				 withBlockIndex: (byte) blockIndex
				 withBlockCount: (byte) blockCount
				  withBlockData: (CByteArray*) blocks
				   withHandler: (id<IHfResponseHandler>) handler;
		
/**
 * writeBlocks - 
 *
 * Sends a CI_WRITE_BLOCKS command to IDBLUE
 *
 * @param tag The RfidTag to write to
 * @param blockIndex The block index to start writing at
 * @param blockCount The number of blocks to write
 * @param blocks The block data to write to the tag
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) writeBlocks: (byte) blockIndex withBlockCount: (byte) blockCount{
 *     SendStatus status = nil;
 *     RfidTag* tag = [[RfidTag alloc] initWithArrayLength: 8];
 *     int bytesPerBlock = 4;
 *     int blockDataLen = bytesPerBlock * blockCount;
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: blockDataLen];
 *     status = [api writeBlocks: tag
 *                      withBlockIndex: blockIndex
 *                      withBlockCount: blockCount
 *                       withBlockData: blockData];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [tag release];
 *     [blockData release];
 * }
 *
 * -(void) writeBlocksResponse: (IDBlueCommand*) command withResponse: (WriteBlocksResponse*) response {
 *     RfidTag* tag = [response rfidTag];
 *     IDBlueTimestamp* ts = [response scanTime];
 *     byte blockIndex = [response blockIndex];
 *     byte blockCount = [response blockCount];
 * }
 *
 * -(void) writeBlocksFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */		
-(SendStatus*) writeBlocks: (RfidTag*) tag
				 withBlockIndex: (byte) blockIndex
				 withBlockCount: (byte) blockCount
				  withBlockData: (CByteArray*) blocks;

/**
 * getBlockIndex - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Index property
 *
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockIndex {
 *     SendStatus status = nil;
 *     status = [api getBlockIndex: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockIndexResponse: (IDBlueCommand*) command withResponse: (BlockIndexProperty*) response {
 *     byte index = [response blockIndex];
 * }
 *
 * -(void) getBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockIndex: (id<IHfResponseHandler>) handler;

/**
 * getBlockIndex - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Index property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockIndex {
 *     SendStatus status = nil;
 *     status = [api getBlockIndex];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockIndexResponse: (IDBlueCommand*) command withResponse: (BlockIndexProperty*) response {
 *     byte index = [response blockIndex];
 * }
 *
 * -(void) getBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockIndex;

/**
 * getBlockCount - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Count property
 *
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockCount {
 *     SendStatus status = nil;
 *     status = [api getBlockCount: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockCountResponse: (IDBlueCommand*) command withResponse: (BlockCountProperty*) response {
 *     byte count = [response blockCount];
 * }
 *
 * -(void) getBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockCount: (id<IHfResponseHandler>) handler;

/**
 * getBlockCount - 
 *
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Count property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockCount {
 *     SendStatus status = nil;
 *     status = [api getBlockCount];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockCountResponse: (IDBlueCommand*) command withResponse: (BlockCountProperty*) response {
 *     byte count = [response blockCount];
 * }
 *
 * -(void) getBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockCount;

/**
 * getBlockData - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Data property
 *
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockData {
 *     SendStatus status = nil;
 *     status = [api getBlockData: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockDataResponse: (IDBlueCommand*) command withResponse: (BlockDataProperty*) response {
 *     CByteArray* blockData = [response blockData];
 * }
 *
 * -(void) getBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockData: (id<IHfResponseHandler>) handler;

/**
 * getBlockData - 
 * 
 * Sends a CI_GET_PROPERTY command to IDBLUE to get the Block Data property
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) getBlockData {
 *     SendStatus status = nil;
 *     status = [api getBlockData];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) getBlockDataResponse: (IDBlueCommand*) command withResponse: (BlockDataProperty*) response {
 *     CByteArray* blockData = [response blockData];
 * }
 *
 * -(void) getBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) getBlockData;

/**
 * setBlockIndex - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Block Index property.
 *
 * @param blockIndex
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockIndex: (byte) index {
 *     SendStatus status = nil;
 *     status = [api setBlockIndex: index
 *                          withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBlockIndexResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBlockIndex: (byte) blockIndex
					 withHandler: (id<IHfResponseHandler>) handler;
	
/**
 * setBlockIndex - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Block Index property.
 *
 * @param blockIndex
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockIndex: (byte) index {
 *     SendStatus status = nil;
 *     status = [api setBlockIndex: index];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBlockIndexResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockIndexFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setBlockIndex: (byte) blockIndex;

/**
 * setBlockCount - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Block Count property.
 *
 * @param blockCount
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockCount: (byte) count {
 *     SendStatus status = nil;
 *     status = [api setBlockCount: count
 *                          withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBlockCountResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBlockCount: (byte) blockCount
					 withHandler: (id<IHfResponseHandler>) handler;
			
/**
 * setBlockCount - 
 * 
 * Sends a CI_SET_PROPERTY command to IDBLUE to set the Block Count property.
 *
 * @param blockCount
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockCount: (byte) count {
 *     SendStatus status = nil;
 *     status = [api setBlockCount: count];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) setBlockCountResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockCountFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */			
-(SendStatus*) setBlockCount: (byte) blockCount;

/**
 * setBlockData - 
 * 
 * Sets the Block Data property of an IDBLUE device.
 *
 * @param blockData The block data that will be written to
 * an RFID tag during an asynchronous write block operation,
 * if the connected mode of IDBLUE is set to CM_WRITE_BLOCK.
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockData {
 *     SendStatus status = nil;
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: 4];
 *     status = [api setBlockData: blockData
 *                         withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [blockData release];
 * }
 *
 * -(void) setBlockDataResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) setBlockData: (CByteArray*) blockData
					withHandler: (id<IHfResponseHandler>) handler;
	
/**
 * setBlockData - 
 * 
 * Sets the Block Data property of an IDBLUE device.
 *
 * @param blockData The block data that will be written to
 * an RFID tag during an asynchronous write block operation,
 * if the connected mode of IDBLUE is set to CM_WRITE_BLOCK.
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueCoreApi* api;
 * -(void) setBlockData {
 *     SendStatus status = nil;
 *     CByteArray* blockData = [[CByteArray alloc] initWithArrayLength: 4];
 *     status = [api setBlockData: blockData];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 *     [blockData release];
 * }
 *
 * -(void) setBlockDataResponse: (IDBlueCommand*) command withResponse: (IDBlueResponse*) response {
 * }
 * -(void) setBlockDataFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */	
-(SendStatus*) setBlockData: (CByteArray*) blockData;
@end
