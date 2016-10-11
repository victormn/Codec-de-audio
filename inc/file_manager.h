#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

int read_wave(char const *arg, short **buffer);
int write_bin(char const *arg, short *buffer, int size);

#endif