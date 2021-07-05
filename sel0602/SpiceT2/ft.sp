Netlist do circuito. Trabalho SPICE-SEL0602. Francisco Reis Nogueira 11954374

V1 1 0 ac 7 SIN(0 47.11 0 0 0)

r1 1 2 8

c1 2 3 40m

r2 3 0 74

c2 3 4 20m

r3 4 0 37

r4 4 5 5

l1 5 0 0.5

.AC LIN 1 47.11 47.11

.print ac V(3,0) V(4,0);

.end
