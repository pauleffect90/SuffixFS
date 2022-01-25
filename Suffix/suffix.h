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


#endif //SUFFIXFS_SUFFIX_H
