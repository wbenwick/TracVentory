
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>

void DebugLog(NSString* format, ...);

typedef unsigned char byte;

typedef enum _Endianness {
    MSB,
    LSB
} Endianness;

/**
 * CommandIdentifier enumeration defines all the valid
 * IDBLUE command identifiers (aka command headers).
 */
typedef enum _CommandIdentifier {
	CI_NO_OP			= 0x00,
	CI_GET_TAG_ID			= 0x01,
	CI_BEEP = 0x03,
	
	CI_SET_PROPERTY = 0x08,
	CI_GET_PROPERTY = 0x09,
	
	CI_SAVE_PROPERTIES = 0x10,
	CI_LOAD_PROPERTIES = 0x11,
	
	CI_READ_BLOCK		= 0x12,
	CI_READ_BLOCKS		= 0x13,
	CI_WRITE_BLOCK		= 0x15,
	CI_WRITE_BLOCKS	= 0x16,
	CI_GET_TAG_INFO	= 0x18,
	CI_LOCK_BLOCK		= 0x19,
	
	//UHF
	CI_WRITE_UHF       = 0x36,
	CI_READ_UHF        = 0x37,
	CI_LOCK_UHF        = 0x38,
	CI_SET_KILL_PWD    = 0x39,
	CI_KILL            = 0x3A,
	
	
	CI_GET_STATUS		= 0x23,
	
	CI_SET_SCANNING	= 0x32,
	
	CI_BOOTLOADER_MODE = 0x3c,
	
	CI_SET_BT_PIN      = 0x40,
	CI_GET_BT_PIN		= 0x41,
	
	CI_SET_BT_NAME		= 0x42,
	CI_GET_BT_NAME		= 0x43,
	
	CI_BOOTLOADER_ACTIVE = 0x5e,
	
	CI_GET_ENTRY_COUNT = 0x60,
	CI_GET_ENTRY = 0x61,
	CI_CLEAR_ENTRIES = 0x62,
	
	CI_ASYNC_PACKET = 0x70,
	
	CI_FACTORY_RESET = 0x74,
	
	CI_BEGIN_COMMANDS		= 0x80,
	CI_END_COMMANDS		= 0x88,
	
	CI_POWER_DOWN		= 0x91,
	CI_TURN_OFF_BT		= 0x92,
	CI_TURN_ON_BT     = 0x93,
	
	CI_HEARTBEAT = 0x96,
	CI_ENABLE_CHANNEL = 0x97,
	
	CI_NACK			= 0x1F,
	CI_BUTTON			= 0xFF
} CommandIdentifier;

/**
 * CommandStatus enumeration defines the possible error
 * codes returned in a response
 */
typedef enum _CommandStatus {
	
	/** The indicated command completed successfully */
	CS_Ok = 0x00,
	
	/** The driver received a NACK (No-Acknowledge) from the IDBLUE device */
	CS_Failed = 0x01,
	
	/** There was an internal error attempting to execute the indicated command */
	CS_Error = 0x02,
	
	/** The function requested is not implemented */
	CS_NotImplemented = 0x03,
	
	/** The indicated command timed out */
	CS_Timeout = 0x04,
	
	/** The command identifier is not recognized */
	CS_InvalidCommandIdentifier = 0x05,
	
	/** The specified operation is not permitted */
	CS_NotPermitted = 0x06,
	
	/** The computed checksum did not match the checksum in the command. */
	CS_ChecksumFailed = 0x07,
	
	/** The command sent to IDBLUE is deprecated */
	CS_Deprecated = 0x08,
	
	/** An invalid property value was specified. */
	CS_InvalidProperty = 0x51,
	
	/** The specified property value is not of the correct type or within the allowed range. */
	CS_InvalidValue = 0x52,
	
	/** An invalid index value was specified. */
	CS_InvalidIndex = 0x53,
	
	/** 
	 * The number of blocks to read/write for the READ_BLOCKS and WRITE_BLOCKS commands exceeds 
	 * the available blocks on the tag. Reserved for future use.
	 */
	CS_TagBlockCountExceeded = 0x54,
	
	/** An internal IDBLUE buffer overflow has occurred. */
	CS_BufferOverflow = 0x55,
	
	/** The requested read operation was incomplete. */
	CS_IncompleteOperation = 0x56,
	
	/**
	 * This indicates the Beep command was executed but no tone was emitted because the 
	 * BuzzerEnabled property is disabled.
	 */
	CS_Muted = 0x57,
	
	/** No data was received from the IDBLUE device */
	CS_NoData = 0x1000,
	
	/** IDBLUE is in bootloader mode */
	CS_Bootloader = 0x1002,
	
	/** IDBLUE is in the process of being disposed */
	CS_IDBlueDriverDisposing = 0x1003,
	
	/** IDBLUE driver is not ready (e.g. IDBLUE driver disconnecting) */
	CS_IDBlueDriverNotReady = 0x1004,
	
	/** The command executed but IDBLUE does not send a response (e.g. power off) */
	CS_NoResponseRequired = 0x1005,
	
	/** An invalid command was processed. */
	CS_InvalidData = 0x1007
} CommandStatus;

/** BeeptType enumeration defines the supported beep types. */
typedef enum _BeepType {
	BT_Low = 0,
	BT_High = 1,
	BT_High2Low = 2,
	BT_Low2High = 3,
	BT_LowLow = 4,
	BT_HighHigh = 5	
} BeepType;

/** PropertyIdentifier enumeration contains the list of all IDBLUE properties */
typedef enum _PropertyIdentifier {
	PI_ContinuousScanEnabled = 0x00,
	PI_RequireTimestamp = 0x01,
	PI_DuplicateElimination = 0x02,
	PI_Timestamp = 0x03,
	PI_DisconnectedMode = 0x04,
	PI_ConnectedMode = 0x05,
	PI_RfidProtocol = 0x06,
	PI_BuzzerEnabled = 0x07,
	PI_DeviceTimeout = 0x08,
	PI_RfidTimeout = 0x09,
	PI_BluetoothTimeout = 0x0A,
	PI_ContinuousScanTimeout = 0x0B,
	PI_BlockIndex = 0x0C,
	PI_BlockData = 0x0D,
	PI_BlockCount = 0x0E,
	PI_VersionInfo = 0x17,
	PI_BootloaderVersion = 0x18,
	PI_HoldToScan = 0x19,
	PI_ConnectToHost = 0x20,
	PI_ActionButtonEnabled = 0x21
} PropertyIdentifier;

/** Whether the Property is a get or set property */
typedef enum _PropertyType {
    PT_Get,
    PT_Set
} PropertyType;

/**
 * ConnectedMode enumeration defines the supported
 * asynchronous operations an IDBLUE device can 
 * perform while connected to a host. 
 */
typedef enum _ConnectedMode {
	/** 
	 * IDBLUE just sends a CI_BUTTON packet back to the host.
	 * No RFID operation is performed.
	 */
	CM_REACTIVE = 0x01,
	
	/**
	 * IDBLUE scans for an RFID tag, and returns 
	 * a CI_GET_TAG_ID packet back to the host containing
	 * the tag id and timestamp of the tag scanned, 
	 * or NACK if no tag was found. 
	 */
	CM_TAGID = 0x03,
	
	/** 
	 * IDBLUE scans for an RFID tag, and returns a CI_READ_BLOCK
	 * packet containing the tag id, timestamp, block index and 
	 * block data of the tag read, or NACK if not tag was found.
	 * The index of the block read is configured using the 
	 * PI_BLOCK_INDEX property.
	 */
	CM_READ_BLOCK = 0x04,
	
	/** 
	 * IDBLUE scans for an RFID tag, and writes a block of data to
	 * the tag. It returns a CI_WRITE_BLOCK packet if succesful,
	 * containing the tag id, timestamp and block index written,
	 * or a NACK response if no tag was found or the tag could not
	 * be written. The index of the block to write is configured
	 * with the PI_BLOCK_INDEX property, and the block data to
	 * be written is configured with the PI_BLOCK_DATA property.
	 */
	CM_WRITE_BLOCK = 0x05,
	
	/** 
	 * IDBLUE scans for an RFID tag, and returns a CI_READ_BLOCKS
	 * packet containing the tag id, timestamp, block index, 
	 * block count and block data read if successful, or a NACK
	 * if the read blocks operation failed. The block index and block
	 * block count to be read are configured with the PI_BLOCK_INDEX
	 * AND PI_BLOCK_COUNT properties, respectively.
	 */
	CM_READ_BLOCKS = 0x06
} ConnectedMode;

/**
 * DisconnectedMode enumeration defines the supported asynchronous operations an 
 * IDBLUE device can perform without being connected to a host.
 */
typedef enum _DisconnectedMode {
	/** Verify tag */
	DM_TAG_VERIFY = 0x00,
	
	/** Store tag information */
	DM_TAG_STORE = 0x01,
} DisconnectedMode;

/**
 * RfidProtocol enumeration defines all the supported RFID protocols for an 
 * IDBLUE device.
 */
typedef enum _RfidProtocol {
	RP_ISO15693 = 0x01,
    RP_TAGIT = 0x02,
	RP_EPC_GEN2 = 0x20
} RfidProtocol;

/**
 * The maximum length of a packet sent to or received from an
 * IDBLUE device.
 */
#define MAX_PACKET_SIZE 256

/**
 * The minimum length of a packet includes a header byte, 2 length
 * bytes followed by a checksum byte.
 */
#define MIN_PACKET_SIZE 4

/** 
 * The maximum number of bytes that can be stored in the payload
 * is the maxiumum length of a packet less the header byte,
 * 2 length bytes and the checksum byte.
 */
#define MAX_PAYLOAD_SIZE (MAX_PACKET_SIZE - MIN_PACKET_SIZE)


/**
 * IDBlue should not be instantiated. It only contains static methods
 */
@interface IDBlue : NSObject {
}

/**
 * Enable or disable logging inside the IDBLUE iOS SDK
 * @param enabled Whether logging is to be enabled or disabled
 */
+(void) enableDebugLog: (BOOL) enabled;

/**
 * Get whether logging is enabled in the IDBLUE iOS SDK
 */
+(BOOL) debugLogEnabled;

/**
 * Convert an NSString object into an array of (ascii character) bytes.
 * @param s the string to be converted
 * @param data pointer to the byte array to receive the ascii bytes
 * @param maxLen the maximum number of bytes that can be put into the buffer
 * (i.e. the length of the byte array).
 * @return the number of ascii characters copied into the byte array.
 */
+(int) toAsciiByteArray: (NSString*) s withData: (byte*) data withMaxLen: (int) maxLen;

/**
 * Convert a byte array of ascii characters into an NSString object
 * @param data the byte array to copy from
 * @param len the number of bytes to copy
 * @return An NSString object containing the specified ascii characters if data is not nil and len > 0.
 * Otherwise, nil is returned.
 */
+(NSString*) getStringFromAscii: (byte*) data withLen: (int) len;

/**
 * Convert an array of bytes into hex values in string format
 * @param data the array of bytes to be converted
 * @param dataLen the number of bytes to convert
 * @return an NSString object containing the hex values of all the bytes, separated by spaces.
 * Returns nil if data is nil or dataLen <= 0
 */
+(NSString*) getHexString: (byte*) data withDataLen: (int) dataLen;

/**
 * Convert an array of bytes into a tag id string. The byte array is traversed in
 * reverse order, and each byte is converted to a 2 character hex string and appended
 * to the end of the tag id string.
 * @param data The byte array to convert to a tag id.
 * @param dataLen The number of bytes to convert
 * @return An NSString object containing the tag id if data is not nil and dataLen > 0, 
 * otherwise nil is returned.
 */
+(NSString*) getHexStringReversed: (byte*) data withDataLen: (int) dataLen;

/**
 * Convert a partial array of bytes into a tag id string. The byte array is traversed in
 * reverse order, and each byte is converted to a 2 character hex string and appended
 * to the end of the tag id string.
 * @param data The byte array to convert to a tag id
 * @param dataLen The number of bytes stored in the byte array
 * @param index The index in the byte array to start copying from
 * @param count The number of characters to convert
 * @return An NSString object containing the tag id if data is not nil, dataLen > 0,
 * and index / count form a sub array that is completely contained in the given array,
 * otherwise nil is returned. 
 */
+(NSString*) getHexStringReversed: (byte*) data withDataLen: (int) dataLen withIndex: (int) index withCount: (int)count;

/**
 * Convert a tag id string into a byte array.
 * @param tagId the tag id string to convert to a byte array. It should be of even length
 * and every 2 characters represents a single byte of data in hex. 
 * @param dest the byte array that will receive the converted data. 
 * @param len the length of the byte array
 * @return the number of bytes copied
 * @remarks The byte array will be in reverse order of the bytes in the tag id string.
 */
+(int) getTagIdBytes: (NSString*) tagId withDest: (byte*) dest withLen: (int) len;

+(void) reverseByteArray: (byte*) data withLen: (int) len;

/**
 * Determines if the given string contains all numeric values
 * @param s The string to check for numeric
 * @return TRUE if the given string has all numeric characters, FALSE
 * otherwise. If the string is nil or empty, FALSE is returned.
 */
+(BOOL) isNumeric: (NSString*) s;

/**
 * Check if the 2 byte arrays contain the same data.
 * @param array1
 * @param len1
 * @param array2
 * @param len2
 * @return TRUE if the arrays are the same length and contains the same data (or are both nil). 
 * Otherwise, returns FALSE.
 */
+(BOOL) compareArrays: (byte*) array1 withLen1: (int) len1 withArray2: (byte*) array2 withLen2: (int) len2;

/**
 * Converts a high byte and a low byte into a word (ushort).
 * @param highAndLow byte array containing 2 bytes (high and low)
 * @return The ushort value formed by left shifting the high byte 8 bits to the left, then oring the low byte.
 */
+(ushort) makeWord: (byte*) highAndLow;

/**
 * Converts a high byte and a low byte into a word (ushort).
 * @param high the high byte
 * @param low the low byte
 * @return The ushort value formed by left shifting the high byte 8 bits to the left, then oring the low byte.
 */
+(ushort) makeWord: (byte) high withLow: (byte) low;

/**
 * The reverse of makeWord. Get the high byte and low byte from the given word, and 
 * copy them into the specified locations.
 * @param word the word to get
 * @param high location of the high byte
 * @param low location of the low byte
 */
+(void) getWord: (ushort) word withHigh: (byte*) high withLow: (byte*) low;

+(void) getDoubleWord: (uint) dword withDest: (byte*) dest;
+(uint) makeDoubleWord: (byte*) src;


/**
 * Compute the checksum of count bytes in the given array (starting at index 0).
 * The checksum is computed by XOR'ing all the bytes.
 * @param data The byte array to compute the checksum for
 * @param count The number of bytes to be included in the checksum
 * @return The XOR of all the bytes (i.e. the checksum)
 */
+(byte) computeChecksum: (byte*) data withCount: (int) count;

/**
 * Determine if the given command header is a valid IDBLUE command header (i.e. it is contained in the 
 * CommandIdentifier enumeration).
 * @param cmd the byte header to check 
 * @return TRUE if the given header is a valid IDBLUE command, FALSE otherwise.
 */
+(BOOL) isValidCommand: (int) cmd;

/**
 * Get command name from the given command identifier
 * @param cmd The command identifier of the command to get the name of
 * @return the name of the command, if the command is valid, otherwise
 * the hex value of the specified command identifier. 
 */
+(NSString*) convertCommandToString: (CommandIdentifier) cmd;

/**
 * Get property name from the given property identifier
 * @param property The property identifier of the property to get the name of
 * @return the name of the property, if the property is valid, otherwise
 * the hex value of the specified property identifier.
 */
+(NSString*) convertPropertyToString: (PropertyIdentifier) property;

/**
 * Gets command status name from the given command status identifier.
 * @param status the command status identifier of the command status to get the name of
 * @return the name of the command status, if the command status is valid, otherwise
 * the hex value of the specified command status identifier.
 */
+(NSString*) convertCommandStatusToString: (CommandStatus) status;

/**
 * Get the connected mode name from the given ConnectedMode enumeration value
 * @param mode The ConnectedMode to get the name of
 * @return The name of the ConnectedMode
 */
+(NSString*) convertConnectedModeToString: (ConnectedMode) mode;

/**
 * Get the disconnected mode name from the given DisconnectedMode enumeration value
 * @param mode The DisconnectedMode to get the name of
 * @return The name of the DisconnectedMode
 */
+(NSString*) convertDisconnectedModeToString: (DisconnectedMode) mode;

@end

