
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCoreApi.h"
#import "UhfResponseHandler.h"

typedef enum _EpcMemoryBank {
    BANK_RESERVED = 0,
    BANK_EPC = 1,
    BANK_TID = 2,
    BANK_USER = 3
} EpcMemoryBank;

/**
 * IDBlueUhfApi is used to issue EPC Gen 2 (UHF) commands to IDBLUE
 */
@interface IDBlueUhfApi : IDBlueCoreApi <IUhfResponseHandler> {
    
}

/**
 * epcRead -
 *
 * Read data from an EPC Gen 2 RFID tag
 *
 * @param bank
 * @param addr
 * @param numWords
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcRead: (EpcMemoryBank) bank withAddr: (byte) addr withNumWords: (byte) numWords {
 *     SendStatus status = nil;
 *     status = [api epcRead: bank withAddr: addr withNumWords: withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcReadResponse: (IDBlueCommand*) command withResponse: (EpcReadTagResponse*) response {
 * }
 *
 * -(void) epcReadFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcRead: (EpcMemoryBank) bank 
                   withAddr: (byte) addr 
               withNumWords: (byte) numWords
               withHandler: (id<IUhfResponseHandler>) handler;
		
/**
 * epcRead -
 *
 * Read data from an EPC Gen 2 RFID tag
 *
 * @param bank
 * @param addr
 * @param numWords
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcRead: (EpcMemoryBank) bank withAddr: (byte) addr withNumWords: (byte) numWords {
 *     SendStatus status = nil;
 *     status = [api epcRead: bank withAddr: addr withNumWords: withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcReadResponse: (IDBlueCommand*) command withResponse: (EpcReadTagResponse*) response {
 * }
 *
 * -(void) epcReadFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */		
-(SendStatus*) epcRead: (EpcMemoryBank) bank 
                   withAddr: (byte) addr 
               withNumWords: (byte) numWords;


/**
 * epcWrite -
 *
 * Write data to an EPC Gen 2 RFID Tag
 *
 * @param bank
 * @param addr
 * @param numWords
 * @param data
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcWrite: (EpcMemoryBank) bank withAddr: (byte) addr withNumWords: (byte) numWords withData:(CByteArray*) data {
 *     SendStatus status = nil;
 *     status = [api epcWrite: bank withAddr: addr withNumWords: numWords withData: data withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcWriteResponse: (IDBlueCommand*) command withResponse: (EpcWriteTagResponse*) respons {
 * }
 * 
 * -(void) epcWriteFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcWrite: (EpcMemoryBank) bank
                    withAddr: (byte) addr
                withNumWords: (byte) numWords
                    withData: (CByteArray*) data
                withHandler: (id<IUhfResponseHandler>) handler;

/**
 * epcWrite -
 *
 * Write data to an EPC Gen 2 RFID Tag
 *
 * @param bank
 * @param addr
 * @param numWords
 * @param data
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcWrite: (EpcMemoryBank) bank withAddr: (byte) addr withNumWords: (byte) numWords withData:(CByteArray*) data {
 *     SendStatus status = nil;
 *     status = [api epcWrite: bank withAddr: addr withNumWords: numWords withData: data withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcWriteResponse: (IDBlueCommand*) command withResponse: (EpcWriteTagResponse*) respons {
 * }
 * 
 * -(void) epcWriteFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcWrite: (EpcMemoryBank) bank
                    withAddr: (byte) addr
                withNumWords: (byte) numWords
                    withData: (CByteArray*) data;
					
/**
 * epcLock - 
 *
 * Lock portions of an EPC Gen 2 RFID tag
 *
 * @param lockbits The payload of the EPCGlobal UHF Class 1 Gen 2 Standard Lock
 * command. Only the least significant 20 bits are used, so lockbits cannot be
 * larger than 0x0FFFFF. See the EPCGlobal UHF Class 1 Gen 2 Standard to
 * determine the appropriate value of lockbits.
 *
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcLock: (uint) lockbits {
 *     SendStatus status = nil;
 *     status = [api epcLock: lockbits withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcLockResponse: (IDBlueCommand*) command withResponse: (EpcLockResponse*) response {
 * }
 *
 * -(void) epcLockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcLock: (uint) lockbits
               withHandler: (id<IUhfResponseHandler>) handler;

/**
 * epcLock - 
 *
 * Lock portions of an EPC Gen 2 RFID tag
 *
 * @param lockbits The payload of the EPCGlobal UHF Class 1 Gen 2 Standard Lock
 * command. Only the least significant 20 bits are used, so lockbits cannot be
 * larger than 0x0FFFFF. See the EPCGlobal UHF Class 1 Gen 2 Standard to
 * determine the appropriate value of lockbits.
 *
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcLock: (uint) lockbits {
 *     SendStatus status = nil;
 *     status = [api epcLock: lockbits withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcLockResponse: (IDBlueCommand*) command withResponse: (EpcLockResponse*) response {
 * }
 *
 * -(void) epcLockFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcLock: (uint) lockbits;
			   
/**
 * epcKill -
 *
 * Kill an EPC Gen 2 RFID tag
 *
 * @param password
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcKill: (CByteArray*) password {
 *     SendStatus status = nil;
 *     status = [api epcKill: password withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcKillResponse: (IDBlueCommand*) command withResponse: (EpcKillResponse*) response {
 * }
 *
 * -(void) epcKillFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcKill: (CByteArray*) password
               withHandler: (id<IUhfResponseHandler>) handler;

/**
 * epcKill -
 *
 * Kill an EPC Gen 2 RFID tag
 *
 * @param password
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcKill: (CByteArray*) password {
 *     SendStatus status = nil;
 *     status = [api epcKill: password withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcKillResponse: (IDBlueCommand*) command withResponse: (EpcKillResponse*) response {
 * }
 *
 * -(void) epcKillFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcKill: (CByteArray*) password;
			   
/**
 * epcSetKillPassword -
 *
 * Set the kill password of an EPC Gen 2 RFID tag
 *
 * @param password
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcSetKillPassword: (CByteArray*) password {
 *     SendStatus status = nil;
 *     status = [api epcSetKillPassword: password withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcSetKillPasswordResponse: (IDBlueCommand*) command withResponse: (EpcSetKillPasswordResponse*) response {
 * }
 * 
 * -(void) epcSetKillPasswordFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcSetKillPassword: (CByteArray*) password
               withHandler: (id<IUhfResponseHandler>) handler;

/**
 * epcSetKillPassword -
 *
 * Set the kill password of an EPC Gen 2 RFID tag
 *
 * @param password
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcSetKillPassword: (CByteArray*) password {
 *     SendStatus status = nil;
 *     status = [api epcSetKillPassword: password withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcSetKillPasswordResponse: (IDBlueCommand*) command withResponse: (EpcSetKillPasswordResponse*) response {
 * }
 * 
 * -(void) epcSetKillPasswordFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 */
-(SendStatus*) epcSetKillPassword: (CByteArray*) password;
			   
/**
 * epcWriteTagId -
 *
 * Writes the EPC identifier to the EPC Gen 2 RFID tag
 *
 * @param tag
 * @param handler An object implementing IUhfResponseHandler that will receive response notifications. 
 * 
 * @remarks The given IResponseHandler will be notified of responses,
 * along with any handlers registered with the addResponseHandler method
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcWriteTagId: (RfidTag*) tag {
 *     SendStatus status = nil;
 *     status = [api epcWriteTagId: tag withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcWriteResponse: (IDBlueCommand*) command withResponse: (EpcWriteTagResponse*) respons {
 * }
 * 
 * -(void) epcWriteFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 *
 * @remarks epcWriteTagId is a wrapper around epcWrite, specifying the address of the EPC location on the tag 
 */
-(SendStatus*) epcWriteTagId:(RfidTag*) tag withHandler:(id<IUhfResponseHandler>) handler;

/**
 * epcWriteTagId -
 *
 * Writes the EPC identifier to the EPC Gen 2 RFID tag
 *
 * @param tag
 * 
 * @remarks Handlers registered with addResponseHandler will receive response notifications.
 *
 * For example:
 * 
 * IDBlueUhfApi* api;
 * -(void) epcWriteTagId: (RfidTag*) tag {
 *     SendStatus status = nil;
 *     status = [api epcWriteTagId: tag withHandler: self];
 *     if ([status successful]) {
 *     }
 *     else {
 *     }
 * }
 *
 * -(void) epcWriteResponse: (IDBlueCommand*) command withResponse: (EpcWriteTagResponse*) respons {
 * }
 * 
 * -(void) epcWriteFailed: (IDBlueCommand*) command withResponse: (NackResponse*) response {
 * }
 *
 *
 * @return A SendStatus indicating if the send was successful
 *
 * @remarks epcWriteTagId is a wrapper around epcWrite, specifying the address of the EPC location on the tag 
 */
-(SendStatus*) epcWriteTagId:(RfidTag*) tag;

@end
