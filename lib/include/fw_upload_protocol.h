#ifndef _FW_UPLOAD_PROTOCOL_H
#define _FW_UPLOAD_PROTOCOL_H
#include <stdio.h>
#include <stdint.h>



#define START_OF_FRAME                         0xAA //start of frame
#define END_OF_FRAME                         0xEF //end of frame
#define MAX_FIRMWARE_SIZE           13
#define WRITE_COMMAND               0x10
#define SEND_FRAME                  0x11

typedef enum 
{
    IDLE,
    CHECK_FRAME,
    PARSE_DATA_FRAME
} upload_firmware_state_t;

union SeqNumber
{
    uint16_t se_num;
    uint8_t high_byte;
    uint8_t low_byte;
};


typedef struct frame
{
    uint8_t start_of_frame;
    uint8_t length_high;
    uint8_t length_low;
    uint8_t cmd;
    uint8_t payload[256];
    uint8_t crc;
    uint8_t end_of_frame;
    uint16_t sequence_number;
} frame_t;


typedef struct firmware
{
    frame_t firmware_frame[MAX_FIRMWARE_SIZE];
    upload_firmware_state_t state;
    uint16_t frame_index;
} firmware_t;

/*GLOBAL VARIABLE*/
extern firmware_t firmware_instance;
extern frame_t temp_frame;
extern uint8_t uart_receive_buff[264];

/*LOCAL FUNCTION*/
_Bool crc_check(frame_t frame);
void EndOfDataFrameCallback(void);
void EndOfCmdFrameCallback(void);

/*EXPORTED FUNCTION*/


#endif