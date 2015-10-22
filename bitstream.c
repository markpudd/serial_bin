/*
*   Bitstream with stuffing
*
*/

#include "bitstream.h"

long calcStuffBufferBitSize(unsigned char * inputBuffer, int length) {
    long numberOfBits = 0;
    int noOfConOnes =0;
    for(int i=0;i<length;i++) {
        for(int b=0;b<8;b++) {
            if( (inputBuffer[i]  & (0x80>>b)) ) {
                noOfConOnes++;
             } else {
                noOfConOnes=0;
            }
            if(noOfConOnes == 5) {
                numberOfBits++;
                noOfConOnes=0;
            }
            numberOfBits++;
        }
    }
    return numberOfBits;
}


void bitstuffFrame(unsigned char * inputBuffer, int length, unsigned char * outputBuffer) {
    long numberOfBits = 0;    
    int noOfConOnes =0;
    for(int i=0;i<length;i++) {
        for(int b=0;b<8;b++) {
            if((numberOfBits & 0x07)==0)
                outputBuffer[numberOfBits>>3]=0;
            unsigned char bit = inputBuffer[i]  & (0x01<<b);
            if( bit ) {
                noOfConOnes++;
            } else {
                noOfConOnes=0;
            }
            if(noOfConOnes == 5) {
                // zeroed
                numberOfBits++;
                if((numberOfBits & 0x07)==0)
                    outputBuffer[numberOfBits>>3]=0;
                noOfConOnes=0;
            }
            outputBuffer[numberOfBits>>3] = inputBuffer[i] | bit;
            numberOfBits++;
        }
    }    
}

long unbitstuffFrame(unsigned char * inputBuffer, int length, unsigned char * outputBuffer) {
    long numberOfBits = 0;    
    int noOfConOnes =0;
    for(int i=0;i<length;i++) {
         for(int b=0;b<8;b++) {
             if((numberOfBits & 0x07)==0)
                 outputBuffer[numberOfBits>>3]=0;
             unsigned char bit = inputBuffer[i]  & (0x01<<b);
             if( bit ) {
                 noOfConOnes++;
             } else {
                 noOfConOnes=0;
             }
             if(noOfConOnes == 5) {
                 // check bit is zero then ignore
                 if(bit)
                     return numberOfBits;
                 noOfConOnes=0;
             } else { 
                outputBuffer[numberOfBits>>3] = inputBuffer[i] | bit;
                numberOfBits++;
             }

         }
     }
     return 0;
}