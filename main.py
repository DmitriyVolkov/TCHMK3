
import BigClass
import sys
import os

if len(sys.argv) < 5 or len(sys.argv) > 7:
    print "Incorrect arguments!"
    print "[1file] [operation] [2file] [3file] [-b| 4 file] [4file]"
    print"4 file is needed for the degree!"
    sys.exit(0)

bin = 0
if len(sys.argv) > 5 :
    if sys.argv[5] == "-b" :        
        bin = 1

a = BigClass.BigIntClass()

b = BigClass.BigIntClass()

if bin == 1 :
    a.ReadBinFile(sys.argv[1])
    b.ReadBinFile(sys.argv[3])
else :
    a.ReadTextFile(sys.argv[1])
    b.ReadTextFile(sys.argv[3])

Res = BigClass.BigIntClass()

if sys.argv[2][0] == '+' :
    Res = a + b
if sys.argv[2][0] == '-' :
    Res = a - b
if sys.argv[2][0] == '*' :
    Res = a * b
if sys.argv[2][0] == '/' :
    Res = a / b
if sys.argv[2][0] == '%' :
    Res = a % b    
if sys.argv[2][0] == '^' :
    c = BigClass.BigIntClass()
    if bin == 1 :
        c.ReadBinFile(sys.argv[6])
    else :
        c.ReadTextFile(sys.argv[5])
    Res = BigClass.degree(a, b, c)
    c.Clear()
  
if bin == 1 :
    Res.WriteBinFile(sys.argv[4])
else :
    Res.WriteTextFile(sys.argv[4])
a.Clear()
b.Clear()
Res.Clear()











    
