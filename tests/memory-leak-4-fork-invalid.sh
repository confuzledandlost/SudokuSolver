TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example2.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

valgrind --log-fd=9 --leak-check=summary ./sudoku.x --fork < $FILE >/dev/null 2>/dev/null 9>$OUT

COUNT=`cat $OUT | grep "definitely lost" | grep -v "0 bytes" | wc -l`
if [ "$COUNT" != 0 ]; then
    echo "Valgrind reports: $COUNT instances" >> $LOG
    echo "  of processes with more than 0 bytes in use at exit." >> $LOG
    cat $OUT >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
