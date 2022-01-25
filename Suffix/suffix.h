#ifndef SUFFIXFS_SUFFIX_H
#define SUFFIXFS_SUFFIX_H

#ifndef PUBLIC
#include "Internal/Inc/internals.h"
#endif

#include "stdint.h"

/// Mount the storage media.
/// \return Returns 1 if operation is successful.
PUBLIC int SUFFIX_Mount(const uint8_t* badBlockBitmap);

/// Create a new file.
/// \param name Filename, max 128 chars
/// \param timestamp Current date & time.
/// \param metadata File metadata.
/// \return Returns 1 if operation is successful.
PUBLIC int SUFFIX_FileCreate(const char* name, uint32_t timestamp, uint32_t metadata);

/// Append data to the current file.
/// \param data Data to append.
/// \param length Length in bytes.
/// \return Returns 1 if operation is successful.
PUBLIC int SUFFIX_FileAppend(uint8_t* data, int length);

/// Get a list of all the files on the media.
/// \param onNewFileFound Invoked as new files are found.
/// \return 1 on operation success.
PUBLIC int SUFFIX_FilesList(void(onNewFileFound(const char* name, uint32_t timestamp, uint32_t metadata, uint16_t startBlock)));

/// Open a file.
/// \param startBlock Starting block of a file.
/// \return 1 on operation success.
PUBLIC int SUFFIX_FileOpen(uint16_t startBlock);

/// Seek to a given file chunk.
/// \param chunkID The id of the chunk.
/// \return 1 on operation success.
PUBLIC int SUFFIX_SeekToChunkID(uint32_t chunkID);

PUBLIC int SUFFIX_FileRead(uint8_t* data, uint16_t length);


/// Get the requested file size.
/// \param startBlock The file starting block.
/// \param endblock The file ending block.
/// \return 1 on operation success.
PUBLIC int SUFFIX_FileSize(uint32_t fileID, uint16_t startBlock, int* size);

#endif //SUFFIXFS_SUFFIX_H
