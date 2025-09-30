#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *stats_system;
    lv_obj_t *velocity_curve;
    lv_obj_t *obj0;
    lv_obj_t *velocity_digit;
    lv_obj_t *odometer_velocity;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *rpm_curve;
    lv_obj_t *obj4;
    lv_obj_t *gear_lever;
    lv_obj_t *gear_lever_gauge;
    lv_obj_t *fuel;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *battery_icon;
    lv_obj_t *right_sign;
    lv_obj_t *left_sign;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *temperature;
    lv_obj_t *brake_sign;
    lv_obj_t *obj9;
    lv_obj_t *highbeam;
    lv_obj_t *lowbeam;
    lv_obj_t *autolight;
    lv_obj_t *position_light;
    lv_obj_t *hazard_sign;
    lv_obj_t *title_stat;
    lv_obj_t *battery_panel;
    lv_obj_t *obj10;
    lv_obj_t *battery_db;
    lv_obj_t *stat_panel;
    lv_obj_t *light_stat;
    lv_obj_t *light_status;
    lv_obj_t *gear_stat;
    lv_obj_t *gear_status;
    lv_obj_t *velocity_stat;
    lv_obj_t *velocity_stat_digit;
    lv_obj_t *brake_stat;
    lv_obj_t *brake_digit;
    lv_obj_t *message_panel;
    lv_obj_t *message_stat;
    lv_obj_t *message_stat_1;
    lv_obj_t *message_stat_2;
    lv_obj_t *light_panel;
    lv_obj_t *ab_stat;
    lv_obj_t *ab_sign;
    lv_obj_t *ab_status;
    lv_obj_t *rab_btn;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_STATS_SYSTEM = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_stats_system();
void tick_screen_stats_system();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
