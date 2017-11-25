#!/bin/bash

exitcode=0

for i in "${@:2}"; do
	result=$($1 $i -output-replacements-xml | grep -c "replacement ")
	if [ "$result" != "0" ]; then
		echo "File does not comply to clang-format :" $i
		exitcode=1
	fi
done

exit $exitcode
