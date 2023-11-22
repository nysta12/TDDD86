/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150
    200
    300
    400
    800
   1600
   3200
   6400
  12800


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
O(n?) p� grund av de fyra n�stlade for-looparna. O(n�) i fallet d� tre kollinj�ra
punkter inte hittas och den fj�rde for-loopen hoppas �ver men v�rstafallstiden �r O(n?).
K�rtiden ovan f�r d� N �r 6400 respektive 12800 har uppskattats men O(n?) i tidskomplexitet.

Sortering:
O(n�) �ven h�r p� grund av for-loopar men h�r finns endast 2 stycken n�stlade loopar.
