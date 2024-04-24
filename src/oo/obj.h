/**
    -----------------------------------------------------------

 	easyvgl
 	obj.h    2024/4/24

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EASYVGL_OO_OBJ_H
#define EASYVGL_OO_OBJ_H

#ifdef __cplusplus
extern "C" {
#endif


#define New(obj,st) \
    st * obj = (st*) malloc( sizeof(st) ); \
    memset( obj, 0, sizeof(st) );

#define NewG(ptr,st) \
    ptr = (st*) malloc( sizeof(st) ); \
    memset( ptr, 0, sizeof(st) );     \

#define Construct(p,st) NewG(p,st)

#define NewStatic(ptr,st) \
    static st * ptr = (st*) malloc( sizeof(st) ); \
    memset( ptr, 0, sizeof(st) );     \

#define NewString( ptr, size ) \
    ptr = malloc( size + 1 );        \
    memset( ptr, 0, size+1 );        \

#define ReleaseMemList( MEM_LIST, LIST_COUNT ) \
if (MEM_LIST){ \
    for (int i = 0; i < LIST_COUNT; i++) {\
        if (MEM_LIST[i]){ free(MEM_LIST[i]); MEM_LIST[i] = NULL; }\
    }\
    free(MEM_LIST);\
    MEM_LIST = NULL;\
}


#ifdef __cplusplus
}
#endif

#endif //EASYVGL_OO_OBJ_H
