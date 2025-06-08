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
    char id[EVG_MAX_FONT_NAME_LEN];
    EvgFont font;
} FontDeclare ;

static FontDeclare * fonts[EVG_MAX_FONT_DECLARE] = {0};
static int total_font = 0;

EvgFont evg_font_declare_cus( char * id, char * src, int size, int line_height, LV_FT_FONT_STYLE style )
{
    printf("evg_font_declare_cus id:%s src:%s size %d, line_height:%d \n",id,src,size,line_height);
    assert( strlen(id) < 32 );
    assert( total_font < EVG_MAX_FONT_DECLARE );

    FontDeclare * font = ( FontDeclare * ) malloc( sizeof( FontDeclare ) );
    memset(font,0,sizeof(FontDeclare));

    strcpy( font->id, id );
    font->font = evg_font( src, size, style );

    if (line_height>EVG_DEFAULT_FONT_LINE_HEIGHT)
        font->font->line_height = line_height;

    fonts[total_font++] = font;

    return font->font;
}

EvgFont evg_font_declare_with_line_height( char * id, char * src, int size, int line_height )
{
    return evg_font_declare_cus( id, src, size, line_height, FT_FONT_STYLE_NORMAL);
}

EvgFont evg_font_declare( char * id, char * src, int size )
{
    return evg_font_declare_with_line_height( id, src, size, 0 );
}

EvgFont evg_font_get( char * id )
{
    assert( strlen(id) < 32 );

    for (int i = 0; i < total_font; ++i) {

        if ( fonts[i] == NULL )
            continue;

        if ( strcmp(fonts[i]->id,id)==0 )
            return fonts[i]->font;
    }

    assert( total_font < EVG_MAX_FONT_DECLARE );
    return NULL;
}

