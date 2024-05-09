*** Korištenje jednog terminala, pokretanje, upis broja u konzolu + signal SIGINT ***

$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID=941 krenuo s radom
Program: upisujem broj 4
Program: upisujem broj 9
Program: upisujem broj 16
10
Program: upisujem broj 121
Program: upisujem broj 144
Program: upisujem broj 169
3
Program: upisujem broj 16
Program: upisujem broj 25
Program: upisujem broj 36
^CPrimio signal SIGINT, prekidam rad
make: *** [Makefile:26: pokreni] Error 1

*** Korištenje dva terminala, prvi u kojem pokrećemo i upisujemo u konzolu, drugi za signale SIGUSR1 i SIGTERM ***

*** prvi terminal ***						***drugi terminal***
$ make pokreni
cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID=1387 krenuo s radom
Program: upisujem broj 4
Program: upisujem broj 9
Program: upisujem broj 16
10
Program: upisujem broj 121
Program: upisujem broj 144
Program: upisujem broj 169
Primio signal SIGUSR1, broj je 13				$ kill -SIGUSR1 1387
Program: upisujem broj 196
Program: upisujem broj 225
Primio signal SIGTERM, pospremam prije izlaska iz programa	$ kill -SIGTERM 1387

***Korištenje dva terminala, prvi u kojem pokrećemo, drugi za echo "broj" > cijev***

*** prvi terminal ***				***drugi terminal***
$ make pokreni
Program s PID=1917 krenuo s radom
Program: upisujem broj 256
Program: upisujem broj 289
Program: upisujem broj 324
Procitan broj iz cijevi: 5			$ echo 5 > cijev
Program: upisujem broj 36
Program: upisujem broj 49
Procitan broj iz cijevi: 25			$ echo 25 > cijev
Program: upisujem broj 676
Program: upisujem broj 729
^CPrimio signal SIGINT, prekidam rad
make: *** [Makefile:26: pokreni] Error 1	
