/**
    -----------------------------------------------------------

 	easyvgl
 	shell.h    2024/4/24

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_UTILS_SHELL_H
#define EASYVGL_UTILS_SHELL_H

#ifdef __cplusplus
extern "C" {
#endif


#define SHELL_CR_NONE         "\e[0m"         // 清除颜色，即之后的打印为正常输出，之前的不受影响
#define SHELL_CR_BLACK        "\e[0;30m"      // 深黑
#define SHELL_CR_L_BLACK      "\e[1;30m"      // 亮黑，偏灰褐
#define SHELL_CR_RED          "\e[0;31m"      // 深红，暗红
#define SHELL_CR_L_RED        "\e[1;31m"      // 鲜红
#define SHELL_CR_GREEN        "\e[0;32m"      // 深绿，暗绿
#define SHELL_CR_L_GREEN      "\e[1;32m"      // 鲜绿
#define SHELL_CR_BROWN        "\e[0;33m"      // 深黄，暗黄
#define SHELL_CR_YELLOW       "\e[1;33m"      // 鲜黄
#define SHELL_CR_BLUE         "\e[0;34m"      // 深蓝，暗蓝
#define SHELL_CR_L_BLUE       "\e[1;34m"      // 亮蓝，偏白灰
#define SHELL_CR_PURPLE       "\e[0;35m"      // 深粉，暗粉，偏暗紫
#define SHELL_CR_L_PURPLE     "\e[1;35m"      // 亮粉，偏白灰
#define SHELL_CR_CYAN         "\e[0;36m"      // 暗青色
#define SHELL_CR_L_CYAN       "\e[1;36m"      // 鲜亮青色
#define SHELL_CR_GRAY         "\e[0;37m"      // 灰色
#define SHELL_CR_WHITE        "\e[1;37m"      // 白色，字体粗一点，比正常大，比bold小
#define SHELL_CR_BOLD         "\e[1m"         // 白色，粗体
#define SHELL_CR_UNDERLINE    "\e[4m"         // 下划线，白色，正常大小
#define SHELL_CR_BLINK        "\e[5m"         // 闪烁，白色，正常大小
#define SHELL_CR_REVERSE      "\e[7m"         // 反转，即字体背景为白色，字体为黑色
#define SHELL_CR_HIDE         "\e[8m"         // 隐藏
#define SHELL_CR_CLEAR        "\e[2J"         // 清除
#define SHELL_CR_CLRLINE      "\r\e[K"        // 清除行

#define SHELL_SWITCHER_GC(CDT) CDT?SHELL_CR_L_GREEN"●"SHELL_CR_NONE:SHELL_CR_GRAY"●"SHELL_CR_NONE
#define SHELL_ALARM_GC(CDT) CDT?SHELL_CR_L_RED"●"SHELL_CR_NONE:SHELL_CR_GRAY"●"SHELL_CR_NONE

#ifdef __cplusplus
}
#endif

#endif //EASYVGL_UTILS_SHELL_H
