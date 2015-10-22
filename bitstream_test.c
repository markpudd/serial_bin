#include "bitstream.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int testNoFiveBits() {
    unsigned char testS[] = {0x00,0x00};
    long bits = calcStuffBufferBitSize(testS,2);
    if(bits != 16) {
        printf("testNoFiveBits -- Failed expected 16 but got %ld\n",bits);
        return 1;
    }
    printf("testNoFiveBits -- Passed\n");
    return 0;
}

int testFiveBits() {
    unsigned char  testS[] = {0x00,0xFF};
    long bits = calcStuffBufferBitSize(testS,2);
    if(bits != 17) {
        printf("testFiveBits -- Failed 17 but got %ld\n",bits);
        return 1;
    }
    printf("testFiveBits -- Passed\n");
    return 0;
}

int testFiveBitsStart() {
    unsigned char  testS[] = {0x1F,0x00};
    long bits = calcStuffBufferBitSize(testS,2);
    if(bits != 17) {
        printf("testFiveBitsStart -- Failed 17 but got %ld\n",bits);
        return 1;
    }
    printf("testFiveBitsStart -- Passed\n");
    return 0;
}

int testFiveBitsMid() {
    unsigned char  testS[] = {0x01,0xF0};
    long bits = calcStuffBufferBitSize(testS,2);
    if(bits != 17) {
        printf("testFiveBitsMid -- Failed 17 but got %ld\n",bits);
        return 1;
    }
    printf("testFiveBitsMid -- Passed\n");
    return 0;
}

int testFiveBitsEnd() {
    unsigned char  testS[] = {0x00,0xF8};
    long bits = calcStuffBufferBitSize(testS,2);
    if(bits != 17) {
        printf("testFiveBitsEnd -- Failed 17 but got %ld\n",bits);
        return 1;
    }
    printf("testFiveBitsEnd -- Passed\n");
    return 0;
}

int testStuffAndUnstuff() {
    unsigned char test[256];
    unsigned char * b1;
    unsigned char * b2;
    int fail = 0;
    for(int i=0;i<255;i++) {
        test[i]=i;
    }
    long bits = calcStuffBufferBitSize(test,256);
    long bytes = (bits+7)/8;
    b1 = (unsigned char *) malloc(bytes);
    b2 = (unsigned char *) malloc(bytes);
    bitstuffFrame(test,256, b1);
    long unret = unbitstuffFrame(b1, bytes, b2);
    if(unret) {
        printf("calcStuffBufferBitSize -- Unstuff issue at %ld\n",unret);
        fail=-1;
    } else {
        for(int i=0;i<255;i++) {
           if(test[i]!=b2[i]) {
               fail =i;
               printf("calcStuffBufferBitSize -- Failed matching at t %d\n",i);
               break;
           }
        }
    }
    
    
    free(b1);
    free(b2);
    if(!fail)
        printf("calcStuffBufferBitSize -- Passed\n");
    
    return fail;
}


int main() {
  int ret = 0;
  ret = ret | testNoFiveBits();
  ret = ret | testFiveBits();
  ret = ret | testFiveBitsStart();
  ret = ret | testFiveBitsMid();
  ret = ret | testFiveBitsEnd();
  ret = ret | testStuffAndUnstuff();
  return ret;
}