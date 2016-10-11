#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

int read_wave(char const *arg, char **buffer);
int write_bin(char const *arg, char *buffer, int size);

#endif