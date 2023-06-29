#include <stdint.h>
#include "message_queue.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

   
/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
 //VD: 3 10:  1 2 3 4 5 6 7 8 9 10
 //           1 2 3 4 5 6 7 8 9 10
 //           1 2 3 4 5 6 7 8 9 10
static uint8_t queue_data[MAXIMUM_NUMBER_OF_ELEMENT][MAXIMUM_BYTES_DATA_PER_ELEMENT];

static uint8_t number_of_element = 0;

static uint8_t push = 0;
static uint8_t pop = 0;

static uint16_t push_index = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
void message_queue_init()
{
    number_of_element = 0;
    push = 0;
    pop = 0;
    push_index = 0;
}

bool message_queue_is_empty()
{
    return (number_of_element == 0);
}

void message_queue_push_char(uint8_t in_char)
{
    queue_data[push][push_index] = in_char;
    push_index++;
    queue_data[push][push_index] = 0;
}

bool message_queue_push_new_element()
{
    bool return_val = 0;
    uint8_t last_push = push;
    
    push++;
    if(push == MAXIMUM_NUMBER_OF_ELEMENT) push = 0;
    
    if(push == pop)
    {
        push = last_push;
    }
    else
    {
        number_of_element++;
        push_index = 0;
        return_val = 1;
    }
    
    return return_val;
}

void message_queue_peek_head_element(uint8_t ** out_element)
{
    *(out_element) = &queue_data[pop][0];
}

void message_queue_remove_head_element()
{
    pop++;
    if(pop == MAXIMUM_NUMBER_OF_ELEMENT) pop = 0;
    number_of_element--;
}
