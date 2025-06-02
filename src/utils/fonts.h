/**
    -----------------------------------------------------------

 	easyVGL
 	fonts.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_BASE_FONTS_H
#define EASYVGL_BASE_FONTS_H

#include "tools.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_APP_FONT_DECLARE 64
#define DEFAULT_FONT_LINE_HEIGHT 0

LvFont LvFontDeclareCustom( char * id, char * src, int size, int line_height, LV_FT_FONT_STYLE style );
LvFont LvFontDeclareWithLineHeight( char * id, char * src, int size, int line_height );
LvFont LvFontDeclare( char * id, char * src, int size );
LvFont LvFontGet( char * id );

#ifdef __cplusplus
}
#endif

#endif //EASYVGL_BASE_FONTS_H
