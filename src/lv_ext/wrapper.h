/**
    -----------------------------------------------------------

 	easyvgl
 	wrapper.h    2024/4/24   
 	
 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_LVEXT_WRAPPER_H
#define EASYVGL_LVEXT_WRAPPER_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LVGL_VERSION_MAJOR


typedef void lv_obj_t;
typedef void lv_font_t;
typedef void lv_event_t;
typedef void lv_timer_t;
typedef void lv_style_t;
typedef void lv_color_t;

#endif


typedef lv_obj_t *     LvView;
typedef lv_obj_t *     LvImg;
typedef lv_obj_t *     LvLabel;
typedef lv_obj_t *     LvTextarea;
typedef lv_obj_t *     LvInput;
typedef lv_obj_t *     LvBtn;
typedef lv_font_t *    LvFont;
typedef lv_event_t *   LvEvent;
typedef lv_timer_t *   LvTimer;
typedef lv_style_t *   LvStyle;
typedef lv_color_t *   LvColor;



#define DEL_VIEW(v) \
    if( v != NULL ){\
    lv_obj_del(v);  \
    v=NULL;\
    }

#define DEL_TIMER(v) \
    if( v != NULL ){\
    lv_timer_del(v);  \
    v=NULL;\
    }

#define FREE_USER_DATA(o) \
    if( o != NULL && o->user_data != NULL ){ \
    free(o);              \
    }




LvView  esy_view( LvView parent );
void    esy_view_remove( LvView obj );
LvView  esy_box( LvView parent );
LvImg   esy_image( LvView parent, const char * src );
LvLabel esy_label( LvView parent );
LvLabel esy_text( LvView parent, const char * str );
LvBtn   esy_button( LvView parent );
LvView  esy_flex_view( LvView parent, lv_flex_flow_t flex );
LvStyle esy_view_shadow( u32 color, u16 size, i16 x, i16 y );
LvStyle esy_view_gradient_cus( u32 c1, u32 c2, i16 pct1, i16 pct2, bool verOrHor );
LvStyle esy_view_gradient_ver(u32 c1, u32 c2 );
LvStyle esy_view_gradient_hor( u32 c1, u32 c2 );
LvStyle esy_view_gradient_ver_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );
LvStyle esy_view_gradient_hor_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 );
LvView  esy_view_radius( LvView view, int r, lv_state_t state );
LvView  esy_view_max( LvView view );
LvView  esy_view_content( LvView view );
LvView  esy_view_clean( LvView obj );
LvView  esy_view_transp( LvView obj );
LvView  esy_view_hide( LvView obj );
LvView  esy_view_show( LvView obj );
LvView  esy_view_scrollable( LvView obj );
LvView  esy_view_not_scrollable( LvView obj );
LvFont  esy_font( char * src, int fontSize, LV_FT_FONT_STYLE fstyle );



#define NewView(P) esy_view(P)
#define NewBox(P) esy_box(P)
#define NewImage(P,SRC) esy_image(P,SRC)
#define NewLabel(P) esy_label(P)
#define NewText(P,TXT) esy_text(P,TXT)
#define NewButton(P) esy_button(P);
#define NewFlexView(P,FLEX) esy_flex_view(P,FLEX)

#define DelView(V) esy_view_remove(V)

#define NewShadow(C,S,X,Y) esy_view_shadow(C,S,X,Y)
#define NewGrad(C1,C2,P1,P2,VoH) esy_view_gradient_cus(C1,C2,P1,P2,VoH)
#define NewGradVer(C1,C2) esy_view_gradient_ver(C1,C2)
#define NewGradHor(C1,C2) esy_view_gradient_hor(C1,C2)
#define NewGradVerCus(C1,C2,P1,P2) esy_view_gradient_ver_cus(C1,C2,P1,P2)
#define NewGradHorCus(C1,C2,P1,P2) esy_view_gradient_hor_cus(C1,C2,P1,P2)

#define NewRadius(V,R,State) esy_view_radius(V,R,State)
#define ViewToMAX esy_view_max( LvView view )
#define ViewToContent(V) esy_view_content(V)
#define CleanView(V) esy_view_clean(V)
#define TransparentView(V) esy_view_transp(V)
#define HideView(V) esy_view_hide(V)
#define ShowView(V) esy_view_show(V)
#define ViewCanScroll(V) esy_view_scrollable(V)
#define ViewCanTScroll(V) esy_view_not_scrollable(V)

#define NewFont(SRC,Size,FTStyle) esy_font(SRC,Size,FTStyle)




i16     esy_left_of( LvView view, i16 offset );
i16     esy_right_of( LvView view, i16 offset );
i16     esy_top_of( LvView view, i16 offset );
i16     esy_bottom_of( LvView view, i16 offset );

void    esy_left_to( LvView view, LvView toView, i16 offset );
void    esy_right_to( LvView view, LvView toView, i16 offset );
void    esy_top_to( LvView view, LvView toView, i16 offset );
void    esy_bottom_to( LvView view, LvView toView, i16 offset );

typedef void (*TickExec) (void * cus_ptr);

void    esy_next_tick_run( TickExec exec, void * cus_ptr );

/**
 * !!!!!!!!!!
 * delay_run  must use carefully  cause it only used with limited 1 exec
 * and make sure  you do not run it in the period
 */
void    esy_delay_run( TickExec exec, int delayMS, void * cus_ptr );

/**
 * Methods extern on Porting Files
 */
extern int screen_width();
extern int screen_height();


#ifdef __cplusplus
}
#endif

#endif //EASYVGL_LVEXT_WRAPPER_H
