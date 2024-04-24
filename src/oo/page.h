/**
    -----------------------------------------------------------

 	easyvgl
 	page.h    2024/4/24

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_OO_PAGE_H
#define EASYVGL_OO_PAGE_H

#include "../lv_ext/wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_PAGE_DEF
    #define MAX_PAGE_DEF 255
#endif

typedef struct PageParam_t
{
    u32 id;
    char * str;
    void * ptr;
} PageParam;

typedef unsigned int PageID;
typedef void * PageInstance;

struct PageView_t;

#define PAGE_DEFINE(PageId,CustomAttrs) \
typedef struct PageId##PageContent_t\
{                                   \
    unsigned int   id;\
    struct PageView_t * pageView;               \
    bool fromBack;                              \
    char * name;\
    LvView self;\
    LvStyle * styleList;\
    CustomAttrs\
    void (*init)        ( struct PageView_t * pageView, struct PageId##PageContent_t * contentView );\
    void (*deinit)      ( struct PageView_t * pageView, struct PageId##PageContent_t * contentView );\
} Page##PageId##Content;


void page_register( PageID, PageInstance );

void page_destroy( PageID );

PageInstance page_instance( PageID );


#ifdef __cplusplus
}
#endif

#endif //EASYVGL_OO_PAGE_H
