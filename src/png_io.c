#ifndef PNG_DEBUG
	#define PNG_DEBUG 3
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <png.h>
#include "file_io.h"
#include "exit_message.h"
#include "png_io.h"
#include "bin_conv.h"

int x, y;
int width, height;
png_byte color_type;
png_byte bit_depth;
png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;	

void read_png_file(char* file_name)
{
	char header[8];    // 8 is the maximum size that can be checked

	/* open file and test for it being a png */
	FILE *fp = fopen(file_name, "rb");
	if (!fp)
		exit_message("[!] Cannot open file.\n");
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
		exit_message("[!] Error when reading header.\n");

	/* initialize stuff */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		exit_message("[!] Error reading png contents.\n");
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		exit_message("[!] Error making info ptr");

	if(setjmp(png_jmpbuf(png_ptr)))
	exit_message("[!] Error setting jump");

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);


  /* read file */
	if(setjmp(png_jmpbuf(png_ptr)))
		exit_message("[!] Error during read_image");

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (y=0; y<height; y++)
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

	png_read_image(png_ptr, row_pointers);

	fclose(fp);
}


void write_png_file(char* file_name)
{
	/* create file */
	FILE *fp = fopen(file_name, "wb");
	if (!fp)
		exit_message("[!] File could not be opened for writing");


	/* initialize stuff */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		exit_message("[!] png_create_write_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		exit_message("[!] png_create_info_struct failed");
	if (setjmp(png_jmpbuf(png_ptr)))
		exit_message("[!] Error during init_io");

	png_init_io(png_ptr, fp);


	/* write header */
	if (setjmp(png_jmpbuf(png_ptr)))
		exit_message("[!] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, width, height,
			bit_depth, color_type, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);


	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr)))
		exit_message("[!] Error during writing bytes");

	png_write_image(png_ptr, row_pointers);
	/* end write */
	if (setjmp(png_jmpbuf(png_ptr)))
		exit_message("[!] Error during end of write");

	png_write_end(png_ptr, NULL);

	/* cleanup heap allocation */
	for (y=0; y<height; y++)
		free(row_pointers[y]);
	free(row_pointers);

	fclose(fp);
}


void process_file(void)
{
	printf("The .png file is %d x %d with a total of %d pixels\n", height, width, height * width);
	if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
		exit_message("[!] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
		"(lacks the alpha channel)");

	if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
		exit_message("[!] color_type of input file must be PNG_COLOR_TYPE_RGBA");

	for (y=0; y<height; y++)
	{
		png_byte* row = row_pointers[y];
		for (x=0; x<width; x++)
		{
			png_byte* ptr = &(row[x*4]);
			/*printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
			x, y, ptr[0], ptr[1], ptr[2], ptr[3]);*/
			/* set red value to 0 and green value to the blue one */
			/*
			 * ptr[0] is the red value
			 * ptr[1] is the green value
			 * ptr[2] is the blue value
			 * ptr[3] is the alpha value
			 */
			ptr[2] = 0x00;
		}
	}
}
void write_steg(unsigned char *bin_arr, size_t size_of_bin_arr, char channel)
{
	printf("The .png file is %d x %d with a total of %d pixels\n", height, width, height * width);
	if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
		exit_message("[!] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
		"(lacks the alpha channel)");

	if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
		exit_message("[!] color_type of input file must be PNG_COLOR_TYPE_RGBA");

	int	int_chan;
	if(channel == 'R' || channel == 'r')
		int_chan = 0;
	else if(channel == 'G' || channel == 'g')
		int_chan = 1;
	else if(channel == 'B' || channel == 'b')
		int_chan = 3;
	else if(channel == 'A' || channel == 'a')
		int_chan = 4;
	else
		exit_message("[!] Invalid channel");
	
	int count = 0;
	for (y=0; y<height; y++)
	{
		png_byte* row = row_pointers[y];
		for (x=0; x<width; x++)
		{
			png_byte* ptr = &(row[x*4]);
			/*printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
			x, y, ptr[0], ptr[1], ptr[2], ptr[3]);*/
			/* set red value to 0 and green value to the blue one */
			/*
			 * ptr[0] is the red value
			 * ptr[1] is the green value
			 * ptr[2] is the blue value
			 * ptr[3] is the alpha value
			 */
			if(count < size_of_bin_arr){
				if(bin_arr[count]){
					if(ptr[int_chan] % 2 == 0){
						ptr[int_chan]++;
					}
				}
				else{
					if(ptr[int_chan] % 2){
						ptr[int_chan]--;
					}
				}
			}
		}
	}
}


void read_steg(unsigned char **bin_arr, size_t *size_of_bin_arr, char channel)
{
	printf("The .png file is %d x %d with a total of %d pixels\n", height, width, height * width);
	if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
		exit_message("[!] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
		"(lacks the alpha channel)");

	if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
		exit_message("[!] color_type of input file must be PNG_COLOR_TYPE_RGBA");

	int	int_chan;
	if(channel == 'R' || channel == 'r')
		int_chan = 0;
	else if(channel == 'G' || channel == 'g')
		int_chan = 1;
	else if(channel == 'B' || channel == 'b')
		int_chan = 3;
	else if(channel == 'A' || channel == 'a')
		int_chan = 4;
	else
		exit_message("[!] Invalid channel");

	unsigned char size_of_bin_arr_bin[64];
	int count = 0;
	for (y=0; y<height; y++)
	{
		png_byte* row = row_pointers[y];
		for (x=0; x<width; x++)
		{
			png_byte* ptr = &(row[x*4]);
			/*printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
			x, y, ptr[0], ptr[1], ptr[2], ptr[3]);*/
			/* set red value to 0 and green value to the blue one */
			/*
			 * ptr[0] is the red value
			 * ptr[1] is the green value
			 * ptr[2] is the blue value
			 * ptr[3] is the alpha value
			 */
			if(count < 64){
				size_of_bin_arr_bin[count++] = ptr[int_chan] % 2;
				continue;
			}
			else if(count == 64){
				bin_to_int64(size_of_bin_arr, size_of_bin_arr_bin);
				*bin_arr = (unsigned char*)malloc(*size_of_bin_arr);
			}
			if(count - 64 == *size_of_bin_arr)
				return;
			(*bin_arr)[count - 64] = ptr[int_chan];
			count++;
		}
	}
}
