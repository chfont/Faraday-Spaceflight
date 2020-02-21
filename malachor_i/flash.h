
#ifndef flash_h
#define flash_h
#include <SPIFlash.h>

#define SHORT_SIZE sizeof(int16_t)
#define FLOAT_SIZE sizeof(float)
unsigned int writeShortArrToFlash(SPIFlash flash, int16_t* data, unsigned int numItems )
{
  unsigned int written = 0;
  for(unsigned int i = 0; i < numItems; i++){
    flash.writeShort(flash.getAddress(SHORT_SIZE), data[i]);
    written += SHORT_SIZE;
  }
  return written;
}

unsigned int writeFloatArrToFlash(SPIFlash flash, float* data, unsigned int numItems){
  unsigned int written = 0;
  for(unsigned int i = 0; i < numItems; i++){
    flash.writeFloat(flash.getAddress(FLOAT_SIZE), data[i]);
    written += FLOAT_SIZE;
  }
  return written;
}

unsigned int writeShortToFlash(SPIFlash flash, int16_t data)
{
  flash.writeShort(flash.getAddress(SHORT_SIZE), data);
  return SHORT_SIZE;
}

unsigned int writeFloatToFlash(SPIFlash flash, float data){
  flash.writeFloat(flash.getAddress(FLOAT_SIZE), data);
  return FLOAT_SIZE;
}

//Todo: Address guards?
bool readShortArrFromFlash(SPIFlash flash, uint32_t start_addr, short* data, unsigned int numItems){
  for(unsigned int i = 0; i < numItems; i++){
    *(data+i) = flash.readShort(start_addr+i);
  }
  return 1;
}

bool readFloatFromFlash(SPIFlash flash, uint32_t addr, float* data){
  *data = flash.readFloat(addr);
}
#endif
