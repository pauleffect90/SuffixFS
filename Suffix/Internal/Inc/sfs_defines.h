#ifndef SUFFIXFS_SFS_DEFINES_H
#define SUFFIXFS_SFS_DEFINES_H

typedef enum
{
    SFS_OK = 1,
    SFS_Error = 0,

} SUFFIX_ERROR_CODES_typedef;

typedef enum
{
    SFS_WRITE_STATUS_OK,
} SUFFIX_WRITE_STATUS_typedef;

typedef struct
{
    uint32_t FID        : 32;       // FILE ID
    uint32_t ChunkID    : 18;       // CHUNK ID
    uint32_t Status     : 14;
} SFS_HEADER_typedef;

typedef struct
{
    int Block;
    int Page;
} ADDRESS_typedef;

typedef struct
{
    struct
    {
        uint8_t HealthyBlocks[512];
        uint8_t FreeBlocks[512];
    } BlockStatus;

    struct
    {
        SFS_HEADER_typedef Header;
        ADDRESS_typedef Address;

    } File;

    int StartBlock;
    int EndBlock;
} PRIVATE_CONTEXT_typedef;

typedef struct
{
		SFS_HEADER_typedef Header;
    char        Filename[128];
    uint32_t    Timestamp;
    uint32_t    Metadata;
} FILE_typedef;

#endif
