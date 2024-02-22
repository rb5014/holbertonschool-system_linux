#!/bin/bash

# Write a sh script that sends the signal SIGQUIT to a process, given its PID
# Usage: signal_send.sh <pid>
# Where <pid> is the PID of the process to send a signal to
# If the number of arguments is not correct, your program must print Usage:
#     %s <pid> (where %s is argv[0]), followed by a new line, and exit with 1

if [ $# -ne 1 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi

kill -QUIT $1

