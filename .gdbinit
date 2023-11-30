set pagination off
set print array-indexes on

set history save on
set history filename .gdb_history
set logging on
set logging file .gdb_log.txt

echo + set args ./test/test01.pas\n
set args ./test/test01.pas
