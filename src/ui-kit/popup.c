/**
    -----------------------------------------------------------

 	easyVGL
 	popup.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "app.h"
#include "popup.h"

static LvViewStyle popupMaskStyles[] =
        {
//                cssBg(0x0),
                cssBgOpa(0),
                // cssBgImg("S:./app/assets/images/maskBg.png"),
                cssSize(1920,440),
                cssEnd()
        };

static LvViewStyle popupContainerStyles[] =
        {
                cssAlign(Center),
                cssRadius(20),
                cssBg(0xffffff),
                cssPaddingXY(50,30),
                cssAlign(Center),
                cssWidth(560),
                cssEnd()
        };

static LvViewStyle popupTitleStyles[] =
        {
                cssFont("LvFontLanTingHei_30",0x333333),
                cssAlign(TopMid),
//                cssSize(LV_SIZE_CONTENT,LV_SIZE_CONTENT),
//                cssAbs(0,30),
                cssEnd()
        };

static LvViewStyle popupDescStyles[] =
        {
                cssFont("LvFontLanTingHei_24",0x333333),
                cssAlign(TopMid),
                cssAbs(0,55),
                cssTextOverflow(Wrap),
                cssWidth(400),
//                cssSize(400,LV_SIZE_CONTENT),
                cssEnd()
        };

static LvViewStyle buttonAreaStyles[] = {
        cssNoBg(),
        cssSize(290,64),
        cssAlign(BottomMid),
        cssAbs(0,0),
        cssFont("LvFontLanTingHei_24",0xFFFFFF),
//            cssRadius(30),
        cssEnd(),
};

static LvViewStyle buttonConfirmStyles[] = {
        cssBg(0xFF8F46),
        cssSize(126,54),
        cssAlign(LeftMid),
        cssAbs(5,0),
        cssFont("LvFontLanTingHei_24",0xFFFFFF),
        cssRadius(30),
        cssEnd(),
};

static LvViewStyle buttonCancelStyles[] = {
        cssBg(0xffeada),
        cssSize(126,54),
        cssAlign(RightMid),
        cssAbs(-5,0),
        cssFont("LvFontLanTingHei_24",0xA0A0A0),
        cssRadius(30),
        cssEnd(),
};

static int  popupCount = 0;
static int  popupMaskCount = 0;

static void popupViewInitButtons( char * confirmText, char * cancelText, PopupView * this );
static void popupViewClose( PopupView * this );
static void popupViewShow( PopupView * this );
static void popupViewConfirmed( LvEvent e);
static void popupViewCanceled( LvEvent e);

static PopupView * popupViewSingleton = NULL;

void * popupViewClear()
{
    if (popupViewSingleton!=NULL)
    {
        popupViewClose(popupViewSingleton);
        popupViewSingleton = NULL;
    }
    return 0;
}

static void autoResizePopup( PopupView * this )
{
    lv_obj_update_layout(this->self);

    lv_obj_set_height( this->container,
                       lv_obj_get_height(this->titleLabel) + 15 +
                       lv_obj_get_height(this->descLabel) + 15 +
                       lv_obj_get_height(this->buttonArea) + 15 +
                       60
                       );

    if (this->useIntroImage) {

        if (this->type==PopupType_QR)
        {
            lv_obj_set_width( this->titleLabel, 540 );
            lv_obj_set_width( this->descLabel, 540 );
            lv_obj_set_width( this->container, 540 + 100 + 50 * 3 );

            lv_obj_align( this->introImageContainer, LV_ALIGN_CENTER, 0, -20);

            lv_obj_align( this->descLabel, LV_ALIGN_BOTTOM_MID, 0, 0 );

            lv_obj_set_height( this->container,
                               lv_obj_get_height(this->titleLabel) + 15 +
                               lv_obj_get_height(this->descLabel) + 15 +
                               160
            );

        }else
        {
            lv_obj_align( this->titleLabel, LV_ALIGN_TOP_RIGHT, 0, 0 );
            lv_obj_align( this->descLabel, LV_ALIGN_TOP_RIGHT, 0, 50 );
            lv_obj_align_to( this->buttonArea, this->descLabel, LV_ALIGN_OUT_BOTTOM_MID, 0, 20 );
            lv_obj_set_width( this->titleLabel, 600 );
            lv_obj_set_width( this->descLabel, 600 );
            lv_obj_set_width( this->container, 600 + 300 + 50 * 3 );
        }

        lv_obj_set_style_text_align( this->titleLabel, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_text_font( this->descLabel, LvFontGet("IntroConfirmDescFont"), 0 );
    }else if ( this->descLabel != NULL )
    {
        lv_obj_set_width( this->container, max(lv_obj_get_width( this->buttonArea ),lv_obj_get_width(this->descLabel)) + 50 * 2 );
    }

}

struct PopupView_t * popupViewSetButtonAreaX (int x,struct PopupView_t * this)
{
    lv_obj_set_x(this->buttonArea,x);
    lv_obj_align(this->buttonArea,LV_ALIGN_BOTTOM_MID,0,20);

    return this;
}
struct PopupView_t * popupViewSetButtonAreaAlign (lv_align_t Align,struct PopupView_t * this)
{
    lv_obj_set_align(this->buttonConfirm,Align);

    return this;
}

static PopupView * popupViewSetButtonText( char * confirmText, char * cancelText, PopupView * this )
{
    popupViewInitButtons( confirmText, cancelText, this );

    return this;
}

static PopupView * popupViewSetQRImageSrc( const char * src, PopupView * this )
{
    this->useIntroImage = true;

    if ( this->introImage == NULL ) {
        this->introImageContainer = lv_view_clean(lv_view(this->container));
        this->introImage = lv_image(this->introImageContainer, src);
    }else
        lv_img_set_src( this->introImage, src );

    lv_obj_set_size( this->introImageContainer, 120, 120 );
//    lv_obj_set_size( this->introImage, 105, 120 );
//    lv_img_set_size_mode( this->introImage, 0 );
    lv_obj_set_style_bg_color( this->introImageContainer, lv_color_hex(0xffffff), 0 );
    lv_obj_set_pos( this->introImageContainer, 0, 15 );

    lv_obj_center( this->introImage );

    lv_obj_add_flag(this->mask, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(this->mask, popupViewCanceled, LV_EVENT_CLICKED, this );
    return this;
}

static PopupView * popupViewSetIntroImageSrc( const char * src, PopupView * this )
{
    this->useIntroImage = true;

    if ( this->introImage == NULL ) {
        this->introImageContainer = lv_view_clean(lv_view(this->container));
        this->introImage = lv_image(this->introImageContainer, src);
    }else
        lv_img_set_src( this->introImage, src );

    lv_obj_set_size( this->introImageContainer, 300, 200 );
    lv_obj_set_style_bg_color( this->introImageContainer, lv_color_hex(0xF1F1F1), 0 );
    lv_obj_set_pos( this->introImageContainer, 0, 25 );

    lv_obj_center( this->introImage );

    return this;
}

static PopupViewCloseCB popupViewClosedCallback = NULL;
static bool             popupViewClosedOnConfirmed = false;

static void popupViewClose( PopupView * this )
{
    EV_DEL_TIMER( this->timer );
    EV_DEL_VIEW( this->self );
    lv_view_hide(getApp()->popupLayer);
    lv_mem_freepopupViewSingleton);
    popupViewSingleton = NULL;

    if (popupViewClosedCallback) {
        popupViewClosedCallback(popupViewClosedOnConfirmed);
        popupViewClosedCallback = NULL;
        popupViewClosedOnConfirmed = false;
    }
}

static void popupViewShow( PopupView * this )
{
    autoResizePopup( this );

    lv_view_show(this->self);
    lv_view_show(getApp()->popupLayer);
}

static void popupViewConfirmed( LvEvent e)
{
    PopupView * this = (PopupView * ) e->user_data;

    if (this->onConfirm)
        this->onConfirm( true, this );

    if (this->onClosed) {
        popupViewClosedCallback = this->onClosed;
        popupViewClosedOnConfirmed = true;
    }
    this->close(this);
}

static void popupViewCanceled( LvEvent e)
{
    PopupView * this = (PopupView * ) e->user_data;

    if (this->onConfirm)
        this->onConfirm( false, this );

    if (this->onClosed) {
        popupViewClosedCallback = this->onClosed;
        popupViewClosedOnConfirmed = false;
    }
    this->close(this);
}

static void popupViewInitButtons( char * confirmText, char * cancelText, PopupView * this )
{

    this->buttonArea = lv_view_clean( lv_view( this->container ) );
    SET_STYLES( this->buttonArea, buttonAreaStyles, this->styleList );
//    lv_obj_set_size( this->buttonArea, 274, 54 );

    this->buttonConfirm     = lv_view_clean(lv_button( this->buttonArea ));

    SET_STYLES( this->buttonConfirm, buttonConfirmStyles, this->styleList );

    if( cancelText != NULL ) {
        this->buttonCancel = lv_view_clean(lv_button(this->buttonArea));
        this->buttonCancelLabel = lv_label(this->buttonCancel);
        lv_label_set_text( this->buttonCancelLabel, cancelText );
        lv_obj_center( this->buttonCancelLabel );
        lv_obj_add_event_cb(this->buttonCancel, popupViewCanceled, LV_EVENT_CLICKED, this);

        SET_STYLES( this->buttonCancel,  buttonCancelStyles,  this->styleList );
        SET_STYLES( this->buttonConfirm, buttonConfirmStyles, this->styleList );
    }
    else
    {
        lv_obj_center( this->buttonConfirm );
    }
    this->buttonConfirmLabel = lv_label(this->buttonConfirm);
    lv_label_set_text( this->buttonConfirmLabel, confirmText != NULL ? confirmText : "确定" );

    lv_obj_center( this->buttonConfirmLabel );

    lv_obj_update_layout(this->buttonArea);

    // need to reset button width
    if (strlen(confirmText)>=4*UTF8_CHAR_LEN)
    {

        lv_obj_set_width( this->buttonConfirm, lv_obj_get_width( this->buttonConfirmLabel ) + 15*2 );

        if (this->buttonCancel!=NULL)
        {
            lv_obj_set_width( this->buttonCancel, lv_obj_get_width( this->buttonCancelLabel ) + 15*2 );
            lv_obj_update_layout( this->buttonArea );
        }
        lv_obj_set_width( this->buttonArea, lv_obj_get_width( this->buttonConfirm ) + 30 + ((this->buttonCancel!=NULL)?lv_obj_get_width( this->buttonCancel):0) );
    }

    lv_obj_add_event_cb(this->buttonConfirm, popupViewConfirmed, LV_EVENT_CLICKED, this);

}

PopupView * popupViewCreate( PopupType type, const char * title, const char * desc )
{

    if (NULL!=popupViewSingleton && popupViewSingleton->type == PopupType_Alert)
    {
        popupViewSingleton->close(popupViewSingleton);
    }

    if (popupViewSingleton!=NULL)
        return NULL;

    CNewAt(popupViewSingleton, PopupView);
    PopupView * this = popupViewSingleton;

    this->type = type;
    this->show = popupViewShow;
    this->close = popupViewClose;
    this->setButtonText = popupViewSetButtonText;
    this->setIntroImageSrc = popupViewSetIntroImageSrc;
    this->setQRImageSrc = popupViewSetQRImageSrc;

    this->setButtonAreaX = popupViewSetButtonAreaX;
    this->setConfirmButtonAlign = popupViewSetButtonAreaAlign;

    this->self = lv_box( getApp()->popupLayer  );
//    this->mask = lv_view_max(lv_view_clean(lv_view(this->self)));
    this->mask = lv_view_max(lv_image(this->self, Image_CommonPath"maskBg.png"));
    SET_STYLES(this->mask, popupMaskStyles, this->styleList);

    this->container = lv_view_clean(lv_view(this->self));

    this->titleLabel = lv_label( this->container );
    lv_label_set_text( this->titleLabel, title );

    SET_STYLES(this->titleLabel, popupTitleStyles, this->styleList);

    if (desc) {
        this->descLabel = lv_label( this->container );
        SET_STYLES(this->descLabel, popupDescStyles, this->styleList);
        lv_label_set_text( this->descLabel, desc );

        if (strlen(desc) < 16*UTF8_CHAR_LEN )
        lv_obj_set_style_text_align( this->descLabel, LV_TEXT_ALIGN_CENTER, 0);
    }
    SET_STYLES(this->container, popupContainerStyles, this->styleList);

    lv_view_hide( this->self );

    return this;
}
