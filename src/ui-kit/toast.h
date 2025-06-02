/**
    -----------------------------------------------------------

 	easyVGL
 	toast.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_UIKIT_TOAST
#define EASYVGL_UIKIT_TOAST

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ToastView_t
{
    LvView      self;
    LvStyle *   styleList;

    bool        showMask;
    bool        withAnimation;

    LvView      mask;

    LvView      container;
    LvLabel     titleLabel;
    LvTimer     timer;

    void (*refresh)             ( struct ToastView_t * view );
    void (*show)                ( struct ToastView_t * view );
    void (*hide)                ( struct ToastView_t * view );
    void (*close)               ( struct ToastView_t * view );

} ToastView;

void toast_close( struct ToastView_t * toastView, bool withAnimation );
struct ToastView_t * toast_show( const char * title, u32 durationMS, bool showMask, bool withAnimation );

#define TOAST( title )      toast_show( title, 2000, true, false )
#define TOAST_FAST( title ) toast_show( title, 1500, true, false )
#define TOAST_SLOW( title ) toast_show( title, 8000, true, false )

void progress_show( const char * title );
void progress_hide();
void progress_update( const char * title, double percent );

#define PROGRESS( title, percent ) progress_update( title, percent );
#define PROGRESS_DONE() progress_hide();


#ifdef __cplusplus
}
#endif

#endif //EASYVGL_UIKIT_TOAST
