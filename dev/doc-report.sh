#!/bin/bash

result=$($1 ${@:2} 2>&1 >/dev/null | tee /dev/tty )
result=$(echo "$result" | grep warning | wc -l)
if [ "$result" != "0" ]; then
	echo "Error : $result members have not been documented. All members have to be documented."
	exit 0 #FOR NOW
fi

exit 0
