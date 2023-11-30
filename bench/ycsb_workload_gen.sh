#!/bin/bash
# Please change this according to your ycsb installation
# so that, ${YCSB_HOME}/bin/ycsb is the binary 
YCSB_HOME=/home/xiaojiawei/softwares/ycsb-0.17.0-RC1
WORKLOAD=/home/xiaojiawei/softwares/memc3/bench/ycsb_workload_settings

for setting in 'kv1M_op1M_zipf.dat' 'kv10M_op10M_zipf.dat' 'kv100M_op100M_zipf.dat'
do
    echo using predefined workloadb to create transaction records for $setting with 5% updates
    echo generateing $setting.load, the insertions used before benchmark
    ${YCSB_HOME}/bin/ycsb load basic -P ${YCSB_HOME}/workloads/workloadb -P $WORKLOAD/$setting > $setting.load
    echo generateing $setting.run, the lookup queries used before benchmark
    ${YCSB_HOME}/bin/ycsb run basic -P ${YCSB_HOME}/workloads/workloadb -P $WORKLOAD/$setting > $setting.run

    # echo using predefined workloadc to create transaction records for $setting with reads only 
    # echo generateing $setting.load, the insertions used before benchmark
    # ${YCSB_HOME}/bin/ycsb load basic -P ${YCSB_HOME}/workloads/workloadc -P $WORKLOAD/$setting > $setting.load
    # echo generateing $setting.run, the lookup queries used before benchmark
    # ${YCSB_HOME}/bin/ycsb run basic -P ${YCSB_HOME}/workloads/workloadc -P $WORKLOAD/$setting > $setting.run
done
