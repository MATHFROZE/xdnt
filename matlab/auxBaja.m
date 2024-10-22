%%borra pantalla
clc
%%borra variables
clear all

FP=.9 %%CFE PENALIZA POR DEBAJO DE 0.9 BECERRIL 134 A 137
L=50
eporciento=3
%%%nom pag 36, becerril pag 178,harper 22,82
%%datos estandar interruptores
%%nom pag 38,74 interruptores
%%pag 137 conductores
interruptor_= [15,20,25,30,35,40,45,50,60,70,80,90,100,110,125,150,175,200,225,250,300,350,400,450,500];
%%interruptores mas pequeñas, mas circuitos; interruptores mas grandes, menos circuitos
interruptor=15
%%Circuitos_Min=PD/VLN*Capacidad_Interruptor
%%tabla_=0 no conozco los datos de carga
%%tabla_=0
%%tabla_=1 conozco los datos de carga
tabla_=1
area=100
%%inmueble=1 casa 33w
%%inmueble=2 restaurant 22w
%%inmueble=3 estacionamiento 6w
inmueble=1
%%factor de demanda viejo 1
%%FD factor de demanda que indica la carga conectada todo el tiempo .7,.8
FD=.7;
%%ampacidad es el limite de corriente sin exeder el maximo de temperatura
%%ampacidd actual 0.8
%%ampacidad vieja 1

ampacidad = .8
%%t es temeperatura
t=38;

%% tap es porcentaje de sobrecarga permitido
TAP=1.2
%%diferencia
diferencia=5
%%POTENCiA DEMANDADA EN KILOWATT
%%carga instalada=CI
%%potencia demanda=PD
%%columna=1 numero de elementos, columna=2 consumo por elemento
%%PD=CI*FD, DONDE F0 ES FACTOR DE DEMANDA(.7 Y .8)

r1=[8,180];
r2=[8,180];
r3=[7,75];
r4=[2,60];
r5=[3,60];
r6=[1,200];
r7=[2,180];
r8=[6,75]; 
r9=[1,200]; 
r10=[4,180];
r11=[9,75]; 
r12=[1,200]; 
r13=[3,180]; 
r14=[7,180]; 
r15=[1,373]; 
tabla=[r1;r2;r3;r4;r5;r6;r7;r8;r9;r10;r11;r12;r13;r14;r15];


%%datos de conductores
%%milimetros cuadrados
r1=[3.31,12,20];
r2=[5.26,10,30];
r3=[8.37,8,40];
r4=[13.3,6,55];
r5=[21.2,4,70];
r6=[26.7,3,85];
r7=[33.6,2,95];
r8=[42.4,1,110];
r9=[53.49,100,125];
r10=[67.43,200,145];
r11=[85.01,300,165];
r12=[107.2,400,195];
tabla_w=[r1;r2;r3;r4;r5;r6;r7;r8;r9;r10;r11;r12]


%%gonen pag 94
KVA_1_tabla=[5;10;15;25;37.5;50;75;100;167;250;333;500];
KVA_3_tabla=[30;45;75;112.5;150;225;300;500];

if t>=26 & t<=30
    FCT=1;
elseif t>=31 & t<=35
        FCT=.91;
elseif t>=36 & t<=40
    FCT=.82;
elseif t>=41 & t<=45
    FCT=.71;
end
    
if tabla_==1
%%if es condicion y va a tener algun vvalor numerico, verdadero=1, falso=0
%%POTENCiA DEMANDADA EN KILOWATT
%%carga instalada=CI
%%potencia demanda=PD
%%columna=1 numero de elementos, columna=2 consumo por elemento
%%PD=CI*FD, DONDE F0 ES FACTOR DE DEMANDA(.7 Y .8)

%%CI carga instalada o total
CI=sum(tabla(:,1).*tabla(:,2))
elseif tabla_==0
    
    %%INMUEBLE1=VIVIENDA 33W
    if inmueble==1
        CI=area*33
    %%INMUEBLE2= RESTAURANTE 22W
    elseif inmueble==2
        CI=area*22
    %%INMUEBLE3= ESTACIONAMIENTO 6W
    elseif inmueble==3
        CI=area*6
    end
end 

PD=CI*FD
if PD<=5e3
    disp('servicio 1fase,2W,VLN=120V')
    VLN=120;
    Ical=(PD/(VLN*FP))/FCT
    Scal=(4*L*Ical)/(eporciento*VLN)
    disp('Trafo estrella aterrizada estrella aterrizada')
    %%trafo_1 igual a uno, es transformador monofasico, trafo_1 igual a 0 significa no puede ser suministrada por trafo 1
    trafo_1=1;
    trafo_3=1;
    %%estrella estrella aterrizada
    %%disp('no suceptible a ferroresonancia')
    %%disp('cargas monofasicas y trifasicas')
     star_ground_star_ground=1;
     %%estrella aterrizada, delta aterrizada
     %%disp('no es suceptible a ferroresonancia')
     %%disp('cargas trifasicas y pequeñas cargas monofasicas(iluminacion))
     %%disp('puede operar en estrella abierta delta abierta')
     %%disp('3W VLL:240, VLL:480, 4W VLL:240, VLN:480')
     star_ground_delta_ground=1;
     
     %%delta-delta aterrizada
     %%disp('cargas trifasicas y pequeñas cargas monofasicas(iluminacion'))
     %%disp('puede operar en delta abierta delta abierta en caso de falla o crecimiento')
     %%disp(3w VLL:240, VLN:120')
     delta_delta_ground=0;
     
elseif 5e3<PD&PD<=10e3
    disp('servicio 1fase,3W,VLL=240V,VLN=120')
    
    VLL=240;
    VLN=120;
    Ical=(PD/(2*VLN*FP))/FCT
    Scal=(2*L*Ical)/(eporciento*VLN)
    trafo_1=1;
    trafo_3=1;
    %%estrella estrella aterrizada
    star_ground_star_ground=1; 
    star_ground_delta_ground=0;
    
elseif 10e3<PD&PD<=25e3
    disp('servicio 3fase,4W,VLL=240V,VLN=120V')
    
    VLL=240;
    VLN=120;
   Ical=(PD/(3*VLN*FP))/FCT
   Scal=(2*L*Ical)/(eporciento*VLN)
   trafo_1=0;
    trafo_3=1;
    %%estrella estrella aterrizada
    star_ground_star_ground=1;
    star_ground_delta_ground=0;

elseif PD>25e3 
      disp('servicio 3f, 4w, vll:480v, vln:240')
      VLL=480;
      VLN=240;
     Ical=(PD/(3*VLN*FP))*FCT %#ok<*NOPTS>
     Scal=(2*L*Ical)/(eporciento*VLN)
     
   trafo_1=0;
   trafo_3=1
   star_ground_star_ground=1;
   star_ground_delta_ground=1;
   delta_delta_ground=1;
end


renglones=size(tabla_w,1);

for renglon=1:renglones
    s_tabla=tabla_w(renglon,1);
    calibre=tabla_w(renglon,2);
    I_tabla=tabla_w(renglon,3);
   if I_tabla- Ical >= diferencia & Scal<s_tabla
       
       disp('seccion de tabla')
     s_tabla
     disp('calibre sugerido')
     calibre
     disp('correinte de tabla sugerida')
    I_tabla
    break
   end
  
end

%%por seguridad los elementos no se utilizan a mas del 80% de su capacidad
Capacidad_Interruptor=interruptor*ampacidad
%%ceil redondea al entero inmediato superior
Circuitos_Min=ceil(PD/(VLN*Capacidad_Interruptor))

%%Pmax=potencia maxima por circuito
Pmax=Capacidad_Interruptor*VLN

%%desbalance<5%
%%desbalance=((Cmayor-Cmenor)/Cmayor))*100

if PD>5e3
%%TRANSFORMADOR MONOFASICO
KVA_1_cal=(I_tabla*VLL)/1000

%%TRANSFORMADOR DE 3 FASES
KVA_3_cal=(I_tabla*VLL*sqrt(3))/1000

end

renglones=size(KVA_1_tabla,1);
for renglon=1:renglones
    if KVA_1_cal<KVA_1_tabla(renglon,1)
        KVA_1_trafo=KVA_1_tabla(renglon,1)
        break
    end
end

renglones=size(KVA_3_tabla,1);
for renglon=1:renglones
    if KVA_3_cal<KVA_3_tabla(renglon,1)
        KVA_3_trafo=KVA_3_tabla(renglon,1)
        break
    end
end

columnas=size(interruptor_,2);
%%ITAP=umbral para que opere la proteccion
I_TAP=Ical*TAP

for columna=1:columnas
    if I_TAP<interruptor_(1,columna)
        %%%%%%%%%%%%%%interruptor principal
    breaker_principal=interruptor_(1,columna)
        break
    end
    
end

 %%LOS ARMONICOS CAUSAN CALENTAMIENTOS EN LOS CONDUCTORES Y PERDIDAS EN UN TRANSFORMADOR