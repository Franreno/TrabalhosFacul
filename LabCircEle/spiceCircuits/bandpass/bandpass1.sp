bandpass1

v1 vin 0 dc 0 ac 1

c1 vin vout 150n

r1 vout 0 10k



.ac dec 10 1 1MEG

.print ac vdb(vout)
.plot ac vdb(vout)

.end