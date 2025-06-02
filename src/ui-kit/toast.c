/**
    -----------------------------------------------------------

 	easyVGL
 	toast.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include <math.h>

#include "app.h"
#include "toast.h"

void toast_close( ToastView * tView, bool withAnimation )
{
    lv_timer_del( tView->timer );

    EV_DEL_VIEW( tView->self );
    lv_mem_free(tView);
}

static void toast_auto_close( LvTimer t )
{
    ToastView * tView = (ToastView*) t->user_data;

    EV_DEL_VIEW( tView->self );

    lv_view_hide(getApp()->toastLayer);

    lv_mem_freetView);
}

static LvViewStyle toastMaskStyles[] =
        {
//                cssBg(0x0),
                cssBgOpa(0),
                cssSize(1920,440),
                cssEnd()
        };

static LvViewStyle toastContainerStyles[] =
        {
                cssBg(0xffffff),
                cssRadius(20),
                cssPaddingXY(50,30),
                cssAlign(Center),
                cssSize(LV_SIZE_CONTENT,LV_SIZE_CONTENT),
                cssEnd()
        };

static LvViewStyle toastLabelStyles[] =
        {
                cssFont("LvFontLanTingHei_30",0x333333),
                cssEnd()
        };

static LvViewStyle progressContainerStyles[] =
        {
                cssExtend(&toastContainerStyles),
                cssBorder(2,0xDDDDDD),
                cssBorderOpa(LV_OPA_100),
                cssEnd()
        };

static LvViewStyle progressLabelStyles[] =
        {
                cssExtend(&toastLabelStyles),
                cssAlignAt(TopMid,0,30),
                cssEnd()
        };

ToastView * toast_show( const char * title, u32 durationMS, bool showMask, bool withAnimation )
{
    CNew( this, ToastView );

    this->self = lv_box( getApp()->toastLayer );
//    this->mask = lv_view_max(lv_view_clean(lv_view(this->self)));
    this->mask = lv_view_max(lv_image(this->self, Image_CommonPath"maskBg.png"));

    this->container = lv_view_clean(lv_view(this->self));
    this->titleLabel = lv_label( this->container );

    lv_label_set_text( this->titleLabel, title );

    SET_STYLES( this->mask, toastMaskStyles, this->styleList );
    SET_STYLES( this->container, toastContainerStyles, this->styleList );
    SET_STYLES( this->titleLabel, toastLabelStyles, this->styleList );

    this->timer = lv_timer_create( toast_auto_close , durationMS, this);
    lv_timer_set_repeat_count( this->timer, 1);

    lv_view_show(getApp()->toastLayer);

    return this;
}

static LvView progressToast = NULL;
static LvView progressToastBar = NULL;
static LvView progressToastMask = NULL;
static LvLabel progressToastText = NULL;
static LvLabel progressToastPercentText = NULL;

static LvStyle * progressStyleList = NULL;

void progress_show( const char * title )
{
    if (progressToast==NULL) {
        progressToast = lv_view_clean(lv_view( getApp()->toastLayer ));

        progressToastBar = lv_bar_create(progressToast);

        lv_bar_set_value(progressToastBar, 0, LV_ANIM_OFF);

        if (title) {
            progressToastText = lv_text(progressToast, title);
            SET_STYLES( progressToastText, progressLabelStyles, progressStyleList );
        }
        SET_STYLES( progressToast, progressContainerStyles, progressStyleList );
    }

    lv_view_show(progressToast);
    lv_view_show(getApp()->toastLayer);
}

void progress_hide()
{
    lv_view_hide(progressToast);
    lv_view_hide(getApp()->toastLayer);
}

void progress_update( const char * title, double percent )
{
//    if ( progressToast == NULL )
        progress_show(title);

    if (title!=NULL)
    {
        if (progressToastText==NULL) {
            progressToastText = lv_text(progressToast, title);
            SET_STYLES( progressToastText, progressLabelStyles, progressStyleList);
        }
        else lv_label_set_text( progressToastText, title );
    }else
    {
        if (progressToastText!=NULL) lv_view_hide( progressToastText );
    }

    lv_bar_set_value( progressToastBar, (int)floor(percent), LV_ANIM_OFF );
}

