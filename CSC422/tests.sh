#!/bin/bash
printf "Starting tests\n\n";
if g++ Clement1.cpp ; then

printf "Command line argument tests\n"
printf "===========================================================================================================\n\n"

printf "Test too few args\n"
./a.out;
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "Test too many args\n"
./a.out 0 1;
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "BAD GRAPH tests\n"
printf "===========================================================================================================\n\n"

printf "Test BAD GRAPH - graph too large\n"
printf "101" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - graph too small\n"
printf "0" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - graph negative vertices\n"
printf "%d" -1 | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - negative vertex number\n"
printf "2 %d" -1 | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - vertex degree too large\n"
printf "2 2" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - invalid neighbour\n"
GRAPH="
5
2 1 3
4 a"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - graph assymetric\n"
GRAPH="
3
2 1 2
0
1 1"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - negative neighbour\n"
GRAPH="
2
1 -1
1 0
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - neighbour too large\n"
GRAPH="
2
1 2
1 0
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - multiple edges\n"
GRAPH="
3
2 1 1
1 0 2
1 2
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD GRAPH - self loops\n"
GRAPH="
3
1 0
0
2 0 1
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "BAD CERTIFICATE tests\n"
printf "===========================================================================================================\n\n"

printf "test BAD CERTIFICATE - invalid certificate size character\n"
GRAPH="
2
1 1
1 0
a
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - dominating set 0\n"
GRAPH="
2
1 1
1 0
0
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - dominating set negative\n"
GRAPH="
2
1 1
1 0
-1
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - dominating set too large\n"
GRAPH="
2
1 1
1 0
3
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - dominating set contains invalid characters\n"
GRAPH="
2
1 1
1 0
2
0 a
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - vertex in dominating set too small\n"
GRAPH="
2
1 1
1 0
2
0 -1
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - vertex in dominating set too small\n"
GRAPH="
2
1 1
1 0
2
0 2
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - set not dominating 1\n"
GRAPH="
3
1 1
1 0
0
1
2
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "test BAD CERTIFICATE - set not dominating 2\n"
GRAPH="
4
1 1
2 0 2
2 1 3
1 2
2
0 1
"
printf "%s" "$GRAPH" | ./a.out 1
printf "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"

printf "Non-verbose test bad graphs\n"
printf "===========================================================================================================\n"

printf "101" | ./a.out 0
printf "0" | ./a.out 0
printf "%d" -1 | ./a.out 0
printf "2 %d" -1 | ./a.out 0
printf "2 2" | ./a.out 0
GRAPH="
5
2 1 3
4 a"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
3
2 1 2
0
1 1"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 -1
1 0
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 2
1 0
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
3
2 1 1
1 0 2
1 2
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
3
1 0
0
2 0 1
"
printf "%s" "$GRAPH" | ./a.out 0

printf "\n"
printf "Non-verbose test bad certificates\n"
printf "===========================================================================================================\n"

GRAPH="
2
1 1
1 0
a
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
0
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
-1
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
3
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
2
0 a
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
2
0 -1
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
2
1 1
1 0
2
0 2
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
3
1 1
1 0
0
1
2
"
printf "%s" "$GRAPH" | ./a.out 0
GRAPH="
4
1 1
2 0 2
2 1 3
1 2
2
0 1
"
printf "%s" "$GRAPH" | ./a.out 0

printf "\n"
printf "Positive tests\n"
printf "===========================================================================================================\n"
TEST_GRAPHS="
1
0
1
0

5
4 1 2 3 4
1 0
1 0
1 0
1 0
1
0

40
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
40
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
"

printf "%s" "$TEST_GRAPHS" | ./a.out 0

printf "\n"
printf "Test against provided output files\n"
printf "===========================================================================================================\n\n"

./a.out 0 < in.txt > my_out.txt;
diff out0.txt my_out.txt;

./a.out 1 < in.txt > my_out.txt;
diff out1.txt my_out.txt;

echo Tests done;

fi
