# EAGC

<details>
  <summary>Tema 1</summary>
  De desenat casa cu ferestre, usa, cerul albastru, soare cu raze, element de dificultate = pasari in zbor
</details>

<details>
  <summary>Tema 2</summary>
  Cu ajutorul mouse-ului dand click stanga se introduc coordonatele varfurilor unui poligon (in ordinea click-urilor). La apasarea butonului dreapta de la mouse, introducerea poligonului se incheie. Din acest moment, cand butonul stanga este apasat si mouse-ul este mutat, poligonul se deplaseaza pe ecran
</details>

<details>
  <summary>Tema 3</summary>
Tema 3: sa se scrie o clasa denumita "Transformare2D" care retine o transformare in coordonate omogene, adica retine o matrice 3x3 de numere reale (double)
Membrii clasei (private):
	- Produs de doua matrici
Functiile clasei (publice):
	- Produs cu un vector de lungime 3 de double ("Produs cu un punct")
	- Compunere (transformare curenta cu alta transformare => noua transformare)
	- Rotatie (primeste cos si sin pentru un unghi si construieste o matrice corespunzatoare rotatiei respective fata de origine pe care o compunem cu transformarea curenta)
	- Scalare (primeste 2 valori Sx si Sy)
	- Simetrie fata de origine (nu primeste parametrii)
	- Simetrie fata de OX
	- Simetrie fata de OY
	- Translatie (primeste 2 valori dx si dy)
	- Rotatie fata de un punct P (primim coordonatele x, y, sin alpha, cos alpha)
	- Simetrie fata de un punct P (primim x,y)
	- Simetrie fata de o dreapta (primim dx,dy, vx, vy)
	- Scalare fata de un punct P
Pentru aplicatia cu poligon (tema 2)consideram suplimentar un obiect de tip "Transformare2D". De fiecare data cand se face redesenarea (Invalidate()) coordonatele initiale ale poligonului se inmultesc succesiv cu matricea de transformari rezultand poligonul final
(cat timp inca este in desenare poligonul (adica sunt selectate punctele) la fiecare Invalidate() se aplica metoda 'Produs cu un punct')

Dupa ce desenarea s-a terminat, tinand butonul stanga apasat, modificam corespunzator mutarii matricea de transformari (inmultind cu o matrice de translatie)
(dupa ce se termina desenarea poligonului (primul click dreapta): click stanga + miscare mouse => translatie cu coordonatele mouse ului)

Daca butonul CTRL este apasat, butonul stanga apasat si miscam mouse-ul, poligonul nostru se va roti in jurul centrului de greutate (miscarea mouse-ului pe orizontala => rotatie, cu rotita de la mouse => scalare). Observatie: o deplasare cu n pixeli se traduce cu o rotatie cu n/100 radiani
Coordonatele centrului de greutate al unui poligon se obtin facand medie aritmetica pentru coordonatele varfurilor
(CTRL + click stanga + mouse => rotesc poligonul in directia mouse-ului)
(CTRL + rotita mouse => scalare)

Cerinta suplimentara: daca se apasa din nou click dreapta, se trece in etapa 3 in care cu ajutorul mouse-ului se introduc coordonatele a 2 puncte care dau dreapta d fata de care poligonului curent i se aplica simetrie
</details>

<details>
  <summary>Tema 4</summary>
Sa se adauge ca si functii externe functiile f si g (primesc U double, capetele intervalelor a si b, returneaza double). Sa se aplice cei 4 pasi pentru reprezentarea unei curbe (vezi teorie curs 4)
</details>

<details>
  <summary>Tema 5</summary>
Cu ajutorul mouse-ului se introduc N+1 puncte (minim 2 puncte). La introducerea unui nou punct nu se accepta decat daca noul punct are coordonata x strict mai mare decat coordonata x a punctului anterior.
La apasarea click dreapta se afiseaza polinomul de interpolare ce trece prin punctele introduse la pasul 1. Cu ajutorul mouse-ului, punctele de control introduse in pasul 1 pot fi mutate. Coordonata X a unui punct mutat nu poate trece de coordonata X a punctului precedent spre stanga, respectiv de coordonata X a punctului urmator spre dreapta
La fiecare mutare a punctului se face o recalculare si reafisare a polinomului d erecalculare folosind formula Lagrange. Poligonul de interpolare il reprezentam asemanator cu reprezentarea unei curbe parametrice fara a mai face pasii de translatie, scalare si simetrie. In momentul reprezentarii polinomului de interpolare, punctele de control vor fi evidentiate prin niste cerculete rosii. Un punct de control poate fi mutat cu mouse-ul in momentul in care se da click in interiorul un cerc rosu.
</details>

<details>
  <summary>Tema 6</summary>
Aceeasi aplicatie cu cea de data trecuta, dar in loc de formula Lagrange, folosim formula Newton, programata eficient.
</details>

<details>
  <summary>Tema 7</summary>
Cu ajutorul mouse-ului se introduc 4 puncte a0, a1, a2, a3.
a0 reprezinta punctul de plecare al curbei
a2 punctul final al curbei

a0a1 = m0
a2a3 = m1

Dupa cele 4 puncte au fost introduse, pe ecran vor aparea desenate cele 2 tangente m0 si m1, precum si curba Coons-Hermit.
Cu ajutorul mouseului, oricare dintre cele 4 puncte poate fi mutat cu redesenare a curbei

Pentru nota 11:
Cu ajutorul mouse-ului se introduc 2k puncte si se deseneaza curbele imbinate care trec prin punctele de indici par si au tangentele corespunzatoare
</details>

<details>
  <summary>Tema 8</summary>
Cu mouseul se introduc n+1 puncte prin click stanga.
La click dreapta, se termina introducerea punctelor de control si se deseneaza curba Bézier.
Cu ajutorul mouseului, pot fi mutate punctele de control cu redesenarea curbei Bézier.

Observatie: Orice mutare de puncte are ca efect modificarea completa a curbei
</details>

<details>
  <summary>Tema 9</summary>
Sa se implementeze curba B-Spline (vezi fisierul de teorie), modificand sau folosind ca si baza programul Bezier anterior
</details>
