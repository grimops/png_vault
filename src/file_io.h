#ifndef _FILE_IO_H_
#define _FILE_IO_H_

int read_file(char *file_path, char **file_contents, size_t *file_size);
int write_file(char *file_path, char *file_contents, size_t file_size);

#endif
