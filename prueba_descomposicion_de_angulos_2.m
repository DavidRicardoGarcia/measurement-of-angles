
clear all;
clc;


theta=-360:0.01:360;
result=zeros(1,4);
result1=zeros(1,4);
result2=zeros(1,4);
y1=zeros(3,length(theta));
cont=1;
cont1=1;
cont2=1;
y1(1,:)=theta;

for i=1:1:length(theta)
y1(2,i)=round(1000*sind(y1(1,i)));
y1(3,i)=cosd(y1(1,i));
end

z12=0;
y12=0;
x12=0;

xi1=0;%rot en z psi 90, -90
xi2=0;%rot en x phi 180, 0
xi3=90;%rot en y theta 180, -90 


xi1a=90;%rot en z psi 180,-10
xi2a=0;%rot en x phi 180,0
xi3a=190;%rot en y theta 180,0

xi1b=0;%rot en z psi 10 , -90
xi2b=0;%rot en x phi 10 , -90
xi3b=0;%rot en y theta 90,-90


%--------Eje coordenado z sistema1-------------



rottz1=[cosd(xi1) -sind(xi1) 0 0;
       sind(xi1) cosd(xi1) 0 0;
       0 0 1 0;
       0 0 0 1];

%--------Eje coordenado x sistema1-------------


rottx1=[1 0 0 0;
       0 cosd(xi2) -sind(xi2) 0;
       0 sind(xi2) cosd(xi2) 0;
       0 0 0 1];
%--------Eje coordenado y sistema1-------------


   
rotty1=[cosd(xi3) 0 sind(xi3) 0;
       0 1 0 0;
       -sind(xi3) 0 cosd(xi3) 0;
       0 0 0 1];

%--------Eje coordenado z sistema2-------------


rottz2=[cosd(xi1a) -sind(xi1a) 0 0;
       sind(xi1a) cosd(xi1a) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema2-------------


rottx2=[1 0 0 0;
       0 cosd(xi2a) -sind(xi2a) 0;
       0 sind(xi2a) cosd(xi2a) 0;
       0 0 0 1];

%--------Eje coordenado y sistema2-------------


rotty2=[cosd(xi3a) 0 sind(xi3a) 0;
       0 1 0 0;
       -sind(xi3a) 0 cosd(xi3a) 0;
       0 0 0 1];

%--------Eje coordenado z sistema3-------------


rottz3=[cosd(xi1b) -sind(xi1b) 0 0;
       sind(xi1b) cosd(xi1b) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema3-------------


rottx3=[1 0 0 0;
       0 cosd(xi2b) -sind(xi2b) 0;
       0 sind(xi2b) cosd(xi2b) 0;
       0 0 0 1];

%--------Eje coordenado y sistema3-------------


rotty3=[cosd(xi3b) 0 sind(xi3b) 0;
       0 1 0 0;
       -sind(xi3b) 0 cosd(xi3b) 0;
       0 0 0 1];
      
      
   
%------------Matrices de rotacion segun tait bryan------------------

Mr1=rottz1*rotty1*rottx1;%gR1
Mr2=rottz2*rotty2*rottx2;%gR2
Mr3=rottz3*rotty3*rottx3;


pf1=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1];
pf2=Mr2*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1];
pf3=Mr3*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1];

Vs=pf1(:,4);%coordenada brazo
Vsa=pf2(:,4);
Vsb=pf3(:,4);
Vsn=[Vs(1)+Vsa(1) Vs(2)+Vsa(2) Vs(3)+Vsa(3)]; %coordenada antebrazo
Vsnn=[Vsn(1)+Vsb(1) Vsn(2)+Vsb(2) Vsn(3)+Vsb(3)]; %coordenada mano

%rotacion del primer segmento por la rotacion en z del segundo segmento

pfz=rottz2*[1 0 0 1000;0 1 0 0;0 0 1 0;0 0 0 1]; % rotar el segundo segmento y desplazar en x
Vsz=pfz(:,4); %Coordenadas en x y z
pruebarotz=[Vs(1)+Vsz(1) Vs(2)+Vsz(2) Vs(3)+Vsz(3)]; % ubicar el vector del segundo segmento en el espacio relativo a al primer segmento

%rotacion del primer segmento por la rotacion en z y la rotacion en y del segundo segmento

pfy=rottz2*rotty2*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1]; % rotar el segundo segmento y desplazar en x
Vsy=pfy(:,4); %Coordenadas en x y z
pruebaroty=[Vs(1)+Vsy(1) Vs(2)+Vsy(2) Vs(3)+Vsy(3)]; % ubicar el vector del segundo segmento en el espacio relativo a al primer segmento

% plot3([0 1000],[0 0],[0 0],'m');
% hold on
% plot3([0 0],[0 1000],[0 0],'m');
% plot3([0 0],[0 0],[0 1000],'m');
% 
% plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'m');
% 
% plot3([0 Vsn(1)],[0 Vsn(2)],[0 Vsn(3)],'black');
% 
% plot3([Vs(1) pruebaroty(1)],[Vs(2) pruebaroty(2)],[Vs(3) pruebaroty(3)],'r');
% 
% grid on
% axis on
% 
% xlabel('eje_x');
% ylabel('eje_y');
% zlabel('eje_z');

%plot3([0 pruebarotz(1)],[0 pruebarotz(2)],[0 pruebarotz(3)],'r');



%-------------Inversa del sistema coordenadas 1----------------

Inv_Mr1=inv(Mr1);

%-------------Inversa del sistema coordenadas 2----------------

Inv_Mr2=inv(Mr2);
%--------------Sistema de referencia 1 con respecto a 2----------------

Mr12=Inv_Mr1*Mr2;

%--------------Sistema de referencia 1 con respecto a 2----------------

Mr23=Inv_Mr2*Mr3;



y12=asind(-Mr12(3,1));
x12=asind(Mr12(3,2)/cosd(y12));
if isnan(x12)
    x12=0;
end
z12=asind(Mr12(2,1)/cosd(y12));
if isnan(z12)
    z12=0;
end
%--------------------------prueba busqueda de angulos------------

ki=0;
%--------Eje coordenado z sistema4-------------


rottz4=[cosd(z12) -sind(z12) 0 0;
       sind(z12) cosd(z12) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema4-------------


rottx4=[1 0 0 0;
       0 cosd(x12) -sind(x12) 0;
       0 sind(x12) cosd(x12) 0;
       0 0 0 1];

%--------Eje coordenado y sistema4-------------


rotty4=[cosd(y12) 0 sind(y12) 0;
       0 1 0 0;
       -sind(y12) 0 cosd(y12) 0;
       0 0 0 1];
op=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rotty4*rottx4*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

VRR=op(:,4); 

if abs(Vsn(1)-VRR(1))<0.001 && abs(Vsn(2)-VRR(2))<0.001 && abs(Vsn(3)-VRR(3))<0.001
ki=1;

end

%------------------------------------------

if ki==0
f1=0;
j=1;
auxx=0;
auxy=0;
auxz=0;
cont=1;
%VALORES POSIBLES DE Y12
  
valy=round(-1000*Mr12(3,1));
if asind(-Mr12(3,1))<1 && asind(-Mr12(3,1))>-1
    valy=0;
end 
[a,b]=find(y1(2,:)==valy);
result=round(y1(1,b));
   
%     
% if(abs(y1(2,j)-(valy))<0.001) && round(y1(1,j))<=180 && round(y1(1,j))>=-180
% 
% result(1,cont)=round(y1(1,j));
% cont=cont+1;
% 
% end 

%SACAR VALORES REPETIDOS
k=1;

while k<=length(result)
[el,rep]=find(result==result(k));
rep(1)=[];
result(rep)=[];
k=k+1;
end

%-------SE ENCUENTRA EL VALOR DE Z12
%SE RECORRE CADA VALOR POSIBLE DE Y12
for i=1:1:length(result)

auxy=result(i);    
 
%VALORES POSIBLES DE Z12

valz=round(1000*Mr12(2,1)/cosd(auxy));
if asind(Mr12(2,1)/cosd(auxy))<1 && asind(Mr12(2,1)/cosd(auxy))>-1
    valz=0;
end 
[c,d]=find(y1(2,:)==valz);
result2=round(y1(1,d));


v=1;

while v<=length(result2)
[el2,rep2]=find(result2==result2(v));
rep2(1)=[];
result2(rep2)=[];
v=v+1;
end

for g=1:1:length(result2)
    
auxz=result2(g);
%auxz=-220;
%--------Eje coordenado z sistema4-------------


rottzl=[cosd(auxz) -sind(auxz) 0 0;
       sind(auxz) cosd(auxz) 0 0;
       0 0 1 0;
       0 0 0 1];
   
 vpa=pf1*rottzl*[1 0 0 1000;0 1 0 0;0 0 1 0;0 0 0 1];
 VRR=vpa(:,4); 
abs(pruebarotz(1)-VRR(1))<50
abs(pruebarotz(2)-VRR(2))<50 
abs(pruebarotz(3)-VRR(3))<50

if abs(pruebarotz(1)-VRR(1))<50 &&  abs(pruebarotz(2)-VRR(2))<50 && abs(pruebarotz(3)-VRR(3))<50
z12=auxz;
f1=1;
break;
end

end

if f1==1
break;    
end   



end
%-------------------------------
figure
plot3([0 1],[0 0],[0 0],'m');
hold on
plot3([0 0],[0 1],[0 0],'m');
plot3([0 0],[0 0],[0 1],'m');
plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'m');
plot3([0 Vsz(1)],[0 Vsz(2)],[0 Vsz(3)],'b');
plot3([0 VRR(1)],[0 VRR(2)],[0 VRR(3)],'black');
plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
plot3([Vs(1) pruebarotz(1)],[Vs(2) pruebarotz(2)],[Vs(3) pruebarotz(3)],'r');
grid on
axis on
xlabel('eje_x');
ylabel('eje_y');
zlabel('eje_z');

auxx=0;
auxy=0;
auxz=0;
%--------Eje coordenado z sistema4-------------

% z12=-45;
rottz4=[cosd(z12) -sind(z12) 0 0;
       sind(z12) cosd(z12) 0 0;
       0 0 1 0;
       0 0 0 1];

%------SE ENCUENTRA EL VALOR DE Y12
%SE RECORRE EL VECTOR DE POSIBLES VALORES DE Y12 PROBANDO HASTA ENCONTRAR
%EL VALOR INDICADO
for u=1:1:length(result)
    
 auxy=result(u);

%--------Eje coordenado y sistema3-------------


rottyl=[cosd(auxy) 0 sind(auxy) 0;
       0 1 0 0;
       -sind(auxy) 0 cosd(auxy) 0;
       0 0 0 1];
      
      
 vpb=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1]*rottz4*rottyl*[1 0 0 0;0 1 0 0;0 0 1 -1000;0 0 0 1];
 VRR=vpb(:,4); 

 abs(pruebaroty(1)-VRR(1))<50
 abs(pruebaroty(2)-VRR(2))<50
 abs(pruebaroty(3)-VRR(3))<50
 
if abs(pruebaroty(1)-VRR(1))<50 && abs(pruebaroty(2)-VRR(2))<50 && abs(pruebaroty(3)-VRR(3))<50
y12=auxy;
%f1=1;
break;
end

end
 

figure
plot3([0 1000],[0 0],[0 0],'m');
hold on
plot3([0 0],[0 1000],[0 0],'m');
plot3([0 0],[0 0],[0 1000],'m');
plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'m');
plot3([0 VRR(1)],[0 VRR(2)],[0 VRR(3)],'black');
plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
plot3([Vs(1) pruebaroty(1)],[Vs(2) pruebaroty(2)],[Vs(3) pruebaroty(3)],'r');
grid on
axis on
xlabel('eje_x');
ylabel('eje_y');
zlabel('eje_z');


%--------Eje coordenado y sistema4-------------
% y12=-90;

rotty4=[cosd(y12) 0 sind(y12) 0;
       0 1 0 0;
       -sind(y12) 0 cosd(y12) 0;
       0 0 0 1];


%------SE ENCUENTRA EL VALOR DE X12
% POSIBLES VALORES DE X12
cont1=1;
for T=1:1:length(theta)

valx=(Mr12(3,2)/cosd(y12));    

if isnan(valx)
    valx=0;
end

if(abs(y1(2,T)-valx)<0.0001) && round(y1(1,T))<180 && round(y1(1,T))>-180
 result1(1,cont1)=round(y1(1,T));
 cont1=cont1+1;
 
end 

end

%SACAR VALORES REPETIDOS
f=1;

while f<=length(result1)
[el1,rep1]=find(result1==result1(f));
rep1(1)=[];
result1(rep1)=[];
f=f+1;
end


%SE RECORRE EL VECTOR DE POSIBLES VALORES DE X12 PROBANDO HASTA ENCONTRAR
%EL VALOR INDICADO
for B=1:1:length(result1)
    
 auxx=result1(B);
%  auxx=60;

%--------Eje coordenado x sistema4-------------


rottx4=[1 0 0 0;
       0 cosd(auxx) -sind(auxx) 0;
       0 sind(auxx) cosd(auxx) 0;
       0 0 0 1]; 
   
 vpc=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rotty4*rottx4*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
 VRR=vpc(:,4); 

if abs(Vsn(1)-VRR(1))<0.001 && abs(Vsn(2)-VRR(2))<0.001 && abs(Vsn(3)-VRR(3))<0.001
x12=auxx;
%f1=1;
break;
end

end
end
%-------------------------------------------------------------------

% y23=asind(-Mr23(3,1));
% x23=asind(Mr23(3,2)/cosd(y23));
% if isnan(x23)
%     x23=0;
% end
% z23=asind(Mr23(2,1)/cosd(y23));
% if isnan(z23)
%     z23=0;
% end



% a=[ cosd(y12)*cosd(z12), cosd(z12)*sind(x12)*sind(y12) - cosd(x12)*sind(z12), sind(x12)*sind(z12) + cosd(x12)*cosd(z12)*sind(y12)];
% b=[ cosd(y12)*sind(z12), cosd(x12)*cosd(z12) + sind(x12)*sind(y12)*sind(z12), cosd(x12)*sind(y12)*sind(z12) - cosd(z12)*sind(x12)];
% c=[       -sind(y12),                        cosd(y12)*sind(x12),                        cosd(x12)*cosd(y12)];
%  
% if Vsa(1)>=0
% x12=+abs(x12);
% else
% x12=-abs(x12);
% end
% 
% if Vsa(2)>=0
% y12=+abs(y12);
% else
% y12=-abs(y12);
% end
% 
% if Vsa(3)>=0
% z12=+abs(z12);
% else
% z12=-abs(z12);
% end
% 
% 
% if Vsb(1)>=0
% x23=+abs(x23);
% else
% x23=-abs(x23);
% end
% 
% if Vsb(2)>=0
% y23=+abs(y23);
% else
% y23=-abs(y23);
% end
% 
% if Vsb(3)>=0
% z23=+abs(z23);
% else
% z23=-abs(z23);
% end
% 

%-----------------reconstruccion del modelo---------------

%--------Eje coordenado z sistema4-------------
% 
% 
% rottz4=[cosd(z12) -sind(z12) 0 0;
%        sind(z12) cosd(z12) 0 0;
%        0 0 1 0;
%        0 0 0 1];
% 
% 
% %--------Eje coordenado x sistema4-------------
% 
% 
% rottx4=[1 0 0 0;
%        0 cosd(x12) -sind(x12) 0;
%        0 sind(x12) cosd(x12) 0;
%        0 0 0 1];
% 
% %--------Eje coordenado y sistema4-------------
% 
% 
% rotty4=[cosd(y12) 0 sind(y12) 0;
%        0 1 0 0;
%        -sind(y12) 0 cosd(y12) 0;
%        0 0 0 1];

%--------Eje coordenado z sistema4-------------

% 
% rottz5=[cosd(z23) -sind(z23) 0 0;
%        sind(z23) cosd(z23) 0 0;
%        0 0 1 0;
%        0 0 0 1];
% 
% 
% %--------Eje coordenado x sistema4-------------
% 
% 
% rottx5=[1 0 0 0;
%        0 cosd(x23) -sind(x23) 0;
%        0 sind(x23) cosd(x23) 0;
%        0 0 0 1];
% 
% %--------Eje coordenado y sistema4-------------
% 
% 
% rotty5=[cosd(y23) 0 sind(y23) 0;
%        0 1 0 0;
%        -sind(y23) 0 cosd(y23) 0;
%        0 0 0 1];
% 
%    
   
%MRR=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rotty4*rottx4*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];%*rottz5*rotty5*rottx5*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

%VRR=MRR(:,4);

pp=acosd(dot(Vs,Vsa)/(norm(Vs)*norm(Vsa)));

% figure
% plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'r');
% hold on
% plot3([0 1],[0 0],[0 0],'m');
% plot3([0 0],[0 1],[0 0],'m');
% plot3([0 0],[0 0],[0 1],'m');
% %plot3([0 Vsa(1)],[0 Vsa(2)],[0 Vsa(3)],'B');
% %plot3([0 Vsb(1)],[0 Vsb(2)],[0 Vsb(3)],'g');
% plot3([0 VRR(1)],[0 VRR(2)],[0 VRR(3)],'black');
% plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
%plot3([Vsn(1) Vsnn(1)],[Vsn(2) Vsnn(2)],[Vsn(3) Vsnn(3)],'y');

% for n=1:1:length(X12)
%    
% 
% rottzi=[cosd(Z12(1,n)) -sind(Z12(1,n)) 0 0;
%        sind(Z12(1,n)) cosd(Z12(1,n)) 0 0;
%        0 0 1 0;
%        0 0 0 1];
% 
% rottxi=[1 0 0 0;
%        0 cosd(X12(1,n)) -sind(X12(1,n)) 0;
%        0 sind(X12(1,n)) cosd(X12(1,n)) 0;
%        0 0 0 1];
% 
% rottyi=[cosd(Y12(1,n)) 0 sind(Y12(1,n)) 0;
%        0 1 0 0;
%        -sind(Y12(1,n)) 0 cosd(Y12(1,n)) 0;
%        0 0 0 1];
%     
% MRRI=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottzi*rottyi*rottxi*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];%*rottz5*rotty5*rottx5*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
% VRRI=MRRI(:,4);    
% plot3([0 VRRI(1)],[0 VRRI(2)],[0 VRRI(3)],'black');
% 
% end

grid on
axis on

xlabel('eje_x');
ylabel('eje_y');
zlabel('eje_z');


