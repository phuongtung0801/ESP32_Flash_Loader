#include <Arduino.h>
#include <HardwareSerial.h>
#include "flash.h"
#include "fw_upload_protocol.h"
HardwareSerial SerialPort(2);  //if using UART2
frame_t send_frame = {0};


void setup() {
  Serial.begin(115200);
  send_frame.start_of_frame = START_OF_FRAME;
  send_frame.length_high = 1;
  send_frame.length_low = 0;
  send_frame.cmd = 3;
  send_frame.crc = 4;
  send_frame.sequence_number = 300;
  send_frame.end_of_frame = END_OF_FRAME;

  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  Serial.println(FLASH_DATA[13248]);
  
 for (size_t i = 0; i < 256; i++)
 {
  send_frame.payload[i] = FLASH_DATA[i];
 }
 

  // put your setup code here, to run once:
  
}

void loop() {
  delay(2000);
  Serial.printf("Start Transmit\n");
  delay(2000);
  Serial.printf("Begin Transmit\n");
  
  SerialPort.write(send_frame.start_of_frame);
  SerialPort.write(send_frame.length_high);
  SerialPort.write(send_frame.length_low);
  SerialPort.write(send_frame.cmd);
  for (size_t i = 0; i < 256; i++)
  {
    // Serial.println(FLASH_DATA[i]);
    SerialPort.write(send_frame.payload[i]);
  }
  SerialPort.write(send_frame.crc);
  uint8_t high_byte = (send_frame.sequence_number & (uint16_t)0xFF00) >> 8;
  uint8_t low_byte = send_frame.sequence_number & (uint16_t)0x00FF;
  SerialPort.write(high_byte);
  SerialPort.write(low_byte);
  // SerialPort.write(send_frame.sequence_number);
  SerialPort.write(send_frame.end_of_frame);
  
  // static float test[4];
  // static uint32_t i;
  // delay(2000);
  // Serial.printf("Hello %d, size of test: %d\n", FLASH_DATA[i], sizeof(FLASH_DATA));
  // i++;
  
  // put your main code here, to run repeatedly:
}