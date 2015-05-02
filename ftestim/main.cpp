// ClimgRL.cpp : définit le point d'entrée pour l'application console.
//

#include "image.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	image i1("../database/apple-1.pgm");
	image i2("../database/bell-2.pgm");
	i1.dessinfourier("fapple.pgm");
	float f=i1.distanceEMD(i2);
	
	cout<<"EMD :"<<f<<endl;
	return 0;
}

