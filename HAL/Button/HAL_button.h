//
// Created by ds on 2023/7/27.
//

#ifndef _HAL_BUTTON_H_
#define _HAL_BUTTON_H_

#include "stdint.h"
#include "string.h"
#include <rtdef.h>

/*--------------------------------------*/
// bsp button pinout
#define BTN_PIN_UP (GET_PIN(C, 5))
#define BTN_PIN_DOWN (GET_PIN(C, 1))
#define BTN_PIN_LEFT (GET_PIN(C, 0))
#define BTN_PIN_RIGHT (GET_PIN(C, 4))

/*--------------------------------------*/

//According to your need to modify the constants.
#define TICKS_INTERVAL    5    //ms
#define DEBOUNCE_TICKS    3    //MAX 8
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)

// bsp button active level
extern rt_bool_t btnActiveStatus;

typedef void (*BtnCallback)(void *);

typedef enum
{
    PRESS_DOWN = 0,
    PRESS_UP,
    PRESS_REPEAT,
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS_START,
    LONG_PRESS_HOLD,
    number_of_event,
    NONE_PRESS
} PressEvent;

typedef struct Button
{
    uint16_t ticks;
    uint8_t repeat: 4;
    uint8_t event: 4;
    uint8_t state: 3;
    uint8_t debounce_cnt: 3;
    uint8_t active_level: 1;
    uint8_t button_level: 1;
    uint8_t button_id;
    uint8_t (*hal_button_Level)(uint8_t button_id_);
    BtnCallback cb[number_of_event];
    struct Button *next;
} Button;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(struct Button *handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id);
void button_attach(struct Button *handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button *handle);
int button_start(struct Button *handle);
void button_stop(struct Button *handle);
void button_ticks(void);


void Button_Init(void);

#ifdef __cplusplus
}
#endif

#endif //_HAL_BUTTON_H_
