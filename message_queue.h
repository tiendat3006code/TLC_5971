#ifndef message_queue_h
#define message_queue_h

#include <stdint.h>
#include <stdbool.h>
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAXIMUM_NUMBER_OF_ELEMENT           40
#define MAXIMUM_BYTES_DATA_PER_ELEMENT      300

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
* queue init, reset all variable in queue
*/
void message_queue_init();

/*!
* check if queue is empty
* return 1 if queue is empty
* return 0 if queue is not empty
*/
bool message_queue_is_empty();

/*!
* push single char to current element
* param[1] input char
*/
void message_queue_push_char(uint8_t in_char);

/*!
* push data to current element completed
* start push data of new element
* return 0 when queue is full
* return 1 if success
*/
bool message_queue_push_new_element();

/*!
* get data of head element
* param[1] output pointer to data of head element
*/
void message_queue_peek_head_element(uint8_t ** out_element);

/*!
* remove head element after peek
*/
void message_queue_remove_head_element();

#ifdef __cplusplus
}
#endif

#endif // myqueue_h
