/**
    -----------------------------------------------------------

 	easyVGL
 	png-sequence.c    2025/6/2

 	@link    : https://github.com/shezw/easyvgl
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

#include "png-sequence.h"

static char tmpFile[SEQ_PATH_MAX_LEN] = {0};


static void showFrame( PNGSequence * seq )
{

    static char fileSrc[SEQ_PATH_MAX_LEN] = {0};
    static char fileSrcLast[SEQ_PATH_MAX_LEN] = {0};

    if( !seq->useSharedFile )
    {
        memset(fileSrc,0,SEQ_PATH_MAX_LEN);
        memset(tmpFile,0,SEQ_PATH_MAX_LEN);

        sprintf( fileSrc, "%s%03d.png", seq->directory, seq->f );
        sprintf( fileSrcLast, "%s%03d.png", seq->directory, seq->f==0 ? seq->max-1 : seq->f-1 );
        memcpy( tmpFile, fileSrc, SEQ_PATH_MAX_LEN );
    }

    if (seq->self==NULL)
            seq->self = evg_image( seq->parent, seq->useSharedFile ? tmpFile : fileSrc );

    lv_img_set_src( seq->self, seq->useSharedFile ? tmpFile : fileSrc );

    if( !seq->useSharedFile )
        lv_img_cache_invalidate_src( fileSrcLast );
}

static void pngSequencePlayFrame( EvgTimer e )
{
    PNGSequence * seq = (PNGSequence*) e->user_data;
    if( seq->paused ) return;
    seq->f++;
    if (seq->f>=seq->max) {

        if (seq->loop)
            seq->f = 0;
        else{
            if(seq->stopCallback)
                seq->stopCallback(seq,seq->stopCbPtr);
            return pngSequenceDestroy(seq);
        }
            
    }

    showFrame( seq );
}

static void pngSequencePlay( PNGSequence * this )
{
    if (this->timer!=NULL)
        lv_timer_del(this->timer);
  
    this->timer = lv_timer_create( pngSequencePlayFrame , 1000/this->fps, this);
    this->paused = false;
    showFrame( this );
}

static void pngSequencePlayAt( PNGSequence * this, uint32_t frame )
{
    this->f = frame;
    pngSequencePlay(this);
}

static void pngSequencePause( PNGSequence * this )
{
    this->paused = true;
    // lv_timer_pause(this->timer);
}

static void pngSequenceResume( PNGSequence * this )
{
    this->paused = false;
    // lv_timer_resume(this->timer);
}

static void pngSequenceStop( PNGSequence * this )
{
    if (this->timer)
        lv_timer_del(this->timer);
    this->timer = NULL;
}

static void pngSequenceSetFPS( PNGSequence * this, uint32_t fps )
{
    this->fps = fps;
}

static void pngSequenceUseSharedFile( PNGSequence * this )
{
    this->useSharedFile = true;
}

static void pngSequenceStopCallback(PNGSequence * this, stopCallback_f stopCallback,void *ptr)
{
    this->stopCallback = stopCallback;
    this->stopCbPtr    = ptr;
}

PNGSequence * pngSequenceCreate( EvgView parent, char * directory, uint32_t total_frames, bool loop )
{
    CNew(seq, PNGSequence);
    CNewString(seq->directory, strlen(directory));
    memcpy(seq->directory,directory, strlen(directory));

    seq->max    = total_frames;
    seq->loop   = loop;
    seq->fps    = DEFAULT_FRAME_RATE;
    seq->useSharedFile = false;
    seq->parent = parent;
    seq->stopCallback = NULL;

    seq->play   = pngSequencePlay;
    seq->playAt = pngSequencePlayAt;
    seq->pause  = pngSequencePause;
    seq->resume = pngSequenceResume;
    seq->stop   = pngSequenceStop;
    seq->useShared = pngSequenceUseSharedFile;
    seq->setStopCb = pngSequenceStopCallback;
    seq->setFPS = pngSequenceSetFPS;

    return seq;
}

void  pngSequenceDestroy( PNGSequence * this )
{
    if (this->directory && strlen(this->directory)>0) {
        lv_mem_free(this->directory);
    }
    EVG_DEL_TIMER(this->timer);
    EVG_DEL_VIEW(this->self);

    lv_mem_free(this);
}
