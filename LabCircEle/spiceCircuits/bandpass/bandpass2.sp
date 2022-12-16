bandpass2

v1 vin 0 dc 0 ac 1

r1 vin vout 10k

c1 vout 0 330p


.ac dec 10 1 1MEG

.print ac vdb(vout)
.plot ac vdb(vout)

.end