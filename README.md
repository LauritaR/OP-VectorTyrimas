# OP-VectorTyrimas
Eksperimentiniai Vector klasės tyrimai
-------------------------------------
Tyrimams buvo sukurta analogiška std::vector klasė vect(vector.h faile), kurioje realizuoti  member tipai, member funkcijos,non-member funkcijos.

--------------------------
*Funkcionalumo palyginimas*
-------------------------
Funkcionalumo palyginimo kodą galima rasti "fun_test.cpp" faile.
Buvo patikrintos tokios funkcijos:
1. 'reserve()' 
Tikrinama reserve(1000) funkcija

 std::vector capacity() prieš reserve():0
 std::vector capacity() po resesrve(): 1000
 vect capacity() prieš reserve(): 0
 vect capacity() po reserve(): 1000

2. 'insert()'
Tikrinama insert() funkcija

std::vector prieš insert(): 1 2 3 
std::vector po insert(): 1 4 2 3 
vect prieš insert(): 1 2 3 
std::vector po insert(): 1 4 2 3 

3. 'erase()'
Tikrinama erase() funkcija

std::vector prieš erase(): 1 4 2 3 
std::vector po erase(): 1 2 3 
vect prieš erase(): 1 4 2 3 
vect po erase(): 1 2 3 

4. 'clear()'
Tikrinama clear() funkcija

std::vector prieš clear(): 1 2 3 
std::vector po clear(): 
vect prieš clear(): 1 2 3
vect po clear():

5. 'shrink_to_fit()'
Tikrinama shrink_to_fit() funkcija

std::vector capacity() prieš shrink_to_fit(): 1000
std::vector capacity() po shrink_to_fit(): 3
vect capacity() prieš shrink_to_fit(): 1000
vect capacity() po shrink_to_fit(): 3

6. 'operator[]' 
Tikrinamas operator[]

std::vector prieš: 1 3 5
std::vector po: 1 3 9

vect prieš : 1 3 5
std::vector po insert(): 1 3 9

Taip pat, papildomai pademonstruotas 'capacity()', 'begin()', 'push_back()' funckionalumas.

----------------------------
*Efektyvumo analizė*
----------------------------
Efektyvumo analizės kodą galima rasti "fun_test.cpp" faile.
Palyginamas std::vector su vect konteineriu, matuojant, kiek laiko užtrunka užpildyti tuščius vektorius su įvairiais dydžiais naudojant 'push_back()' funkciją.
Išmatuojamas laikas, kiek užtrunka užpildyti vektorių su *10.000,100.000,1.000.000,10.000.000,100.000.000* int tipo elementų.


|Įrašų sk.    |std::vector(s)|vect(s)|
|-------------|--------------|-------------|
|10000        |0.0002168     |0.0001539    |
|100000       |0.0010394     |0.0002418    |
|1000000      |0.0135953     |0.0130759    |
|10000000     |0.120412      |0.144413     |
|100000000    |1.21532       |1.39779      |
--------------------------------------------

Galima pastebėti, kad iki 1.000.000 elementų vect veikia greičiau nei std::vector.

--------------------------------------------
*Atminties perskirstymai*
--------------------------------------------
Atminties perskirstymo analizės kodą galima rasti"fun_test.cpp" faile.
Užpildant konteinerius 100.000.000 elementų, atminties perskirstymas abiems vyksta *28 kartus*.

---------------------------------------------
*std::vector pakeitimas vect konteineriu 2.0 versijoje*
---------------------------------------------
Visoje programoje, sukurtoje 2.0 versijos pagrindu, std::vector konteineris buvo pakeistas vect savarankiškai sukurtu konteineriu.
Naudojant 100.000 elementų failą, buvo palyginta ankstesnių versijų(std::vector) ir naujos(vect) veikimo sparta.

|Konteineris|Generavimas(s)|Nuskaitymas(s)|Rūšiavimas(s)|Išvedimas(s)|Skirstymas(s)      |
|-----------|--------------|--------------|-------------|------------|-------------------|
|vect       |0.0388958     |0.225937      |0.42372      |0.119403    |0.0627537          |
|std::vector|0.203583      |0.172811      |0.487787     |0.092127    |0.603963           |
------------------------------------------------------------------------------------------




