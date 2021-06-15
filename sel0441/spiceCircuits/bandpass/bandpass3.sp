bandpass2

v1 vin 0 dc 0 ac 1

c1 vin 1 150n

r1 1 0 10k

r2 1 vout 10k

c2 vout 0 330p 

.ac dec 10 1 1MEG

.print ac vdb(vout)
.plot ac vdb(vout)

.end