TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-invalid-all-subgrids.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

./sudoku.x < $FILE >$OUT 2>&1

echo "Your output" >> $LOG
echo "--------------------------" >> $LOG
cat $OUT >> $LOG
echo "--------------------------" >> $LOG

HIT=`grep -l -i "subgrid" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Does not recognize problem with some subgrid" >> $LOG
    echo "FAIL $TEST"
    exit
fi

HIT=`grep -l -i "input is not a valid Sudoku" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Did not print 'The input is not a valid Sudoku.'" >> $LOG
    echo "FAIL $TEST"
    exit
fi

HIT=`grep -l "input is a valid Sudoku" $OUT`
if [ x"$OUT" == x"$HIT" ]; then
    echo "Contains 'The input is a valid Sudoku.'?" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
