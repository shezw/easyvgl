/**
    -----------------------------------------------------------

 	easyVGL
 	modules/timer.h    2025/6/8

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_UIKIT_TIME_MANAGE_H
#define EVG_UIKIT_TIME_MANAGE_H

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TimeUpdateNotify) ( const char * timeStr, int YYYY, int Mon, int D, int H, int Min, int Sec );
typedef void (*TimeSyncedNotify) ( void );

/**
 * get TimeStamp (time_t) from str
 * @param timeStr "%Y-%m-%d %H:%M:%S"
 * @return
 * @example
    printf("%ld\n",strToTimeStamp( "2023-10-25 00:00:00" ));
 */
long strToTimeStamp( const char * timeStr );

typedef struct TimeManager_t {
    int  ( * watch) ( TimeUpdateNotify callback );
    int  ( * watchSynced) ( TimeSyncedNotify callback );
    void ( * unWatch ) ( int fd );
    void ( * unWatchSynced ) ( int fd );
    void ( * setZone ) ( i8 zoneOffset );
    int  ( * getSeason ) ();
    int  ( * getSolarTerms ) ( bool useNearMode );
    int  ( * getWorkdays) ( void );
    void ( * sync ) (void);
    void ( * forceSync ) (void);

    int  ( * getYear) ();
    int  ( * getMonth) ();
    int  ( * getDay) ();
    int  ( * getHour) ();
    int  ( * getMinute) ();
    int  ( * getSecond) ();

    unsigned long long  ( * getTimeStampMilliSeconds) ();
    long  ( * getTimeStampSeconds) ();
} TimeManager;

int  timer_getYear();
int  timer_getMonth();
int  timer_getDay();
int  timer_getHour();
int  timer_getMinute();
int  timer_getSecond();

unsigned long long timer_getTimeStampMilliSeconds();
long timer_getTimeStampSeconds();

const TimeManager *
timeManagerCreate();

void
timeManagerDestroy();



#ifdef __cplusplus
}
#endif

#endif //EVG_UIKIT_TIME_MANAGE_H
