#include <Ticker.h>
#include <SPI.h>
#include "KHOI_TLC5971.h"
#include "effect_control.h"
#include "config.h"

/****************************************************************************
       Define & const
 ****************************************************************************/
#define dktc_blink_time 1
#define dktc_turn_on_time 100

#define random_time_sang 10
#define random_time_tat 1

#define block_time_dem_sang 5
#define block_time_dem_tat 4

#define all_blink_time 1
#define all_on_time 50

//======================  SANG TICH LUY =======================
//===========
//=============================================================


typedef enum {
  dktc,
  roll_effect,
  random_effect,
  block_effect,
  floor_effect,
  startup,
  all_on_effect,
  all_blink_effect,
  all_off_effect,
  one_effect,
  tat_ca_no_effect,
  none,
} effect_state_t;

typedef enum {
  random_turn,
  block_turn,
  roll_turn,
} sequence_state_t;

/****************************************************************************
       local function
 ****************************************************************************/
void stop_app_ticker();

//use this to sync effect
void dummy_function();
void reset_param();
void all_on_step();
void dktc_step();
void floor_effect_step();
void startup_effect_step();
void random_effect_step();
void block_effect_step();
void one_effect_step();
/****************************************************************************
       local variable and object
 ****************************************************************************/
effect_state_t current_effect = startup;
effect_state_t last_effect = none;

sequence_state_t current_sequence_turn = random_turn;
sequence_state_t last_sequence_turn = random_turn;

// variables use for DKTC effect
Ticker dktc_ticker;
static int blink_count[all_model_total_number_of_port];
static int turn_on_count[all_model_total_number_of_port];

// variables use for all on effect
Ticker all_on_ticker;
static int all_blink_count[all_model_total_number_of_port];
static int all_turn_on_count[all_model_total_number_of_port];

//random_effect vars
Ticker random_effect_ticker;
static int random_effect_port = 0;
static int random_effect_do_sang = 0;
static int random_effect_dem_sang = 0;
static bool random_effect_random_on = true;
static bool random_effect_done = false;

//block_effect vars
Ticker block_effect_ticker;
static int block_effect_block = 0;
static int block_effect_do_sang = 0;
static int block_effect_dem_sang = 0;
static bool block_effect_done = false;
static bool block_effect_running_on = true;
static bool block_effect_done_block = false;

//floor effect vars
Ticker all_blink_ticker;


//one effect vars


/*****************************************************************************
       code
 *****************************************************************************/
Ticker roll_dong_bo_ticker;

unsigned long roll_last_millis;
unsigned long roll_current_millis;

/***************ROLL_EFFECT *******************/
//roll: sáng từng tầng, giữ sáng tầng cuối --> sau đó sáng tuần tự các tòa
//--> giữ tầng cuối sáng sau đó tắt hết
//--> cần define thời gian tắt trước khi bật tòa đó
//--> define thời gian tòa đó sáng
//--> define thời gian giữ sáng của tầng cuối
//
//--> cần 1 biến đẻ xác định là sáng tầng hoặc sáng tòa -->

Ticker roll_ticker;
bool roll_sang_tung_tang = false;
bool roll_sang_toan_bo = false;
bool roll_effect_done = false;
bool roll_xong_tang_hien_tai = false;
int roll_tang_hien_tai = 0;
int roll_do_sang = 0;
int roll_dem_sang = 0;
int roll_giu_sang = 0;
bool roll_all_sang_dan = true;
int roll_all_do_sang = 0;
int roll_all_dem_sang = 0;
unsigned long roll_last_time_giu_tang_cuoi = 0;


void roll_step() {
  roll_effect_done = false;

  if (roll_sang_toan_bo) {
    if (roll_all_sang_dan == true) {
      for (int i = 0; i < all_model_total_number_of_port; i++) {
        set_data_proc(i, roll_all_do_sang);
      }
      roll_all_do_sang = roll_all_do_sang + 5;
    } else {
      for (int i = 0; i < all_model_total_number_of_port; i++) {
        set_data_proc(i, roll_all_do_sang);
      }
      roll_all_do_sang = roll_all_do_sang - 5;
    }
    if (roll_all_do_sang >= 255) {
      roll_all_do_sang = 255;
      roll_all_dem_sang++;
      if (roll_all_dem_sang > roll_time_giu_sang_toan_bo) {
        // Serial.print(millis());
        // Serial.println(": Bat dau giu tat toan bo");
        roll_all_sang_dan = false;
        roll_all_dem_sang = 0;
      }
    }
    if (roll_all_do_sang <= 0) {
      roll_all_do_sang = 0;
      roll_all_dem_sang++;
      if (millis() - roll_last_millis > roll_time_dong_bo) {

        roll_last_millis = millis();
        // Serial.print(millis());

        // Serial.println(": het thoi gian doi dong bo");
        roll_all_sang_dan = true;
        roll_all_dem_sang = 0;
        //thoat sang toan bo, quay ve ban dau:
        roll_sang_toan_bo = false;

        if (current_effect == startup) {

          //sd cho hu03:
          Serial.println("End roll, start random");
          stop_app_ticker();
          //reset parameters
          random_effect_port = 0;
          random_effect_do_sang = 0;
          random_effect_dem_sang = 0;
          random_effect_random_on = true;
          random_effect_done = false;
          random_effect_ticker.attach(0.04, random_effect_step);
        }
      }
      if (roll_all_dem_sang > roll_time_giu_tat_toan_bo) {

        // Serial.print(millis());
        // Serial.println(": Het giu tat toan bo");
        roll_all_sang_dan = true;
        roll_all_dem_sang = 0;
        //thoat sang toan bo, quay ve ban dau:
        roll_sang_toan_bo = false;

        //sd cho hu03:
        if (current_effect == startup) {

          stop_app_ticker();
          Serial.println("End roll, start random");
          //reset parameters
          random_effect_port = 0;
          random_effect_do_sang = 0;
          random_effect_dem_sang = 0;
          random_effect_random_on = true;
          random_effect_done = false;
          random_effect_ticker.attach(0.04, random_effect_step);
        }
      }
    }
    updateData();
    guiDuLieu();
  } else {
    if (roll_sang_tung_tang == true) {
      if (roll_tang_hien_tai == 3) {
        roll_last_millis = millis();
        roll_last_time_giu_tang_cuoi = millis();
        // Serial.print(roll_last_millis);
        // Serial.println(": Cap nhat last millis");
      }
      for (int i = 0; i < all_model_total_number_of_port; i++) {
        if ((i >= this_esp_port_start) && (i <= this_esp_port_end)) {
          if (this_esp_data[i - this_esp_port_start][1] == roll_tang_hien_tai) {
            set_data_proc(this_esp_data[i - this_esp_port_start][0], roll_do_sang);
          }
        } else {
          dummy_function();
        }
      }
      updateData();
      guiDuLieu();
      roll_do_sang += 40;
    } else {
      for (int i = 0; i < all_model_total_number_of_port; i++) {
        if ((i >= this_esp_port_start) && (i <= this_esp_port_end)) {
          if (this_esp_data[i - this_esp_port_start][1] == roll_tang_hien_tai) {
            set_data_proc(this_esp_data[i - this_esp_port_start][0], roll_do_sang);
          }
        } else {
          dummy_function();
        }
      }
      updateData();
      guiDuLieu();
      if (roll_tang_hien_tai == all_model_total_number_of_block - 1 && roll_sang_tung_tang == false) {
        if (millis() - roll_last_time_giu_tang_cuoi > roll_time_dong_bo_giu_tang_cuoi) {
          roll_last_time_giu_tang_cuoi = millis();
          roll_giu_sang = roll_time_giu_sang_tang_cuoi - 1;
        }

        if (roll_giu_sang < roll_time_giu_sang_tang_cuoi) {
          roll_giu_sang++;
          roll_do_sang = roll_do_sang + 40;
        }
      }
      roll_do_sang -= 40;
    }
    // nhay sang tang moi.
    if ((roll_do_sang >= 255) && (roll_xong_tang_hien_tai) && (roll_sang_tung_tang)) {
      roll_do_sang = 0;
      roll_tang_hien_tai++;
      //sang den tang cuoi --> giu sang 1 thoi gian = tang dem sang
      // if (roll_tang_hien_tai >= all_model_total_number_of_block) {
      //   roll_tang_hien_tai = all_model_total_number_of_block;
      if (roll_tang_hien_tai >= all_model_total_number_of_block_max) {
        roll_tang_hien_tai = all_model_total_number_of_block_max;
        roll_dem_sang++;
        if (roll_dem_sang > roll_time_dem_sang) {
          roll_dem_sang = 0;
          roll_sang_tung_tang = false;
          roll_do_sang = 255;
          // Serial.print(millis());
          // Serial.println(":  Chuan bi dem tat");
          // Serial.println("Da sang het cac tang");
          roll_tang_hien_tai = 0;
        }
      }

      roll_xong_tang_hien_tai = false;
    }
    //ban dau: roll_xong_tang_hien_tai = false, sau khi sang xong 1 block --> roll_xong_tang_hien_tai = true. sau do nhay sang block moi.
    if ((roll_do_sang >= 255) && (!roll_xong_tang_hien_tai) && (roll_sang_tung_tang)) {
      roll_do_sang = 255;
      roll_xong_tang_hien_tai = true;
    }
    if ((roll_do_sang <= 0) && (roll_xong_tang_hien_tai) && (!roll_sang_tung_tang)) {
      roll_do_sang = 255;
      roll_tang_hien_tai++;

      if (roll_tang_hien_tai >= all_model_total_number_of_block) {
        roll_tang_hien_tai = all_model_total_number_of_block;
        roll_dem_sang++;
        if (roll_dem_sang > roll_time_dem_tat) {
          roll_dem_sang = 0;
          roll_sang_tung_tang = true;
          // block_effect_done = true;  //ket thuc efect
          roll_tang_hien_tai = 0;
          roll_do_sang = 0;
          roll_giu_sang = 0;
          roll_xong_tang_hien_tai = false;
          // Serial.print(millis());
          // Serial.println(": Da dem tat het");
          // Serial.println("Da tat het cac tang");
          // Serial.println("Chuan bi sang tat ca");
          roll_sang_toan_bo = true;
          // roll_ticker.detach();
          // //truoc khi detach da sang 1 thoi gian = roll_time_giu_sang_tang_cuoi
          // tlc_all_on();
          // delay(roll_time_giu_sang_toa);
          // tlc_all_off();
          // last_effect = startup;
          // delay(roll_time_giu_tat_toan_bo);
          // effect_control_roll_effect();
        }
      }
      roll_xong_tang_hien_tai = false;
    }
    if ((roll_do_sang <= 0) && (!roll_xong_tang_hien_tai) && (!roll_sang_tung_tang)) {
      roll_do_sang = 0;
      roll_xong_tang_hien_tai = true;
    }
  }
}

void effect_control_roll_effect() {
  current_effect = roll_effect;
  //reset parameters
  roll_tang_hien_tai = 0;
  roll_do_sang = 0;
  roll_dem_sang = 0;
  roll_giu_sang = 0;
  // block_effect_done = false;
  roll_sang_tung_tang = true;
  roll_xong_tang_hien_tai = false;

  stop_app_ticker();
  if (current_effect != last_effect) {
    Serial.print(millis());
    Serial.println("Start roll effect");
    roll_ticker.attach(0.03, roll_step);
  }

  last_effect = current_effect;
}

/* END ROLL EFFECT*/


void turn_off_led(int led) {
  if ((led >= this_esp_port_start) && (led <= this_esp_port_end)) {
    set_data_proc(led - this_esp_port_start, 0x00);
    //    updateData();
    //    guiDuLieu();
  }
}

void turn_on_led(int led) {
  if ((led >= this_esp_port_start) && (led <= this_esp_port_end)) {
    set_data_proc(led - this_esp_port_start, 0xff);
  }
  updateData();
  guiDuLieu();
}

void stop_app_ticker() {
  switch (current_effect) {
    case dktc:
      random_effect_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      roll_ticker.detach();
      break;
    case startup:
      random_effect_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      roll_ticker.detach();
      dktc_ticker.detach();
      tlc_all_off();
      break;
    case tat_ca_no_effect:
      random_effect_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      roll_ticker.detach();
      dktc_ticker.detach();
      tlc_all_off();

      break;
    case random_effect:
      block_effect_ticker.detach();
      dktc_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      roll_ticker.detach();
      tlc_all_off();
      break;
    case block_effect:
      random_effect_ticker.detach();
      dktc_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      roll_ticker.detach();
      tlc_all_off();
      break;
    case roll_effect:
      random_effect_ticker.detach();
      dktc_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      tlc_all_off();
      break;
    case all_on_effect:
      random_effect_ticker.detach();
      roll_ticker.detach();
      dktc_ticker.detach();
      block_effect_ticker.detach();
      all_blink_ticker.detach();
      break;
    case all_off_effect:
      random_effect_ticker.detach();
      dktc_ticker.detach();
      roll_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      all_blink_ticker.detach();
      break;
    case all_blink_effect:
      random_effect_ticker.detach();
      roll_ticker.detach();
      dktc_ticker.detach();
      block_effect_ticker.detach();
      all_on_ticker.detach();
      break;

    default:
      break;
  }
}

// sync effect
void dummy_function() {
  volatile char dummy_a;
  char dummy_b = 1;
  dummy_a = dummy_b + 1;
}

//=======================================================================
//                   ticker_step
//=======================================================================

void dktc_step() {
  for (int i = 0; i < (all_model_total_number_of_port); i++) {
    if ((blink_count[i] == 0) && (turn_on_count[i] == 0)) {
      turn_off_led(i);
    } else if ((blink_count[i] == 0) && (turn_on_count[i] >= 0)) {
      turn_on_led(i);
      turn_on_count[i]--;
    } else if (blink_count[i] > 0) {
      blink_count[i]--;
      if (blink_count[i] % 2) turn_on_led(i);
      else turn_off_led(i);
    }
  }

  updateData();
  guiDuLieu();
}

void reset_param() {
  for (int i = 0; i < all_model_total_number_of_port; i++) {
    blink_count[i] = 0;
    turn_on_count[i] = 0;
    all_blink_count[i] = 0;
    all_turn_on_count[i] = 0;
  }
  random_effect_port = 0;
  random_effect_do_sang = 0;
  random_effect_dem_sang = 0;
  random_effect_random_on = true;
  random_effect_done = false;

  //block_effect vars
  block_effect_block = 0;
  block_effect_do_sang = 0;
  block_effect_dem_sang = 0;
  block_effect_done = false;
  block_effect_running_on = true;
  block_effect_done_block = false;
}
void all_on_step() {
  for (int i = 0; i < (all_model_total_number_of_port); i++) {
    if ((all_blink_count[i] == 0) && (all_turn_on_count[i] == 0)) {
      turn_off_led(i);
    } else if ((all_blink_count[i] == 0) && (all_turn_on_count[i] >= 0)) {
      turn_on_led(i);
      all_turn_on_count[i]--;
    } else if (all_blink_count[i] > 0) {
      all_blink_count[i]--;
      if (all_blink_count[i] % 2) turn_on_led(i);
      else turn_off_led(i);
    }
  }

  updateData();
  guiDuLieu();
}

static int all_blink_do_sang = 0;
static int all_blink_sang_dan = true;
static int all_blink_dem_sang = 0;
void all_blink_step() {
  if (all_blink_sang_dan == true) {
    for (int i = 0; i < all_model_total_number_of_port; i++) {
      set_data_proc(i, all_blink_do_sang);
    }
    all_blink_do_sang = all_blink_do_sang + 5;
  } else {
    for (int i = 0; i < all_model_total_number_of_port; i++) {
      set_data_proc(i, all_blink_do_sang);
    }
    all_blink_do_sang = all_blink_do_sang - 5;
  }
  if (all_blink_do_sang >= 255) {
    all_blink_do_sang = 255;
    all_blink_dem_sang++;
    if (all_blink_dem_sang > 300) {
      all_blink_sang_dan = false;
      all_blink_dem_sang = 0;
    }
  }
  if (all_blink_do_sang <= 0) {
    all_blink_do_sang = 0;
    all_blink_dem_sang++;
    if (all_blink_dem_sang > 50) {
      all_blink_sang_dan = true;
      all_blink_dem_sang = 0;
    }
  }

  updateData();
  guiDuLieu();
}

void all_off_function() {
  uint8_t led_state[all_model_total_number_of_port];
  uint8_t num_led_off = 0;

  stop_app_ticker();
  do {
    num_led_off = 0;
    for (int i = 0; i < all_model_total_number_of_port; i++) {
      led_state[i] = get_data_proc(i);
      if (led_state[i] > 4) {
        led_state[i] -= 5;
        set_data_proc(i, led_state[i]);
        num_led_off++;
        delay(10);
      }
    }
    updateData();
    guiDuLieu();
  } while (num_led_off > 0);
  tlc_all_off();
}



// ban dau sang random, giu sang 1 luc
// sau khi sang random thi sang block, sau do giu sang
// Cuoi cung sang cuon

//startup_effect vars
Ticker startup_effect_ticker;
static int startup_do_sang = 0;
static int startup_dem_sang = 0;
static bool startup_dimming_on = true;
static bool startup_done = false;
bool startup_playing = false;  //sau khi het tat ca hieu ung, cho bien nay ve false.
void startup_effect_step() {
  current_effect = startup;
  stop_app_ticker();
  startup_playing = false;

  //reset parameters
  random_effect_port = 0;
  random_effect_do_sang = 0;
  random_effect_dem_sang = 0;
  random_effect_random_on = true;
  random_effect_done = false;

  if (startup_playing == false && current_effect != last_effect) {
    Serial.println("Start startup from random effect");
    random_effect_ticker.attach(0.04, random_effect_step);
    startup_playing = true;
  }
  last_effect = startup;
}

void effect_startup() {
  startup_effect_step();
}

void random_effect_step() {
  random_effect_done = false;

  if (random_effect_random_on) {

    if (get_data_proc(randomBuffer[random_effect_port]) < 255) {
      if ((randomBuffer[random_effect_port] >= this_esp_port_start) && (randomBuffer[random_effect_port] <= this_esp_port_end)) {
        // Serial.print("Data proc truoc 0: "), Serial.println(get_data_proc(0));
        int temp_var = this_esp_data[randomBuffer[random_effect_port] - this_esp_port_start][0];
        set_data_proc(temp_var, random_effect_do_sang);

        // Serial.print("PROC: "); Serial.println(randomBuffer[random_effect_port] - this_esp_port_start);
        // Serial.print("Data proc sau 0: "), Serial.println(get_data_proc(0));
      } else {
        dummy_function();
      }
    }
    updateData();
    guiDuLieu();
    random_effect_do_sang += 45;
  } else {
    if (random_effect_do_sang <= 10) random_effect_do_sang = 0;
    if (get_data_proc(randomBuffer[random_effect_port]) >= 0) {
      if ((randomBuffer[random_effect_port] >= this_esp_port_start) && (randomBuffer[random_effect_port] <= this_esp_port_end)) {
        set_data_proc(this_esp_data[randomBuffer[random_effect_port] - this_esp_port_start][0], random_effect_do_sang);
      } else {
        dummy_function();
      }
    }
    updateData();
    guiDuLieu();
    random_effect_do_sang -= 45;
  }

  if ((!random_effect_random_on) && (random_effect_do_sang <= 0)) {
    random_effect_do_sang = 255;
    random_effect_port++;
    if (random_effect_port >= all_model_total_number_of_port) {
      random_effect_port = all_model_total_number_of_port;
      random_effect_do_sang = 0;
      random_effect_dem_sang++;
      if (random_effect_dem_sang > random_time_tat) {
        random_effect_dem_sang = 0;
        random_effect_port = 0;
        random_effect_random_on = true;
        random_effect_done = true;
        random_effect_port = 0;
        random_effect_do_sang = 0;
        random_effect_random_on = true;
        if (current_effect == startup) {
          //nhay sang block.
          Serial.println("End randoom. Start block");
          stop_app_ticker();
          //reset parameters
          block_effect_block = 0;
          block_effect_do_sang = 0;
          block_effect_dem_sang = 0;
          block_effect_done = false;
          block_effect_running_on = true;
          block_effect_done_block = false;

          block_effect_ticker.attach(0.04, block_effect_step);
        }
        Serial.println("Da tat het random");
      }
    }
  }

  if ((random_effect_random_on) && (random_effect_do_sang >= 255)) {
    random_effect_do_sang = 0;
    random_effect_port++;
    if (random_effect_port >= all_model_total_number_of_port) {
      random_effect_port = all_model_total_number_of_port;
      random_effect_do_sang = 255;
      random_effect_dem_sang++;
      if (random_effect_dem_sang > random_time_sang) {
        random_effect_dem_sang = 0;
        random_effect_port = 0;
        random_effect_random_on = false;
        // Serial.println("Da sang het randoom");
      }
    }
  }
}

void effect_control_dktc_on_off_v2() {
  current_effect = dktc;
  stop_app_ticker();
  last_effect = current_effect;
}

void block_effect_step() {
  block_effect_done = false;
  if (block_effect_running_on) {
    for (int i = 0; i < all_model_total_number_of_port; i++) {
      if ((i >= this_esp_port_start) && (i <= this_esp_port_end)) {
        if (this_esp_data[i - this_esp_port_start][1] == block_effect_block) {
          set_data_proc(this_esp_data[i - this_esp_port_start][0], block_effect_do_sang);
        }
      } else {
        dummy_function();
      }
    }
    updateData();
    guiDuLieu();
    block_effect_do_sang += 40;
  } else {
    for (int i = 0; i < all_model_total_number_of_port; i++) {
      if ((i >= this_esp_port_start) && (i <= this_esp_port_end)) {
        if (this_esp_data[i - this_esp_port_start][1] == block_effect_block) {
          set_data_proc(this_esp_data[i - this_esp_port_start][0], block_effect_do_sang);
        }
      } else {
        dummy_function();
      }
    }
    updateData();
    guiDuLieu();
    block_effect_do_sang -= 40;
  }

  // nhay sang block moi.
  if ((block_effect_do_sang >= 255) && (block_effect_done_block) && (block_effect_running_on)) {
    block_effect_do_sang = 0;
    block_effect_block++;
    //sang den block cuoi --> giu sang 1 thoi gian = block dem sang
    if (block_effect_block >= all_model_total_number_of_block_max) {
      block_effect_block = all_model_total_number_of_block_max;
      block_effect_dem_sang++;
      if (block_effect_dem_sang > block_time_dem_sang) {
        block_effect_dem_sang = 0;
        block_effect_running_on = false;
        block_effect_do_sang = 255;
        // Serial.println("Da sang het block");
      }
    }
    block_effect_done_block = false;
  }
  //ban dau: block_effect_done_block = false, sau khi sang xong 1 block --> block_effect_done_block = true. sau do nhay sang block moi.
  if ((block_effect_do_sang >= 255) && (!block_effect_done_block) && (block_effect_running_on)) {
    block_effect_do_sang = 255;
    block_effect_done_block = true;
  }

  if ((block_effect_do_sang <= 0) && (block_effect_done_block) && (!block_effect_running_on)) {
    block_effect_do_sang = 255;
    block_effect_block--;

    if (block_effect_block <= 0) {
      block_effect_block = 0;
      block_effect_dem_sang++;
      if (block_effect_dem_sang > block_time_dem_tat) {
        block_effect_dem_sang = 0;
        block_effect_running_on = true;
        block_effect_block = 0;
        block_effect_do_sang = 0;
        block_effect_dem_sang = 0;
        block_effect_running_on = true;
        block_effect_done_block = false;
        block_effect_do_sang = 0;
        block_effect_done = true;
        if (current_effect == startup) {
          Serial.println("End block, start roll_effect");
          //reset parameters
          roll_tang_hien_tai = 0;
          roll_do_sang = 0;
          roll_dem_sang = 0;
          roll_giu_sang = 0;
          // block_effect_done = false;
          roll_sang_tung_tang = true;
          roll_xong_tang_hien_tai = false;

          stop_app_ticker();
          startup_playing = false;
          roll_ticker.attach(0.03, roll_step);
        }
        // Serial.println("Da tat het block");
      }
    }
    block_effect_done_block = false;
  }
  if ((block_effect_do_sang <= 0) && (!block_effect_done_block) && (!block_effect_running_on)) {
    block_effect_do_sang = 0;
    block_effect_done_block = true;
  }
}

//=======================================================================
//                   start_effect
//=======================================================================

void effect_dktc_not_blink(int led) {
  set_data_proc(led, 255);
  updateData();
  guiDuLieu();
}

void effect_control_all_on() {
  current_effect = all_on_effect;
  stop_app_ticker();
  reset_param();

  //dktc copy
  for (int i = 0; i < all_model_total_number_of_port; i++) {
    all_blink_count[i] = all_blink_time * 2;
    all_turn_on_count[i] = all_on_time;
  }

  if (current_effect != last_effect) {
    Serial.println("effect all on");
    all_on_ticker.attach(0.3, all_on_step);
  }
  last_effect = current_effect;
}
void effect_control_all_off() {
  current_effect = all_off_effect;
  stop_app_ticker();
  reset_param();
  tlc_all_off();
  last_effect = current_effect;
}

void effect_control_all_blink() {
  current_effect = all_blink_effect;
  stop_app_ticker();
  all_blink_do_sang = 0;
  all_blink_dem_sang = 0;
  all_blink_sang_dan = true;
  if (current_effect != last_effect) {
    Serial.println("start all_blink");
    all_blink_ticker.attach(0.05, all_blink_step);
  }
  last_effect = current_effect;
}

void effect_dktc_start_blink(int led) {
  current_effect = dktc;
  stop_app_ticker();

  blink_count[led] = dktc_blink_time * 2;
  turn_on_count[led] = dktc_turn_on_time;

  if (current_effect != last_effect) {
    tlc_all_off();
    Serial.println("start dktc");
    dktc_ticker.attach(0.3, dktc_step);
  }
  last_effect = current_effect;
}

void effect_dktc_on_off(int led, int state) {
  current_effect = dktc;
  stop_app_ticker();
  if (state == 1) {
    turn_on_led(led);
  } else if (state == 0) {
    turn_off_led(led);
  }
  last_effect = current_effect;
}

void effect_start_random_effect() {
  current_effect = random_effect;
  stop_app_ticker();

  //reset parameters
  random_effect_port = 0;
  random_effect_do_sang = 0;
  random_effect_dem_sang = 0;
  random_effect_random_on = true;
  random_effect_done = false;

  if (current_effect != last_effect) {
    Serial.println("start random");
    random_effect_ticker.attach(0.04, random_effect_step);
  }
  last_effect = current_effect;
}

void effect_tat_ca_sang_no_effect() {
  current_effect = tat_ca_no_effect;
  stop_app_ticker();
  tlc_all_on();
  last_effect = current_effect;
}

void effect_tat_tat_ca() {
  current_effect = tat_ca_no_effect;
  stop_app_ticker();
  tlc_all_off();
  last_effect = current_effect;
}

void effect_start_block_effect() {
  current_effect = block_effect;
  stop_app_ticker();

  //reset parameters
  block_effect_block = 0;
  block_effect_do_sang = 0;
  block_effect_dem_sang = 0;
  block_effect_done = false;
  block_effect_running_on = true;
  block_effect_done_block = false;

  if (current_effect != last_effect) {
    Serial.println("start block");
    block_effect_ticker.attach(0.04, block_effect_step);
  }
  last_effect = current_effect;
}

//=======================================================================
//                   init
//=======================================================================
void effect_control_init(void) {
  tlc_init();
  // effect_start_random_effect();
  // effect_control_roll_effect();
  // startup_effect_step();
  // effect_control_all_on();
  //  dktc_ticker.attach(0.3, dktc_step);
  // startup_effect_ticker.attach(0.04, startup_effect_step);
  // block_effect_ticker.attach(0.04, block_effect_step);
  // random_effect_ticker.attach(0.04, random_effect_step);
  // effect_control_all_blink();
  // effect_control_sequence();
  Serial.println("Done init");
  effect_start_block_effect();
  //test_tlc();
  
}
void test_tlc() {
  
    set_data_proc(1, 255);
    updateData();
    guiDuLieu();
    Serial.println("on");
    delay(1000);
    set_data_proc(1, 0);
    updateData();
    guiDuLieu();
    Serial.println("off");
    delay(1000);
  
}