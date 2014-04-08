
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "TimestampResponse.h"

@interface EpcReadTagResponse : TimestampResponse {
@private
    CByteArray* _tagData;
}

-(CByteArray*) tagData;

@end
