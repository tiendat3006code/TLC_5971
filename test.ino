#include <WiFi.h>
#include <Arduino.h>
#include <Ticker.h>
//include OTA
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>

#include "config.h"
#include "effect_control.h"
#include "KHOI_TLC5971.h"
#include "message_queue.h"

#define T302

#ifdef T302
const char *ssid = "t302";
const char *password = "889988998899";
#endif

#ifdef laohac91
const char *ssid = "laohac91";
const char *password = "998899889988";
#endif

#ifdef home
const char *ssid = "TP-Link-T3";
const char *password = "datcong888";
#endif
// effect_control test1;
void init_ip();
const int led_debug = 4;
int addr_static_ip = 0;

#ifdef T302
IPAddress ip(192, 168, 1, addr_static_ip);
// IPAddress ip;  //set static ip
IPAddress gateway(192, 168, 1, 1);   //set getteway
IPAddress subnet(255, 255, 255, 0);  //set subnet
#endif

//server
const int port = 8888;
const int max_clients = 10;
WiFiServer server(port);
WiFiClient clients(max_clients);

Ticker led_debug_ticker;
Ticker check_queue_ticker;
Ticker effect_random;
//OTA port
const int ota_port = 8888;
AsyncWebServer ota_server(ota_port);

void setWiFi() {
  // Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
  WiFi.mode(WIFI_STA);         //che do station
  WiFi.begin(ssid, password);  //ssid + pass wifi
  Serial.print("DANG KET NOI");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(200);
  }
  Serial.print("KET NOI THANH CONG");
  Serial.println();
  Serial.print("DIA CHI IP:");
  Serial.print(WiFi.localIP());
  Serial.println();
  Serial.print("DIA CHI MAC:");
  Serial.println(WiFi.macAddress());
}
void led_debug_step() {
  static bool debug_led_state = 0;
  if (debug_led_state) {
    debug_led_state = false;
  } else {
    debug_led_state = true;
  }
  digitalWrite(led_debug, debug_led_state);
}
void check_queue_step() {
  uint8_t *message_queue_element;
  int offset = 0;
  if (!message_queue_is_empty()) {
    message_queue_peek_head_element((uint8_t **)&message_queue_element);

    Serial.println("pop queue->");

    while (message_queue_element[offset] == message_synch) {
      offset++;
    }
  }
  Serial.print((char)message_queue_element[offset]);
  Serial.println((char)message_queue_element[offset + 3]);
  switch (message_queue_element[offset]) {
    case message_type_effect:
      //hieu ung
      if (message_queue_element[offset + 3] == message_effect_random) {
        //HU01 - random
        effect_start_random_effect();
      } else if (message_queue_element[offset + 3] == message_effect_block) {
        //HU02 - block
        effect_start_block_effect();
      } else if (message_queue_element[offset + 3] == message_effect_all_blink) {
        //HU05-all_blink_dimming
        effect_control_all_blink();
      } else if (message_queue_element[offset + 3] == message_effect_roll) {
        //HU03-sang tich luy
        effect_control_roll_effect();
      } else if (message_queue_element[offset + 3] == message_effect_sequence) {
        //HU03-sang tich luy
        effect_startup();
      }
      break;

    case message_type_dktc:
      //DKTC
      // for (int i = 0; i < all_model_total_number_of_port; i++) {
      //   if (message_queue_element[offset + 5 + i] == message_dktc_on) {
      //     for (int j = 0; j < all_model_total_number_of_port; j++) {
      //       if (this_esp_data[j][0] == i) {
      //         effect_dktc_on_off(j);
      //       }
      //     }
      //     Serial.println(i);
      //   }
      // }
      effect_control_dktc_on_off_v2();
      for (int i = 0; i < all_model_total_number_of_port; i++) {
        if (message_queue_element[offset + 5 + i] == message_dktc_on) {
          // effect_dktc_on_off(i, 1);
          set_data_proc(i - this_esp_port_start, 0xff);
        } else if (message_queue_element[offset + 5 + i] == message_dktc_off) {
          // effect_dktc_on_off(i, 0);
          set_data_proc(i - this_esp_port_start, 0x00);
        }
      }
      updateData();
      guiDuLieu();
      break;
    case message_type_tat_ca:
      if (message_queue_element[offset + 2] == message_all_on) {
        //AAA0-all off
        effect_tat_ca_sang_no_effect();
      } else if (message_queue_element[offset + 2] == message_all_off) {
        //AAA1-all on
        effect_tat_tat_ca();
      }
      break;
    case message_type_all:
      if (message_queue_element[offset + 3] == message_all_off) {
        //AAA0-all off
        effect_control_all_off();
      } else if (message_queue_element[offset + 3] == message_all_on) {
        //AAA1-all on
        effect_control_all_on();
      }
      break;

    case message_type_one:
      break;

    default:
      break;
  }

  //remove head element after process
  message_queue_remove_head_element();
}

void init_ip() {
  int addr_state[4] = { 0 };
  int addr_pin[] = { ADDR0_PIN, ADDR1_PIN, ADDR2_PIN, ADDR3_PIN };
  Serial.print("State IP pin: ");
  for (int i = 0; i < 4; i++) {
    pinMode(addr_pin[i], INPUT);
    addr_state[i] = digitalRead(addr_pin[i]);
    if (addr_state[i] != 0) {
      addr_static_ip += addr_state[i] * pow(2, i);
    }
    Serial.print(addr_state[i]);
  }
  Serial.println();
  addr_static_ip += base_static_ip;
  // ip = IPAddress ip2(192, 168, 1, addr_static_ip);
  ip[3] = addr_static_ip;
}

void setup() {
  setWiFi();
   Serial.begin(115200);
  //  WiFi.begin(ssid, password);  //ssid + pass wifi
  //   if (WiFi.status() != WL_CONNECTED) {
  //   Serial.print("loi");
  //   delay(200);
  // }else 
  // {
  //   Serial.println("ok");
  // }
  // Serial.println("ok");
  pinMode(led_debug, OUTPUT);
  led_debug_ticker.attach(0.5, led_debug_step);
  //start check timer
  //check_queue_ticker.attach(0.1, check_queue_step);
  effect_control_init();
  init_ip();
  led_debug_ticker.detach();
  //effect_dktc_start_blink(1);
  //test_tlc();
  //effect_tat_ca_sang_no_effect();
  //effect_start_random_effect();
  effect_tat_ca_sang_no_effect();  
  updateData();
  guiDuLieu();
}
void loop() {
  //test_tlc();
  //tlc_all_on();
  
  //turn_on_led(4);
}