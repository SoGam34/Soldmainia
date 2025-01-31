#!/bin/bash

printf "Starting\n\n"

meson compile -C builddir cDebug tDebug gDebug | grep -F '[-W' | sort | uniq -c | sort -nr
printf "Evreything compile succsesfully \n\n"

testSummary=$(meson test -C builddir | tail -n8 | head -n6 | grep -v 0 | cut -d : -f1)
testCount=$(echo $testSummary | wc -l)
if [[ $testCount == '1' ]]; then
  if [[ $testSummary == 'Ok' ]]; then
    printf "Evreything testet succsesfully\n"
  else
    printf "The Tests are not in the ok categories in other Words: TEST FAILD"
    exit 1
  fi
else
  printf "The Tests are in several categories in other Words: TEST FAILD"
  exit 1
fi

ninja -C builddir coverage-text >/dev/null
n="$(cat builddir/meson-logs/coverage.txt | grep TOTAL | cut -c 60- | cut -d % -f1)"
if [[ $n > 4 ]]; then
  echo coverage is greater then 4%% That is wonderful.
else
  echo code coverage ist $n% wich is bad and should instantly improved
  exit 1
fi

meson compile -C builddir format >/dev/null
printf "\nFormatet Evreything\n\n"

# cppcheckWarnings=$(cppcheck src --enable=all -x c++ -q 2>cppcheck.log && grep -v "error: The code contains unhandled character(s)" cppcheck.log | grep -Gv "<*>" | grep src | sort | uniq -c | sort -nr)
cppcheck src --enable=all -x c++ -q 2>cppcheck.log && grep -v "error: The code contains unhandled character(s)" cppcheck.log | grep -Gv "<*>" | grep src | sort | uniq -c | sort -nr
printf "Cppcheck Finished\n\n"

# if [[ $(printf $cppcheckWarnings | wc -l) > 100 ]]; then
#   echo "you have to many warnings in the project! Consider starting withe these warnings: "
#   printf $cppcheckWarnings
#   exit 1
#
# elif [[ $cppcheckWarnings > 0 ]]; then
#   echo "There is room to improve but its OK if you commit! Look at these: "
#   printf $cppcheckWarnings
# fi

printf "FINISH! Happy Commiting!"
lazygit
