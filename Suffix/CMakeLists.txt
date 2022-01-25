
set(BASE ${CMAKE_CURRENT_LIST_DIR})

message("### LOADING SUFFIX FILESYSTEM ###")

function(SUFFIX_GET_SOURCES SOURCES)

    list(APPEND ${SOURCES} "${BASE}/suffix.c")
    list(APPEND ${SOURCES} "${BASE}/suffix.h")
    list(APPEND ${SOURCES} "${BASE}/suffix_configuration.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Inc/internals.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Inc/sfs_defines.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Inc/sfs_driver.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Inc/sfs_ll_driver.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Src/sfs_driver.c")

    list(APPEND ${SOURCES} "${BASE}/Internal/Inc/sfs_emulator.h")
    list(APPEND ${SOURCES} "${BASE}/Internal/Src/sfs_emulator.c")


    list(APPEND ${SOURCES} "${BASE}/Internal/Src/sfs_utils.c")
    message(${BASE})
    set(${SOURCES} "${${SOURCES}}" PARENT_SCOPE)
endfunction()