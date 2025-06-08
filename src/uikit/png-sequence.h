/**
    -----------------------------------------------------------

 	easyVGL
 	png-sequence.h    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#ifndef EVG_PNG_SEQUENCE_H
#define EVG_PNG_SEQUENCE_H

#include "../utils/lv_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_FRAME_RATE 24
#define SEQ_PATH_MAX_LEN   128

/**

 PNG Sequence    readme

    @description
 one sequence should be a folder  with all png images started from 000.png to max.png
 like:
 test/
    000.png 001.png 002.png ... 999.png  (0-9 means 10frames)

    @create
    create a new png-sequence with:

    const PNGSequence * seq = pngSequenceCreate( lv_container_obj_ptr, "S:./assets/fx/test/", 100, true );
    seq->play(seq);
    seq->pause();

    @destroy
    remove a png-sequence with:

    seq->stop();
    pngSequenceDestroy( seq );

 */
struct PNGSequence_t;
typedef void (*stopCallback_f)(struct PNGSequence_t *seq,void *ptr);

typedef struct PNGSequence_t
{
    EvgView  parent;
    EvgImg   self;
    EvgTimer timer;

    char *  directory;
    bool    loop;
    bool    useSharedFile;
    bool    paused;
    uint32_t f;
    uint32_t max;
    uint32_t fps;
    void    *stopCbPtr; 
    stopCallback_f  stopCallback;

    void (* setFPS)     (struct PNGSequence_t *, uint32_t fps);

    void (* play)       (struct PNGSequence_t *);
    void (* useShared)  (struct PNGSequence_t *);
    void (* playAt)     (struct PNGSequence_t *, uint32_t frame);
    void (* pause)      (struct PNGSequence_t *);
    void (* resume)     (struct PNGSequence_t *);
    void (* stop)       (struct PNGSequence_t *);
    void (* setStopCb)  (struct PNGSequence_t *,stopCallback_f stopCallback,void *ptr);
} PNGSequence;

PNGSequence * pngSequenceCreate( EvgView parent, char * directory, uint32_t total_frames, bool loop );
void  pngSequenceDestroy( PNGSequence * this );

#ifdef __cplusplus
}
#endif

#endif //EVG_PNG_SEQUENCE_H
