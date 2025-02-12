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

HIT=`egrep -l -i "(right[ -](bottom|lower))|((bottom|lower)[ -]right) subgrid" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Does not recognize problem with right bottom subgrid" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
