/**
    -----------------------------------------------------------

 	easyVGL
 	fonts.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_UTILS_FONTS_H
#define EVG_UTILS_FONTS_H

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVG_MAX_FONT_DECLARE 64
#define EVG_MAX_FONT_NAME_LEN 32
#define EVG_DEFAULT_FONT_LINE_HEIGHT 0

EvgFont evg_font_declare_cus( char * id, char * src, int size, int line_height, LV_FT_FONT_STYLE style );
EvgFont evg_font_declare_with_line_height( char * id, char * src, int size, int line_height );
EvgFont evg_font_declare( char * id, char * src, int size );
EvgFont evg_font_get( char * id );

#ifdef __cplusplus
}
#endif

#endif //EVG_UTILS_FONTS_H
