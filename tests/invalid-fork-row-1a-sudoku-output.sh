TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-invalid-r7r9.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

./sudoku.x --fork < $FILE >$OUT 2>&1

echo "Your output" >> $LOG
echo "--------------------------" >> $LOG
cat $OUT >> $LOG
echo "--------------------------" >> $LOG

HIT=`grep -l -i "row" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Does not recognize problem with a row" >> $LOG
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
