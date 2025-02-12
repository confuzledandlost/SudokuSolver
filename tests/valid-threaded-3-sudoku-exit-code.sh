TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example1-whitespace.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

./sudoku.x < $FILE >/dev/null 2>/dev/null

# Check exit code
CODE=$?
if [ "$CODE" != 0 ]; then 
    echo "Exited with code $CODE " >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
