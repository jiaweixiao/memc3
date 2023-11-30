#!/bin/bash

if [[ $1 != 'chain' && $1 != 'cuckoo' ]]; then
  echo "wrong option"
  exit 0
fi

#clean
pushd build_$1
test -z "memc3" || rm -f memc3
test -z "" || rm -f
test -z "memc3-debug sizes testapp timedrun" || rm -f memc3-debug sizes testapp timedrun
rm -f *.o
test -z "*.gcov *.gcno *.gcda *.tcov" || rm -f *.gcov *.gcno *.gcda *.tcov
popd

#build
make clean
make

mv memc3 build_$1
mv memc3-debug build_$1
mv *.o build_$1
mv *.gcno build_$1
mv .deps build_$1
mv testapp build_$1
mv sizes build_$1
mv timedrun build_$1
