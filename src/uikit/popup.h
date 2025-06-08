/**
    -----------------------------------------------------------

 	easyVGL
 	popup.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_UIKIT_POPUP_H
#define EVG_UIKIT_POPUP_H

#include "uikit.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UIKIT_TEXT_CONFIRM
#define UIKIT_TEXT_CONFIRM "确定"
#define UIKIT_TEXT_CANCEL  "取消"
#define UIKIT_TEXT_CLOSE   "关闭"
#endif // UIKIT_TEXT_CONFIRM

typedef enum PopupType_e
{
    PopupType_None  = 0,
    PopupType_Alert,
    PopupType_Confirm,
    PopupType_Input,

    PopupType_IntroductionConfirm,
    PopupType_QR,

    PopupType_MAX
} PopupType;

struct PopupView_t;

typedef void (*PopupViewConfirmCB) ( bool isConfirmed, struct PopupView_t * popupView );
typedef void (*PopupViewCloseCB) ( bool isConfirmed );

typedef struct PopupView_t {

    PopupType   type;
    u32         id;

    EvgView      self;

    EvgStyle *   styleList;

    bool        showMask;
    bool        withAnimation;

    EvgView      mask;

    EvgView      container;
    EvgLabel     titleLabel;
    EvgLabel     descLabel;

    bool        useIntroImage;
    EvgView      introImageContainer;
    EvgImg       introImage;

    EvgView      buttonArea;

    EvgBtn       buttonConfirm;
    EvgLabel     buttonConfirmLabel;
    EvgBtn       buttonCancel;
    EvgLabel     buttonCancelLabel;

    void *      user_data;
    EvgTimer     timer;

    struct PopupView_t * (*setButtonText) ( char * confirmText, char * cancelText, struct PopupView_t * this);
    struct PopupView_t * (*setIntroImageSrc) ( const char * imageSrc, struct PopupView_t * this);
    struct PopupView_t * (*setQRImageSrc)    ( const char * imageSrc, struct PopupView_t * this);
    struct PopupView_t * (*setButtonAreaX) (int x,struct PopupView_t * this);
    struct PopupView_t * (*setConfirmButtonAlign) (lv_align_t Align,struct PopupView_t * this);

    PopupViewConfirmCB onConfirm;
    PopupViewCloseCB   onClosed;

    void (*show)            ( struct PopupView_t * popupView );
    void (*close)           ( struct PopupView_t * popupView );

} PopupView;

PopupView * popupViewCreate( PopupType type, const char * title, const char * desc );

void *popupViewClear();

#define ALERT(title, desc)  \
PopupView * popupView = popupViewCreate( PopupType_Alert, title, desc );\
popupView->setButtonText( UIKIT_TEXT_CONFIRM, NULL, popupView )->show(popupView)

#define CONFIRM_CUS(title, desc, coText, caText) \
PopupView * popupView = popupViewCreate( PopupType_Confirm, title, desc ); \
if(popupView) {\
popupView->setButtonText( coText, caText, popupView )->show(popupView);    \
}

#define CONFIRM(title, desc) CONFIRM_CUS( title, desc, UIKIT_TEXT_CONFIRM, UIKIT_TEXT_CANCEL )

#define INTRO_CONFIRM_CUS(title, desc, imgSrc, coText, caText) \
PopupView * popupView = popupViewCreate( PopupType_IntroductionConfirm, title, desc ); \
if(popupView){ \
popupView->setIntroImageSrc( imgSrc, popupView ); \
popupView->setButtonText( coText, caText, popupView )->show(popupView); \
}

#define INTRO_CONFIRM( title, desc, imgSrc ) INTRO_CONFIRM_CUS( title, desc, imgSrc, UIKIT_TEXT_CONFIRM, UIKIT_TEXT_CANCEL )

#define POPUP_QR( title, qrPath, desc ) \
PopupView * popupView = popupViewCreate( PopupType_QR, title, desc ); \
if(popupView) {\
popupView->setQRImageSrc( qrPath, popupView ); \
popupView->setButtonText( UIKIT_TEXT_CONFIRM, NULL, popupView )->show(popupView);  \
evg_view_hide(popupView->buttonConfirm); \
}


#ifdef __cplusplus
}
#endif

#endif //EVG_UIKIT_POPUP_H
