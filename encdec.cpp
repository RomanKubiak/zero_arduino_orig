#include "zero.h"

/** Symmetric with decodefrom7 - encodes bytes to 7-bit values, with an overflow byte 
* to store extra bits. Returns the number of total bytes written to the destination byte array*/
int encodeTo7(byte* srcBytes, byte* dstBytes, int srcCount){
  byte overflowByte = 0;
  byte overflowPos = 0;
  int dstPos = 0; //current writing position in dst array
  for(int srcPos = 0; srcPos < srcCount; srcPos++){

    //store msb in overflowByte, filling bits from left, shifting one extra to avoid msb
    overflowByte |= (srcBytes[srcPos] & 0x80) >> (overflowPos + 1); //store msb in overflow byte using next free position
    overflowPos++; //update overflow write position

    //passthrough the 7-bit truncated byte filling destination array from left
    dstBytes[dstPos] = srcBytes[srcPos] & ~0x80; //write the 7 allowed bits (zeroing the msb)
    dstPos++;//update destination write position

    //write overflow byte to stream when it's full or stream is ending
    if(overflowPos == 7 || srcPos == srcCount-1){ //byte full or stream ended
      dstBytes[dstPos] = overflowByte; //write the 7 allowed bits
      dstPos++; //update destination write position
      overflowByte = 0; //reset overflow byte
      overflowPos = 0; //start writing from beginning again
    }
  }
  return dstPos;
}

/** Should be symmetric with encodeTo7(). It populates the specified number of output bytes by reading
* 7 bits from each source byte and retrieving the extra bit from a 7-bit overflow byte which is written after 
* after each frame of 7 bytes (with the final frame potentially being less than 7 bytes). */
void decodeFrom7(byte* srcBytes, byte* dstBytes, int dstCount){
  int srcPos = 0;
  int partialFrameLength = dstCount % 7; //find out number of bytes stored in last frame (remainder from frames of 7)
  //int srcCount = ((dstCount / 7) * 8) + (partialFrameLength == 0 ? 0 : partialFrameLength + 1); //count of source bytes needed
  int overflowPos = 0; //keeps track of the next overflow bit to read from the overflow byte 
  for(int dstPos = 0; dstPos < dstCount; dstPos++){

    //get the 7 bits from the current byte, and reconstruct the final bit from the overflowbyte
    int frameLength = dstPos + partialFrameLength < dstCount ? 7 : partialFrameLength; //frame length (not including overflow byte)
    dstBytes[dstPos] = srcBytes[srcPos] | ((srcBytes[srcPos - overflowPos + frameLength] << (1 + overflowPos)) | 0x80); //read extra overflow bit from predictably offset overflow byte 
                                                                                                      //(srcPos - overflowPos is the start of the frame)
    overflowPos++; //update overflow read position
    srcPos++; //update src read position
    if(overflowPos == 7){
      overflowPos = 0;
      srcPos++; //update read position to skip the overflow byte
    }
  }
}
