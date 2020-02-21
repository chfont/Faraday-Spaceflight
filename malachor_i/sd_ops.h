#ifndef sd_ops_h
#define sd_ops_h

#include<SD.h>


//TODO: Maybe use binary format over csv format, for optimized storage
enum Mode {
	   READ,
	   WRITE
};

File init_sd(String f, Mode m)
{
  if(m == READ){
    return SD.open(f,FILE_READ);
  } else {
    return SD.open(f, FILE_WRITE);
  }
}

//Dump short array into file, csv format
unsigned int dump_short_array_csv(File f, short* data, unsigned int num_items ){
  unsigned int written = 0;
  for(unsigned int i = 0; i < num_items; i++){
    written += f.write(data[i]);
    written += f.write(',');
  }
  //Return 1 on success
  if(written == 3*num_items){
    return 1;
  }
  return 0;
}

unsigned int dump_short_csv(File f, short data){
  unsigned int written = 0;
  written += f.write(data);
  written += f.write(',');
  return written ==3? 1 : 0;
}

unsigned int dump_float_array_csv(File f, float* data, unsigned int num_items){
  unsigned int written = 0;
  for(unsigned int i = 0; i < num_items; i++){
    written += f.write(data[i]);
    written += f.write(',');
  }
  return written == 5*num_items? 1: 0;
}

unsigned int dump_float_csv(File f, float data){
  unsigned int written = 0;
  written += f.write(data);
  written += f.write(',');
  return written == 5? 1 :0;
}


#endif 
