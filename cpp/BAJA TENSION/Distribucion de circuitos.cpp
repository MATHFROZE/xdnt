#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct data // para almacenar datos de tabla
{
    string name; // nombre del elemento
    double pow; // potencia del elemento
    int phases, item, id; // numero de fases / numero de item generado / identficador de fase

    // sobrecargar el struct para usar el sort
    bool operator < (const data& xd) const
    {
        if(pow<xd.pow) return true;
        else if(pow==xd.pow && item<xd.item) return true;
        else if(pow==xd.pow && item==xd.item && id<xd.id) return true;
        return false;
    }

};
struct arr // para ordenar sumas por linea
{
    int index;
    double sum;
    bool operator < (const arr& xd)
    {
        if(sum<xd.sum) return true;
        return false;
    }
};
void readTab(vector < data >& values, int n, double& sum)
{
    int cant, k=1;
    data elem;

    cout<<"Introduzca Nombre - Fases - Cantidad - Potencia:"<<endl;
    for(int c=0;c<n;c++)
    {
        cout<<"Renglon "<<c+1<<endl;
        cin>>elem.name>>elem.phases>>cant>>elem.pow; // nombre, fases, cantidad y potencia

        sum+=cant*elem.pow;
        elem.pow/=elem.phases;
        
        for(int d=0;d<cant;d++,k++)
            for(int e=0;e<elem.phases; e++)
            {
                elem.item=k; // elemento perteneciente
                elem.id=e+1; // numero de fase
                values.push_back(elem);
            }
    }

    sort(values.rbegin(), values.rend()); // ordenar de mayor a menor

}

//Balancear lineas
void minimizeMaxDifference(vector <data>& tabla, int m, double& totalPower, vector< vector<int> >& lines, vector <arr>& sumLine) 
{
    int n = tabla.size();
    double Savg=totalPower/m;

 
    // Distribuir los números en los grupos

    for (int i = 0; i < n; i++) 
    {
        // Asignar el número al grupo con la menor suma acumulada
        
        sort( groupSums.begin(), groupSums.end() );

        for(int c=0; c<m; c++) // distribuir las fases del item
            if(tabla[i].phases>i)
            {
                i++;
                int f=groupSums[i].index; // consultar indice de la i-esima suma de linea
                lines[f].push_back(i); // agregar indice a la linea 
                groupSums[f].sum += values[i].pow;
            }

    }
// ultima revision 30/09/2024 13:57 pm
    // Calcular la diferencia máxima entre las sumas de los grupos y el promedio
    double maxDiff = 0;
    for (int i = 0; i < m; ++i) 
    {
        double diff = fabs(Savg - groupSums[i].sum);
        
        if (diff > maxDiff) 
            maxDiff = diff;
    }


}
void doCircuits(vector < vector< vector <data> > >& circuits, vector < vector <data> >& lines, int m, double maxPower, vector < vector <double> >& circuitSum)
{
    for(int numLine=0; numLine<m;numLine++) // linea actual
    {
        int numCircuit=0; // circuito actual
        while(!lines[numLine].empty()) // mientras hayan elementos en espera
        {
            int n= lines[numLine].size(); // actualizar tamaño de la espera a recorrer

            for(int j=0;j<n && !lines[numLine].empty();j++) // recorrer la linea
                if(circuitSum[numLine][numCircuit]+lines[numLine][j].pow<=maxPower) // Potencia valida para añadir al circuito
                {
                    circuitSum[numLine][numCircuit] += lines[numLine][j].pow; // actualizar potencia del circuito
                    circuits[numLine][numCircuit].push_back(lines[numLine][j]); // agregar al circuito
                    lines[numLine].erase(lines[numLine].begin()+j); // eliminar de la lista de espera
                    n--;
                }

            double minVal= lines[numLine].back().pow; // valor minimo en espera

            if(circuitSum[numLine][numCircuit]+minVal>maxPower) // crear circuito nuevo
            {
                numCircuit++;
                circuits.resize(numCircuit);
                circuitSum.resize(numCircuit);
            }
        }
    }
    for(int c=0;c<m;c++)
    {
        cout<<endl<<"sumas linea "<<c+1<<": "<<endl;
        for(double x: circuitSum[c])
        cout<<x<<" ";
        cout<<endl;
    }
}


int n,s; // renglones de la tabla
double power, maxPower; // Carga instalada / Potencia maxima por circuito
vector <data> tabla; // tabla de cargas
vector < vector <int> > lines; // indices de cargas por linea
vector < vector< vector <int> > circuits; // circuitos por linea
vector <arr> lineSum; // suma de cada linea
vector< vector<double> > circuitSum; // suma de cada circuito
int main() 
{
    int m = 3;  // Número de grupos
    lines.resize(m);
    circuits.resize(m);
    lineSum.resize(m);
    circuitSum.resize(m);
    maxPower=1200;
    cout<<"Introduzca renglones de la tabla:"<<endl;
    cin>>n;
    readTab(tabla, n, power);

    cout<< endl << "Carga instalada: " << power <<endl;

    minimizeMaxDifference(tabla, m, power, lines, lineSum);

    doCircuits(circuits, lines, m, maxPower, circuitSum);
    
    return 0;
}