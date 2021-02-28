#!/bin/bash

./helper.pl --update-makefiles || exit 1

makefiles=(makefile makefile_include.mk makefile.shared makefile.unix makefile.mingw makefile.msvc)
vcproj=(libtomcrypt_VS2008.vcproj)

if [ $# -eq 1 ] && [ "$1" == "-c" ]; then
  git add ${makefiles[@]} ${vcproj[@]} doc/Doxyfile && git commit -m 'Update makefiles'
fi

exit 0

# ref:         HEAD -> develop
# git commit:  e8afa13d5c19d2757ff56537d34802c1dad2c507
# commit time: 2019-04-10 17:05:59 +0200
