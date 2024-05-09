***PRIMJER 1: Korištenje jednog terminala, pokretanje, upis broja u konzolu + signal SIGINT ***

$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID=1138 krenuo s radom
Program: upisujem broj 4
Program: upisujem broj 9
Program: upisujem broj 16
Program: upisujem broj 25
10
Program: upisujem broj 121
Program: upisujem broj 144
Program: upisujem broj 169
5
Program: upisujem broj 36
Program: upisujem broj 49
^CPrimio signal SIGINT, prekidam rad
make: *** [Makefile:26: pokreni] Error 1

***PRIMJER 2: Korištenje dva terminala, prvi u kojem pokrećemo i upisujemo u konzolu, drugi za signale SIGUSR1 i SIGTERM ***

*** prvi terminal ***						***drugi terminal***
$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID=1443 krenuo s radom
Program: upisujem broj 4
Program: upisujem broj 9
10
Program: upisujem broj 121
Program: upisujem broj 144
Primio signal SIGUSR1, broj je 12				$ kill -SIGUSR1 1443
Program: upisujem broj 169
Program: upisujem broj 196
Primio signal SIGTERM, pospremam prije izlaska iz programa	$ kill -SIGTERM 1443

***PRIMJER 3: Korištenje dva terminala, prvi u kojem pokrećemo, drugi za echo "broj" > cijev (upis preko cjevovoda)***

*** prvi terminal ***				***drugi terminal***
$ make pokreni
Program s PID=1848 krenuo s radom
Program: upisujem broj 225
Program: upisujem broj 256
Procitan broj iz cijevi: 7			$ echo 7 > cijev
Program: upisujem broj 64
Program: upisujem broj 81
Procitan broj iz cijevi: 3			$ echo 3 > cijev
Program: upisujem broj 16
^CPrimio signal SIGINT, prekidam rad
make: *** [Makefile:26: pokreni] Error 1


***PRIMJER 4: Korištenje dva terminala, kombinacija upisa preko konzole i cjevovoda***

***prvi terminal***						***drugi terminal***
$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID=2363 krenuo s radom
Program: upisujem broj 4
Program: upisujem broj 9
20
Program: upisujem broj 441
Program: upisujem broj 484
Procitan broj iz cijevi: 5					 $ echo 5 > cijev
Program: upisujem broj 36
Program: upisujem broj 49
10
Program: upisujem broj 121
Program: upisujem broj 144
^CPrimio signal SIGINT, prekidam rad
make: *** [Makefile:26: pokreni] Error 1