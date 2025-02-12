TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example2.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

TRACE=tests/output/`basename $TEST`.trace

rm -f "$TRACE".*
strace -e trace=process -o $TRACE -ff ./sudoku.x --fork < $FILE >/dev/null 2>/dev/null

NUM=`ls "$TRACE".* | wc -l`
if [ "$NUM" -lt 28 ]; then
    echo "Expected 28 processes to be created" >> $LOG
    echo "These are the pids of processes that were created" >> $LOG
    ls "$TRACE".* >> $LOG
    echo "FAIL $TEST"
    exit
fi

PARENT=`ls "$TRACE".* | sort | head -n1`
REAPED=`grep wait $PARENT | wc -l`
if [ "$REAPED" -lt 27 ]; then
    echo "Expected 27 children to be reaped" >> $LOG
    echo "According to strace, only $REAPED child/children got reaped" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
