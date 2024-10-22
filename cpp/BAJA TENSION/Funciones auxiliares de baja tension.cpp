#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct data 
{
    string name;
    int pow,item;

    //sobrecargar el struct para usar el sort
    bool operator < (const data& xd) const
    {
        if(pow<xd.pow) return true;
        else if(pow==xd.pow && item<xd.item) return true;
        return false;
    }

};
void readTab(vector< data >& values, int n)
{
    int cant, k=1;
    double sum;
    data elem;
    string name;

    for(int c=0;c<n;c++)
    {
        cin>>elem.name>>cant>>elem.pow; //nombre, cantidad y potencia
        sum+=cant*elem.pow;
        for(int d=0;d<cant;d++,k++)
        {
            elem.item=k;
            values.push_back(elem);
        }
    }
    sort(values.begin(), values.end());
    for(data c:values)
    cout<<c.pow<<" "<<c.name<<" "<<c.item<<endl;
}
int n;
vector < data > tabla;
int main()
{
    cin>>n;
    readTab(tabla, n);
    cout<<endl<<"Terminator"<<endl;
}