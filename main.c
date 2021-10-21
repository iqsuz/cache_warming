#include <stdio.h>
#include <string.h>
#include <err.h>
#include <msgpack.h>

#include "base64.h"

void print(char const* buf,size_t len);

int main(int argc, char *argv[])
{
	msgpack_sbuffer sbuf;
    msgpack_packer pk;
    msgpack_zone mempool;
    msgpack_object deserialized;

    uint8_t *decoded_hex_data;
    int decoded_str_len, decoded_hex_len;
    char *decoded_string;

    if(argc < 2){
        errx(-1, "No encoded data inputted!\n");
    }
    if(argc > 2){
        errx(-1, "To much arguments!\n");
    }
    
    decoded_string = base64_malloc(argv[1], strlen(argv[1]), &decoded_str_len);

    if(base64_decode(argv[1], strlen(argv[1]), decoded_string) == -1){
        printf("base64_decode failed!\n");
        return -1;
    }
        
    decoded_hex_data = base64_strtohex(decoded_string, decoded_str_len, &decoded_hex_len);
    if(decoded_hex_data == NULL){
        printf("base64_strtohex failed!\n");
        return -1;
    }

    sbuf.data = (char *)decoded_hex_data;
    sbuf.size = decoded_hex_len;
    sbuf.alloc = decoded_hex_len;

    //msgpack_sbuffer_init(&sbuf); ****Never use this function if you have your own data.
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_zone_init(&mempool, decoded_hex_len);
    msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);
    msgpack_object_print(stdout, deserialized);
    puts("");
}