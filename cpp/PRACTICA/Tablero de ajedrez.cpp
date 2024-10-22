#include <iostream>
using namespace std;
char m;
int n,k;
int main()
{
  cin>>m>>n;
  k=m+n;
  if(k&1)
    cout<<"BLANCO";
  else
    cout<<"NEGRO";
}