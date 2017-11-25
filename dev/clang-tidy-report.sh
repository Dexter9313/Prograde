#!/bin/bash

result=$($1 ${@:2} 2> /dev/null | tee /dev/tty)
result=$(echo "$result" | wc -l)
if [ "$result" != "1" ]; then
	exit 1
fi

exit 0
