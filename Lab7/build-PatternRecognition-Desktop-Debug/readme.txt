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
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
O(n?) på grund av de fyra nästlade for-looparna. O(n³) i fallet då tre kollinjära
punkter inte hittas och den fjärde for-loopen hoppas över men värstafallstiden är O(n?).
Körtiden ovan för då N är 6400 respektive 12800 har uppskattats men O(n?) i tidskomplexitet.

Sortering:
O(n²) även här på grund av for-loopar men här finns endast 2 stycken nästlade loopar.
