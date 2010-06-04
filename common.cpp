

#include "common.h"

//doublToStr funkcja konwertujaca wartosc liczbowa na string
string doublToStr(double number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void printTable(int * t, int size){
		for(int i =0;i<size;i++)
			cout << t[i] << endl;
		return;
}
void printTable(double * t, int size){
		for(int i =0;i<size;i++)
			cout << t[i] << endl;
		return;
}



