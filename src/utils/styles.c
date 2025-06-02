/**
    -----------------------------------------------------------

 	easyVGL
 	styles.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "tools.h"
#include "styles.h"
#include "fonts.h"

// FIXME && TODO
// need to recheck memleak when add styles on malloc

ViewSize DefaultSize = {LV_SIZE_CONTENT,LV_SIZE_CONTENT};

void markCustomStyle        ( LvStyle * styleList, LvStyle style )
{
    for (int i = 0; i < MAX_CUSTOM_STYLES; i++) {
        if (styleList[i] == style ) return;
        if (styleList[i] == NULL) {
//            printf("markCustomStyle %p %p \n", styleList[i], style );
            styleList[i] = style;
            return;
        }
    }
}

void releaseCustomStyles    ( LvStyle * styleList, LvStyle style )
{
    if (styleList==NULL) return;
    for (int i = 0; i < MAX_CUSTOM_STYLES; i++) {
        if (styleList[i] == style) {
//            printf("releaseCustomStyles free [%p]\n",styleList[i]);
            lv_mem_freestyleList[i]);
            styleList[i] = NULL;
        }
    }
}

void cleanCustomStyles      ( LvStyle * styleList )
{
    if (styleList==NULL) return;
    for (int i = 0; i < MAX_CUSTOM_STYLES; i++) {
        if (styleList[i] != NULL) {
            // FIXME free twice
//            printf("cleanCustomStyles free [%p] (%d) \n",styleList[i],i);
            lv_mem_free styleList[i] );
            styleList[i] = NULL;
        }
    }
    lv_mem_freestyleList);
}

void lv_view_set_style( LvView view, LvViewStyle * style )
{
    if ( style->style >= ViewStyle_Max )
        return;

    switch ( style->style) {
        case ViewStyle_Align:
            lv_obj_align( view, style->int_v, 0, 0);
            break;
        case ViewStyle_Center:
            lv_obj_center( view );
            break;
        case ViewStyle_PosX:
            lv_obj_set_x( view, style->int_v );
            break;
        case ViewStyle_PosY:
            lv_obj_set_y( view, style->int_v );
            break;

        case ViewStyle_Width:
            lv_obj_set_width( view, style->int_v );
            break;

        case ViewStyle_BorderWidth:
            lv_obj_set_style_border_width( view, style->int_v, style->onState );
            break;

        case ViewStyle_BorderColor:
            lv_obj_set_style_border_color( view, lv_color_hex(style->int_v), style->onState );
            break;

        case ViewStyle_BorderOpa:
            lv_obj_set_style_border_opa( view, style->int_v, style->onState );
            break;

        case ViewStyle_Height:
            lv_obj_set_height( view, style->int_v );
            break;
        case ViewStyle_Size:
            lv_obj_set_size( view, ((ViewSize*)style->obj_v)->w, ((ViewSize*)style->obj_v)->h);
            break;

        case ViewStyle_BackgroundColor:
            lv_obj_set_style_bg_color( view, lv_color_hex( (u32)style->int_v), style->onState);
            break;

        case ViewStyle_BackgroundOpa:
            lv_obj_set_style_bg_opa( view, style->int_v, style->onState);
            break;

        case ViewStyle_BackgroundImage:
            lv_obj_set_style_bg_img_src( view, style->str_v, style->onState );
            break;

        case ViewStyle_BackgroundImageOpa:
            lv_obj_set_style_bg_img_opa( view, style->int_v, style->onState );
            break;

        case ViewStyle_BackgroundImageReColor:
            lv_obj_set_style_bg_img_recolor( view, lv_color_hex(style->int_v), style->onState);
            break;

        case ViewStyle_BackgroundImageReColorOpa:
            lv_obj_set_style_bg_img_recolor_opa( view, style->int_v, style->onState );
            break;

        case ViewStyle_BackgroundImageTiled:
            lv_obj_set_style_bg_img_tiled( view, style->int_v, style->onState );
            break;

        case ViewStyle_LabelText:
            lv_label_set_text( view, style->str_v );
            break;

        case ViewStyle_Font:
            lv_obj_set_style_text_font( view, LvFontGet( (char*)style->str_v ), style->onState);
            break;

        case ViewStyle_FontColor:
            lv_obj_set_style_text_color( view, lv_color_hex( (u32)style->int_v ), style->onState );
            break;

        case ViewStyle_Padding:
            lv_obj_set_style_pad_all( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_PaddingXY:
            lv_obj_set_style_pad_left( view, ((ViewPos*)style->obj_v)->x , style->onState);
            lv_obj_set_style_pad_right( view, ((ViewPos*)style->obj_v)->x , style->onState);
            lv_obj_set_style_pad_top( view, ((ViewPos*)style->obj_v)->y , style->onState);
            lv_obj_set_style_pad_bottom( view, ((ViewPos*)style->obj_v)->y , style->onState);
            break;

        case ViewStyle_PaddingLeft:
            lv_obj_set_style_pad_left( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_PaddingRight:
            lv_obj_set_style_pad_right( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_PaddingTop:
            lv_obj_set_style_pad_top( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_PaddingBottom:
            lv_obj_set_style_pad_bottom( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_Radius:
            lv_view_radius( view, (u16) style->int_v , style->onState);
            break;

        case ViewStyle_ImageRadius:
            lv_view_radius( view, (u16) style->int_v, style->onState);
            lv_obj_set_style_clip_corner( view, true, style->onState);
            break;

        case ViewStyle_TextOverflow:
            lv_label_set_long_mode( view, style->int_v);
            break;

        case ViewStyle_TextLineSpace:
            lv_obj_set_style_text_line_space( view, style->int_v, style->onState );
            break;

        case ViewStyle_TextAlign:
            lv_obj_set_style_text_align( view, style->int_v, style->onState );
            break;

        default:

            break;
    }

}

LvStyle * lv_view_set_styles( LvView view, LvViewStyle * styles, LvStyle * styleList )
{
    LvViewStyle * style;

    if (styleList==NULL) {
        styleList = (LvStyle*) malloc(MAX_CUSTOM_STYLES * sizeof(LvStyle *));
        lv_memset(styleList,0,MAX_CUSTOM_STYLES * sizeof(LvStyle *));
    }
    static int marked = 0;

    int idx = 0;
    while ( (style = &styles[idx++]) )
    {
        if ( style->style >= ViewStyle_Max )
            break;

        switch ( style->style) {

            case ViewStyle_Extend:
            {
                lv_view_set_styles( view, style->obj_v, styleList );
                break;
            }

            case ViewStyle_BackgroundGradient: {
                LvGradientDef *grad = (LvGradientDef *) style->obj_v;
                LvStyle gradStyle = lv_view_gradient_cus(grad->c1, grad->c2, grad->p1 ? grad->p1 : 0,
                                                         grad->p2 ? grad->p2 : 255, grad->dir);
                lv_obj_add_style(view, gradStyle, style->onState);
//                    marked++;
//                    printf("gradStyle [%p] \n", gradStyle);
//                    markCustomStyle(styleList, gradStyle);
                // ISSUE armhf cannot access gradStyle
                // TODO  there are to ptr in gradient style . but now only free 1 ptr
                break;
            }

            case ViewStyle_Shadow: {
                LvShadowDef *shadow = (LvShadowDef *) style->obj_v;
                if (shadow) {
                    LvStyle shadowStyle = lv_view_shadow(shadow->color, shadow->size, shadow->x, shadow->y);
                    lv_obj_add_style(view, shadowStyle, style->onState);
                    marked++;
                    markCustomStyle(styleList, shadowStyle);
                }else{
                    lv_obj_set_style_shadow_opa( view, 0, 0);
                }
                break;
            }

            default:
                lv_view_set_style( view, style );
                break;
        }

    }

    if (marked==0)
    {
        lv_mem_freestyleList);
        return NULL;
    }

    return styleList;

}
