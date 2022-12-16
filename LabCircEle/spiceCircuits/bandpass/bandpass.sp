bandpass
*
v1      vin     0       dc 0 ac 1
*
c1      vin     vout_hp 150n
r1      vout_hp 0       10k
*
r2      vin     vout_lp 10k
c2      vout_lp 0       330p
*
c3      vin     vint    150n
r3      vint    0       10k
r4      vint    vout    10k
c4      vout    0       330p

*
.ac dec 10 1 1MEG
*
.save vout_hp vout_lp vout
*
.meas ac v10 find v(vout) at = 10
.meas ac v100 find v(vout) at = 100
.meas ac v1000 find v(vout) at = 1000
.meas ac fc_low find frequency when vdb(vout) = -3 cross = 1
.meas ac fc_high find frequency when vdb(vout) = -3 cross = 2
.meas ac pc find vp(vout) when vdb(vout) = -3
*
.print ac vdb(vout)
.plot ac vdb(vout)
.print ac vdb(vout_hp) vdb(vout_lp)
.plot ac vdb(vout_hp) vdb(vout_lp)
*
.end