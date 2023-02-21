/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */

/**
 * The time stats header holding histogram data
 * structures and function prototypes.
 */
#ifndef STATS_TIME_H
#define STATS_TIME_H

#define NSEC_BIN (1000)
#define USEC_BIN (1000)
#define MSEC_BIN (1000)
#define NSEC_UNIT (100)// in 100 ns
#define USEC_UNIT (10*1000) // in 10 us
#define MSEC_UNIT (1*1000*1000) // in 1 ms

struct stat_time_hist {
    uint64_t cnt;
    uint64_t sum;
    uint64_t sum2;
    uint64_t min;
    uint64_t max;
    long nanos[MSEC_BIN];
    long micros[USEC_BIN];
    long millis[MSEC_BIN];
};

void stats_add_time(struct stat_time_hist *hist, uint64_t value);
uint64_t get_hist_avg(struct stat_time_hist *hist);
uint64_t get_hist_dev(struct stat_time_hist *hist);
uint64_t find_hist_quantile(struct stat_time_hist *hist, float quantile);
void histogram_aggregate(struct stat_time_hist *to, struct stat_time_hist *from);
uint64_t timespec_diff(struct timespec *start, struct timespec *end);

// High resolution clock
// https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
#define TIME(statement, difftime_nsec) \
    do { \
        struct timespec tv_stt, tv_end; \
        clock_gettime(CLOCK_MONOTONIC , &tv_stt); \
        do { statement; } while(0);	\
        clock_gettime(CLOCK_MONOTONIC , &tv_end); \
        uint64_t stt_nsec = 1000000000*tv_stt.tv_sec + tv_stt.tv_nsec; \
        uint64_t end_nsec = 1000000000*tv_end.tv_sec + tv_end.tv_nsec; \
        difftime_nsec = end_nsec - stt_nsec; \
    } while (0)

#define STATS_TIME(hist, lat_nsec) \
    do { \
        stats_add_time(hist, lat_nsec); \
    } while (0)

#endif /* STATS_TIME_H */
