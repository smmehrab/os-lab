#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/dev/usart.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
* first argument define the type of string to kprintf and kscanf,
* %c for charater
* %s for string,
* %d for integer
* %x hexadecimal
* %f for floating point number
*/

/***************************************************************
function definitions
***************************************************************/

// Indirect Helpers
void copyMemoryElements(void *destination, void *source, size_t n);
uint8_t* copyString(uint8_t* destination, const uint8_t* source);
uint8_t* concatString(uint8_t* str1, const uint8_t* str2);
void intToString(uint8_t* str, int n);
void hexToString(uint8_t* str, int n);
int power(int a, int b);
void floatToString(uint8_t* str, float n);
// Direct Helpers
void handleCharacter(uint8_t* source, uint8_t* destination, char ioType);
void handleString(uint8_t* source, uint8_t* destination, char ioType);
void handleInteger(uint8_t* source, uint8_t* destination, char ioType);
void handleHexadecimal(uint8_t* source, uint8_t* destination, char ioType);
void handleFloat(uint8_t* source, uint8_t* destination, char ioType);
// Main
void kprintf(uint8_t *format, uint8_t* outvar, uint8_t *endString);
void kscanf(uint8_t *format, uint8_t* invar);

/***************************************************************
function implementations
***************************************************************/

void copyMemoryElements(void *destination, void *source, size_t n) {
    char *cSource = (char *)source;
    char *cDestination = (char *)destination;     
    for (int i=0; i<n; i++)
        cDestination[i] = cSource[i];
}

uint8_t* copyString(uint8_t* destination, const uint8_t* source) {
    if (destination != NULL) {
        uint8_t *p = destination;
        while (*source != '\0') {
            *p = *source;
            p++;
            source++;
        } 
        *p = '\0';
    }
    return destination;
}

uint8_t* concatString(uint8_t* str1, const uint8_t* str2) {
  uint8_t* str = str1;
  if(str1 && str2) {
    while(*str1) {
      str1++;
    }
    while(*str2) {
      *str1++ = *str2++;
    }
    *str1 = '\0';
  }
  return str;
}

void intToString(uint8_t* str, int n) {
    int signBit = 0;
    if (n < 0) {
        n *= -1;
        str[0] = '-';
        signBit = 1;
    }
    
    int index = 0;
    uint8_t temp[10000];
    do {
        temp[index] = '0' + (n%10);
        n /= 10;
        index++;
    } while(n);

    int digitCount = index;
    index -= 1;
    for (int i = index; i >= 0; i--) {
        str[index - i + signBit] = temp[i];
    }
    str[digitCount + signBit] = 0;
}

void hexToString(uint8_t* str, int n) {
    char digits[] = "0123456789ABCDEF";
    int signBit = 2;
    
    if (n < 0) {
        n *= -1;
        copyString(str, (uint8_t*)"-0x");
        signBit += 1;
    } 
    else {
        copyString(str, (uint8_t*)"0x");
    }

    int index = 0;
    uint8_t temp[10000];
    do {
        temp[index] = digits[n%16];
        n /= 16;
        index++;
    } while(n);

    int digitCount = index;
    index -= 1;
    for (int i = index; i >= 0; i--) {
        str[index - i + signBit] = temp[i];
    }
    str[digitCount + signBit] = 0;
}

int power(int a, int b) {
    int r=1;
    for (int i = b; i>0; i--) {
        r *= a;
    }
    return r;
}

void floatToString(uint8_t* str, float n) {
    // integer part calculation
    intToString(str, (int)n);
    // fractional leading zero calculation
    uint8_t fractionalLeadingZeros[8] = {0};
    int fractionalLeadingZeroCount = 0;
    float fraction = n - (int)n;
    while (fractionalLeadingZeroCount<7) {
        float test = (fraction * 10.0);
        if(test < 0) {
            test = test * (-1);
        }
        if(test >= 1.00) {
            break;
        }
        fractionalLeadingZeros[fractionalLeadingZeroCount] = '0';
        fraction *= 10.0;
        fractionalLeadingZeroCount++;
    }
    // rest of fractional calculation
    uint8_t fractionalRest[10000];
    intToString(fractionalRest, abs((n - (int)n) * 1000000));
    // concat them all
    concatString(str, (uint8_t*)".");
    concatString(str, fractionalLeadingZeros);
    concatString(str, fractionalRest);
}

void handleCharacter(uint8_t* source, uint8_t* destination, char ioType) {
    if(ioType=='i') {
        // _USART_WRITE(USART2,(uint8_t*)"> kscanf(): [CHARACTER] \'");
        source[1] = '\0';
        // _USART_WRITE(USART2,(uint8_t*)source);
        // _USART_WRITE(USART2,(uint8_t*)"\'\n");
        *destination = source[0];
    }
    else if(ioType=='o') {
        // _USART_WRITE(USART2,(uint8_t*)"> kprintf(): [CHARACTER]\n");
        destination[0] = *source;
        destination[1] = 0;
    }
}

void handleString(uint8_t* source, uint8_t* destination, char ioType) {
    if(ioType=='i') {
        // _USART_WRITE(USART2,(uint8_t*)"> kscanf(): [STRING] \"");
        // _USART_WRITE(USART2,(uint8_t*)source);
        // _USART_WRITE(USART2,(uint8_t*)"\"\n");
        int i = 0;
        while(source[i]){
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0';
    }
    else if(ioType=='o') {
        // _USART_WRITE(USART2,(uint8_t*)"> kprintf(): [STRING]\n");
        copyString(destination, source);
    }
}

void handleInteger(uint8_t* source, uint8_t* destination, char ioType) {
    if(ioType=='i') {
        // _USART_WRITE(USART2,(uint8_t*)"> kscanf: [INTEGER] \n");

        int sign = 1;
        int number = 0;
        int index = 0;

        if(source[0] == '-'){
            sign = -1;
            index++;
        }
     
        while(source[index] != '\0') {
            if(source[index] >= '0' && source[index] <= '9') {
                number = (number*10) + (source[index] - '0');
            } 
            else {
                break;
            }
            index++;
        }

        number = number * sign;
        uint32_t *p = (uint32_t*)destination;
        (*p) = number;
    }
    else if(ioType=='o') {
        // _USART_WRITE(USART2,(uint8_t*)"> kprintf(): [INTEGER]\n");
        int temp;
        copyMemoryElements((char*)&temp, source, sizeof(int));
        intToString(destination, temp);
    }
}

void handleHexadecimal(uint8_t* source, uint8_t* destination, char ioType) {
    if(ioType=='i') {
        // _USART_WRITE(USART2,(uint8_t*)"> kscanf(): [HEXADECIMAL] \n");
            
        int sign = 1;
        int number = 0;
        int index = 0;

        if(source[0] == '-') {
            sign = -1;
            index++;
        }
     
        while(source[index] != '\0') {
            if(source[index] >= '0' && source[index] <= '9') {
                number = (number*16) + (source[index] - '0');
            }
            else if(source[index]>='A' && source[index]<='F') {
                number = (number*16) + (source[index] - 55);
            }
            else {
                break;
            }
            index++;
        }

        number = number * sign;
        uint32_t *p = (uint32_t*)destination;
        (*p) = number;
    }
    else if(ioType=='o') {
        // _USART_WRITE(USART2,(uint8_t*)"> kprintf(): [HEXADECIMAL]\n");
        int tempHex;
        copyMemoryElements((char*)&tempHex, source, sizeof(int));
        hexToString(destination, tempHex);
    }
}

void handleFloat(uint8_t* source, uint8_t* destination, char ioType) {
    if(ioType=='i') {
        // _USART_WRITE(USART2,(uint8_t*)"> kscanf(): [FLOAT] \n");
        int sign = 1;
        float number = 0.0;
        int index = 0;
        int radixFound = 0;
        int fractionalPartCount = 0;

        if(source[0] == '-') {
            sign = -1;
            index++;
        }   

        while(source[index] != '\0') {
            if((source[index] >= '0' && source[index] <= '9') && !radixFound) {
                number = (number*10) + (source[index] - '0');
            }
            else if((source[index] >= '0' && source[index] <= '9') && radixFound) {
                int nominator = source[index] - '0';
                int denominator = power(10, fractionalPartCount);
                number += ((nominator*1.0F)/denominator);
                fractionalPartCount++;
            }
            else if(source[index] == '.') {
                radixFound = 1;
                fractionalPartCount++;
            }
            else {
                break;
            }
            index++;
        }

        number = number * sign;
        float *p= (float*)destination;
        (*p) = number;
    }
    else if(ioType=='o') {
        // _USART_WRITE(USART2,(uint8_t*)"> kprintf(): [FLOAT]\n");
        float tempFloat;
        copyMemoryElements((char*)&tempFloat, source, sizeof(float));
        floatToString(destination, tempFloat);
    }
}

/***************************************************************
kprintf()
***************************************************************/

void kprintf(uint8_t *format, uint8_t* outvar, uint8_t *endString) {
    uint8_t output[10000];
    char c = format[1];
    switch (c) {
        case 'c':
            handleCharacter(outvar, output, 'o');
            break;
        case 's':
            handleString(outvar, output, 'o');
            break;
        case 'd':
            handleInteger(outvar, output, 'o');
            break;
        case 'x':
            handleHexadecimal(outvar, output, 'o');
            break;
        case 'f':
            handleFloat(outvar, output, 'o');
            break;
        default:
            break;
    }
    _USART_WRITE(USART2,(uint8_t*)"> ");
    _USART_WRITE(USART2,(uint8_t*)output);
    _USART_WRITE(USART2,(uint8_t*)endString);
}

/***************************************************************
kscanf()
***************************************************************/

void kscanf(uint8_t *format, uint8_t* invar) {
	uint8_t input[200];
	_USART_READ(USART2, input, 1000);
    char c = format[1];
    switch (c) {
        case 'c':
            handleCharacter(input, invar, 'i');
            break;
        case 's':
            handleString(input, invar, 'i');
            break;
        case 'd':
            handleInteger(input, invar, 'i');
            break;
        case 'x':
            handleHexadecimal(input, invar, 'i');
            break;
        case 'f':
            handleFloat(input, invar, 'i');
            break;
        default:
            break;
    }
}
