/**
    -----------------------------------------------------------

 	easyVGL
 	modules/timer.c    2025/6/8

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "timer.h"

#define MAX_CALLERS 8
#define TIMESTRING_LEN 64
#define FACTORY_BIRTH  1600000000

static bool  onStartUp = true;

static TimeManager * timerGl = NULL;
static bool quit_timer_thread = false;
static pthread_t ptimer_t;

static char * timeString;
static int  Year = 0;
static int  Month = 0;
static int  Day = 0;
static int  Hour = 0;
static int  Minute = 0;
static int  Second = 0;
static int  Workdays = 0; // 0 - 6    周日 -> 周一 --> 周六
static int  Season = 0; // 季节
static int  SolarTerms = 0; // 中国节气

static i8   zoneOffset = 0;

static struct tm tm_time_tm;
static struct timeval tm_time_tv;

static TimeUpdateNotify callers[MAX_CALLERS] = {0};
static TimeSyncedNotify sync_callers[MAX_CALLERS] = {0};

static int  timeCount = 0;
static bool timeSynced = false;

static void forcedSyncTime()
{
    // todo
}

static void notifyCallers()
{
    for (int j = 0; j < MAX_CALLERS; j++) {

        if (callers[j]!=NULL)
            callers[j]( timeString, Year, Month, Day, Hour, Minute, Second );
    }
}

static void notifySyncCallers()
{
    printf("notifySyncCallers\n");
    for (int j = 0; j < MAX_CALLERS; j++) {

        if (sync_callers[j]!=NULL)
            sync_callers[j]();
    }
}

int  timer_getYear ()
{
    return Year;
}
int  timer_getMonth ()
{
    return Month;
}
int  timer_getDay ()
{
    return Day;
}
int  timer_getHour ()
{
    return Hour;
}
int  timer_getMinute ()
{
    return Minute;
}

int  timer_getSecond ()
{
    return Second;
}

static void syncTimeNow()
{
    gettimeofday(&tm_time_tv, NULL);
    if (tm_time_tv.tv_sec>FACTORY_BIRTH)
        tm_time_tv.tv_sec += zoneOffset * 3600;

    if (onStartUp && tm_time_tv.tv_sec<FACTORY_BIRTH) {
        system("date -s \'1970-01-01 00:00:00\'; sync;");
        tm_time_tv.tv_sec = 0;
        onStartUp = false;
    }
    tm_time_tm = *localtime(&(tm_time_tv.tv_sec));

    Workdays = tm_time_tm.tm_wday;
    strftime(timeString, TIMESTRING_LEN, "%Y-%m-%d %H:%M:%S", &tm_time_tm);

    printf("timeString: %s\n", timeString);

    sscanf(timeString, "%d-%d-%d %d:%d:%d", &Year, &Month, &Day, &Hour, &Minute, &Second);
    if (tm_time_tv.tv_sec<FACTORY_BIRTH)
    {
        Year  =  Month =  Day   = 0;
        Workdays = 1;
    }
}

static void * run_timer( void * args )
{
    int ret = 0;
    while (!quit_timer_thread)
    {
        if (!timeSynced) {
            timeCount++;
            if (Year > 2000)
            {
                timeSynced = true;
                notifySyncCallers();
            }
            if (timeCount == 5) {
                if (Year < 2000) {
                    printf("time not synced\n");
                    forcedSyncTime();
                }
                timeCount = 0;
            }
        }

        syncTimeNow();
        notifyCallers();

        sleep(1);
    }
    return 0;
}

static int getWorkDays()
{
    return Workdays;
}

static int setNotifyCallBack( TimeUpdateNotify cb )
{
    for (int j = 0; j < MAX_CALLERS; j++) {

        if (callers[j]==NULL) {
            callers[j] = cb;
            return j;
        }
    }
    return -1;
}

static void unWatchCallBack( int fd )
{
    callers[fd] = NULL;
}

static int setSyncedCallBack( TimeSyncedNotify cb )
{
    for (int j = 0; j < MAX_CALLERS; j++) {

        if (sync_callers[j]==NULL) {
            sync_callers[j] = cb;
            return j;
        }
    }
    return -1;
}

static void unWatchSyncedCallBack( int fd )
{
    sync_callers[fd] = NULL;
}

static void setZoneOffset( i8 targetZoneOffset )
{
       zoneOffset = targetZoneOffset;
}

typedef enum SeasonId_e
{
    SeasonSpring = 0,
    SeasonSummer = 1,
    SeasonAutumn = 2,
    SeasonWinter = 3
} SeasonId;

static int  getSeason()
{
    if ( Month<2 || (Month==2 && Day<5) )
        Season = SeasonWinter;
    else if ( Month<5 || (Month==5 && Day<5) )
        Season = SeasonSpring;
    else if ( Month<8 || (Month==8 && Day<7) )
        Season = SeasonSummer;
    else if ( Month<11 || (Month==11 && Day<07) )
        Season = SeasonAutumn;
    else
        Season = SeasonWinter;

    return Season;
}

/**
 * 查询当前日期所属的节气 节气以上一个为准
0-5
    立春	2月3-5日
    雨水	2月18-20日
    惊蛰	3月5-7日
    春分	3月20-22日
    清明	4月4-6日
    谷雨	4月19-21日
6-11
    立夏	5月5-7日
    小满	5月20-22日
    芒种	6月5-7日
    夏至	6月21-22日
    小暑	7月6-8日
    大暑	7月22日-24日
12-17
    立秋	8月7-9日
    处暑	8月22-24日
    白露	9月7-9日
    秋分	9月22-24日
    寒露	10月8-9日
    霜降	10月23-24日
18-23
    立冬	11月7-8日
    小雪	11月22-23日
    大雪	12月6-8日
    冬至	12月21-23日
    小寒	1月5-7日
    大寒	1月20-21日
 * @return int
 */
static const int SolarDates[][3] =
{
    {1,5,7},
    {1,20,21},
    {2,3,5},
    {2,18,20},
    {3,5,7},
    {3,20,22},
    {4,4,6},
    {4,19,21},
    {5,5,7},
    {5,20,22},
    {6,5,7},
    {6,21,22},
    {7,6,8},
    {7,22,24},
    {8,7,9},
    {8,22,24},
    {9,7,9},
    {9,22,24},
    {10,8, 9},
    {10,23,24},
    {11,7,8},
    {11,22,23},
    {12,6,8},
    {12,21,23}
};

long strToTimeStamp( const char * timeStr )
{
    struct tm _time_tm;

    strptime(timeStr,"%Y-%m-%d %H:%M:%S",&_time_tm);

    return mktime(&_time_tm);
}

unsigned long long timer_getTimeStampMilliSeconds()
{
    static struct timeval t_tv;
    gettimeofday(&t_tv, NULL);
    return (t_tv.tv_sec * 1000) + (t_tv.tv_usec/1000);
}

long timer_getTimeStampSeconds()
{
    static struct timeval t_tv;
    gettimeofday(&t_tv, NULL);
    return t_tv.tv_sec;
}

static int getChineseSolarTerms( bool useNearMode )
{

    if (useNearMode)
    {
        char   timeStr[64] = {0};

        time_t timeStamp = tm_time_tv.tv_sec;

        time_t solarDistanceStart = 0;
        time_t solarDistanceEnd = 0;

        int solarDistance[24] = {0};

        for (int i = 0; i < 24; i++) {

            memset(timeStr,0,64);
            sprintf(timeStr,"%d-%d-%d 00:00:00",Year,SolarDates[i][0],SolarDates[i][1]);
            solarDistanceStart = llabs(strToTimeStamp(timeStr) - timeStamp);

            memset(timeStr,0,64);
            sprintf(timeStr,"%d-%d-%d 00:00:00",Year,SolarDates[i][0],SolarDates[i][2]);
            solarDistanceEnd = llabs(strToTimeStamp(timeStr) - timeStamp);

            solarDistance[i] = solarDistanceStart<solarDistanceEnd ? solarDistanceStart : solarDistanceEnd;
        }

        SolarTerms = 0;
        for (int i = 1; i < 24; i++) {
            if (solarDistance[i]<solarDistance[i-1])
                SolarTerms = i;
        }
    }
    else
    {
        for (int j = 0; j < 24; j++) {

            if ((Month>SolarDates[j][0]) || ((Month==SolarDates[j][0]) && (Day >= SolarDates[j][1])) )
            {
                SolarTerms = j;
            }
        }
    }
    return (SolarTerms+22)%24;
}

const TimeManager *
timeManagerCreate()
{
    if (timerGl==NULL) {
        CNewAt(timerGl, TimeManager);
        timeString = malloc(64);
        memset( callers, 0, MAX_CALLERS * sizeof(TimeUpdateNotify) );
    }

    timerGl->sync = syncTimeNow;
    timerGl->forceSync = forcedSyncTime;
    timerGl->watch = setNotifyCallBack;
    timerGl->unWatch = unWatchCallBack;
    timerGl->watchSynced = setSyncedCallBack;
    timerGl->unWatchSynced = unWatchSyncedCallBack;
    timerGl->getWorkdays = getWorkDays;
    timerGl->setZone = setZoneOffset;
    timerGl->getSeason = getSeason;
    timerGl->getSolarTerms = getChineseSolarTerms;

    timerGl->getYear = timer_getYear;
    timerGl->getMonth = timer_getMonth;
    timerGl->getDay = timer_getDay;
    timerGl->getHour = timer_getHour;
    timerGl->getMinute = timer_getMinute;
    timerGl->getSecond = timer_getSecond;

    timerGl->getTimeStampMilliSeconds = timer_getTimeStampMilliSeconds;
    timerGl->getTimeStampSeconds = timer_getTimeStampSeconds;

    pthread_create( &ptimer_t, NULL, run_timer, NULL );

    return timerGl;
}

void
timeManagerDestroy()
{
    quit_timer_thread = true;
    pthread_join( ptimer_t, 0 );

    if (timerGl!=NULL)
    {
        memset( callers, 0, 8 * sizeof(TimeUpdateNotify) );
        free(timerGl);
        free(timeString);
        timerGl = NULL;
    }
}

