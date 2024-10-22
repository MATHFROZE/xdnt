#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
void readArray(vector<int>& xd, int n)
{
    for(int c=0;c<n;c++)
    cin>>xd[c];
}
void printArray(vector<int>& xd, int n)
{
    for(int c=0;c<n;c++)
    cout<<xd[c]<<" ";
}

int main()
{   
    cin>>n;
    vector <int>hola (n);
    readArray(hola, n);
    printArray(hola,n);
}