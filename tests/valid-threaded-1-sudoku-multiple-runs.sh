TEST=`basename "${0%.sh}"`
OUT=tests/output/$TEST.out
LOG=tests/output/$TEST.log
FILE=tests/example1.txt
mkdir -p tests/output/

echo "This is $FILE" > $LOG
echo "--------------------------" >> $LOG
cat $FILE >> $LOG
echo "--------------------------" >> $LOG

echo "Running program multiple times to detect timing bugs" >> $LOG
for i in {1..20}
do
    ./sudoku.x < $FILE >$OUT 2>&1
    
    echo "Your output" >> $LOG
    echo "--------------------------" >> $LOG
    cat $OUT >> $LOG
    echo "--------------------------" >> $LOG
    
    HIT=`grep -l -i "input is a valid Sudoku" $OUT`
    if [ x"$OUT" != x"$HIT" ]; then
        echo "Does not contain 'The input is a valid Sudoku'" >> $LOG
        echo "FAIL $TEST"
        exit
    fi
done
echo "PASS $TEST"

