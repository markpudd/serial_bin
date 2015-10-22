/*
*   Bitstream with stuffing
*
*/

#ifndef BITSTREAM_H
#define BITSTREAM_H

long calcStuffBufferBitSize(unsigned char * inputBuffer, int length);
void bitstuffFrame(unsigned char * inputBuffer, int length, unsigned char * outputBuffer);
long unbitstuffFrame(unsigned char * inputBuffer, int length, unsigned char * outputBuffer);

#endif 
