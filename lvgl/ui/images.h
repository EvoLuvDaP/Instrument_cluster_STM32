#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_car_fuel;
extern const lv_img_dsc_t img_turn_sign_1;
extern const lv_img_dsc_t img_battery;
extern const lv_img_dsc_t img_brake;
extern const lv_img_dsc_t img_headlight;
extern const lv_img_dsc_t img_airbag;
extern const lv_img_dsc_t img_bg;
extern const lv_img_dsc_t img_highbeam;
extern const lv_img_dsc_t img_lowbeam;
extern const lv_img_dsc_t img_autolight;
extern const lv_img_dsc_t img_position_light;
extern const lv_img_dsc_t img_hazard_light;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/
