*Circuito RC - sinal sin

v1 vin 0 dc 0 ac 1 SIN 0 1 200

r1 vin vout 1k

c1 vout 0 1u

*.tran 100u 16m
.ac dec 10 1 100k

.plot db(v(vout))