ptr: 0

++++++++[>++++++++++<-]>++++.
<++++[>++++++++++<-]>---.
---------.
-----------.
<+++++++[>----------<-]>+.
<++++++++[>++++++++++<-]>+++.
----.
--.
--------.
+++++++++++++++.
------------.
+.
+++++.
-------.
<+++++++[>----------<-]>-.
<+++[>++++++++++<-]>.
<+++[>----------<-]>.

ptr: 1
0: 0
1: 0x20

2: loop flag (0 to break)
3: 0x0A (LF)
4: temp 0
5: temp1
6: temp2
7: temp3
8: temp4
9: zero

set 2 to 1
>+
ptr: 2

set 3 to LF
>++++++++++
ptr: 3

<
ptr: 2
[
  input char to 4

  >>
  ptr: 4
  ,

  move 3 to 5 and 6
  <
  ptr: 3
  [
    >>+
    >+
    <<<-
  ]

  move 6 to 3
  >>>
  ptr: 6
  [
    <<<+
    >>>-
  ]

  now 3 is copied to 5

  move each value from 10

  >>>>
  ptr: 10

  seek to next zero
  [>]

  <
  ptr: last char of sequence

  [
    move char to next address
    [>+<-]
    <
  ]
  ptr: 9

  move value of  4 to 10 and decrement 5
  <<<<<
  ptr: 4
  [
    >-
    >>>>>+
    <<<<<<-
  ]
  char is LF if 5 is zero
  >
  ptr: 5
  [
    increment loop flag of 2
    <<<+>>>

    set 5 to zero
    [-]
  ]

  decrement loop flag
  <<<
  ptr: 2
  -
]

<<
ptr: 0
++++++[>++++++++++<-]>---.
<++[>++++++++++<-]>++.
++++++.
<++++++++[>----------<-]>-----.
<++++++++[>++++++++++<-]>++++.
+++++.
---------.
-----------.
-.
<+++++++[>----------<-]>++.
++.

ptr: 1
0: 0
1: 0x22


>
ptr: 2

now data from 10 is set to string ends with LF
>>>>>>>>
ptr:10

remove LF
[-]>
ptr: 11

seek to next zero
[>]

<
ptr: last char of sequence

output each char in reversed order
[.<]
ptr: 10


<<<<<<<<<
ptr: 1
.
<++[>----------<-]>----.