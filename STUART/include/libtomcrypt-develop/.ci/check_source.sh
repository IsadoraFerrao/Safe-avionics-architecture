#!/bin/bash

# output version
bash .ci/printinfo.sh

make clean > /dev/null

echo "checking..."
./helper.pl --check-all || exit 1

exit 0

# ref:         HEAD -> develop
# git commit:  e8afa13d5c19d2757ff56537d34802c1dad2c507
# commit time: 2019-04-10 17:05:59 +0200
