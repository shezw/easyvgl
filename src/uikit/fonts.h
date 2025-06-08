/**
    -----------------------------------------------------------

 	easyVGL
 	font.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_UIKIT_FONTS_H
#define EVG_UIKIT_FONTS_H

#include "../utils/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_EVG_DEFAULT_FONTS
#define USE_EVG_DEFAULT_FONTS 1
#endif // USE_EVG_DEFAULT_FONTS

#if USE_EVG_DEFAULT_FONTS

#define Arial_FontName              "Arial.ttf"

#define Roboto_Thin_FontName        "Roboto-Thin.ttf"
#define Roboto_Light_FontName       "Roboto-Light.ttf"
#define Roboto_Regular_FontName     "Roboto-Regular.ttf"
#define Roboto_Medium_FontName      "Roboto-Medium.ttf"
#define Roboto_Bold_FontName        "Roboto-Bold.ttf"
#define Roboto_Black_FontName       "Roboto-Black.ttf"

#define DroidSansFallback_FontName  "DroidSansFallback.ttf"

#endif//USE_EVG_DEFAULT_FONTS

int evg_default_fonts_init();

#ifdef __cplusplus
}
#endif

#endif //EVG_UIKIT_FONTS_H
