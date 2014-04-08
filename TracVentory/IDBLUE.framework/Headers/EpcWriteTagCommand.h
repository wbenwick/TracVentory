
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "IDBlueCommand.h"

@interface EpcWriteTagCommand : IDBlueCommand {
    
}

-(id) initWithBank:(byte) bank 
          withAddr:(byte) addr
      withNumWords:(byte) numWords 
          withData:(byte*) data 
           withLen:(int) len;

@end
