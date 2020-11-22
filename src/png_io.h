#ifndef _PNG_IO_H_
#define _PNG_IO_H_

void read_png_file(char*);
void write_png_file(char*);
void process_file(void);
void write_steg(unsigned char *bin_arr, size_t size_of_bin_arr, char channel);
void read_steg(unsigned char **bin_arr, size_t *size_of_bin_arr, char channel);

#endif
