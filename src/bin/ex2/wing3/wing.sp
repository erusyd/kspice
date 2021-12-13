ex 2 from wing paper

O1 2 0 3 0 singlelossy1
r1 1 2 100
r2 3 0 100
c1 3 0 1pf
VES 1 0 PULSE (0 1 0ns 0.05ns 0.05ns 0.4ns 1ns)

.TRAN 0.05n 1.0N

.model singlelossy1 ltra R = 2.77778 L =0.25e-6 G = 0 C= 0.1e-9 len=0.04
.END
