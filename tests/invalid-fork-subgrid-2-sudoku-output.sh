TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example-invalid-r4c3MiddleLeft.txt
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

HIT=`egrep -l -i "(left[ -](middle|center))|((middle|center)[ -]left) subgrid" $OUT`
if [ x"$OUT" != x"$HIT" ]; then
    echo "Does not recognize problem with left middle subgrid" >> $LOG
    echo "FAIL $TEST"
    exit
fi

echo "PASS $TEST"
