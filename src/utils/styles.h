//
// Created by 志伟佘 on 2023/6/26.
//

#ifndef EVG_UTILS_STYLES_H
#define EVG_UTILS_STYLES_H

#include "lv_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CUSTOM_STYLES  32

#define SET_STYLES( view, styles, styleList ) styleList = lv_view_set_styles( view, styles, styleList )
#define SET_STYLE( view, style ) lv_view_set_style( view, style )

typedef enum EvgStyle_ViewAlign_e
{
    ViewAlign_Default = LV_ALIGN_DEFAULT,
    ViewAlign_TopLeft = LV_ALIGN_TOP_LEFT,
    ViewAlign_TopMid  = LV_ALIGN_TOP_MID,
    ViewAlign_TopRight = LV_ALIGN_TOP_RIGHT,
    ViewAlign_BottomMid = LV_ALIGN_BOTTOM_MID,
    ViewAlign_BottomLeft = LV_ALIGN_BOTTOM_LEFT,
    ViewAlign_BottomRight = LV_ALIGN_BOTTOM_RIGHT,
    ViewAlign_LeftMid = LV_ALIGN_LEFT_MID,
    ViewAlign_RightMid = LV_ALIGN_RIGHT_MID,
    ViewAlign_Center = LV_ALIGN_CENTER,

    ViewAlign_Max
} ViewAlign;

typedef enum EvgStyle_TextOverflow_e
{
    ViewTextOverflow_Default = 0,

    ViewTextOverflow_Wrap = LV_LABEL_LONG_WRAP,             /**< Keep the object width, wrap the too long lines and expand the object height*/
    ViewTextOverflow_Dot = LV_LABEL_LONG_DOT,              /**< Keep the size and write dots at the end if the text is too long*/
    ViewTextOverflow_Scroll = LV_LABEL_LONG_SCROLL,           /**< Keep the size and roll the text back and forth*/
    ViewTextOverflow_ScrollCircular = LV_LABEL_LONG_SCROLL_CIRCULAR,  /**< Keep the size and roll the text circularly*/
    ViewTextOverflow_Clip = LV_LABEL_LONG_CLIP,             /**< Keep the size and clip the text out of it*/

    ViewTextOverflow_Max
} TextOverflow;

typedef enum EvgStyle_TextAlign_e
{
    ViewTextAlign_Default = 0,
    ViewTextAlign_Auto = LV_TEXT_ALIGN_AUTO,
    ViewTextAlign_Center = LV_TEXT_ALIGN_CENTER,
    ViewTextAlign_Left = LV_TEXT_ALIGN_LEFT,
    ViewTextAlign_Right = LV_TEXT_ALIGN_RIGHT,

    ViewTextAlign_Max
} TextAlign;

typedef enum EvgStyle_Type_e
{
    ViewStyle_None = 0,


    ViewStyle_Align,
    ViewStyle_Center,

    ViewStyle_Abs,
    ViewStyle_Pos,
    ViewStyle_PosX,
    ViewStyle_PosY,

    ViewStyle_Size,

    ViewStyle_Width,
    ViewStyle_Height,

    ViewStyle_BackgroundColor,
    ViewStyle_BackgroundOpa,
    ViewStyle_BackgroundGradient,
    ViewStyle_BackgroundImage,
    ViewStyle_BackgroundImageOpa,
    ViewStyle_BackgroundImageReColor,
    ViewStyle_BackgroundImageReColorOpa,
    ViewStyle_BackgroundImageTiled,

    ViewStyle_Padding,
    ViewStyle_PaddingXY,
    ViewStyle_PaddingTop,
    ViewStyle_PaddingLeft,
    ViewStyle_PaddingRight,
    ViewStyle_PaddingBottom,

    ViewStyle_Radius,
    ViewStyle_ImageRadius,

    ViewStyle_Shadow,

    ViewStyle_BorderWidth,
    ViewStyle_BorderColor,
    ViewStyle_BorderOpa,

    ViewStyle_Font,
    ViewStyle_FontColor,
    ViewStyle_TextLineSpace,
    ViewStyle_LabelText,

    // TODO
    ViewStyle_Transition,


    // Text Layout Styles
    ViewStyle_TextOverflow,
    ViewStyle_TextAlign,


    // Mark
    ViewStyle_Extend,

    ViewStyle_Max,

    ViewStyle_End = 0xff

} ViewStyleType;

typedef enum ViewStyleState_e
{
    ViewStyleState_Default     =  0x0000,
    ViewStyleState_Checked     =  0x0001,
    ViewStyleState_Focused     =  0x0002,
    ViewStyleState_FocusKey    =  0x0004,
    ViewStyleState_Edited      =  0x0008,
    ViewStyleState_Hovered     =  0x0010,
    ViewStyleState_Pressed     =  0x0020,
    ViewStyleState_Scrolled    =  0x0040,
    ViewStyleState_Disabled    =  0x0080,

    ViewStyleState_USER_1      =  0x1000,
    ViewStyleState_USER_2      =  0x2000,
    ViewStyleState_USER_3      =  0x4000,
    ViewStyleState_USER_4      =  0x8000,

    ViewStyleState_ScrollBar           = 0x010000,   /**< The scrollbar(s)*/
    ViewStyleState_Indicator           = 0x020000,   /**< Indicator, e.g. for slider, bar, switch, or the tick box of the checkbox*/
    ViewStyleState_Knob                = 0x030000,   /**< Like handle to grab to adjust the value*/
    ViewStyleState_Selected            = 0x040000,   /**< Indicate the currently selected option or section*/
    ViewStyleState_Items               = 0x050000,   /**< Used if the widget has multiple similar elements (e.g. table cells)*/
    ViewStyleState_Ticks               = 0x060000,   /**< Ticks on scale e.g. for a chart or meter*/
    ViewStyleState_Cursor              = 0x070000,   /**< Mark a specific place e.g. for text area's cursor or on a chart*/

    ViewStyleState_CustomFirst         = 0x080000,    /**< Extension point for custom widgets*/

    ViewStyleState_ANY         =  0xFFFF,    /**< Special value can be used in some functions to target all states*/

} ViewStyleState;

typedef struct EvgViewStyle_t
{
    ViewStyleType style;
    ViewStyleState onState;

    char *  str_v;
    void *  obj_v;
    i32     int_v;

} EvgViewStyle;

typedef struct EvgGradientDef_t
{
    u8 dir;

    u32 p1;
    u32 c1;

    u32 c2;
    u32 p2;
} EvgGradientDef;

typedef struct EvgShadowDef_t
{
    u32 color;
    i32 size;
    i32 x;
    i32 y;
} EvgShadowDef;

typedef struct ViewSize_t
{
    u32 w;
    u32 h;
} ViewSize;

extern ViewSize DefaultSize;

typedef struct ViewPos_t
{
    u32 x;
    u32 y;
} ViewPos;

#define AnyView void *

EvgStyle * lv_view_set_styles( EvgView view, EvgViewStyle * styles, EvgStyle * styleList );
void      lv_view_set_style( EvgView view, EvgViewStyle * style );

void markCustomStyle        ( EvgStyle * styleList, EvgStyle style );
void releaseCustomStyles    ( EvgStyle * styleList, EvgStyle style );
void cleanCustomStyles      ( EvgStyle * styleList );





#define css(k,val,type) \
{\
.style = ViewStyle_##k,\
.type##_v = val\
}

#define cssAt(k,v,t,st) \
{\
.style = ViewStyle_##k,\
.t##_v = v,\
.onState = ViewStyleState_##st\
}

#define cssBg( c )                          css( BackgroundColor, c, int )
#define cssBgOpa( o )                       css( BackgroundOpa, o, int )
#define cssNoBg()                           css( BackgroundOpa, 0, int )
#define cssBgAt( c, s )                     cssAt( BackgroundColor, c, int, s )
#define cssBgOpaAt( o, s )                  cssAt( BackgroundOpa, o, int, s )
#define cssBgImg( s )                       css( BackgroundImage, s, str )
#define cssBgImgOpa( o )                    css( BackgroundImageOpa, o, int)
#define cssBgImgReColor( c )                css( BackgroundImageReColor, c, int)
#define cssBgImgReColorOpa( o )             css( BackgroundImageReColorOpa, c, int)
#define cssBgImgTiled()                     css( BackgroundImageTiled, true, int )
#define cssBgImgAt( src, s )                cssAt( BackgroundImage, src, str, s )
#define cssBgImgOpaAt( o, s )               cssAt( BackgroundImageOpa, o, int, s)
#define cssBgImgReColorAt( c, s )           cssAt( BackgroundImageReColor, c, int, s)
#define cssBgImgReColorOpaAt( o, s )        cssAt( BackgroundImageReColorOpa, c, int, s)
#define cssBgImgTiledAt( s )                cssAt( BackgroundImageTiled, true, int, s )


#define cssBorderColorAt( c, state )        cssAt(BorderColor,c,int,state)
#define cssBorderWidthAt( w, state )        cssAt(BorderWidth,w,int,state)
#define cssBorderOpaAt( opa, state )        cssAt(BorderOpa,opa,int,state)
#define cssBorderAt( width, color, state )  cssBorderWidthAt( width, state), cssBorderColorAt( color, state )
#define cssNoBorderAt( state )              cssBorderWidthAt(0,state), cssBorderOpaAt(0,state)

#define cssBorderColor( c )                 cssBorderOpaAt( c, Default )
#define cssBorderWidth( w )                 cssBorderWidthAt( w, Default )
#define cssBorderOpa( opa )                 cssBorderOpaAt( opa, Default )
#define cssBorder( width, color )           cssBorderAt( width, color, Default )
#define cssNoBorder()                       cssNoBorderAt(Default)

#define cssAlign( align )                   css(Align,ViewAlign_##align,int)

#define cssWidth( w )                       css(Width,w,int)
#define cssHeight( h )                      css(Height,h,int)
#define cssSize( w,h )                      cssWidth(w), cssHeight(h)
#define cssPosX( x )                        css(PosX,x,int)
#define cssPosY( y )                        css(PosY,y,int)
#define cssPos( x, y)                       cssPosX(x), cssPosY(y)
#define cssAbs( x, y)                       cssPos(x,y)
#define cssCenter()                         css(Center,0,int)

#define cssAlignAt( align, x, y )           css(Align,ViewAlign_##align,int), cssPos(x,y)

#define cssGradientBgAt( gradPtr, state)    cssAt(BackgroundGradient,gradPtr,obj,state)
#define cssGradientBg( gradPtr )            cssGradientBgAt(gradPtr,Default)

#define cssShadowAt( shadowPtr, state )     cssAt(Shadow,shadowPtr,obj,state)
#define cssShadow( shadowPtr )              cssShadowAt( shadowPtr, Default)
#define cssNoShadowAt( state )              cssAt(Shadow,NULL,obj,state )
#define cssNoShadow()                       cssNoShadowAt( Default )

#define cssRadius( r )                      css(Radius,r,int)
#define cssImageRadius( r )                 css(ImageRadius,r,int)

#define cssFontName( n )                    css(Font,n,str)
#define cssFontColor( c )                   css(FontColor,c,int)
#define cssFont( name, color )              cssFontName(name), cssFontColor(color)
#define cssLabelText( txt )                 css(LabelText, txt, str)
#define cssText( txt )                      cssLabelText( txt )

#define cssFontNameAt( n, state )           cssAt(Font,n,str,state)
#define cssFontColorAt( c, state )          cssAt(FontColor,c,int,state)
#define cssFontAt( name, color, state )     cssFontNameAt(name,state), cssFontColorAt(color,state)

#define cssTextOverflow( e )                css(TextOverflow,ViewTextOverflow_##e,int)
#define cssTextAlign(e)                     css(TextAlign,ViewTextAlign_##e,int)
#define cssLineSpace( n )                   css(TextLineSpace,n,int)

#define cssPadding( p )                     css(Padding, p, int)
#define cssNoPadding()                      css(Padding, 0, int)
#define cssPaddingXY( x,y )                 css(PaddingLeft,x,int), css(PaddingRight,x,int), css(PaddingTop,y,int), css(PaddingBottom,y,int)

#define cssPaddingLeft( p )                 css(PaddingLeft,p,int)
#define cssPaddingRight( p )                css(PaddingRight,p,int)
#define cssPaddingTop( p )                  css(PaddingTop,p,int)
#define cssPaddingBottom( p )               css(PaddingBottom,p,int)

#define cssPaddingAt( p, state )            cssAt(Padding, p, int, state)
#define cssNoPaddingAt( state )             cssAt(Padding, 0, int, state)
#define cssPaddingXYAt( x,y, state )        cssAt(PaddingLeft,x,int, state), cssAt(PaddingRight,x,int, state), cssAt(PaddingTop,y,int, state), cssAt(PaddingBottom,y,int, state)

#define cssEnd()                            css(End,0,int)

#define cssExtend( CSS )                    css(Extend,CSS,obj)

#define cssGetW(o) lv_obj_get_width(o)
#define cssGetH(o) lv_obj_get_height(o)


#ifdef __cplusplus
}
#endif


#endif //EVG_UTILS_STYLES_H
