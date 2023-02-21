all: bench_trace_gen bench_client

bench_trace_gen: bench_trace_gen.cc
	g++ -std=c++0x -o bench_trace_gen bench_trace_gen.cc -lssl -lcrypto -lz

bench_client: bench_client.o stats_latency.o
	gcc -std=gnu99 -O2 -o bench_client bench_client.o stats_latency.o -lmemcached -lm -pthread -L/usr/lib -L/usr/local/lib

bench_client.o: bench_client.c
	gcc -std=gnu99 -O2 -c bench_client.c stats_latency.c -I/usr/include -I/usr/include

stats_latency.o: stats_latency.c
	gcc -std=gnu99 -O2 -c stats_latency.c -I/usr/include -I/usr/include

clean:
	-rm *.o bench_client bench_trace_gen
