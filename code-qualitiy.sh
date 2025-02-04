#!/bin/bash
Red='\033[1;91m'    # Red
Green='\033[1;92m'  # Green
Color_Off='\033[0m' # Text Reset

printf " Starting\n\n"

##################
# compiling      #
##################

meson compile -C builddir cDebug tDebug gDebug >build.log
if [[ $? -ne 0 ]]; then
  cat build.log | grep "schwerwiegender Fehler:" --color
  printf "That's why the $Red build failed $Color_Off and the script stops now! Have fun fixing it!(for more details look into test.log or try building the program)"
  exit 1
fi

grep -F '[-W' build.log | sort | uniq -c | sort -nr
printf "$Green Everything compile successfully $Color_Off \n\n"

###################
# Testing         #
###################

meson test -C builddir >test.log
if [[ $? -ne 0 ]]; then
  cat test.log | grep "schwerwiegender Fehler:"
  echo -e "$Red That's why the tests failed and the script stops now! Have fun fixing it(for more details look into test.log or try building the program)!$Color_Off"
  exit 1
fi

testSummary=$(cat test.log | tail -n8 | head -n6 | grep -v 0 | cut -d : -f1)
testCount=$(echo $testSummary | wc -l)
if [[ $testCount == '1' ]]; then
  if [[ $testSummary == 'Ok' ]]; then
    printf "$Green Everything tested successfully $Color_Off \n\n"
  else
    printf "$Red The Tests are not in the ok categories in other Words: TEST FAILED $Color_Off"
    exit 1
  fi
else
  printf "$Red The Tests are in several categories in other Words: TEST FAILED $Color_Off"
  exit 1
fi

#################
# CODE COVERAGE #
#################

ninja -C builddir coverage-text >/dev/null
n="$(cat builddir/meson-logs/coverage.txt | grep TOTAL | cut -c 60- | cut -d % -f1)"
if [[ $n > 10 ]]; then
  echo -e "$Green Code Coverage is greater then 4%($n). That is a good beginning. $Color_Off\n"
else
  echo -e "$Red Code Coverage is $n% which is bad and should instantly improved $Color_Off"
  exit 1
fi

meson compile -C builddir format >/dev/null
printf "$Green Formatted Everything $Color_Off \n\n"

#################
# STATIC-ANALYSIS #
#################

# cppcheckWarnings=$(cppcheck src --enable=all -x c++ -q 2>cppcheck.log && grep -v "error: The code contains unhandled character(s)" cppcheck.log | grep -Gv "<*>" | grep src | sort | uniq -c | sort -nr)
cppcheck src --enable=all -x c++ -q 2>cppcheck.log && grep -v "error: The code contains unhandled character(s)" cppcheck.log | grep -Gv "<*>" | grep src --color | sort | uniq -c | sort -nr
printf "$Green Cppcheck Finished $Color_Off \n\n"

# if [[ $(printf $cppcheckWarnings | wc -l) > 100 ]]; then
#   echo "you have to many warnings in the project! Consider starting withe these warnings: "
#   printf $cppcheckWarnings
#   exit 1
#
# elif [[ $cppcheckWarnings > 0 ]]; then
#   echo "There is room to improve but its OK if you commit! Look at these: "
#   printf $cppcheckWarnings
# fi

printf "$Green FINISH! Happy Committing! $Color_Off"
lazygit
