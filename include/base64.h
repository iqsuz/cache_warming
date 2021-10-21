/**
 * @file 	base64.h
 * @author	Ali
 * @version ---
 * @date  	10/17/2021
 * @brief	This file contains all function prototypes, definitions,
 * 			and related includes for base64 library.
 * 
 * 
 */


/* Define to prevent recursive inclusion.*/
#ifndef _BASE64_H_
#define _BASE64_H_

/* Includes*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes.*/
uint8_t base64_decode(const char *input, int input_len, char *output);
int8_t base64_decode_hash(const char *key);
char *base64_malloc(char *input, int input_len, int *output_len);
uint8_t *base64_strtohex(char *input, int input_len, int *decoded_hex_len);

#endif
