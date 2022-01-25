//
// Created by Paul on 1/24/2022.
//

#include <stdio.h>
#include <memory.h>
#include "Internal/Inc/sfs_emulator.h"
#include "Internal/Inc/sfs_emulator.h"

static FILE* disk_image;

void SFSE_Initialize()
{
//    disk_image = fopen("Z:\\DiskImage\\disk_image.txt", "r+");
}
void SFSE_WritePage(int block, int page, const uint8_t* data, int length)
{
    printf("WRITTING B%04u P%04u\n", block, page);
    disk_image = fopen("Z:\\DiskImage\\disk_image.txt", "r+");
    fseek(disk_image, block * 64 * 4224 + page * 4224, SEEK_SET);
    fwrite(data, 1, length, disk_image);
    fflush(disk_image);
    fclose(disk_image);
}

void SFSE_ReadPage(int block, int page, uint8_t* data, int length)
{
    disk_image = fopen("Z:\\DiskImage\\disk_image.txt", "r+");
    fseek(disk_image, block * 64 * 4224 + page * 4224, SEEK_SET);
    fread(data, 1, length, disk_image);
    fclose(disk_image);
}

void SFSE_FormatBlock(int block)
{
    disk_image = fopen("Z:\\DiskImage\\disk_image.txt", "r+");
    uint8_t data[4224];
    memset(data, 0xFF, 4224);
    fseek(disk_image, block * 64 * 4224, SEEK_SET);
    fwrite(data, 1, 4224, disk_image);
    fflush(disk_image);
    fclose(disk_image);
}