#include <iostream>

#include <vector>

#include <fstream>
#include <random>
#include <array>
#include <map>
#include <algorithm>
using namespace std;

typedef map<string ,vector<string>> Equipe;

int number_random(int limite)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, limite);

    return dis(gen);
}

vector<array<string,2>> random_short(Equipe & equipe)
{
    vector<array<string,2>> composition;

    auto save_equipe=equipe;

    for(auto & E : save_equipe)
    {
        if(E.second.size()==0)
            continue;

        array<string,2> res;

        res[0]= E.first;

        int it =number_random(E.second.size()-1);

        res[1]= E.second[it];

        for(auto & E2 : save_equipe)
        {
            if(E2.first==res[1])
            {
                E2.second.clear();
                E2.second.push_back(res[0]);
                continue;
            }

            auto it_rem2=find(E2.second.begin(),E2.second.end(),res[0]);

            if(it_rem2 != E2.second.end())
                E2.second.erase(it_rem2);

            it_rem2=find(E2.second.begin(),E2.second.end(),res[1]);

            if(it_rem2 != E2.second.end())
                E2.second.erase(it_rem2);
        }

        bool any=false;
        for(auto i=0; i< composition.size() ;i++)
        {
            if(res[0]==composition[i][0] ||res[0]==composition[i][1] || res[1]==composition[i][0] ||res[1]==composition[i][1])
                any=true;
        }

        if(!any)
            composition.push_back(res);
    }

    for(auto & E : equipe)
    {
        for(auto & C : composition)
        {
            if(E.first == C[0])
            {
                for(auto i=0; i < E.second.size() ; i++)
                {
                    if(E.second[i] == C[1])
                    {
                        E.second.erase(E.second.begin()+i);
                        i=0;
                    }


                }
            }
            else if(E.first == C[1])
            {
                for(auto i=0; i < E.second.size() ; i++)
                {
                    if(E.second[i] == C[0])
                    {
                        E.second.erase(E.second.begin()+i);
                        i=0;
                    }

                }
            }
        }
    }

    return composition;
}

int main()
{
    std::ifstream If_Ls_player("list_player.txt"); //mini 4

    if(If_Ls_player.bad())
    {
        cerr << "le fichier \"list_player.txt\" na pas pu etre ouvert" << endl;
        string att;
        getline(cin, att);
        return -1;
    }

    string name_player;

    vector<string> ls_player;
    Equipe equipes;

    while(getline(If_Ls_player,name_player))
        ls_player.push_back(name_player);

    if(ls_player.size()%2 != 0)
    {
        cerr << "le nombre d'equipe doit etre paire" << endl;
        string att;
        getline(cin, att);
        return -1;
    }

    for(auto i=0u; i < ls_player.size() ; i++)
    {
        equipes[ls_player[i]];

        for(auto j=0u; j < ls_player.size() ; j++)
        {
            if(j!=i)
                equipes[ls_player[i]].push_back(ls_player[j]);
        }
    }

    int nb(0);
    cout << "nombre de tours de jeu: ";
    cin >> nb;

    ofstream Of("resultat.txt");

    if(Of.bad())
    {
        cerr << "le fichir resultat.txt na pas pu etre ecrit" << endl;
        string att;
        getline(cin, att);
        return -1;
    }

    for(auto i=0; i<nb ;i++)
    {
        Of << "Tour " << i+1 << endl;
	cout << "Tour " << i+1 << endl;
        for(auto & n : random_short(equipes))
	{
		Of << "\t" <<n[0] << " vs " << n[1] << endl;
		cout << "\t" <<n[0] << " vs " << n[1] << endl;
	}

        Of << endl;
	cout <<endl;
    }

	string att;
        getline(cin, att);
	cin.get();

    return 0;
}
