#!/bin/bash

# output version
bash .ci/printinfo.sh

bash .ci/build.sh " $1" "$2 -O2" "$3 IGNORE_SPEED=1" "$4" "$5"
if [ -a testok.txt ] && [ -f testok.txt ]; then
   echo
else
   echo
   echo "Test failed"
   exit 1
fi

rm -f testok.txt
bash .ci/build.sh " $1" "$2 -Os" "$3 IGNORE_SPEED=1 LTC_SMALL=1" "$4" "$5"
if [ -a testok.txt ] && [ -f testok.txt ]; then
   echo
else
   echo
   echo "Test failed"
   exit 1
fi

rm -f testok.txt
bash .ci/build.sh " $1" "$2" "$3 LTC_DEBUG=1" "$4" "$5"
if [ -a testok.txt ] && [ -f testok.txt ]; then
   echo
else
   echo
   echo "Test failed"
   exit 1
fi

rm -f testok.txt
bash .ci/build.sh " $1" "$2" "$3" "$4" "$5"
if [ -a testok.txt ] && [ -f testok.txt ]; then
   echo
else
   echo
   echo "Test failed"
   exit 1
fi

exit 0

# ref:         HEAD -> develop
# git commit:  e8afa13d5c19d2757ff56537d34802c1dad2c507
# commit time: 2019-04-10 17:05:59 +0200
