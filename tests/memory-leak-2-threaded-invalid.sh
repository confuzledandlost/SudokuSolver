TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example2.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

valgrind --log-fd=9 --leak-check=summary ./sudoku.x < $FILE >/dev/null 2>/dev/null 9>$OUT

COUNT=`cat $OUT | grep "definitely lost" | grep -v "0 bytes" | wc -l`
BYTES=`cat $OUT | grep "definitely lost" | tr -s ' ' | cut --delimiter=' ' -f4`
if [ "$COUNT" != 0 ]; then
    echo "Valgrind reports:" >> $LOG
    cat $OUT | grep "definitely lost" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
