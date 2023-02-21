#ifndef _BENCH_COMMON_H_
#define _BENCH_COMMON_H_

#include "bench_config.h"
#include "stats_latency.h"

/* type of each query */
enum query_types{
    query_put=0,
    query_get,
    query_del,
};

/* 
 * format of each query, it has a key and a type and we don't care
 * the value
 */
typedef struct __attribute__((__packed__)) {
    char hashed_key[NKEY];
    char type;
} query;

/* bench result */
typedef struct {
    double total_tput;
    double total_time;
    size_t total_hits;
    size_t total_miss;
    size_t total_gets;
    size_t total_puts;
    size_t num_threads;
    struct stat_time_hist get_lat;
} result_t;
#endif
