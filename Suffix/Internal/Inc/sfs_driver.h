#ifndef SUFFIXFS_SFS_DRIVER_H
#define SUFFIXFS_SFS_DRIVER_H

#include "stdint.h"

int SFSD_Initialize();
int SFSD_ReadPage(int block, int page, void* data, uint16_t length);
int SFSD_WritePage(int block, int page, void* data, uint16_t length);
int SFSD_FormatBlock(int block);

#endif //SUFFIXFS_SFS_DRIVER_H
