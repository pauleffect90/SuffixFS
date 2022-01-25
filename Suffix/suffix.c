#line 0 "SUFFIX"
#include <memory.h>
#include <string.h>
#include "suffix.h"
#include "Internal/Inc/sfs_defines.h"


#define MOD(X, Y) ((X) & ((Y)-1))

#include "stdio.h"
#include "Internal/Inc/sfs_driver.h"






PRIVATE PRIVATE_CONTEXT_typedef this;


PRIVATE void MarkBlockAsBad(int block);
PRIVATE void MarkBlockAsUsed(int block);
PRIVATE void MarkBlockAsFree(int block);
PRIVATE int IncrementAddress(int* block, int* page);
PRIVATE int IncrementAddressEx();
PRIVATE int IsBlockHealthy(int block);
PRIVATE int IsBlockFree(int block);
PRIVATE int IsBlockValid(uint16_t block);
PRIVATE int GetNextAvailableBlock(int startBlock, int* endBlock);
PRIVATE int IsBlockWritten(int block);
PRIVATE void GetAvailableBlocks();

PUBLIC int SUFFIX_Mount(const uint8_t* badBlockBitmap)
{
    SFSD_Initialize();

    if(badBlockBitmap == NULL)
    {
        // TODO FORMAT MEDIA
    }

    memcpy(this.BlockStatus.HealthyBlocks, badBlockBitmap, 512);
    memset(this.BlockStatus.FreeBlocks, 0xFF, 512);

    for (int i = 8; i < 4096; ++i)
    {
        // CHECK IF IS USED
        if(IsBlockHealthy(i) != SFS_OK) continue;
        if(IsBlockWritten(i) == SFS_OK)
        {
            printf("BLOCK %u IS WRITTEN\n", i);
            MarkBlockAsUsed(i);
        }
    }


//    MarkBlockAsUsed(4094);
//    MarkBlockAsUsed(4095);
//    MarkBlockAsUsed(8);
//    MarkBlockAsUsed(9);
//    MarkBlockAsUsed(10);
//    MarkBlockAsUsed(11);
//    for (int i = 0; i < 1500; ++i)
//    {
//        MarkBlockAsUsed(i);
//    }
//    for (int i = 2500; i < 4096; ++i)
//    {
//        MarkBlockAsUsed(i);
//    }
//    for (int i = 0; i < 4096; ++i)
//    {
//        MarkBlockAsUsed(i);
//    }


    // FIND START POSITION
    GetAvailableBlocks();

//    SUFFIX_FileCreate("test.mp3", 1000, 1);
//    uint8_t testData[4224];
//    for (int i = 0; i < 128; ++i)
//    {
//        memset(testData, 0xFF-i, 4224);
//        SUFFIX_FileAppend(testData, 4224 - sizeof(SFS_HEADER_typedef));
//    }

    for (int i = 0; i < 4095; ++i)
    {
        // READ FILE ID
    }


    return SFS_OK;
}


PUBLIC int SUFFIX_FileCreate(const char* name, uint32_t timestamp, uint32_t metadata)
{
    if(this.File.Address.Block == this.EndBlock)
    {
        LOG("OUT OF SPACE");
    }
    else
    {
        LOG_SUCCESS("CREATING FILE %s AT B%04u", name, this.File.Address.Block);
        this.File.Address.Page = 0;
    }
    FILE_typedef file =
        {
        .Timestamp = timestamp,
        .Metadata = metadata,
        };
    strcpy(file.Filename, name);
    SFSD_WritePage(this.File.Address.Block, this.File.Address.Page, &file, sizeof(file));
    IncrementAddressEx();
    MarkBlockAsUsed(this.File.Address.Block);
    this.File.Header.FID = timestamp;
    this.File.Header.ChunkID = 0;
    return SFS_OK;
}

PUBLIC int SUFFIX_FileAppend(uint8_t* data, int length)
{
    MarkBlockAsUsed(this.File.Address.Block);
    uint8_t buffer[4224];
    memcpy(buffer + sizeof(this.File.Header), data, length);
    memcpy(buffer, &this.File.Header, sizeof(this.File.Header));
    SFSD_WritePage(this.File.Address.Block, this.File.Address.Page, buffer, length + sizeof(this.File.Header));
    ++this.File.Header.ChunkID;
    IncrementAddressEx();
    return SFS_OK;
}


PRIVATE int IsBlockWritten(int block)
{
    uint32_t fileID;
    SFSD_ReadPage(block, 0, &fileID, sizeof(uint32_t));
    if(fileID != 0xFFFFFFFF) return SFS_OK;
    return SFS_Error;
}

PRIVATE int IncrementAddressEx()
{
    if(this.File.Address.Page == 63)
    {
        this.File.Address.Page = 0;
        int nextBlock;
        int result = GetNextAvailableBlock(this.File.Address.Block, &nextBlock);
        if(result)
        {
            this.File.Address.Block = nextBlock;
            return SFS_OK;
        }
        return SFS_Error;
    }
    ++this.File.Address.Page;
    return SFS_OK;
}


PRIVATE int IncrementAddress(int* block, int* page)
{
    if(*page == 63)
    {
        int nextBlock = 0;
        int result = GetNextAvailableBlock(*block, &nextBlock);
        if(result)
        {
            *block = nextBlock;
            *page = 0;
            return SFS_OK;
        }
        return SFS_Error;
    }
    else
    {
        *page = *page + 1;
        return SFS_OK;
    }
}

PRIVATE int GetNextAvailableBlock(int startBlock, int* endBlock)
{
    int currentBlock = startBlock;
    for(;;)
    {
        if(++currentBlock == 4096) currentBlock = 8;
        if(currentBlock == startBlock) return SFS_Error;
        if(IsBlockValid(currentBlock))
        {
            *endBlock = currentBlock;
            return SFS_OK;
        }
    }
}

PRIVATE int IsBlockValid(uint16_t block)
{
    return (IsBlockHealthy(block) && IsBlockFree(block));
}

PRIVATE int IsBlockHealthy(int block)
{
    if ((this.BlockStatus.HealthyBlocks[block / 8] >> MOD(block, 8)) & 1U)
    {
        return SFS_OK;
    }
    return SFS_Error;
}


PRIVATE int IsBlockFree(int block)
{
    if ((this.BlockStatus.FreeBlocks[block / 8] >> MOD(block, 8)) & 1U)
    {
        return SFS_OK;
    }
    return SFS_Error;
}

PRIVATE void MarkBlockAsBad(int block)
{
    this.BlockStatus.HealthyBlocks[block / 8] &= ~(1UL << MOD(block, 8));
}

PRIVATE void MarkBlockAsFree(int block)
{
    this.BlockStatus.FreeBlocks[block / 8] |= (1UL << MOD(block, 8));
}

PRIVATE void MarkBlockAsUsed(int block)
{
    this.BlockStatus.FreeBlocks[block / 8] &= ~(1UL << MOD(block, 8));
}


PRIVATE void GetAvailableBlocks()
{
    int blockIterator;
    if(IsBlockFree(4095) != SFS_OK)
    {
        // FIND FIRST UNUSED BLOCK
        for (blockIterator = 8; blockIterator < 4095; ++blockIterator)
        {
            if(IsBlockFree(blockIterator) == SFS_OK)
            {
                break;
            }
        }
        // FOUND FIRST FREE BLOCK
    }
    else
    {
        for (blockIterator = 4095; blockIterator > 7; --blockIterator)
        {
            if(IsBlockFree(blockIterator) != SFS_OK)
            {
                // FOUND WRITTEN BLOCK
                break;
            }
        }
        int tmpPage = 63;
        IncrementAddress(&blockIterator, &tmpPage);
    }

    int endBlock = blockIterator;
    int tmpPage = 63;
    IncrementAddress(&endBlock, &tmpPage);
    for(;;)
    {
        tmpPage = 63;
        int tmpBlock = endBlock;
        if(IncrementAddress(&tmpBlock, &tmpPage) != SFS_OK) break;
        else
        {
            if(tmpBlock == blockIterator) break;
            endBlock = tmpBlock;
        }
    }

    this.StartBlock = blockIterator;
    this.EndBlock = endBlock;
    this.File.Address.Block = this.StartBlock;
    this.File.Address.Page = 0;

    if(this.StartBlock == this.EndBlock)
    {
        LOG("NO BLOCKS AVAILABLE");
    }
    else
    {
        LOG("AVAILABLE BLOCKS %04u - %04u", this.StartBlock, this.EndBlock);
    }
}