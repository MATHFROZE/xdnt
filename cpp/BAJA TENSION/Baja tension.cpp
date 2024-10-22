#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct data 
{
    string name;
    double pow;
    int item, phases;

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

    cout<<"Introduzca Nombre - Cantidad - Potencia:"<<endl;
    for(int c=0;c<n;c++)
    {
        cout<<"Leer renglon "<<c+1<<endl;
        cin>>elem.name>>cant>>elem.pow; //nombre, cantidad y potencia
        sum+=cant*elem.pow;
        for(int d=0;d<cant;d++,k++)
        {
            elem.item=k;
            values.push_back(elem);
        }
    }
    sort(values.begin(), values.end());
    cout<<endl<<endl<<"Tabla: "<<endl;
    for(data c:values)
    cout<<c.item<<" "<<c.name<<" "<<c.pow<<endl;
    cout<<endl<<endl;
}

// Función para minimizar el valor máximo de abs(Savg - Si)
void minimizeMaxDifference(vector<data>& values, int m, double& totalSum) 
{
    int n = values.size();
    vector<vector<data>> groups(m);

    // Calcular la suma total y el promedio (Savg)
    for (data num : values)
        totalSum += num.pow;
        
    double Savg = totalSum / m;

    // Ordenar los números de mayor a menor para distribuirlos
    sort(values.rbegin(), values.rend());

    // Distribuir los números en los grupos
    vector <double> groupSums(m, 0);

    for (int i = 0; i < n; ++i) 
    {
        // Asignar el número al grupo con la menor suma acumulada
        int minGroup = 0;
        
        for (int j = 1; j < m; ++j)
            if (groupSums[j] < groupSums[minGroup]) 
                minGroup = j;
                
        groups[minGroup].push_back(values[i]);
        groupSums[minGroup] += values[i].pow;
    }

    // Calcular la diferencia máxima entre las sumas de los grupos y el promedio
    double maxDiff = 0;
    for (int i = 0; i < m; ++i) 
    {
        double diff = fabs(Savg - groupSums[i]);
        
        if (diff > maxDiff) 
            maxDiff = diff;
    }

    // Imprimir los grupos y la diferencia máxima
    cout << "Grupos:\n";
    for (int i = 0; i < m; ++i) 
    {
        cout << "Grupo " << i + 1 << ": "<< "(Suma: " << groupSums[i] << ")\n";
        
        for (data num : groups[i]) 
            cout << num.name<<": " << num.pow << " "<<endl;
        cout<<endl<<endl;
    }

    cout << "Diferencia máxima: " << maxDiff << endl << "Objetivo: "<<Savg;
}



int n;
double power;
vector < data > tabla;

int main() 
{
    int m = 3;  // Número de grupos
    cout<<"Introduzca renglones de la tabla:"<<endl;
    cin>>n;
    readTab(tabla, n);
    minimizeMaxDifference(tabla, m, power);
    cout<< endl << "Carga instalada: " << power <<endl;
    return 0;
}