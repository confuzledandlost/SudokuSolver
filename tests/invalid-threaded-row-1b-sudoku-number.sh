TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-invalid-r7r9.txt
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

NUM=`grep -i "row" $OUT | uniq | wc -l`
if [ $NUM -gt 2 ]; then
    echo "Reported $NUM different row problems" >> $LOG
    echo "Expected at most 2 in this file" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
