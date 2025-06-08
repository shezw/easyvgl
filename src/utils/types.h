/**
    -----------------------------------------------------------

 	easyVGL
 	types.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_UTILS_TYPES_H
#define EVG_UTILS_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>

#include <pthread.h>

#include <sys/time.h>

#include <lvgl/lvgl.h>

#include <cjson/cJSON.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef u8
    #define u8  unsigned char
    #define u16 unsigned short
    #define u32 unsigned int
    #define uint64 unsigned long
#endif

#ifndef i8
    #define i8  char
    #define i16 short
    #define i32 int
    #define int64 long
#endif

#define SH_NONE         "\e[0m"         //   清除颜色，即之后的打印为正常输出，之前的不受影响
#define SH_BLACK        "\e[0;30m"      //   深黑
#define SH_L_BLACK      "\e[1;30m"      //   亮黑，偏灰褐
#define SH_RED          "\e[0;31m"      //   深红，暗红
#define SH_L_RED        "\e[1;31m"      //   鲜红
#define SH_GREEN        "\e[0;32m"      //   深绿，暗绿
#define SH_L_GREEN      "\e[1;32m"      //   鲜绿
#define SH_BROWN        "\e[0;33m"      //   深黄，暗黄
#define SH_YELLOW       "\e[1;33m"      //   鲜黄
#define SH_BLUE         "\e[0;34m"      //   深蓝，暗蓝
#define SH_L_BLUE       "\e[1;34m"      //   亮蓝，偏白灰
#define SH_PURPLE       "\e[0;35m"      //   深粉，暗粉，偏暗紫
#define SH_L_PURPLE     "\e[1;35m"      //   亮粉，偏白灰
#define SH_CYAN         "\e[0;36m"      //   暗青色
#define SH_L_CYAN       "\e[1;36m"      //   鲜亮青色
#define SH_GRAY         "\e[0;37m"      //   灰色
#define SH_WHITE        "\e[1;37m"      //   白色，字体粗一点，比正常大，比bold小
#define SH_BOLD         "\e[1m"         //   白色，粗体
#define SH_UNDERLINE    "\e[4m"         //   下划线，白色，正常大小
#define SH_BLINK        "\e[5m"         //   闪烁，白色，正常大小
#define SH_REVERSE      "\e[7m"         //   反转，即字体背景为白色，字体为黑色
#define SH_HIDE         "\e[8m"         //   隐藏
#define SH_CLEAR        "\e[2J"         //   清除
#define SH_CLRLINE      "\r\e[K"        //   清除行

#define SHELL_SWITCHER_GC(CDT) CDT?SH_L_GREEN"●"SH_NONE:SH_GRAY"●"SH_NONE
#define SHELL_ALARM_GC(CDT) CDT?SH_L_RED"●"SH_NONE:SH_GRAY"●"SH_NONE

#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define UTF8_CHAR_LEN 3

#define APP_Common_default_path     "./res/"
#define Preference_default_path     "./res/preferences/"
#define Image_Common_default_path   "S:./res/assets/images/"
#define Audio_Common_default_path   "./res/assets/audios/"
#define FX_Common_default_path      "S:./res/assets/fx/"

typedef void (*LoopCaller) (void) ;

#define CNew(O,T) \
    T * O = (T*) malloc( sizeof(T) ); \
    memset( O, 0, sizeof(T) );

#define CNewAt(P,T) \
    P = (T*) lv_mem_alloc(sizeof(T)); \
    memset( P, 0, sizeof(T) ); \

#define CNewString( P, LEN ) \
    P = malloc( LEN + 1 );        \
    memset( P, 0, LEN+1 );        \

#define ReleaseMemList( MEM_LIST, LIST_COUNT ) \
if (MEM_LIST){ \
    for (int i = 0; i < LIST_COUNT; i++) {\
        if (MEM_LIST[i]){ lv_mem_free(MEM_LIST[i]); MEM_LIST[i] = NULL; }\
    }\
    lv_mem_free(MEM_LIST);\
    MEM_LIST = NULL;\
}

#ifdef __cplusplus
}
#endif


#endif //EVG_UTILS_TYPES_H
