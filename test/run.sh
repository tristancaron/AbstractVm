#!/bin/sh

AVM=../bin/avm
LOG=./log.txt

printf "" > ${LOG}

if [ ! -e ${AVM} ] ; then
	echo "AVM not found..."
	exit
fi

printf "\033[1;33m1 - A - File name :\033[0m\n"
OUTPUT=$(${AVM} ./files/1_A_FILE_NAME.wrong 2>&1 | tail -1)
if [ "$OUTPUT" != "" ]; then
	printf "\033[0;32mTEST PASSED\033[0m\n"
else
	printf "\033[0;31mTEST FAILED\033[0m\n"
fi
echo "1 - A - File name :" >> ${LOG}
echo ${OUTPUT} >> ${LOG}

printf "\033[1;33m1 - B - Comments :\033[0m\n"
OUTPUT=`${AVM} ./files/1_B_COMMENT.avm  2>&1 | tail -1`
if [ "$OUTPUT" = "" ] && [ $? = 0 ]; then
	printf "\033[0;32mTEST PASSED\033[0m\n"
else
	printf "\033[0;31mTEST FAILED\033[0m\n"
fi
echo "1 - B - Comments :" >> ${LOG}
echo ${OUTPUT} >> ${LOG}
