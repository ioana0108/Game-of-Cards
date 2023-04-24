AMESTECARE

*initDeck()

	- functie ce creeaza lista/ pachetul de carti



*addCard()

	- calculeaza pozitia ultimei carti din pacheta
	- adauga pe pozitia urmatoarea cartea avand 
caracteristiile primite ca parametri
	- returneaza lista/pachetul avand cartea noua 
adaugata pe ultima pozitie



afisare()

	- afiseaza lista in fisierul de iesire




*invert()

	- primeste ca parametru lista initiala
	- returneaza lista cu elementele listei initiale
inversate prin recursivitate




*intercalation()

	- primeste drept argument lista de prelucrat
	- imparte lista in alte 2 liste egale
	- adauga in lista finala elementele de pe pozitii
pare, in ordine, din lista initiala
	- adauga apoi in lista finala elementele de pe 
pozitii impare, in ordine, din lista initiala
	- returneaza lista finala




*Mongean()

	- primeste drept argument lista de prelucrat
	- creeaza alte 2 liste, in prima fiind elementele
listei initiale de pe pozitii impare, iar in a doua cele
de pe pozitii pare
	- inverseaza prima lista folosind functia
invert() descrisa anterior
	- adauga la finalul primei listei cea de-a doua lista
si s-a obtinut lista finala




*Npiles()

	- primeste ca parametru lista/pachetul, numarul
de subpachete si vectorul de indici
	- numara in variabila nr_cards cate carti
contine pachetul
	- parcurge lista initiala
	- in functie de indexul primit ca parametru in
vectorul indexes[] ajunge la subgrupul de carti cu 
indexul respectiv si il adauga in lista finala
	- returneaza lista finala




gotCard()

	- verifica daca o carte primita ca parametru 
alaturi de caracteristicile aferente se afla intr-un pachet




findCard()

	- gaseste cartea care poate fi jucata de un 
jucator (in cazul in care acesta nu a avut in pachet o carte
de aceeasi culoare cu cea anterior jucata)




RollingStone()

	- imparte cartile din pachetul initial in 4
subpachete
	- numara cate carti de fiecare culoare are fiecare
jucator
	- cat timp niciun jucator nu si-a terminat cartile,
verifica pentru fiecare dintre cei 4 jucatori daca au in
pachet o carte de aceeasi culoare cu cea anterior jucacata
( apeland functia got_card() ). In caz afirmativ, se 
actualizeaza cate carti are in total in acel moment 
jucatorul si cate carti de fiecare culoare are sau, altfel, 
daca jucatorul nu are cartea ceruta, "calculeaza" urmatoarea 
carte folosind functia findCard(), apoi actualizeaza 
numarul de carti total, plus numarul de carti de fiecare 
culoare pe care il mai are
	- la final verifica lista carui jucator a ramas
goala, jucatorul respectiv fiind castigator