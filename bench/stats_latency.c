#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include "stats_latency.h"

void stats_add_time(struct stat_time_hist * hist, uint64_t value) {
    /* Value is in nanoseconds */
    hist->cnt += 1;
    hist->sum += value;
    hist->sum2 += value*value;
    hist->min = fmin(hist->min, value);
    hist->max = fmax(hist->max, value);

    if(value < NSEC_BIN * NSEC_UNIT){
        int bin = value / NSEC_UNIT;
        hist->nanos[bin] += 1;
    } else if(value < USEC_BIN * USEC_UNIT){
        int bin = value / USEC_UNIT;
        hist->micros[bin] += 1;
    } else if (value < MSEC_BIN * MSEC_UNIT){
        int bin = (int)value / MSEC_UNIT;
        hist->millis[bin] += 1;
    } else {
        hist->millis[MSEC_BIN -1] += 1;
    }
}

uint64_t get_hist_avg(struct stat_time_hist* hist) {
    if (hist->cnt)
        return (uint64_t)(hist->sum / hist->cnt);
    return 0;
}

uint64_t get_hist_dev(struct stat_time_hist* hist) {
    if (hist->cnt && (hist->cnt - 1))
        return (uint64_t)sqrt((hist->cnt * hist->sum2 - hist->sum * hist->sum) / (hist->cnt * (hist->cnt - 1)));
    return 0;
}

uint64_t find_hist_quantile(struct stat_time_hist* hist, float quantile) { 
    //Find the nth-percentile
    long nTillQuantile = hist->cnt * quantile;
    long count = 0;
    int i;
    for(i = 0; i < NSEC_BIN; i++) {
        count += hist->nanos[i];
        if( count >= nTillQuantile ){
            return i * NSEC_UNIT;
        }
    }//End for i

    for(i = 0; i < USEC_BIN; i++) {
        count += hist->micros[i];
        if( count >= nTillQuantile ){
            return i * USEC_UNIT;
        }
    }//End for i

    for(i = 0; i < MSEC_BIN; i++) {
        count += hist->millis[i];
        if( count >= nTillQuantile ){
            return i * MSEC_UNIT;
        }
    }//End for i
    return 1000000000;
}

void histogram_aggregate(struct stat_time_hist *to, struct stat_time_hist *from) {
    to->cnt += from->cnt;
    to->sum += from->sum;
    to->sum2 += from->sum2;
    to->min = fmin(to->min, from->min);
    to->max = fmax(to->max, from->max);

    int i;
    for (i = 0; i < NSEC_BIN; i++) {
        to->nanos[i] += from->nanos[i];
    }
    for (i = 0; i < USEC_BIN; i++) {
        to->micros[i] += from->micros[i];
    }
    for (i = 0; i < MSEC_BIN; i++) {
        to->millis[i] += from->millis[i];
    }
}

/* Calculate the nanoseconds difference*/
uint64_t timespec_diff(struct timespec *start, 
                           struct timespec *end)
{
  uint64_t r = (end->tv_sec - start->tv_sec)*1000000000;

  /* Calculate the microsecond difference */
  if (end->tv_nsec > start->tv_nsec)
    r += (end->tv_nsec - start->tv_nsec);
  else if (end->tv_nsec < start->tv_nsec)
    r -= (start->tv_nsec - end->tv_nsec);
  return r;
}
