TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example1.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

TRACE=tests/output/`basename $TEST`.trace

rm -f "$TRACE".*
strace -e trace=process -o $TRACE -ff ./sudoku.x --fork < $FILE >/dev/null 2>/dev/null

NUM=`grep "clone(" $TRACE.* | grep -v "CLONE_THREAD" | wc -l`
if [ "$NUM" -lt 2 ]; then
    echo "Oops. Looks like you never called fork" >> $LOG
    echo "Only $NUM pids got created when we ran your program." >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
