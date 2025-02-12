TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-invalid-c1c3.txt
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

HIT=`grep -l -i "column 3" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Does not recognize problem with Column 3" >> $LOG
    echo "FAIL $TEST"
    exit
fi


echo "PASS $TEST"
