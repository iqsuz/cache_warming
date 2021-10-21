#include "base64.h"

/**
 * @brief Convert char digit to integer.
 * @param ch: Input char digit.
 * @return Returns integer value of char digit. If fails return 0xFF
*/
static uint8_t _base64_chartohex(char ch)
{
    if(ch >= '0' && ch <= '9') return (ch - '0');   //0-9(char) --> 0-9 (int)
    if(ch >= 'A' && ch <= 'F') return (ch - 55);    //A-F --> 10-15 
    if(ch >= 'a' && ch <= 'f') return (ch - 87);    //a-f --> 10-15
    return 0xFF; //Conversion fail.
}

/**
 * @brief Decodes base64 encoded message.
 * @param input: Initial address of base64 encoded message.
 * @param input_let: Length of input text.
 * @param output: Allocated address for output message.
 * @return 0 if successful, -1 if fails.
*/
uint8_t base64_decode(const char *input, int input_len, char *output)
{
    uint8_t sextets[4];
    uint32_t three_bytes = 0x00000000;

    if(input_len % 4 != 0){
        printf("Input string is not multiple of 4!\n");
        return -1;
    }

    for(int i = 0; i < input_len; i += 4){
        sextets[0] = input[i] != '=' ? base64_decode_hash((input + i)) : 0;
        sextets[1] = input[i] != '=' ? base64_decode_hash((input + i + 1)) : 0;
        sextets[2] = input[i] != '=' ? base64_decode_hash((input + i + 2)) : 0;
        sextets[3] = input[i] != '=' ? base64_decode_hash((input + i + 3)) : 0;

        three_bytes |= sextets[0]; three_bytes <<= 6;
        three_bytes |= sextets[1]; three_bytes <<= 6;
        three_bytes |= sextets[2]; three_bytes <<= 6;
        three_bytes |= sextets[3];

        *(output++) = (char)(three_bytes >> 16);
        *(output++) = (char)(three_bytes >> 8);
        *(output++) = (char)three_bytes;

        three_bytes = 0x00000000;  
    }

    return 0;
}

/**
 * @brief This function gets decoded base64 char as an input and
 *convert it to base64 table correspond integer. 
 * @param key: Address of decoded char.
 * @return Integer value of decoded data in base64 table. -1 if fails.
*/
int8_t base64_decode_hash(const char *key)
{
    if(*key >= 65 && *key <= 90) return *key - 65;      //If key is A-Z, then return 0-25.
    if(*key >= 97 && *key <= 122) return *key - 71;     //If key is a-z, then return 26-51.
    if(*key >= 48 && *key <= 57) return *key + 4;       //If key is 0-9, then return 52-61.
    if(*key == 43) return 62;                           //If key is +, return 62.
    if(*key == 47) return 63;                           //If key is /, return 63.

    return -1;  //return if not in range.
}

/**
 * @brief Allocate memory for decoded message.
 * @param input: Initial address of base64 encoded message.
 * @param input_let: Length of input text.
 * @param output_len: Address to which length of output will be stored.
 * @return allocated memory address. If fails return exit(-1).
*/
char *base64_malloc(char *input, int input_len, int *output_len)
{
    char *ret_val;
    *output_len = input_len / 4 * 3;

    //Is there any padding? If so decrement output_len.
    if(input[input_len - 1] == '=') (*output_len)--;
    if(input[input_len - 2] == '=') (*output_len)--;

    ret_val = (char *)malloc(sizeof(char) * (*output_len));

    if(ret_val == NULL){
        printf("base64_malloc couldn't allocate enough memory!\n");
        exit(-1);
    }

    return ret_val;
}

/**
 * @brief Convert decoded base64 string to Hex equivalent.
 * @param input: Address of base64 decoded string.
 * @param input_let: Length of decoded string.
 * @param decoded_hex_len: Address to which length of decoded hex will be stored.
 * @return Address of hex array. If fails return NULL.
*/
uint8_t *base64_strtohex(char *input, int input_len, int *decoded_hex_len)
{
    *decoded_hex_len = input_len / 2;
    uint8_t *temp = (uint8_t *)malloc(sizeof(uint8_t) * (*(decoded_hex_len)));
    uint8_t *ret_hex = temp;    //Store initial address since temp will be iterated through function.
    uint8_t second_digit, first_digit; 

    if(input_len % 2){
        printf("Missing hex digit!\n");
        return NULL;
    }

    for(int i = 0; i < input_len; i += 2){
        second_digit = _base64_chartohex(input[i]);
        first_digit = _base64_chartohex(input[i+1]);

        *(temp++) = (second_digit << 4) + first_digit;
    }

    return ret_hex;
}