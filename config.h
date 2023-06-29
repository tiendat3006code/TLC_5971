#ifndef config_h
#define config_h

#include <stdint.h>
#include <stdbool.h>
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
   Definitions
 ******************************************************************************/

//static ip: 192.168.31.xxx
#define ADDR0_PIN 35
#define ADDR1_PIN 34
#define ADDR2_PIN 39
#define ADDR3_PIN 36

/* Nhung thu can config:
 * number ESP cua tlc, so cong, so block phai chinh xac
 * Thoi gian sang tang cuoi cua cac board la khac nhau. A>B>C....
 * Doi voi roll_effect: config so block > 1 so voi thuc te.
 
*/
//*********************************************************************
//  CONFIG TIME
//*********************************************************************
#define roll_time_dong_bo 80000          //thoi gian dong bo cho toan bo hieu ung roll
#define roll_time_dong_bo_giu_tang_cuoi 60000 //thoi gian tang cuoi sang, sau do cung tat tai giay thu 60
#define roll_time_giu_tat_toan_bo 100000   //Dat cang lon cang tot, vi config theo timer roi
#define roll_time_giu_sang_tang_cuoi 1   //Dat cang lon cang tot, vi config theo timer roi


#define all_model_total_number_of_port 144
#define port_bo_qua 144
#define all_model_total_number_of_block_max 39


//*********************************************************************
//  CHOOSE ESP
//*********************************************************************
// #define TOP 0
// #define MID 1
// #define BOTTOM 2

// // #define ESP_NUM BOTTOM
// //===========================TOP=======================================
// #if ESP_NUM == TOP
// // //hu3, sang tich luy
// #define roll_time_dem_sang 5
// #define roll_time_dem_tat 3
// #define roll_time_giu_sang_toan_bo 100
// #define base_static_ip  150

// #endif //ESP_NUM == TOP
// //===========================MID=======================================
// #if ESP_NUM == MID
// //hu3, sang tich luy
// #define roll_time_dem_sang 5
// #define roll_time_dem_tat 6
// #define roll_time_giu_sang_toan_bo 100

// #define base_static_ip  (150-1)
// #endif //ESP_NUM == MID
// //===========================BOTTOM=======================================
// #if ESP_NUM == BOTTOM
// //hu3, sang tich luy
// #define roll_time_dem_sang 5
// #define roll_time_dem_tat 9
// #define roll_time_giu_sang_toan_bo 100
// #define base_static_ip  (150-2)

// #endif //ESP_NUM == BOTTOM


//Note: Khai bao so tang > 1 so voi so tang thuc te
//Lam nhu vay de tang cuoi ko bi nhay
//tang cuoi hay de sang port ma ko cam voi cong tlc nao
//******************************************************
//  CONFIG PORT
//******************************************************
//=========================TOP==========================
// #if ESP_NUM == TOP
// #define all_model_total_number_of_block 8 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
// #define this_esp_number_of_tlc 1
// #define  port_thang_test 0
// const int this_esp_data[all_model_total_number_of_port][2] = {
//   8, port_thang_test;
//   0,1,
//   1,2,
//   2,3,
//   3,4,
//   4,5,
//   5,6,
//   6,7,
//   140,8,
//   140,9,
//   140,10,
//   140,11,
//   140,12,
// };
// #endif //ESP_NUM == TOP

// //=========================MID==========================
// #if ESP_NUM == MID
// #define all_model_total_number_of_block 11
// #define this_esp_number_of_tlc 1
// const int this_esp_data[all_model_total_number_of_port][2] = {
//   // 2,1,  //address 2 chu ko phai cong so 2--> neu map cong 1 thi de so la 0.
//   0,1,
//   1,2,
//   2,3,
//   3,4,
//   4,5,
//   5,6,
//   6,7,
//   7,8,
//   8,9,
//   9,10,
//   140,11,
//   140,12,
// };
// #endif //ESP_NUM == MID

// //=========================BOTTOM==========================
// #if ESP_NUM == BOTTOM
// #define all_model_total_number_of_block 9
// #define this_esp_number_of_tlc 1
// const int this_esp_data[all_model_total_number_of_port][2] = {
//   0,1,
//   1,2,
//   2,3,
//   3,4,
//   4,5,
//   5,6,
//   6,7,
//   7,8,
//   140,9,--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+++++++++++++++++++
//   140,10,
//   140,11,
//   140,12,
// };
// #endif // ESP_NUM == BOTTOM

//=====================================================================================================================================================
//                BAT DAU CHO CAC TOA CHINH THUC TU  A ==> L
//=====================================================================================================================================================
/** Config IP:  base: 192.168.31.150
 *Toa A: 0
 *Toa B: 1
 *Toa C: 2
 *Toa D: 3
 *Toa E: 4
 *Toa F: 5
 *Toa G: 6
 *Toa H: 7
 *Toa I: 8
 *Toa J: 9
 *Toa K: 10
 *Toa L: 11
*/
#define base_static_ip  155
#define IP_OFFSET_A     0
#define IP_OFFSET_B     1
#define IP_OFFSET_C     2
#define IP_OFFSET_D     3
#define IP_OFFSET_E     4
#define IP_OFFSET_F     5
#define IP_OFFSET_G     6
#define IP_OFFSET_H     7
#define IP_OFFSET_I     8
#define IP_OFFSET_J     9
#define IP_OFFSET_K     10
#define IP_OFFSET_L     11
#define IP_OFFSET_disable 12

#define port_fake           140
#define stt_tang_thang      38  //cai nay chua ro nen tam thoi de 50, cho no ko sang
//CHON ESP
#define IP_OFFSET_ESP      IP_OFFSET_A    //////===========================THAY CAI NAY============================
/********** Toa A *************/
#if  IP_OFFSET_ESP == IP_OFFSET_A
// #define all_model_total_number_of_block 12 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 1
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 43
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 3
// #define roll_time_giu_sang_toan_bo 100
#define roll_time_giu_sang_toan_bo 180

const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,12,
    3,13,
    4,2,
    5,2,
    6,2,
    7,2,
    8,3,
    9,3,
    10,3,
    11,3,
    12,4,
    13,4,
    14,4,
    15,4,
    16,5,
    17,5,
    18,5,
    19,5,
    20,6,
    21,6,
    22,6,
    23,6,
    24,7,
    25,7,
    26,7,
    27,7,
    28,8,
    29,8,
    30,8,
    31,8,
    32,9,
    33,9,
    34,9,
    35,9,
    36,10,
    37,10,
    38,10,
    39,10,
    40,11,
    41,11,
    42,11,
    43,11,
    port_fake, 12,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_A

/********** Toa B *************/
#if IP_OFFSET_ESP == IP_OFFSET_B
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 9
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 104
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 6
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,4,
    9,4,
    10,4,
    11,5,
    12,5,
    13,5,
    14,6,
    15,6,
    16,6,
    17,7,
    18,7,
    19,7,
    20,8,
    21,8,
    22,8,
    23,9,
    24,9,
    25,9,
    26,10,
    27,10,
    28,10,
    29,11,
    30,11,
    31,11,
    32,12,
    33,12,
    34,12,
    35,13,
    36,13,
    37,13,
    38,14,
    39,14,
    40,14,
    41,15,
    42,15,
    43,16,
    44,16,
    45,16,
    46,16,
    47,17,
    48,17,
    49,18,
    50,18,
    51,18,
    52,18,
    53,19,
    54,19,
    55,19,
    56,20,
    57,20,
    58,20,
    59,20,
    60,21,
    61,21,
    62,22,
    63,22,
    64,22,
    65,23,
    66,23,
    67,24,
    68,24,
    69,24,
    70,25,
    71,25,
    72,26,
    73,26,
    74,26,
    75,27,
    76,27,
    77,27,
    78,28,
    79,28,
    80,28,
    81,28,
    82,29,
    83,29,
    84,29,
    85,30,
    86,30,
    87,30,
    88,30,
    89,31,
    90,31,
    91,32,
    92,32,
    93,33,
    94,33,
    95,33,
    96,33,
    97,34,
    98,34,
    99,35,
    100,35,
    101,36,
    102,36,
    103,37,
    104,37,
    port_fake, 38,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_B

/********** Toa C *************/
#if IP_OFFSET_ESP == IP_OFFSET_C
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 10
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 109
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 9
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,4,
    9,4,
    10,4,
    11,5,
    12,5,
    13,5,
    14,6,
    15,6,
    16,6,
    17,7,
    18,7,
    19,7,
    20,8,
    21,8,
    22,8,
    23,9,
    24,9,
    25,9,
    26,10,
    27,10,
    28,10,
    29,11,
    30,11,
    31,11,
    32,12,
    33,12,
    34,12,
    35,13,
    36,13,
    37,13,
    38,14,
    39,14,
    40,14,
    41,15,
    42,15,
    43,15,
    44,16,
    45,16,
    46,16,
    47,17,
    48,17,
    49,17,
    50,18,
    51,18,
    52,18,
    53,19,
    54,19,
    55,19,
    56,20,
    57,20,
    58,21,
    59,21,
    60,22,
    61,22,
    62,22,
    63,23,
    64,23,
    65,23,
    66,24,
    67,24,
    68,24,
    69,25,
    70,25,
    71,25,
    72,26,
    73,26,
    74,26,
    75,27,
    76,27,
    77,27,
    78,28,
    79,28,
    80,28,
    81,29,
    82,29,
    83,29,
    84,30,
    85,30,
    86,30,
    87,31,
    88,31,
    89,31,
    90,32,
    91,32,
    92,32,
    93,33,
    94,33,
    95,33,
    96,34,
    97,34,
    98,34,
    99,35,
    100,35,
    101,35,
    102,37,
    103,37,
    104,37,
    105,37,
    106,37,
    107,37,
    108,37,
    109,37,
    port_fake,38,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_C

/********** Toa D *************/
#if IP_OFFSET_ESP == IP_OFFSET_D
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 9
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 106
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 12
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,4,
    9,4,
    10,4,
    11,4,
    12,5,
    13,5,
    14,5,
    15,6,
    16,6,
    17,6,
    18,6,
    19,7,
    20,7,
    21,7,
    22,8,
    23,8,
    24,8,
    25,8,
    26,9,
    27,9,
    28,9,
    29,10,
    30,10,
    31,10,
    32,10,
    33,11,
    34,11,
    35,11,
    36,12,
    37,12,
    38,12,
    39,13,
    40,13,
    41,13,
    42,14,
    43,14,
    44,14,
    45,15,
    46,15,
    47,15,
    48,16,
    49,16,
    50,16,
    51,16,
    52,17,
    53,17,
    54,17,
    55,18,
    56,18,
    57,18,
    58,18,
    59,19,
    60,19,
    61,19,
    62,20,
    63,21,
    64,21,
    65,21,
    66,22,
    67,22,
    68,22,
    69,22,
    70,23,
    71,23,
    72,24,
    73,24,
    74,24,
    75,25,
    76,25,
    77,26,
    78,26,
    79,26,
    80,27,
    81,27,
    82,28,
    83,28,
    84,28,
    85,29,
    86,29,
    87,30,
    88,30,
    89,30,
    90,31,
    91,31,
    92,32,
    93,32,
    94,32,
    95,33,
    96,33,
    97,34,
    98,34,
    99,34,
    100,35,
    101,35,
    102,36,
    103,36,
    104,37,
    105,37,
    106,37,
    107,37,
    port_fake,38,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_D

/********** Toa E *************/
#if IP_OFFSET_ESP == IP_OFFSET_E
// #define all_model_total_number_of_block 13 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 3
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 34
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 15
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,13,
    3,2,
    4,2,
    5,2,
    6,3,
    7,3,
    8,3,
    9,4,
    10,4,
    11,4,
    12,5,
    13,5,
    14,5,
    15,6,
    16,6,
    17,6,
    18,7,
    19,7,
    20,7,
    21,8,
    22,8,
    23,8,
    24,9,
    25,9,
    26,9,
    27,10,
    28,10,
    29,10,
    30,11,
    31,11,
    32,11,
    33,12,
    34,12,
    35,12,
port_fake,13,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_E

/********** Toa F *************/
#if IP_OFFSET_ESP == IP_OFFSET_F
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua 
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 11
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 125
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 18
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,2,
    6,3,
    7,3,
    8,3,
    9,3,
    10,4,
    11,4,
    12,4,
    13,4,
    14,5,
    15,5,
    16,5,
    17,5,
    18,6,
    19,6,
    20,6,
    21,6,
    22,7,
    23,7,
    24,7,
    25,7,
    26,8,
    27,8,
    28,8,
    29,8,
    30,9,
    31,9,
    32,9,
    33,9,
    34,10,
    35,10,
    36,10,
    37,10,
    38,11,
    39,11,
    40,11,
    41,11,
    42,12,
    43,12,
    44,12,
    45,12,
    46,13,
    47,13,
    48,13,
    49,13,
    50,14,
    51,14,
    52,14,
    53,14,
    54,15,
    55,15,
    56,15,
    57,16,
    58,16,
    59,16,
    60,16,
    61,17,
    62,17,
    63,17,
    64,18,
    65,18,
    66,18,
    67,18,
    68,19,
    69,19,
    70,19,
    71,20,
    72,21,
    73,21,
    74,21,
    75,22,
    76,22,
    77,22,
    78,22,
    79,23,
    80,23,
    81,23,
    82,24,
    83,24,
    84,24,
    85,24,
    86,25,
    87,25,
    88,25,
    89,26,
    90,26,
    91,26,
    92,26,
    93,27,
    94,27,
    95,27,
    96,28,
    97,28,
    98,28,
    99,28,
    100,29,
    101,29,
    102,29,
    103,30,
    104,30,
    105,30,
    106,30,
    107,31,
    108,31,
    109,31,
    110,32,
    111,32,
    112,32,
    113,33,
    114,33,
    115,34,
    116,34,
    117,34,
    118,34,
    119,35,
    120,35,
    121,35,
    122,36,
    123,37,
    124,37,
    125,37,
    port_fake,38,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_F

/********** Toa G *************/
#if IP_OFFSET_ESP == IP_OFFSET_G
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 11
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 127
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 21
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,3,
    9,4,
    10,4,
    11,4,
    12,5,
    13,5,
    14,5,
    15,5,
    16,6,
    17,6,
    18,6,
    19,6,
    20,7,
    21,7,
    22,7,
    23,7,
    24,8,
    25,8,
    26,8,
    27,9,
    28,9,
    29,9,
    30,9,
    31,10,
    32,10,
    33,10,
    34,11,
    35,11,
    36,11,
    37,11,
    38,12,
    39,12,
    40,12,
    41,12,
    42,13,
    43,13,
    44,13,
    45,14,
    46,14,
    47,14,
    48,15,
    49,15,
    50,15,
    51,15,
    52,16,
    53,16,
    54,16,
    55,17,
    56,17,
    57,17,
    58,17,
    59,18,
    60,18,
    61,18,
    62,19,
    63,19,
    64,19,
    65,19,
    66,20,
    67,21,
    68,21,
    69,22,
    70,22,
    71,22,
    72,23,
    73,23,
    74,23,
    75,23,
    76,24,
    77,24,
    78,24,
    79,24,
    80,25,
    81,25,
    82,25,
    83,26,
    84,26,
    85,26,
    86,26,
    87,27,
    88,27,
    89,27,
    90,27,
    91,28,
    92,28,
    93,28,
    94,29,
    95,29,
    96,29,
    97,29,
    98,30,
    99,30,
    100,30,
    101,30,
    102,31,
    103,31,
    104,31,
    105,32,
    106,32,
    107,32,
    108,32,
    109,33,
    110,33,
    111,33,
    112,33,
    113,34,
    114,34,
    115,34,
    116,34,
    117,35,
    118,35,
    119,35,
    120,37,
    121,37,
    122,37,
    123,37,
    124,37,
    125,37,
    126,37,
    127,37,
    port_fake,38,
};
#endif //IP_OFFSET_ESP == IP_OFFSET_G

/********** Toa H *************/
#if IP_OFFSET_ESP == IP_OFFSET_H
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 10
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 109
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 24
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,4,
    9,4,
    10,4,
    11,5,
    12,5,
    13,5,
    14,6,
    15,6,
    16,6,
    17,7,
    18,7,
    19,7,
    20,8,
    21,8,
    22,8,
    23,9,
    24,9,
    25,9,
    26,10,
    27,10,
    28,10,
    29,11,
    30,11,
    31,11,
    32,12,
    33,12,
    34,12,
    35,13,
    36,13,
    37,13,
    38,14,
    39,14,
    40,14,
    41,15,
    42,15,
    43,15,
    44,16,
    45,16,
    46,16,
    47,16,
    48,16,
    49,17,
    50,17,
    51,17,
    52,18,
    53,18,
    54,18,
    55,18,
    56,19,
    57,19,
    58,19,
    59,20,
    60,21,
    61,21,
    62,21,
    63,22,
    64,22,
    65,22,
    66,22,
    67,23,
    68,23,
    69,23,
    70,24,
    71,24,
    72,24,
    73,24,
    74,25,
    75,25,
    76,25,
    77,26,
    78,26,
    79,26,
    80,26,
    81,27,
    82,27,
    83,27,
    84,28,
    85,28,
    86,28,
    87,28,
    88,29,
    89,29,
    90,29,
    91,30,
    92,30,
    93,30,
    94,30,
    95,31,
    96,31,
    97,32,
    98,32,
    99,32,
    100,33,
    101,33,
    102,33,
    103,34,
    104,34,
    105,35,
    106,35,
    107,36,
    108,37,
    109,37,
    port_fake,38,
};
#endif

/********** Toa I *************/
#if IP_OFFSET_ESP == IP_OFFSET_I
// #define all_model_total_number_of_block 12 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 4
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 43
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 27
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,12,
    3,13,
    4,2,
    5,2,
    6,2,
    7,2,
    8,3,
    9,3,
    10,3,
    11,3,
    12,4,
    13,4,
    14,4,
    15,4,
    16,5,
    17,5,
    18,5,
    19,5,
    20,6,
    21,6,
    22,6,
    23,6,
    24,7,
    25,7,
    26,7,
    27,7,
    28,8,
    29,8,
    30,8,
    31,8,
    32,9,
    33,9,
    34,9,
    35,9,
    36,10,
    37,10,
    38,10,
    39,10,
    40,11,
    41,11,
    42,11,
    43,11,
    port_fake,12,
};
#endif

/********** Toa J *************/
#if IP_OFFSET_ESP == IP_OFFSET_J
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 12
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 137
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 30
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,2,
    6,3,
    7,3,
    8,3,
    9,3,
    10,3,
    11,4,
    12,4,
    13,4,
    14,4,
    15,5,
    16,5,
    17,5,
    18,5,
    19,5,
    20,6,
    21,6,
    22,6,
    23,6,
    24,7,
    25,7,
    26,7,
    27,7,
    28,7,
    29,8,
    30,8,
    31,8,
    32,8,
    33,9,
    34,9,
    35,9,
    36,9,
    37,9,
    38,10,
    39,10,
    40,10,
    41,10,
    42,11,
    43,11,
    44,11,
    45,11,
    46,11,
    47,12,
    48,12,
    49,12,
    50,12,
    51,13,
    52,13,
    53,13,
    54,13,
    55,13,
    56,14,
    57,14,
    58,14,
    59,14,
    60,15,
    61,15,
    62,15,
    63,15,
    64,15,
    65,16,
    66,16,
    67,16,
    68,16,
    69,16,
    70,17,
    71,17,
    72,17,
    73,17,
    74,17,
    75,18,
    76,18,
    77,18,
    78,18,
    79,18,
    80,19,
    81,19,
    82,19,
    83,19,
    84,19,
    85,20,
    86,21,
    87,21,
    88,21,
    89,22,
    90,22,
    91,22,
    92,22,
    93,23,
    94,23,
    95,23,
    96,24,
    97,24,
    98,24,
    99,24,
    100,24,
    101,25,
    102,25,
    103,26,
    104,26,
    105,26,
    106,26,
    107,27,
    108,27,
    109,27,
    110,28,
    111,28,
    112,28,
    113,28,
    114,29,
    115,29,
    116,30,
    117,30,
    118,30,
    119,31,
    120,31,
    121,31,
    122,32,
    123,32,
    124,32,
    125,32,
    126,33,
    127,33,
    128,34,
    129,34,
    130,34,
    131,35,
    132,35,
    133,35,
    134,36,
    135,37,
    136,37,
    137,37,
    port_fake,38,
};
#endif

/********** Toa K *************/
#if IP_OFFSET_ESP == IP_OFFSET_K
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 11
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 124
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 33
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,3,
    6,3,
    7,3,
    8,3,
    9,4,
    10,4,
    11,4,
    12,5,
    13,5,
    14,5,
    15,5,
    16,6,
    17,6,
    18,6,
    19,7,
    20,7,
    21,7,
    22,7,
    23,8,
    24,8,
    25,8,
    26,9,
    27,9,
    28,9,
    29,9,
    30,10,
    31,10,
    32,10,
    33,11,
    34,11,
    35,11,
    36,11,
    37,12,
    38,12,
    39,12,
    40,13,
    41,13,
    42,13,
    43,13,
    44,14,
    45,14,
    46,14,
    47,15,
    48,15,
    49,15,
    50,15,
    51,16,
    52,16,
    53,16,
    54,17,
    55,17,
    56,17,
    57,17,
    58,18,
    59,18,
    60,18,
    61,19,
    62,19,
    63,19,
    64,19,
    65,20,
    66,21,
    67,21,
    68,22,
    69,22,
    70,22,
    71,23,
    72,23,
    73,23,
    74,23,
    75,24,
    76,24,
    77,24,
    78,25,
    79,25,
    80,25,
    81,25,
    82,26,
    83,26,
    84,26,
    85,27,
    86,27,
    87,27,
    88,27,
    89,28,
    90,28,
    91,28,
    92,29,
    93,29,
    94,29,
    95,29,
    96,30,
    97,30,
    98,30,
    99,31,
    100,31,
    101,31,
    102,31,
    103,32,
    104,32,
    105,32,
    106,33,
    107,33,
    108,33,
    109,33,
    110,34,
    111,34,
    112,34,
    113,35,
    114,35,
    115,35,
    116,35,
    117,37,
    118,37,
    119,37,
    120,37,
    121,37,
    122,37,
    123,37,
    124,37,
    port_fake,38,
};
#endif

/********** Toa L *************/
#if IP_OFFSET_ESP == IP_OFFSET_L
// #define all_model_total_number_of_block 38 //So tang thuc te chi la 7, tang 8 chi de danh lua ESP
//Sua hieu ung bo sang tang cuoi --> cho so bolock len = max
#define all_model_total_number_of_block all_model_total_number_of_block_max

#define this_esp_number_of_tlc 12
//number excel - 1 (count from 0)
#define this_esp_port_start 0
#define this_esp_port_end 136
//Chinh rieng tung bo
#define roll_time_dem_sang 5
#define roll_time_dem_tat 36
// #define roll_time_giu_sang_toan_bo 100
const int this_esp_data[all_model_total_number_of_port][2] = {
    0,stt_tang_thang,
    1,1,
    2,2,
    3,2,
    4,2,
    5,2,
    6,3,
    7,3,
    8,3,
    9,3,
    10,4,
    11,4,
    12,4,
    13,4,
    14,5,
    15,5,
    16,5,
    17,5,
    18,6,
    19,6,
    20,6,
    21,6,
    22,7,
    23,7,
    24,7,
    25,7,
    26,8,
    27,8,
    28,8,
    29,8,
    30,9,
    31,9,
    32,9,
    33,9,
    34,10,
    35,10,
    36,10,
    37,10,
    38,11,
    39,11,
    40,11,
    41,11,
    42,12,
    43,12,
    44,12,
    45,12,
    46,13,
    47,13,
    48,13,
    49,13,
    50,14,
    51,14,
    52,14,
    53,14,
    54,15,
    55,15,
    56,15,
    57,15,
    58,16,
    59,16,
    60,16,
    61,16,
    62,16,
    63,17,
    64,17,
    65,17,
    66,17,
    67,18,
    68,18,
    69,18,
    70,18,
    71,18,
    72,19,
    73,19,
    74,19,
    75,19,
    76,20,
    77,21,
    78,21,
    79,21,
    80,22,
    81,22,
    82,22,
    83,22,
    84,23,
    85,23,
    86,23,
    87,24,
    88,24,
    89,24,
    90,24,
    91,24,
    92,25,
    93,25,
    94,25,
    95,26,
    96,26,
    97,26,
    98,26,
    99,26,
    100,27,
    101,27,
    102,27,
    103,28,
    104,28,
    105,28,
    106,28,
    107,29,
    108,29,
    109,29,
    110,29,
    111,30,
    112,30,
    113,30,
    114,30,
    115,31,
    116,31,
    117,31,
    118,32,
    119,32,
    120,32,
    121,32,
    122,33,
    123,33,
    124,33,
    125,34,
    126,34,
    127,34,
    128,34,
    129,34,
    130,35,
    131,35,
    132,35,
    133,36,
    134,37,
    135,37,
    136,37,
    port_fake,38,
};
#endif

//Generate number from 0-144.

const int randomBuffer[all_model_total_number_of_port] = {
  1,
  92,
  76,
  36,
  129,
  71,
  70,
  30,
  35,
  142,
  20,
  77,
  132,
  112,
  59,
  34,
  89,
  120,
  13,
  46,
  130,
  101,
  87,
  4,
  61,
  100,
  3,
  57,
  2,
  67,
  117,
  26,
  90,
  68,
  62,
  37,
  39,
  141,
  17,
  137,
  28,
  131,
  109,
  65,
  118,
  93,
  50,
  133,
  38,
  54,
  45,
  42,
  73,
  49,
  75,
  55,
  143,
  123,
  86,
  91,
  43,
  63,
  11,
  82,
  116,
  119,
  99,
  64,
  27,
  60,
  32,
  25,
  81,
  110,
  24,
  96,
  41,
  124,
  53,
  33,
  105,
  134,
  80,
  102,
  139,
  114,
  16,
  19,
  128,
  31,
  126,
  12,
  51,
  97,
  125,
  66,
  107,
  115,
  84,
  69,
  85,
  22,
  88,
  29,
  10,
  15,
  58,
  94,
  113,
  78,
  79,
  7,
  21,
  83,
  127,
  74,
  136,
  95,
  135,
  8,
  14,
  9,
  103,
  44,
  48,
  104,
  111,
  108,
  72,
  18,
  138,
  52,
  106,
  6,
  23,
  98,
  140,
  40,
  5,
  121,
  56,
  47,
  122,
  0,
};
//fit in the old code format
const int BOARD_COUNT = this_esp_number_of_tlc;
const int REGISTER_COUNT = BOARD_COUNT * 1;  // 1 board có 1 chip
const int PORT_COUNT = REGISTER_COUNT * 12;


#ifdef __cplusplus
}
#endif

#endif  // config_h