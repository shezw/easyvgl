/**
 * @file lv_virtualknob.h
 *
 */

#ifndef LV_VIRTUAL_KNOB_H
#define LV_VIRTUAL_KNOB_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../lvgl.h"

#if LV_USE_VIRKNOB

enum {
    LV_VIRTUAL_KNOB_MODE_HUE,
    LV_VIRTUAL_KNOB_MODE_SATURATION,
    LV_VIRTUAL_KNOB_MODE_VALUE
};
typedef uint8_t lv_virknob_mode_t;

typedef void ( *knobDoneCB ) ( uint32_t angle, void * user_data, bool isEnd );


/*Data of color picker*/
typedef struct {
    lv_obj_t obj;
    lv_color_hsv_t hsv;
    struct {
        lv_point_t pos;
        uint8_t recolor     : 1;
    } knob;
    uint32_t last_click_time;
    uint32_t last_change_time;
    lv_point_t last_press_point;
    lv_virknob_mode_t mode  : 2;
    uint8_t mode_fixed            : 1;
    bool loop;
    uint16_t last_h;
    knobDoneCB cb;
    void * init_data;
    bool showKnob;
} lv_virknob_t;

extern const lv_obj_class_t lv_virknob_class;

lv_obj_t * lv_virknob_create(lv_obj_t * parent, bool knob_recolor, void * init_data, knobDoneCB cb );

void lv_virknob_set_knob_display( lv_obj_t * virknob_obj, bool isShow );

bool lv_virknob_set_hsv(lv_obj_t * obj, lv_color_hsv_t hsv);

lv_color_hsv_t lv_virknob_get_hsv(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_VIRKNOB*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_VIRTUAL_KNOB_H*/

