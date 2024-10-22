#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long int lld;

lld n,h,t,value;
vector<lld>arbol;

void insert(vector<lld>& xd, lld i, lld value) //insertar nuevo nodo
{
    if( xd[i]==-1 ) //espacio libre
    {
        xd[i]=value;
        return;
    }

    else if(value < xd[i]) //hacer hijo menor -> izquierdo
        insert(xd, 2*i+1, value);

    else
        insert(xd, 2*i+2, value); //hacer hijo mayor -> derecho
        
}

void preorder(vector<lld>& xd, lld i, lld n) //raiz->izquierdo->derecho
{
    if( i<n && xd[i]!=-1 )
    {
        cout<<xd[i]<<" "; //raiz
        preorder(xd, 2*i+1, n); //izquierda
        preorder(xd, 2*i+2, n); //derecha
    }

    return;
}

void inorder(vector<lld>& xd, lld i, lld n) //izquierdo->raiz->derecho
{
    if( i<n && xd[i]!=-1 )
    {
        inorder(xd, 2*i+1, n); //izquierda
        cout<<xd[i]<<" "; //raiz
        inorder(xd, 2*i+2, n); //derecha
    }

    return;
}

void postorder(vector<lld>& xd, lld i, lld n) //izquierdo->derecho->raiz
{
    if( i<n && xd[i]!=-1 )
    {
        postorder(xd, 2*i+1, n); //izquierda
        postorder(xd, 2*i+2, n); //derecha
        cout<<xd[i]<<" "; //raiz
    }
    return;
}


int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin>>n;
    t=pow(2,n)-1;//maximo espaciado del arbol (tamaño)
    arbol.resize(t,-1);

    for(lld c=0;c<n;c++)
    {
        cin>>value;
        insert(arbol, 0, value);
    }
    
    preorder(arbol, 0, t);
    cout<<endl;
    inorder(arbol, 0, t);
    cout<<endl;
    postorder(arbol, 0, t);

    return 0;
}