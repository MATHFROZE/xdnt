#include <iostream>
#include <deque>

using namespace std;
typedef long long int lld;

lld n,x,y,s;
deque<lld>cola;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
        cin>>n;

        for(lld c=0;c<n;c++)
        {
            cin>>x;
                if(x==1) //se forma cliente
                {
                    cin>>y;
                    cola.push_back(y);
                }

                else if(x==2) //atender cliente
                {
                    if(!cola.empty())
                    {
                        s+=cola.front();
                        cola.pop_front();
                    }
                }
                
                else if(x==3) //clientes restantes
                    cout<<cola.size()<<endl;

                else //tacos vendidos
                    cout<<s<<endl;

        }

        

    return 0;
}