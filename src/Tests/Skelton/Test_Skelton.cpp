#include "Test_Skelton.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

			    
void MySkeltonTest(string file,string name)
{
    MetaImage i(file);
  MetaImage i2=i.getNormalized();
  i2.iterRemoveNoise();
  i2.Fill();
  i2.savePGM("../src/Tests/Skelton/"+name+".pgm");
  i2.Skelton("../src/Tests/Skelton/"+name+".sk.pgm");

}

void Test_Skelton (){
  
  MySkeltonTest("../database/spring-1.pgm","spring");
  MySkeltonTest("../database/butterfly-10.pgm","butterfly");
  MySkeltonTest("../database/device9-6.pgm","device9");
  MySkeltonTest("../database/pocket-20.pgm","pocket");
  MySkeltonTest("../database/cup-7.pgm","cup");
  MySkeltonTest("../database/turtle-1.pgm","turtle-1");
  MySkeltonTest("../database/turtle-14.pgm","turtle-2");
  
  
}