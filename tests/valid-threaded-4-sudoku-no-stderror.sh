TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-valid-2-whitespace.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

./sudoku.x < $FILE >/dev/null 2>$OUT

echo "Your stderror" >> $LOG
echo "--------------------------" >> $LOG
cat $OUT >> $LOG
echo "--------------------------" >> $LOG

if [ -s $OUT ]; then
    echo "Valid sudoku produced output to stderr?" >> $LOG
    echo "FAIL $TEST"
    exit
fi
echo "PASS $TEST"
