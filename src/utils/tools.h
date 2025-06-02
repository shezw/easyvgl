/**
    -----------------------------------------------------------

 	easyVGL
 	tools.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_LV_TOOLS_H
#define EASYVGL_LV_TOOLS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LvView      lv_obj_t *
#define LvImg       lv_obj_t *
#define LvLabel     lv_obj_t *
#define LvTextarea  lv_obj_t *
#define LvInput     lv_obj_t *
#define LvBtn       lv_obj_t *
#define LvFont      lv_font_t *
#define LvEvent     lv_event_t *
#define LvTimer     lv_timer_t *
#define LvStyle     lv_style_t *
#define LvColor     lv_color_t

#define EV_DEL_VIEW(v) \
    if( v != NULL ){\
    lv_obj_del(v);  \
    v=NULL;\
    }

#define EV_DEL_TIMER(v) \
    if( v != NULL ){\
    lv_timer_del(v);  \
    v=NULL;\
    }

#define EV_FREE_USER_DATA(o) \
    if( o != NULL && o->user_data != NULL ){ \
    lv_mem_freeo);              \
    }

LvView  lv_view( LvView parent );
void    lv_view_remove( LvView obj );
LvView  lv_box( LvView parent );
LvImg   lv_image( LvView parent, const char * src );
LvLabel lv_label( LvView parent );
LvLabel lv_text( LvView parent, const char * str );
LvBtn   lv_button( LvView parent );
LvView  lv_flex_view( LvView parent, lv_flex_flow_t flex );

LvStyle lv_view_shadow( u32 color, u16 size, i16 x, i16 y );
LvStyle lv_view_gradient_cus( u32 c1, u32 c2, i16 pct1, i16 pct2, bool verOrHor );
LvStyle lv_view_gradient_ver(u32 c1, u32 c2 );
LvStyle lv_view_gradient_hor( u32 c1, u32 c2 );
LvStyle lv_view_gradient_ver_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );
LvStyle lv_view_gradient_hor_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );

LvView  lv_view_radius( LvView view, int r, lv_state_t state );
LvView  lv_view_max( LvView view );
LvView  lv_view_content( LvView view );
LvView  lv_view_clean( LvView obj );
LvView  lv_view_transp( LvView obj );
LvView  lv_view_hide( LvView obj );
LvView  lv_view_show( LvView obj );
LvView  lv_view_scrollable( LvView obj );

LvFont  lv_font( char * src, int fontSize, LV_FT_FONT_STYLE fstyle );

i16     lv_left_of( LvView view, i16 offset );
i16     lv_right_of( LvView view, i16 offset );
i16     lv_top_of( LvView view, i16 offset );
i16     lv_bottom_of( LvView view, i16 offset );

void    lv_left_to( LvView view, LvView toView, i16 offset );
void    lv_right_to( LvView view, LvView toView, i16 offset );
void    lv_top_to( LvView view, LvView toView, i16 offset );
void    lv_bottom_to( LvView view, LvView toView, i16 offset );

typedef void (*TickExec) (void * cus_ptr);

void    lv_next_tick_run( TickExec exec, void * cus_ptr );

/**
 * !!!!!!!!!!
 * delay_run  must use carefully  cause it only used with limited 1 exec
 * and make sure  you do not run it in the period
 */
void    lv_delay_run( TickExec exec, int delayMS, void * cus_ptr );

/**
 * Methods extern on Porting Files
 */
extern int screen_width();
extern int screen_height();

#ifdef __cplusplus
}
#endif


#endif //EASYVGL_LV_TOOLS_H
