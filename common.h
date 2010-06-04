

#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <unistd.h> //sleep usleep
#include <limits.h>

#define DEBUG false //jaki tryb pracy programu: normalny czy debugowania  DEBUG={true,false}
#define INV false //INVESTIGATE


/** \defgroup errors Obsługa błędów
      \code
      #include "errors.h"
      \endcode
      Moduł zawiera funkcje i definicje odpowiedzialne za obsługę błędów,
zgłaszanych przez inne moduły oprogramowania, związane z działaniem
aplikacji. \n
...
*/
/*@{*/
using namespace std;

string doublToStr(double number);
void printTable(int * t, int size);
void printTable(double * t, int size);

/*@}*/


#endif
