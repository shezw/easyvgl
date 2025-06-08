/**
    -----------------------------------------------------------

 	easyVGL
 	porting/api.h  2025/6/8

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_PORTING_API_H
#define EVG_PORTING_API_H

#include "utils.h"

#include "api/mutex.h"
#include "api/wlan.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef void (*GlobalInputEventCB) ( int x, int y, int eventType );

int  watchGlobalInputEvent( GlobalInputEventCB cb );
void unwatchGlobalInputEvent( int fd );

void notifyGlobalInputEvent( int x, int y, int eventType );

void porting_init(char *display, char *input);

void porting_loop_ns(unsigned int nanosecond);

void porting_loop_wasm( void * arg );

void setLoopCaller( LoopCaller caller );

#ifdef __cplusplus
}
#endif

#endif //EVG_PORTING_API_H
