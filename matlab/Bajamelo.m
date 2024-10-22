clc
clear all

tab= 1 %conocer los datos de carga --bandera

area= 100 %area del terreno (m2)

fd= 0.7 %factor de demanda-- 70%

inmueble= 1 %tipo de inmueble --Pagina 45 de la NOM

ampacidad= 0.8 %corriente maxima sin exceder temperatura

tap= 1.2 %porcentaje de sobrecarga permitido

fp= 0.9 %fp= 1 cuando no se conoce,  fp= 1 cargas resistivas,  fp= 0.9 minimo cfe --Becerril pag 137

l= 50 %longitud del conductor (m)

e= 3 %porcentaje de caida en el circuito secundario -- NOM pag 36

t= 38 %temperatura (°c)


%Factor de corrección por temperatura
if t>= 26 & t<= 30
    fct= 1 
elseif t>= 31 & t<= 35
    fct= 0.91
elseif t>= 36 & t<= 40
    fct= 0.82
elseif t>= 41 & t<= 45
    fct= 0.71
end

if tab== 1 % tabla de carga instalada

    %col1= numero de elementos,  col2=  consumo por elemento
    r1= [8, 180];
    r2= [8, 180];
    r3= [7, 75];
    r4= [2, 60];
    r5= [3, 60];
    r6= [1, 200];
    r7= [2, 180];
    r8= [6, 75];
    r9= [1, 200];
    r10= [4, 180];
    r11= [9, 75];
    r12= [1, 200];
    r13= [3, 180];
    r14= [7, 180];
    r15= [1, 373];

    tabla= [r1;r2;r3;r4;r5;r6;r7;r8;r9;r10;r11;r12;r13;r14;r15];

    ci= sum( tabla(:,  1) .* tabla(:,  2) ) %carga instalada (w)
    
else
    carga= [33, 22] %carga por metro cuadrado (w/m2) -- pag 45 NOM
    ci= carga(inmueble)*area %carga instalada (w)

end

pd= ci*fd %potencia demandada (w)

if pd<= 5e3
        disp('Servicio 1f,  2w,  vln=  120 v')
        vln= 120
        ical= pd/(vln*fp*fct)
        scal= (4*l*ical)/(e*vln)
        disp('Transformador Estrella aterrizada - Estrella aterrizada')
        trafo1= 1 %puede ser suministrado por transformador monofasico
        trafo3= 1 %no puede ser suministrado por transformador trifasico
        
        %disp('No es susceptible a ferroresonancia')
        %disp('Cargas monofasicas y trifasicas')
        %disp('vll= 480 y vln= 240; vll= 240 y vln= 120')
        sgsg= 1; %conexion estrella aterrizada - estrella aterrizada
        
        %disp('No es susceptible a ferroresonancia')
        %disp('Cargas monofasicas (iluminarias / pequeñas) y trifasicas')
        %disp('Puede operar en estrella abierta- delta abierta)
        %disp('vll= 480 y vln= 240; vll= 240 y vln= 120')
        sgdg= 1; %conexion estrella aterrizada- delta aterrizada
        
        %%delta-delta aterrizada
        %disp('cargas trifasicas y pequeñas cargas monofasicas(iluminacion'))
        %disp('puede operar en delta abierta delta abierta en caso de falla o crecimiento')
        %disp(3w, vll= 240, vln= 120')
        dgdg= 0; %conexion delta aterrizada - delta aterrizada
       
        
elseif pd<= 10e3
        disp('Servicio 1f,  3w,  vll=  240 v,  vln=  120 v')
        vll= 240
        vln= 120
        ical= pd/(2*vln*fp*fct)
        scal= 2*l*ical/(e*vln)
        
        trafo1= 1
        trafo3= 1
      
        sgsg= 1;
        sgdg= 0;
        dgdg= 0;
        
elseif pd<= 25e3
        disp('Servicio 3f,  4w,  vll=  240 v,  vln=  120 v')
        vll= 240
        vln= 120
        ical= pd/(3*vln*fp*fct)
        scal= (2*l*ical)/(e*vln)
        
        trafo1= 0
        trafo3= 1
        
        sgsg= 1;
        sgdg= 0;
        dgdg= 0;
        
else
        disp('Servicio 3f,  4w,  vll=  480 v,  vln=  240 v')
        vll= 480
        vln= 240
        ical= pd/(3*vln*fp*fct)
        scal= (2*l*ical)/(e*vln*fct)
        
        trafo1= 0
        trafo3= 1
        
        sgsg= 1;
        sgdg= 1;
        dgdg= 1;
        
end

%%NOM 001 SEDE pag.138
%%Tabla de conductores
r1= [3.31, 12, 20];
r2= [5.26, 10, 30];
r3= [8.37, 8, 40];
r4= [13.3, 6, 55];
r5= [21.2, 4, 70];
r6= [26.7, 3, 85];
r7= [33.6, 2, 95];
r8= [42.4, 1, 110];
r9= [53.49, 100, 125];
r10= [67.43, 200, 145];
r11= [85.01, 300, 165];
r12= [107.2, 400, 195];

% Area (mm2),  Calibre,  Ampacidad (A)
tablaw= [r1;r2;r3;r4;r5;r6;r7;r8;r9;r10;r11;r12];
renglones= size(tablaw, 1)
dif= 5 % Amperes de holgura

for renglon= 1: renglones
    
    stab= tablaw(renglon, 1);
    calibre= tablaw(renglon, 2);
    itab= tablaw(renglon, 3);
    
    if itab-ical >=  dif && stab >=  scal
        disp('Seccion de tabla sugerida')
        stab
        disp('Calibre sugerido')
        calibre
        disp('Corriente de tabla sugerida')
        itab

        break
        
    end
    
end

%NOM pagina 38 y 74 (Datos de interruptores)
tablaint= [15,20,25,30,35,40,45,50,60,70,80,90,100,110,125,150,175,200,225,250,300,350,400,450,500]; %interruptores
disp( 'Se propone un interruptor de:')
interruptor= tablaint(1)
capinterruptor= interruptor*ampacidad % 80% de la capacidad maxima del conductor

%NOM pagina 137 (conductores)
pmax= vln*capinterruptor %potencia maxima por circuito derivado
mincircuitos= ceil( pd/pmax )

%Becerril pag. 200,  harper residenciales pag. 97
%desbalance= ((cmayor-cmenor)/cmayor)*100

tabkva1= [ 5;10;15;25;37.5;50;75;100;167;250;333;500 ];
tabkva3= [ 30;45;75;112.5;150;225;300;500 ];


kvaCal1= (itab*vll)/1000 %potencia para un monofasico
kvaCal3=  kvaCal1*sqrt(3) %potencia para un trifasico

renglones= size( tabkva1, 1 );
for renglon= 1: renglones
    kvatab1= tabkva1( renglon, 1 );
    if kvatab1 > kvaCal1
        disp('Transformador 1f recomendado:')
        kvatab1
        break
    end
end

renglones= size( tabkva3, 1 );
for renglon= 1: renglones
    kvatab3= tabkva3( renglon, 1 );
    if kvatab3 > kvaCal3
        disp('Transformador 3f recomendado:')
        kvatab3
        break
    end
end

itap= ical*tap %umbral para que opere la protección del interruptor principal

columnas= size( tablaint, 2 );

for columna= 1: columnas
    itab= tablaint( 1, columna );
    if itab > itap
        disp('Se recomienda un interruptor principal de:')
        mainbreaker= itab
        break
    end
end

 %%LOS ARMONICOS CAUSAN CALENTAMIENTOS EN LOS CONDUCTORES Y PERDIDAS EN UN TRANSFORMADOR