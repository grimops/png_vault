#ifndef _STR_BIN_H_
#define _STR_BIN_H_
#include <stddef.h>

void str_to_bin(char *file_str, size_t size_of_file, unsigned char *bin_arr);
void bin_to_str(unsigned char *bin_arr, size_t size_of_bin_arr, char *file_str);
void int64_to_bin(size_t integer_64, unsigned char *bin_arr);
void bin_to_int64(size_t *integer_64, unsigned char *bin_arr);

#endif
