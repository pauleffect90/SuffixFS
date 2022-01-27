#include <stdio.h>
#include "suffix.h"
#include "memory.h"


void OnNewFileFound(const char* name, uint32_t id, uint32_t metadata, uint16_t startBlock)
{
    int size;
    SUFFIX_FileSize(id, startBlock, &size);
    printf("FOUND FILE[%u] %s \t\tIN BLOCK %04u: SIZE %d.\n", id, name, startBlock, size);
//    SUFFIX_FileOpen(startBlock);
//    SUFFIX_SeekToChunkID(128);
}

int main()
{
    printf("SFS ENTRY POINT\n");
    uint8_t bitMap[512];
    memset(bitMap, 0xFF, 512);
    SUFFIX_Mount(bitMap);
//    SUFFIX_FilesList(OnNewFileFound);
    SUFFIX_FileOpen(8);
    SUFFIX_SeekToChunkID(5);
    for(;;)
    {
        uint8_t data[4224];
        if(SUFFIX_FileRead(data, 4224) != 1) break;
        for (int i = 0; i < 16; ++i)
        {
            printf("%02X ", data[i + 8]);
        }
        printf("\n");
    }

    printf("SFS EXIT POINT\n");
    return 0;
}
