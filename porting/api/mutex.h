/**
    -----------------------------------------------------------

 	easyVGL
 	porting/common/mutex.h  2025/6/7

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_PORTING_API_MUTEX_H
#define EVG_PORTING_API_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

void evg_porting_mutex_init();
void evg_porting_lock();
void evg_porting_unlock();
void evg_porting_mutex_destroy();

#define EVG_LOCK_RUN( PROG ) \
evg_porting_lock();             \
PROG;\
evg_porting_unlock();

#ifdef __cplusplus
}
#endif

#endif //EVG_PORTING_API_MUTEX_H
