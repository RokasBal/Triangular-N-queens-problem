#include <fstream>
#include "script.h"

void printScript(std::ofstream& output) {
    output <<"PIRMA DALIS" <<std::endl;

    output <<"Užduoties sąlyga: Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų. (Triangular N-queens problem)" <<std::endl <<std::endl;

    output <<"Sprendimo eiga: " <<std::endl;
    output <<"Sprendinio ieškojimas pradedamas nuo viršaus į apačią, valdoves statant pradedant nuo kairės į dešinę." <<std::endl;
    output <<"Prieš padedant valdovę lentoje, patikrinama, ar ji nebūtų kertama kitų, jau pastatytų, valdovių." <<std::endl;
    output <<"Jei valdovė būtų kertama, tikrinamos kitos laisvos lentos vietos toje pačioje eilutėje, eilutę užbaigus einama viena eilute žemyn." <<std::endl;
    output <<"Jei valdovė nebūtų kertama, ji padedama lentoje. Jei liko daugiau nepadėtų valdovių, tikrinimas vyksta toliau, pradedant viena eilute žemiau." <<std::endl;
    output <<"Neradus tinkamos vietos valdovei, gryžtama atgal ir bandoma valdoves išdelioti kitaip (vykdomas BACKTRACKING)." <<std::endl;
    output <<"Suradus tinkamas vietas visoms karalienėms, sprendimas užbaigiamas." <<std::endl <<std::endl;
}