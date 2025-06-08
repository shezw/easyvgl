/**
    -----------------------------------------------------------

 	easyVGL
 	tools.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_LV_WRAPPER_H
#define EVG_LV_WRAPPER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EvgView      lv_obj_t *
#define EvgImg       lv_obj_t *
#define EvgLabel     lv_obj_t *
#define EvgTextarea  lv_obj_t *
#define EvgInput     lv_obj_t *
#define EvgBtn       lv_obj_t *
#define EvgFont      lv_font_t *
#define EvgEvent     lv_event_t *
#define EvgTimer     lv_timer_t *
#define EvgStyle     lv_style_t *
#define EvgColor     lv_color_t

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
    lv_mem_free(o);              \
    }

EvgView  evg_view( EvgView parent );
void    evg_view_remove( EvgView obj );
EvgView  evg_box( EvgView parent );
EvgImg   evg_image( EvgView parent, const char * src );
EvgLabel evg_label( LvView parent );
LvLabel evg_text( LvView parent, const char * str );
LvBtn   evg_button( LvView parent );
LvView  evg_flex_view( LvView parent, lv_flex_flow_t flex );

LvStyle evg_view_shadow( u32 color, u16 size, i16 x, i16 y );
LvStyle evg_view_gradient_cus( u32 c1, u32 c2, i16 pct1, i16 pct2, bool verOrHor );
LvStyle evg_view_gradient_ver(u32 c1, u32 c2 );
LvStyle evg_view_gradient_hor( u32 c1, u32 c2 );
LvStyle evg_view_gradient_ver_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );
LvStyle evg_view_gradient_hor_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );

LvView  evg_view_radius( LvView view, int r, lv_state_t state );
LvView  evg_view_max( LvView view );
LvView  evg_view_content( LvView view );
LvView  evg_view_clean( LvView obj );
LvView  evg_view_transp( LvView obj );
LvView  evg_view_hide( LvView obj );
LvView  evg_view_show( LvView obj );
LvView  evg_view_scrollable( LvView obj );

LvFont  evg_font( char * src, int fontSize, LV_FT_FONT_STYLE fstyle );

i16     evg_left_of( LvView view, i16 offset );
i16     evg_right_of( LvView view, i16 offset );
i16     evg_top_of( LvView view, i16 offset );
i16     evg_bottom_of( LvView view, i16 offset );

void    evg_left_to( LvView view, LvView toView, i16 offset );
void    evg_right_to( LvView view, LvView toView, i16 offset );
void    evg_top_to( LvView view, LvView toView, i16 offset );
void    evg_bottom_to( LvView view, LvView toView, i16 offset );

typedef void (*TickExec) (void * cus_ptr);

void    evg_next_tick_run( TickExec exec, void * cus_ptr );

/**
 * !!!!!!!!!!
 * delay_run  must use carefully  cause it only used with limited 1 exec
 * and make sure  you do not run it in the period
 */
void    evg_delay_run( TickExec exec, int delayMS, void * cus_ptr );

/**
 * Methods extern on Porting Files
 */
extern int screen_width();
extern int screen_height();

#ifdef __cplusplus
}
#endif


#endif //EVG_LV_WRAPPER_H
