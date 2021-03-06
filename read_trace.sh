#!/bin/bash
if test ! -f "$1"
then
    echo "Error: executable $1 does not exist."
    exit 1
fi
if test ! -f "$2"
then
    echo "Error: trace log $2 does not exist."
    exit 1
fi
EXECUTABLE="$1"
TRACELOG="$2"
RED="\e[31m"
GREEN="\e[32m"
WHITE="\e[39m"
while read LINETYPE FADDR CADDR CTIME; do
    FNAME="$(addr2line -f -e ${EXECUTABLE} ${FADDR}|head -1)"
    CDATE="$(date -Iseconds -d @${CTIME})"
    if test "${LINETYPE}" = "e"
    then
	CNAME="$(addr2line -f -e ${EXECUTABLE} ${CADDR}|head -1)"
	CLINE="$(addr2line -s -e ${EXECUTABLE} ${CADDR})"
	echo -e "$GREEN \bEnter$WHITE ${FNAME} at ${CDATE}, called from ${CNAME} (${CLINE})"
    fi
    if test "${LINETYPE}" = "x"
    then
	echo -e "$RED \bExit$WHITE ${FNAME} at ${CDATE}"
    fi
    done < "${TRACELOG}"
