#!/bin/sh
test_dir='./test'
test_num=4
correct=0

make clean
make

if [ -e $test_dir ] ; then  
mkdir -p $test_dir
fi

echo "========== Test 1 : E3 argument ==========="
./wave 12345 54321 > $test_dir/serial_wave_1
./cuda_wave 12345 54321 > $test_dir/cuda_wave_1
diff $test_dir/serial_wave_1 $test_dir/cuda_wave_1
if [ $? -eq 0 ] ; then 
    correct=$(( $correct + 1 ))
fi
echo "\n"

echo "========== Test 2 : small argument ==========="
./wave 20 20 > $test_dir/serial_wave_2
./cuda_wave 20 20 > $test_dir/cuda_wave_2
diff $test_dir/serial_wave_2 $test_dir/cuda_wave_2
if [ $? -eq 0 ] ; then 
    correct=$(( $correct + 1 ))
fi
echo "\n"

echo "========== Test 3 : large argument ==========="
./wave 1000000 2000 > $test_dir/serial_wave_3
./cuda_wave 1000000 2000 > $test_dir/cuda_wave_3
diff $test_dir/serial_wave_3 $test_dir/cuda_wave_3
if [ $? -eq 0 ] ; then 
    correct=$(( $correct + 1 ))
fi
echo "\n"

echo "========== Test 4 : Super large argument ==========="
./wave 1000000 10000 > $test_dir/serial_wave_4
./cuda_wave 1000000 10000 > $test_dir/cuda_wave_4
diff $test_dir/serial_wave_4 $test_dir/cuda_wave_4
if [ $? -eq 0 ] ; then 
    correct=$(( $correct + 1 ))
fi
echo "\n"

accuracy=`echo 'scale=2;'$correct'/'$test_num | bc -l`

echo "================================================"
echo "Total Test: ${test_num}" 
echo "Correct: ${correct}"
echo "Accuracy: ${accuracy} " 
echo "================================================"
