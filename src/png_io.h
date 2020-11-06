#ifndef _PNG_IO_H_
#define _PNG_IO_H_



#ifdef _PNG_IO_C_
	int x, y;
 
	int width, height;
	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;	
#endif


void read_png_file(char*);
void write_png_file(char*);
void process_file(void);



#endif
