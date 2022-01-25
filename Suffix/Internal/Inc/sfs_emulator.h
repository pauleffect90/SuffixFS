#ifndef SUFFIXFS_SFS_EMULATOR_H
#define SUFFIXFS_SFS_EMULATOR_H

#include "stdint.h"

void SFSE_Initialize();
void SFSE_WritePage(int block, int page, const uint8_t* data, int length);
void SFSE_ReadPage(int block, int page, uint8_t* data, int length);
void SFSE_FormatBlock(int block);

#endif //SUFFIXFS_SFS_EMULATOR_H
