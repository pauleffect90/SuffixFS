#ifndef SUFFIXFS_INTERNALS_H
#define SUFFIXFS_INTERNALS_H

#define PUBLIC __attribute((unused))
#define PRIVATE static __attribute((unused))
#define PROTOTYPE __attribute__((weak, unused))
#define IMPORT extern

#ifndef LOG
#define LOG(...)                do { printf("[%s] ", __FILE__); printf(__VA_ARGS__); printf("\n");          } while(0)
#define LOG_WARNING( ...)       do { printf("[%s] WARNING: ", __FILE__); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_SUCCESS( ...)       do { printf("[%s] SUCCESS: ", __FILE__); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_ERROR( ...)         do { printf("[%s] !ERROR!: ", __FILE__); printf(__VA_ARGS__); printf("\n"); } while(0)
#define LOG_ARRAY(ARR, LEN)     do { printf("[%s] ", __FILE__); for(int IDX = 0; IDX < LEN; ++IDX) printf("%02X ", ARR[IDX]); printf("\n"); } while(0)
#endif


#endif //SUFFIXFS_INTERNALS_H
