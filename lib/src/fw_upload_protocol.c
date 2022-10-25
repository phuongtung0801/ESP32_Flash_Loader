#include "fw_upload_protocol.h"

firmware_t firmware_instance ={0};
frame_t temp_frame = {0};
uint8_t uart_receive_buff[264] = {0};


void firmware_upload_protocol()
{
    switch (firmware_instance.state)
    {
    case IDLE:
        if (temp_frame.start_of_frame)
        {
            /* code */
        }
        
        break;
    
    default:
        break;
    }
}
