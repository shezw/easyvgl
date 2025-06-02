/**
    -----------------------------------------------------------

 	easyVGL
 	fonts.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "fonts.h"

typedef struct FontDeclare_t
{
    char id[32];
    LvFont font;
} FontDeclare ;

static FontDeclare * fonts[MAX_APP_FONT_DECLARE] = {0};
static int total_font = 0;

LvFont LvFontDeclareCustom( char * id, char * src, int size, int line_height, LV_FT_FONT_STYLE style )
{
    printf("LvFontDeclareCustom id:%s src:%s size %d, line_height:%d \n",id,src,size,line_height);
    assert( strlen(id) < 32 );
    assert( total_font < MAX_APP_FONT_DECLARE );

    FontDeclare * font = ( FontDeclare * ) malloc( sizeof( FontDeclare ) );
    lv_memset(font,0,sizeof(FontDeclare));

    strcpy( font->id, id );
    font->font = lv_font( src, size, style );

    if (line_height>DEFAULT_FONT_LINE_HEIGHT)
        font->font->line_height = line_height;

    fonts[total_font++] = font;

    return font->font;
}

LvFont LvFontDeclareWithLineHeight( char * id, char * src, int size, int line_height )
{
    return LvFontDeclareCustom( id, src, size, line_height, FT_FONT_STYLE_NORMAL);
}

LvFont LvFontDeclare( char * id, char * src, int size )
{
    return LvFontDeclareWithLineHeight( id, src, size, 0 );
}

LvFont LvFontGet( char * id )
{
    assert( strlen(id) < 32 );

    for (int i = 0; i < total_font; ++i) {

        if ( fonts[i] == NULL )
            continue;

        if ( strcmp(fonts[i]->id,id)==0 )
            return fonts[i]->font;
    }

    assert( total_font < MAX_APP_FONT_DECLARE );
    return NULL;
}

