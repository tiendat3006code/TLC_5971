#ifndef effect_control_h
#define effect_control_h

#include <stdint.h>
#include <stdbool.h>
#include "Arduino.h"
#include <config.h>

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
   message define
 ******************************************************************************/
#define message_synch '#'
#define message_end '$'
#define message_type_effect 'H'
#define message_type_dktc 'D'
#define message_type_all 'A'  //All. AAA0: All off, AAA1: All on
#define message_type_one 'O'  //ONE. OOO00 --> đèn 1 tắt, OOO01 --> đèn 1 bật. Số đèn là số số 0 ở giữa, cái cuối là trạng thái đèn
#define message_type_tat_ca 'T'

//hu01 random
//hu02 block
#define message_effect_random '1'
#define message_effect_block '2'
#define message_effect_all_blink '5'
#define message_effect_sequence '4'
#define message_effect_roll '3'

#define message_all_off '0'
#define message_all_on '1'

#define message_dktc_off '0'
#define message_dktc_on '1'

#define message_one_off '0'
#define message_one_on '1'

/*******************************************************************************
 * API
 ******************************************************************************/
void effect_control_init(void);
void effect_dktc_start_blink(int led);
void effect_dktc_not_blink(int led);
void effect_dktc_on_off(int led, int state);

void effect_start_random_effect();
void effect_start_block_effect();

void effect_control_all_on();
void effect_control_all_off();

void effect_startup();
void effect_control_all_blink();
void effect_control_sequence();
void effect_control_roll_effect();
void effect_control_dktc_on_off_v2();

void effect_tat_ca_sang_no_effect();
void effect_tat_tat_ca();
void test_tlc();
#ifdef __cplusplus
}
#endif

#endif // effect_h
