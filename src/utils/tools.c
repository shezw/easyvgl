/**
    -----------------------------------------------------------

 	easyVGL
 	tools.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "tools.h"

LvView lv_view( LvView parent )
{
    LvView obj = lv_obj_create( parent );
    lv_obj_set_size( obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT );

    return obj;
}


void lv_view_remove( LvView obj )
{
    lv_obj_del(obj);
}

LvView  lv_box( LvView parent )
{
    return lv_view_clean(lv_view_transp(lv_view(parent)));
}


LvImg  lv_image( LvView parent, const char * src )
{
    LvImg img = lv_img_create( parent );
    lv_obj_set_size( img, LV_SIZE_CONTENT, LV_SIZE_CONTENT );

    if (src!=NULL)
    lv_img_set_src( img, src );

    return img;
}

LvLabel  lv_label( LvView parent )
{
    LvLabel label = lv_label_create( parent );
    lv_obj_set_size( label, LV_SIZE_CONTENT, LV_SIZE_CONTENT );

    return label;
}

LvLabel lv_text( LvView parent, const char * str )
{
    LvLabel label = lv_label(parent);
    lv_label_set_text(label,str);
    return label;
}

LvBtn  lv_button( LvView parent )
{
    LvBtn button = lv_btn_create( parent );

    return button;
}

LvView lv_flex_view( LvView parent, lv_flex_flow_t flex )
{
    LvView obj = lv_view( parent );
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, flex);
    return obj;
}

LvStyle lv_view_shadow( u32 color, u16 size, i16 x, i16 y )
{
    lv_style_t * style = malloc( sizeof(lv_style_t) );
    lv_style_init(style);

    lv_style_set_shadow_width(style, size);
    lv_style_set_shadow_color(style, lv_color_hex(color));

    lv_style_set_shadow_ofs_x(style, x);
    lv_style_set_shadow_ofs_y(style, y);

    return style;
}

LvStyle lv_view_gradient_cus( u32 c1, u32 c2, i16 pct1, i16 pct2, bool verOrHor )
{
    lv_style_t * style = malloc( sizeof(lv_style_t) );
    lv_style_init(style);

    /*Make a gradient*/
    lv_style_set_bg_opa(style, LV_OPA_COVER);
    lv_grad_dsc_t * grad = malloc( sizeof(lv_grad_dsc_t) );
    grad->dir = verOrHor ? LV_GRAD_DIR_VER : LV_GRAD_DIR_HOR;
    grad->stops_count = 2;
    grad->stops[0].color = lv_color_hex(c1);
    grad->stops[1].color = lv_color_hex(c2);

    /*Shift the gradient to the bottom*/
    grad->stops[0].frac  = pct1;
    grad->stops[1].frac  = pct2;

    lv_style_set_bg_grad(style, grad);

    return style;
}


LvStyle lv_view_gradient_ver_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 )
{
    return lv_view_gradient_cus( c1, c2, pct1, pct2, true );
}

LvStyle lv_view_gradient_hor_cus( u32 c1, u32 c2, i16 pct1, i16 pct2 )
{
    return lv_view_gradient_cus( c1, c2, pct1, pct2, false );
}

LvStyle lv_view_gradient_ver(u32 c1, u32 c2 )
{
    return lv_view_gradient_ver_cus( c1, c2, 0, 255 );
}

LvStyle lv_view_gradient_hor( u32 c1, u32 c2 )
{
    return lv_view_gradient_hor_cus( c1, c2, 0, 255 );
}


LvView lv_view_radius( LvView view, int r, lv_state_t state )
{
    lv_obj_set_style_radius( view, r, state );
    return view;
}

LvView  lv_view_max( LvView view )
{
    lv_obj_set_size( view, LV_PCT(100), LV_PCT(100) );
    return view;
}

LvView  lv_view_content( LvView view )
{
    lv_obj_set_size( view, LV_SIZE_CONTENT, LV_SIZE_CONTENT );
    return view;
}


LvView lv_view_clean( LvView obj )
{
    lv_obj_set_style_pad_all( obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_border_width( obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_border_opa( obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_radius( obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT );

    lv_obj_clear_flag( obj, LV_OBJ_FLAG_SCROLLABLE);

    return obj;
}

LvView lv_view_transp( LvView obj )
{
    lv_obj_set_style_bg_opa(obj,0, LV_PART_MAIN | LV_STATE_DEFAULT );
    return obj;
}

LvView lv_view_hide( LvView obj )
{
    lv_obj_add_flag( obj, LV_OBJ_FLAG_HIDDEN );
    return obj;
}

LvView lv_view_show( LvView obj )
{
    lv_obj_clear_flag( obj, LV_OBJ_FLAG_HIDDEN );
    return obj;
}

LvView  lv_view_scrollable( LvView obj )
{
    lv_obj_add_flag( obj, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_scrollbar_mode( obj, LV_SCROLLBAR_MODE_ACTIVE );

    return obj;
}

LvFont lv_font( char * src, int fontSize, LV_FT_FONT_STYLE fstyle )
{
    /*Create a font*/
    lv_ft_info_t * info = (lv_ft_info_t *) malloc( sizeof(lv_ft_info_t) ) ;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    info->name   = src;
    info->weight = fontSize;
    info->style  = fstyle;
    info->mem    = NULL;

    if(!lv_ft_font_init(info)) {
        LV_LOG_ERROR("create failed.");
    }

    /*Create style with the new font*/
    lv_style_t * style = (lv_style_t *) malloc( sizeof(lv_style_t) ) ;
    lv_style_init(style);
    lv_style_set_text_font( style, info->font);
    lv_style_set_text_align( style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    return info->font;
}


i16     lv_left_of( LvView view, i16 offset )
{
    if ( view == NULL ) return offset;
    lv_obj_update_layout( view );
    return offset + lv_obj_get_style_pad_left( view, 0 ) + lv_obj_get_x( view );
}

i16     lv_right_of( LvView view, i16 offset )
{
    if ( view == NULL ) return offset;
    lv_obj_update_layout( view );
    return offset + lv_obj_get_x( view ) + lv_obj_get_width(view);
}

i16     lv_top_of( LvView view, i16 offset )
{
    if ( view == NULL ) return offset;
    lv_obj_update_layout( view );
    return offset + lv_obj_get_style_pad_top( view, 0 ) + lv_obj_get_y( view );
}

i16     lv_bottom_of( LvView view, i16 offset )
{
    if ( view == NULL ) return offset;
    lv_obj_update_layout( view );
    return offset + lv_obj_get_y( view ) + lv_obj_get_height(view);
}


void    lv_left_to( LvView view, LvView toView, i16 offset )
{
    lv_obj_set_x( view, lv_left_of( toView , offset) );
}

void    lv_right_to( LvView view, LvView toView, i16 offset )
{
    lv_obj_set_x( view, lv_right_of( toView , offset) );
}

void    lv_top_to( LvView view, LvView toView, i16 offset )
{
    lv_obj_set_y( view, lv_top_of( toView , offset) );
}

void    lv_bottom_to( LvView view, LvView toView, i16 offset )
{
    lv_obj_set_y( view, lv_bottom_of( toView , offset) );
}

static LvTimer   tmpTimer = NULL;
static TickExec  next_exec = NULL;
static void *    next_exec_ptr = NULL;

static void next_auto_exec( LvTimer t )
{
    if (next_exec) {
        next_exec(t->user_data);
    }
    next_exec = NULL;
    next_exec_ptr = NULL;
}

void    lv_next_tick_run( TickExec exec, void * cus_ptr )
{
    next_exec = exec;
    next_exec_ptr = cus_ptr;

    tmpTimer = lv_timer_create( next_auto_exec , 50, cus_ptr);
    lv_timer_set_repeat_count( tmpTimer, 1);
}

static LvTimer   delay_timer = NULL;
static TickExec  delay_exec = NULL;
static void *    delay_exec_ptr = NULL;

static void delay_auto_exec( LvTimer t )
{
    if (delay_exec) {
        delay_exec(t->user_data);
    }
    delay_exec = NULL;
    delay_exec_ptr = NULL;
}

void    lv_delay_run( TickExec exec, int delayMS, void * cus_ptr )
{
    delay_exec = exec;
    delay_exec_ptr = cus_ptr;

    delay_timer = lv_timer_create( delay_auto_exec , delayMS, cus_ptr);
    lv_timer_set_repeat_count( delay_timer, 1);
}
