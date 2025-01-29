#!/bin/bash

printf "\n\nStarting\n\n"

meson compile -C builddir cDebug tDebug gDebug | grep -F '[-W' | sort | uniq -c | sort -nr
printf "\n\nEvreything compile succsesfully \n\n"

meson test -C builddir | grep -F '[-W' | sort | uniq -c | sort -nr
printf "\n\nEvreything testet succsesfully \n\n"

ninja -C builddir coverage-text >/dev/null 2>/dev/null

n="$(cat builddir/meson-logs/coverage.txt | grep TOTAL | cut -c 60- | cut -d % -f1)"
if [[ $n > 90 ]]; then
  echo coverage is greater then 90%% That is wonderful $n
else
  echo code coverage ist $n% wich is bad and should instantly improved
  exit 1
fi

meson compile -C builddir format
printf "\n\nFormatet Evreything \n\n"

# meson compile -C builddir tidy >tidy.log
# echo "\n\n Tidy Finished\n\n"

# tidyErrors=$(cat tidy.log | grep 'error:' | grep -v 'error: error reading' | sort | uniq -c | sort -nr | grep -c 'error:')
#
# if [[ tidyErrors > 0 ]]; then
#   echo "There are some errors thrown by tidy please fix them:\n"
#   cat tidy.log | grep 'error:' | grep -v 'error: error reading' | sort | uniq -c | sort -nr
#   exit 1
# else
#   echo "There are no tidy Errors wich is great :) "
# fi
#
# tidyWarnings=$(cat tidy.log | grep "warning:" | sort | uniq -c | sort -nr | grep -c "warning:")
#
# if [[ tidyWarnings > 100 ]]; then
#   echo "you have to many warnings in the project! Consider starting withe these warnings: "
#   head -n 30 $tidyWarnings
#   exit 1
#
# elif [[ tidyWarnings > 0 ]]; then
#   echo "There is room to improve! Look at these: "
#   head -n 30 $tidyWarnings
# fi

printf "\n\n FINISH! Happy Commiting! \n\n"

git status
