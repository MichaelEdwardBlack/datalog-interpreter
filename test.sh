#!/bin/bash
INPUT_PATH="test/inputs"
OUTPUT_PATH="test/outputs"
EXPECTED_PATH="test/expected_outputs"
PROGRAM="lab4"

if [ $# = 0 ]; then
	g++ -g -Wall -std=c++17 -o ${PROGRAM} *.h *.cpp
	for i in 1 2 3 4 5 6 7 8 9 10 11
	do
		./${PROGRAM} "${INPUT_PATH}/in${i}.txt" > "${OUTPUT_PATH}/out${i}.txt"
		DIFF=$(diff ${OUTPUT_PATH}/out${i}.txt ${EXPECTED_PATH}/expected_out${i}.txt)
		if [ "$DIFF" == "" ]
		then
			echo "Test for in${i}.txt passed!"
	   	else
			echo "Test for in${i}.txt failed!"
			diff ${OUTPUT_PATH}/out${i}.txt ${EXPECTED_PATH}/expected_out${i}.txt
    		fi
	done
fi
while [ "$1" != "" ]; do
	case $1 in
		### run a specific test number ###
		-t | --test)
			shift
			./${PROGRAM} "${INPUT_PATH}/in$1.txt" > "${OUTPUT_PATH}/out$1.txt"
			DIFF=$(diff ${OUTPUT_PATH}/out$1.txt ${EXPECTED_PATH}/expected_out$1.txt)
			if [ "$DIFF" == "" ]
			then
				echo "Test for in$1.txt passed!"
			else
				echo "Test for in$1.txt failed!"
				tkdiff ${OUTPUT_PATH}/out$1.txt ${EXPECTED_PATH}/expected_out$1.txt
			fi
			;;
		### run the program with a specified input file ###
		-i | --input)
			shift
			./${PROGRAM} $1
			;;
		### run the program with no input files ###
		-r | --run)
			./${PROGRAM}
			;;
		### run the complexity test ###
		-c | --complexity)
			pmccabe *.cpp
			;;
		### display the differences between your output and the expected output ###
		### requires a test number immediately following the flag ###
		-d | --display)
			shift
			tkdiff ${OUTPUT_PATH}/out$1.txt ${EXPECTED_PATH}/expected_out$1.txt
			;;
		### display the help menu ###
		-h | --help)
			echo "Usage: $0 [option...] {test_number|file_name}" >&2
    			echo
			echo "			no flags will run all test cases"
			echo "	-t, --test	run test on test file specified by the file number"
			echo "	-i, --input	run test on input file specified by the file name"
      			echo "	-r, --run	run program with no inputs files"
			echo " 	-c, --complexity	run complexity test (complexity > 8 is too high)"
			echo "	-d,	--display	displays the differences of output and expected output of specified test number"
			echo "	-h, --help	display the help"
	   		echo

		 	echo "Examples:"
			echo
			echo "	./test.sh"
			echo "	./test.sh --test 1"
			echo "	./test.sh -f input20.txt"
			echo "	./test.sh --run"
			echo "	./test.sh -c -t 10"
			echo "	./test.sh --display 7"
			echo "	./test.sh --help"
		    	exit 0
			;;
		-*)
			echo "Invalid arguments!"
			echo "	-h, --help for help"
			;;
	esac
	shift
done
