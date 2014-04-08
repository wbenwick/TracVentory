
// Copyright © 2013 Cathexis Innovations Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import "SimpleResponse.h"

/**
 * ButtonPressResponse is used to process asynchronous button press responses
 * from IDBLUE. IDBLUE sends the asynchronous button press even when the
 * connected mode is set to REACTIVE (CM_REACTIVE), and the front button
 * of IDBLUE is pressed, while connected to a host.
 */
@interface ButtonPressResponse : SimpleResponse {
    
}

@end
