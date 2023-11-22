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
    150      0.029        0.011
    200      0.079        0.048
    300      0.220        0.081
    400      0.627        0.118
    800      4.520        0.398
   1600      35.748       1.347
   3200      278.634      4.697
   6400      9151.971     17.996
  12800      146431.541   78.305


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
O(n?) p� grund av de fyra n�stlade for-looparna. O(n�) i fallet d� tre kollinj�ra
punkter inte hittas och den fj�rde for-loopen hoppas �ver men v�rstafallstiden �r O(n?).
K�rtiden ovan f�r n�r N �r 6400 respektive 12800, har uppskattats med O(n?) i tidskomplexitet
allts� v�rstafalls scenariot, k�rtiden �r f�rmodligen mindre vid k�rning d� alla fyra for-loopar
int k�rs varenda g�ng.

Sortering:
O(n�), �ven h�r p� grund av for-looparna, men h�r finns endast 2 stycken n�stlade loopar
d�rav en tidskomplexitet p� O(n�).
