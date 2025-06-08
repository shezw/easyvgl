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

#include "toast.h"

void toast_close( ToastView * tView, bool withAnimation )
{
    lv_timer_del( tView->timer );

    EVG_DEL_VIEW( tView->self );
    free(tView);
}

static void toast_auto_close( EvgTimer t )
{
    ToastView * tView = (ToastView*) t->user_data;

    EVG_DEL_VIEW( tView->self );

    evg_view_hide(getApp()->toastLayer);

    free(tView);
}

static EvgViewStyle toastMaskStyles[] =
        {
//                cssBg(0x0),
                cssBgOpa(0),
                cssSize(1920,440),
                cssEnd()
        };

static EvgViewStyle toastContainerStyles[] =
        {
                cssBg(0xffffff),
                cssRadius(20),
                cssPaddingXY(50,30),
                cssAlign(Center),
                cssSize(LV_SIZE_CONTENT,LV_SIZE_CONTENT),
                cssEnd()
        };

static EvgViewStyle toastLabelStyles[] =
        {
                cssFont("EvgFontLanTingHei_30",0x333333),
                cssEnd()
        };

static EvgViewStyle progressContainerStyles[] =
        {
                cssExtend(&toastContainerStyles),
                cssBorder(2,0xDDDDDD),
                cssBorderOpa(LV_OPA_100),
                cssEnd()
        };

static EvgViewStyle progressLabelStyles[] =
        {
                cssExtend(&toastLabelStyles),
                cssAlignAt(TopMid,0,30),
                cssEnd()
        };

ToastView * toast_show( const char * title, u32 durationMS, bool showMask, bool withAnimation )
{
    CNew( this, ToastView );

    this->self = evg_box( getApp()->toastLayer );
//    this->mask = evg_view_max(evg_view_clean(evg_view(this->self)));
    this->mask = evg_view_max(evg_image(this->self, Image_Common_default_path"maskBg.png"));

    this->container = evg_view_clean(evg_view(this->self));
    this->titleLabel = evg_label( this->container );

    lv_label_set_text( this->titleLabel, title );

    SET_STYLES( this->mask, toastMaskStyles, this->styleList );
    SET_STYLES( this->container, toastContainerStyles, this->styleList );
    SET_STYLES( this->titleLabel, toastLabelStyles, this->styleList );

    this->timer = lv_timer_create( toast_auto_close , durationMS, this);
    lv_timer_set_repeat_count( this->timer, 1);

    evg_view_show(getApp()->toastLayer);

    return this;
}

static EvgView progressToast = NULL;
static EvgView progressToastBar = NULL;
static EvgView progressToastMask = NULL;
static EvgLabel progressToastText = NULL;
static EvgLabel progressToastPercentText = NULL;

static EvgStyle * progressStyleList = NULL;

void progress_show( const char * title )
{
    if (progressToast==NULL) {
        progressToast = evg_view_clean(evg_view( getApp()->toastLayer ));

        progressToastBar = lv_bar_create(progressToast);

        lv_bar_set_value(progressToastBar, 0, LV_ANIM_OFF);

        if (title) {
            progressToastText = evg_text(progressToast, title);
            SET_STYLES( progressToastText, progressLabelStyles, progressStyleList );
        }
        SET_STYLES( progressToast, progressContainerStyles, progressStyleList );
    }

    evg_view_show(progressToast);
    evg_view_show(getApp()->toastLayer);
}

void progress_hide()
{
    evg_view_hide(progressToast);
    evg_view_hide(getApp()->toastLayer);
}

void progress_update( const char * title, double percent )
{
//    if ( progressToast == NULL )
        progress_show(title);

    if (title!=NULL)
    {
        if (progressToastText==NULL) {
            progressToastText = evg_text(progressToast, title);
            SET_STYLES( progressToastText, progressLabelStyles, progressStyleList);
        }
        else lv_label_set_text( progressToastText, title );
    }else
    {
        if (progressToastText!=NULL) evg_view_hide( progressToastText );
    }

    lv_bar_set_value( progressToastBar, (int)floor(percent), LV_ANIM_OFF );
}

