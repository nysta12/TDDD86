/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
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
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
O(n?) på grund av de fyra nästlade for-looparna. O(n³) i fallet då tre kollinjära
punkter inte hittas och den fjärde for-loopen hoppas över men värstafallstiden är O(n?).
Körtiden ovan för när N är 6400 respektive 12800, har uppskattats med O(n?) i tidskomplexitet
alltså värstafalls scenariot, körtiden är förmodligen mindre vid körning då alla fyra for-loopar
int körs varenda gång.

Sortering:
O(n²), även här på grund av for-looparna, men här finns endast 2 stycken nästlade loopar
därav en tidskomplexitet på O(n²).
