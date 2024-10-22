#include <iostream>

using namespace std;

long long int n;
int fib[1000000];

int main() 
{
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  for(int c=0;c<2;c++)
  fib[c]=c;
  cin>>n;
  
  for(long long int c=2;c<=n;c++)
  {
    fib[c]=fib[c-1]+fib[c-2];
    fib[c]%=2017;
  }

  cout<<fib[n];
  return 0;
}