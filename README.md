# Parallelism-RFI
Tanner T. Connor M. Blake J.
* Included is a merge sort that can be ran on a number of integers or a csv file of NNU alumni
* For integers, call like:
>Parallelism-RFI.exe NumberOfThreads i NumberOfInts unsortedOutputFile.txt sortedOutputFile.txt

* For the csv, call like:
>Parallelism-RFI.exe NumberOfThreads a (n or d) inputFile.csv sortedOutputFile.csv

* Where n sorts based on names, d sorts based on dates

#### Notes
* When running, writing to the output files will take significantly longer than sorting the file. The time recorded for the Merge Sort does not include this extra time.
