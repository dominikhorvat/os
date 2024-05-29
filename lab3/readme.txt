-----Primjer 1------
***Terminal 1***						***Terminal 2***
$make pokreni
cc -Wall -MMD   -c -o lab3.o lab3.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab3.o signali.o datoteke.o -lm -lpthread -o lab3
Program s PID=20823 krenuo s radom
Krecem s radom, zadnji broj je bio: 1
Trenutni broj na obradi: 2
Program: upisujem broj 4
Trenutni broj na obradi: 3
Program: upisujem broj 9
Trenutni broj na obradi: 4
10
Program: upisujem broj 16
Trenutni broj na obradi: 11
Program: upisujem broj 121
Trenutni broj na obradi: 12
Stvorena je dretva!						$echo 3 > cijev
Stvorena je dretva!
Trenutni broj na obradi: 13
Trenutni broj na obradi: 14
Program: upisujem broj 144
Trenutni broj na obradi: 15
Program: upisujem broj 169
Trenutni broj na obradi: 16
Program: upisujem broj 196
Trenutni broj na obradi: 17
Program: upisujem broj 225
Trenutni broj na obradi: 18
Program: upisujem broj 256
Trenutni broj na obradi: 19
Program: upisujem broj 289
Trenutni broj na obradi: 20
Program: upisujem broj 324
Obrisana je dretva!						$echo 2 > cijev
Program: upisujem broj 361
Trenutni broj na obradi: 21
Program: upisujem broj 400
Trenutni broj na obradi: 22
Program: upisujem broj 441
Trenutni broj na obradi: 23
Program: upisujem broj 484
Trenutni broj na obradi: 24
Primio signal SIGINT, prekidam rad				$ kill -SIGINT 20823
make: *** [Makefile:26: pokreni] Error 1

-----Primjer 2------
***Terminal 1***						***Terminal 2***
$ make pokreni
cc -Wall -MMD   -c -o lab3.o lab3.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab3.o signali.o datoteke.o -lm -lpthread -o lab3
Program s PID=22807 krenuo s radom
Krecem s radom, zadnji broj je bio: 1
Trenutni broj na obradi: 2
Program: upisujem broj 4
Trenutni broj na obradi: 3
Stvorena je dretva!						$ echo 7 > cijev
Stvorena je dretva!
Stvorena je dretva!
Stvorena je dretva!
Stvorena je dretva!
Stvorena je dretva!
Trenutni broj na obradi: 4
Trenutni broj na obradi: 5
Trenutni broj na obradi: 6
Trenutni broj na obradi: 7
Trenutni broj na obradi: 8
Trenutni broj na obradi: 9
Program: upisujem broj 9
Trenutni broj na obradi: 10
Program: upisujem broj 25
Trenutni broj na obradi: 11
Program: upisujem broj 16
Trenutni broj na obradi: 12
Program: upisujem broj 36
Trenutni broj na obradi: 13
Program: upisujem broj 49
Trenutni broj na obradi: 14
Program: upisujem broj 64
Trenutni broj na obradi: 15
Program: upisujem broj 81
Trenutni broj na obradi: 16
Program: upisujem broj 100
Trenutni broj na obradi: 17
Program: upisujem broj 121
Obrisana je dretva!						$ echo 2 > cijev
Program: upisujem broj 144
Obrisana je dretva!
Program: upisujem broj 169
Obrisana je dretva!
Program: upisujem broj 196
Obrisana je dretva!
Program: upisujem broj 225
Obrisana je dretva!
Program: upisujem broj 256
Trenutni broj na obradi: 18
Program: upisujem broj 289
Trenutni broj na obradi: 19
Program: upisujem broj 324
Trenutni broj na obradi: 20
Program: upisujem broj 361
Trenutni broj na obradi: 21
Program: upisujem broj 400
Trenutni broj na obradi: 22
Program: upisujem broj 441
Trenutni broj na obradi: 23
Primio signal SIGINT, prekidam rad				$kill -SIGINT 22807
make: *** [Makefile:26: pokreni] Error 1
