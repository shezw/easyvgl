/**
    -----------------------------------------------------------

 	easyvgl
 	page.c    2024/4/24

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "page.h"
#include "obj.h"

static PageInstance * allPages = NULL;
static unsigned int   allPageCount = 0;

static void page_init()
{
    Construct(allPages,PageInstance);
}

static void page_deinit()
{
    free(allPages);
    allPages = NULL;
}

void page_register( PageID id, PageInstance pageInst )
{
    assert(id<MAX_PAGE_DEF);

    if( !allPages ) page_init();

    allPages[id] = pageInst;
    allPageCount++;
}

void page_destroy( PageID id)
{
    allPageCount--;

    if (!allPageCount)  page_deinit();
}

PageInstance page_instance( PageID id)
{
    assert(id<MAX_PAGE_DEF);

    return allPages[id];
}
