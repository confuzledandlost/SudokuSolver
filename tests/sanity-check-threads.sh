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
strace -e trace=process -o $TRACE -ff ./sudoku.x < $FILE >/dev/null 2>/dev/null

NUM=`grep "CLONE_THREAD" $TRACE.* | wc -l`
if [ "$NUM" -lt 1 ]; then
    echo "Oops. Looks like you never called pthread_create" >> $LOG
    echo "$NUM instances of clone(...CLONE_THREAD...) were in seen by strace." >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
