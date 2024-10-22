#include <iostream>
#include <vector>

using namespace std;
typedef long long int lld;

string n;
lld x;
bool band;
vector<char>pila;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

        cin>>n;
        x=n.size();

        for(lld c=0;c<x;c++) //recorrer cadena
        {

            if(n[c]=='(') //agregar a espera
            pila.push_back(n[c]);

            else if(!pila.empty()) //completar balanceo
            pila.pop_back();

            else //no hay elemento a balancear
            {
                band=1;
                break;
            }

        }
        
        if(!pila.empty()) //no se balancearon todos los elementos
        band=1;
        
        if (band)
        cout<< "NO";
        else
        cout<< "SI";
    return 0;
}