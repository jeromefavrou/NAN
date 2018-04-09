#include <iostream>
#include <array>

#include "Sources/c++/header/auto_building.hpp"

#include "I_E.hpp"

using namespace std;

/** faire methode get_memory et get_info sur IO_rnl, learning et rnl_type*/

/** acces base de donné*/

/** metre a jour sauvegarde importation*/

/** mettre en place inertie*/

/** mettre en place donné test pour generalisation*/

/**programmer gpu*/

/**gestion des erreur a revoir*/

int main()
{
    cout << "Version pre Alpha 0.0.2 test binaire\nsur x86 Intel pentium 2X 2.4Ghz\n"<<endl;

    /////////////////////////////////////////////////
    ///construction BDD E/S
    /////////////////////////////////////////////////

    IO_rnl Win_out;

    /*Win_out+=array<vector<float>,2>{{{0,0},{0,0,0,1}}};
    Win_out+=array<vector<float>,2>{{{0,1},{1,1,0,0}}};
    Win_out+=array<vector<float>,2>{{{1,0},{1,1,0,0}}};
    Win_out+=array<vector<float>,2>{{{1,1},{0,1,1,0}}};*/



    /////////////////////////////////////////////////
    ///construction du reseaux de neurones
    /////////////////////////////////////////////////

    RNL IA;

    IA.clear();
    IA.clear_error();

    /*IA.Add_O(RNL::Init_O<float>(2)); ///deux entrées
    IA.Add_O(RNL::Init_O<float>(2)); ///deux neurones cachés
    IA.Add_O(RNL::Init_O<float>(4)); ///quatre sorties

    IA.Add_B(RNL::Init_B<float>(2,RNL::NORMAL));
    IA.Add_B(RNL::Init_B<float>(4,RNL::NORMAL));

    IA.Add_W(RNL::Init_W<float>(2,2,RNL::NORMAL));
    IA.Add_W(RNL::Init_W<float>(2,4,RNL::NORMAL));*/

    import(IA,Win_out,"data/");
    /////////////////////////////////////////////////
    ///definition des paremtre de propagation
    /////////////////////////////////////////////////

    LSpread propag;

    propag.set_hidden_layer_func(LSpread::SIGMOIDE_LOGISTIQUE);
    propag.set_out_layer_func(LSpread::HEAVISIDE);
    propag.set_alpha(1);
    propag.set_spread_type(LSpread::CPU);


    /////////////////////////////////////////////////
    ///definition des parametre d'apprentissage
    /////////////////////////////////////////////////

    Learning Apprentissage;

    Apprentissage.set_epsilon(Learning::LINEAR_ERROR);
    Apprentissage.set_it(10000);
    Apprentissage.set_inertie(Learning::CONST,false);
    Apprentissage.set_auto_stop(true,0.02,10);
    Apprentissage.set_save_as(false,"");

    /////////////////////////////////////////////////
    ///auto construction du reseau (en dev)
    /////////////////////////////////////////////////
    Auto_Building A_B;

    A_B.set_spreed_device(LSpread::CPU);

    //A_B.building(IA,Win_out,propag,Apprentissage);

    /////////////////////////////////////////////////
    ///apprentissage
    /////////////////////////////////////////////////

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Apprentissage.Learn(IA,Win_out,propag);

    end = std::chrono::system_clock::now();


    /////////////////////////////////////////////////
    ///Affichage resultats
    /////////////////////////////////////////////////

    display(IA,Win_out,propag);

    cout <<"apprentissage en: "<<static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())/1000000.0f<< " s\n"<<endl;
    cout <<"taux apprentissage: "<<(1.0-Apprentissage.get_error())*100.0<<'%'<<endl<<endl;

    save_as(IA,Win_out,"data/");

    cerr <<rnl_error_to_str(IA.get_error());
    cerr <<rnl_error_to_str(Win_out.get_error());

    return 0;
}





















/*int main()
{
    cout << "Version pre Alpha 0.0.2\n"<<endl;

    string path("data/");

    RNL IA;
    IO_rnl Win_out;

    import(IA,Win_out,path);

    IA.clear();
    IA.clear_error();

    IA.Add_O(RNL::Init_O<float,2>(0));
    IA.Add_O(RNL::Init_O<float,2>(0));
    IA.Add_O(RNL::Init_O<float,4>(0));

    IA.Add_B(RNL::Init_B<float,2>(RNL::NORMAL));
    IA.Add_B(RNL::Init_B<float,4>(RNL::NORMAL));

    IA.Add_W(RNL::Init_W<float,2,2>(RNL::NORMAL));
    IA.Add_W(RNL::Init_W<float,2,4>(RNL::NORMAL));

    LSpread propag;
    propag.set_hidden_layer_func(LSpread::SIGMOIDE_LOGISTIQUE);
    propag.set_out_layer_func(LSpread::HEAVISIDE);
    propag.set_alpha(1);
    propag.set_spread_type(LSpread::CPU);

    Learning Apprentissage;
    Apprentissage.set_epsilon(Learning::LINEAR,1);
    Apprentissage.set_it(10000);
    Apprentissage.set_inertie(Learning::CONST,false,1);
    Apprentissage.set_auto_stop(true,0.01,10);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Apprentissage.Learn(IA,Win_out,propag);

    end = std::chrono::system_clock::now();

    display(IA,Win_out,propag);

    cout <<"apprentissage en: "<<static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000.0f<< " s\n"<<endl;
    cout <<"taux apprentissage: "<<(1.0-Apprentissage.get_error())*100.0<<'%'<<endl;

    save_as(IA,Win_out,path);

    cerr <<rnl_error_to_str(IA.get_error());
    cerr <<rnl_error_to_str(Win_out.get_error());

    return 0;
}*/


