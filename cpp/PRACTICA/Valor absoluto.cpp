// Escolta
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long int lld;

struct node
{
    lld num;    // valor numerico o dato

    lld arr;    // arreglo al que pertenece

    bool operator < ( const node& xd ) const // ordenar por valor numerico
    {
        if( num<xd.num )
        return true;
        else
        return false;
    } 
};

struct tuples
{
    lld sizeArr;    // tamaño de cada arreglo

    lld tupleFind;  // bandera por arreglo encontrado en la tupla

    lld tupleR;     // tupla resultante

    lld posArr;     // posicion de la variable en la tupla ordenada

    lld sortVar;    // tupla ordenada

    bool operator < ( const tuples& xd ) const  // ordenar por valor de la tupla
    {
        if( tupleR<xd.tupleR )
        return true;
        else
        return false;
    } 
};

void readArr(vector <node> line, lld numArr, vector <tuples> info, lld& lim);
void initTuple(vector <node> line, vector <tuples> info, lld& band, lld &pos);
void reposArr(vector <node> line, vector <tuples> info, lld& pos);

vector <node> line (300000);  // arreglo general

vector <tuples> info (3); // informacion de la tupla

lld lim;    // limite del arreglo general

lld band;   // bandera general de los arreglos encontrados

lld pos;    // posicion en el recorrido del arreglo general 

int main()
{
    for(lld c=0; c<3;c++) // leer el tamaño de cada arreglo
        cin>> info[c].sizeArr;

    for(lld c=0; c<3; c++) // leer los arreglos y meterlos en uno solo
        readArr(line, c, info, lim);

    sort(line, line+lim); // ordenar el arreglo general

    initTuple(line, info, band, pos); // obtener la primera tupla y ultima posicion del barrido
    reposArr(line, info, pos);

    cout<<"xd";
}

// !    reposicionar y actualizar informacion de la tupla
void reposArr(vector <node> line, vector <tuples> info, lld& pos)
{
    // paso 1 consultar la posicion (posArr) en el arreglo ordenado (sortVar)
    lld numArr= line[ pos ].arr; // numero de arreglo insertado
    lld x= info[ numArr ].posArr; 

    // paso 2 recorrer las posiciones en (posArr) y en (sortVar)
    for(lld c=x; c<2; c++)
    {
        lld y= info[c+1].sortVar; // numero de arreglo y
        info[c].sortVar= y; // recorrer las mayores 1 posicion
        info[y].posArr--; // reducir los indices una posicion
    }

    // paso 3 agregar a la cola
    info[3].sortVar= numArr; // ultimo valor añadido
    info[ numArr ].posArr= 3; // ultima posicion actualizada

    // paso 4 añadir a la tupla
    info[ numArr ].tupleR= line[ pos ].num;
}

// !    seleccionar la primera tupla previo a la comparacion
void initTuple(vector <node> line, vector <tuples> info, lld& band, lld &pos)
{
    for( pos; !band; pos++)
    {
        lld x= line[ pos ].arr;
        lld y= line[ pos ].num;
    
        info[x].tupleFind= 1; // arreglo encontrado en la tupla
        info[x].tupleR= y; // arreglo sustituido en la tupla

        for(lld i= 0; i<3; i++) // determinar si se han allado todas los arreglos en la tupla
            band*= info[i].tupleFind;
    }
}

// !    leer arreglo particular e insertar en el arreglo general
void readArr(vector <node> line, lld numArr, vector <tuples> info, lld& lim) 
{
    lld init= lim; // ultimo elemento registrado
    lim= init + info[ numArr ].sizeArr; // nuevo limite actualizado
    for(lld c= init; c<lim; c++)
    {
        cin>> line[c].num;
        line[c].arr= numArr;
    }
}
