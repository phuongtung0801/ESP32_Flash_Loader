#ifndef _SENDER_H
#define _SENDER_H
#include <Arduino.h>
#include <HardwareSerial.h>
#include "flash.h"
#include "fw_upload_protocol.h"
#define CMD_IO    2
/*STATE LIST*/
#define WRITE_COMMAND               0x10
#define SEND_FRAME                  0xA0
#define WAIT                        0xA1

/*define error type*/
#define FRAME_MISMATCH              0xE1    //SOF or EOF mismatch
#define INVALID_LENGTH              0xE2    //LEN mismatch
#define INVALID_CRC                 0xE3    //Error in CRC checking frame
#define INVALID_SEQ                 0xE4    //Wrong sequence number
/*ACK MESSAGE*/
#define READY_TO_RECEIVE            0x0A
#define DATA_FRAME_OK               0x0B    //frame receive ok


extern HardwareSerial SerialPort;  //if using UART2
extern frame_t send_frame;

static uint8_t sender_state = WAIT;


void state_machine();
void uart_send();



#endif