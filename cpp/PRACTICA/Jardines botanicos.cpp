#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long int lld;

struct data
{
    lld pos, ti, mins;
    
     bool operator < (const data& xd) const
     {
        if( pos<xd.pos ) 
            return true;
        else    
            return false;
     }
};

lld interseccion(vector <data>& xd, lld i, lld j)
{
    lld h= ceil( (xd[j].pos-xd[i].pos) / (xd[j].ti + xd[i].ti) );
    return h;
}

lld n, p, monster, solve;
vector <data> plant (10e3);
vector < vector<lld> > times (10e3, vector <lld> (10e3) );

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    cin>>n>>p; // tamaño del recorrido - numero de plantas
    for(lld c=0;c<p;c++)
    cin>>plant[c].pos>>plant[c].ti; //posicion de la planta c - crecimeinto


    sort(plant.begin(), plant.begin()+p); //ordenar las p plantas

    for(lld c=0;c<p;c++) //calcular la interseccion de la planta c con las demas plantas a la derecha
    {
        plant[c].mins=10e12;
        
        for(lld d=c+1;d<p;d++)
        {
            times[c][d]= interseccion(plant, c, d); //interseccion
            plant[c].mins= min(plant[c].mins, times[c][d]);
        }
    }

       solve=10e12;

    for(lld c=0;c<p;c++)
    {
        for(lld d=c+1;d<p;c++)
        {
            monster= max(times[c][d], plant[d].mins);
            solve= min(solve, monster);
        }
    }
    cout<<solve;

    return 0;
}