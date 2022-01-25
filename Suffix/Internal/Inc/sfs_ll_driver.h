//
// Created by Paul on 1/24/2022.
//

#ifndef SUFFIXFS_SFS_LL_DRIVER_H
#define SUFFIXFS_SFS_LL_DRIVER_H

#include "suffix_configuration.h"

#define MEDIA_CMD_IDENTIFY          0x9F
#define MEDIA_CMD_SET_FEATURE       0x1F
#define MEDIA_CMD_GET_FEATURE       0x0F
#define MEDIA_TABLE_BLOCK_LOCK      0xA0
#define MEDIA_CMD_READ_CELL_ARRAY   0x13
#define MEDIA_CMD_READ_BUFFER       0x03
#define MEDIA_CMD_WRITE_ENABLE      0x06
#define MEDIA_CMD_PROGRAM_LOAD      0x02
#define MEDIA_CMD_PROGRAM_EXECUTE   0x10
#define MEDIA_CMD_BLOCK_ERASE       0xD8

#define MEDIA_STATUS_ECC_FAIL       0x02


#if SUFFIX_EMULATOR == 1
#define     NFS_LL_SELECT_FLASH                     do { } while(0)
#define     NFS_LL_DESELECT_FLASH                   do { } while(0)
#define     NFS_LL_SendSync(X)                      do{uint8_t tmpVal = (X); FE_TransmitReceive((&tmpVal)); } while(0)
#define     NFS_LL_ReadSync(X)                      FE_TransmitReceive((X))
#define     NFS_LL_SendAsync(X, LENGTH)             do { for(int nIDX = 0; nIDX < LENGTH; ++nIDX) FE_TransmitReceive((X+nIDX));     }while(0)
#else

#endif
#endif //SUFFIXFS_SFS_LL_DRIVER_H
