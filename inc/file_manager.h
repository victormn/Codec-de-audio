#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

int read_wave(char const *arg, short **buffer);
int write_bin(char const *arg, short *buffer, int size);
int split_header(short **header, short **data, short * file, int fileSize, int headerSize);
int merge_header(short **file, short *header, short * data, int dataSize, int headerSize);
int merge_compress_flags(short **result, short *file, int size, int d, int c, int h);
int remove_compress_flags(short **result, short *file, int size);

#endif