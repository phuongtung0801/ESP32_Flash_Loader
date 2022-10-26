#include "sender_state_machine.h"
HardwareSerial SerialPort(2);  //if using UART2
frame_t send_frame = {0};
static uint8_t response_buffer[4];


void state_machine()
{
    switch (sender_state)
    {
    case WAIT:
        static uint32_t counter = 0;
        if(SerialPort.available())
        {
            // Serial.println("Dm");
            uint8_t temp_buff = SerialPort.read();
            Serial.println(temp_buff);
            if (temp_buff == READY_TO_RECEIVE)
            {
                Serial.println("Fuck");
                sender_state = WRITE_COMMAND;
            }
            else SerialPort.println("Nguyen Lam Tuong Vy bu cu");
        }
        // if (digitalRead(CMD_IO) == HIGH)
        // {
            
        //     // Serial.println("Hello");
        //         uart_send();
        //         delay(100);
                
        //     // Serial.printf("Counter is %d\n", counter);    
        // }
        break;
    case WRITE_COMMAND:
        send_frame.start_of_frame = START_OF_FRAME;
        send_frame.length_high = 1;
        send_frame.length_low = 0;
        send_frame.cmd = WRITE_COMMAND;
         for (size_t i = 0; i < 256; i++)
        {
        send_frame.payload[i] = 0;
        }
        send_frame.crc = 4;
        send_frame.sequence_number = 0;
        send_frame.end_of_frame = END_OF_FRAME;
        uart_send();
        sender_state = WAIT;
        break;
    case SEND_FRAME:
        break;
    
    default:
        break;
    }
}

void uart_send()
{
    SerialPort.write(send_frame.start_of_frame);
    SerialPort.write(send_frame.length_high);
    SerialPort.write(send_frame.length_low);
    SerialPort.write(send_frame.cmd);
    for (size_t i = 0; i < 256; i++)
    {
        SerialPort.write(send_frame.payload[i]);
    }
    SerialPort.write(send_frame.crc);
    uint8_t high_byte = (send_frame.sequence_number & (uint16_t)0xFF00) >> 8;
    uint8_t low_byte = send_frame.sequence_number & (uint16_t)0x00FF;
    SerialPort.write(high_byte);
    SerialPort.write(low_byte);
    // SerialPort.write(send_frame.sequence_number);
    SerialPort.write(send_frame.end_of_frame);
    SerialPort.flush();
}