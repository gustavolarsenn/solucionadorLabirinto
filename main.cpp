#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

#include "Sistema.h"

int main(void){

    Sistema s1("sistema", s1.lerTamLinha(), s1.lerTamColuna());

    s1.caminhoCorreto();

    return 0;
}