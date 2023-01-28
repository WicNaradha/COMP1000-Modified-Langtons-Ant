#!/bin/bash
#Single Line Grep:
grep -E "\b08:5[3-9]\b.*\b([0-9]{1,3}\.){3}[0-9]{1,3}\b" logfile.txt

#USED TO CHECK NUMBER OF LINES:
echo Number of Lines Counted: $(grep -c -E "\b08:5[3-9]\b.*\b([0-9]{1,3}\.){3}[0-9]{1,3}\b" logfile.txt)