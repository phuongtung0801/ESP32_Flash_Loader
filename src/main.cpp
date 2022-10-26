#include <Arduino.h>
#include "sender_state_machine.h"



void setup() {
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  Serial.begin(115200);
  pinMode(CMD_IO, INPUT);
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

  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  // Serial.println(FLASH_DATA[13248]);
  
 for (size_t i = 0; i < 256; i++)
 {
  send_frame.payload[i] = FLASH_DATA[i];
 }
 


  // put your setup code here, to run once:
  
}

void loop() {
  // 

  // if (digitalRead(CMD_IO) == HIGH)
  // {
    
  //   Serial.println("Hello");
  // }

  // Serial.printf("Start Transmit\n");
  // delay(2000);
  // Serial.printf("Begin Transmit\n");
  state_machine();
  // SerialPort.write(send_frame.start_of_frame);
  // SerialPort.write(send_frame.length_high);
  // SerialPort.write(send_frame.length_low);
  // SerialPort.write(send_frame.cmd);
  // for (size_t i = 0; i < 256; i++)
  // {
  //   // Serial.println(FLASH_DATA[i]);
  //   SerialPort.write(send_frame.payload[i]);
  // }
  // SerialPort.write(send_frame.crc);
  // uint8_t high_byte = (send_frame.sequence_number & (uint16_t)0xFF00) >> 8;
  // uint8_t low_byte = send_frame.sequence_number & (uint16_t)0x00FF;
  // SerialPort.write(high_byte);
  // SerialPort.write(low_byte);
  // // SerialPort.write(send_frame.sequence_number);
  // SerialPort.write(send_frame.end_of_frame);
}