#include "Internal/Inc/sfs_driver.h"
#include "Internal/Inc/sfs_ll_driver.h"
#include "suffix_configuration.h"



#if SUFFIX_EMULATOR == 1
#include "Internal/Inc/sfs_emulator.h"

int SFSD_Initialize()
{
    SFSE_Initialize();
    return 1;
}

int SFSD_ReadPage(int block, int page, void* data, uint16_t length)
{
    SFSE_ReadPage(block, page, data, length);
    return 1;
}

int SFSD_WritePage(int block, int page, void* data, uint16_t length)
{
    SFSE_WritePage(block, page, data, length);
    return 1;
}

int SFSD_FormatBlock(int block)
{
    SFSE_FormatBlock(block);
    return 1;
}


#else
#define MEDIA_CMD_ADDRESS(BUFFER, C, B, P)  do { (BUFFER)[0] = C; (BUFFER)[1] = (B) >> 10; (BUFFER)[2] = (B) >> 2; (BUFFER)[3] = (B) << 6 | (P);} while(0)
#endif

