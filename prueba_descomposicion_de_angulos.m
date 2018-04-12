
clear all;
clc;

xi1=0;%rot en z psi
xi2=0;%rot en x phi
xi3=-45;%rot en y theta


xi1a=0;%rot en z psi 
xi2a=-45;%rot en x phi 
xi3a=-90;%rot en y theta

xi1b=0;%rot en z psi 
xi2b=0;%rot en x phi 
xi3b=-90;%rot en y theta


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

pf1=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf2=Mr2*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf3=Mr3*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

Vs=pf1(:,4);
Vsa=pf2(:,4);
Vsb=pf3(:,4);
Vsn=[Vs(1)+Vsa(1) Vs(2)+Vsa(2) Vs(3)+Vsa(3)];
Vsnn=[Vsn(1)+Vsb(1) Vsn(2)+Vsb(2) Vsn(3)+Vsb(3)];
%-------------Inversa del sistema coordenadas 1----------------

Inv_Mr1=inv(Mr1);

%-------------Inversa del sistema coordenadas 2----------------

Inv_Mr2=inv(Mr2);
%--------------Sistema de referencia 1 con respecto a 2----------------

Mr12=Inv_Mr1*Mr2;

%--------------Sistema de referencia 1 con respecto a 2----------------

Mr23=Inv_Mr2*Mr3;


% [ cos(y)*cos(z), cos(z)*sin(x)*sin(y) - cos(x)*sin(z), sin(x)*sin(z) + cos(x)*cos(z)*sin(y)]
% [ cos(y)*sin(z), cos(x)*cos(z) + sin(x)*sin(y)*sin(z), cos(x)*sin(y)*sin(z) - cos(z)*sin(x)]
% [       -sin(y),                        cos(y)*sin(x),                        cos(x)*cos(y)]
%  

y12=asind(-Mr12(3,1));
x12=asind(Mr12(3,2)/cosd(y12));
z12=asind(Mr12(2,1)/cosd(y12));

y23=asind(-Mr23(3,1));
x23=asind(Mr23(3,2)/cosd(y23));
z23=asind(Mr23(2,1)/cosd(y23));

%-----------------reconstruccion del modelo---------------

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

%--------Eje coordenado z sistema4-------------


rottz5=[cosd(z23) -sind(z23) 0 0;
       sind(z23) cosd(z23) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema4-------------


rottx5=[1 0 0 0;
       0 cosd(x23) -sind(x23) 0;
       0 sind(x23) cosd(x23) 0;
       0 0 0 1];

%--------Eje coordenado y sistema4-------------


rotty5=[cosd(y23) 0 sind(y23) 0;
       0 1 0 0;
       -sind(y23) 0 cosd(y23) 0;
       0 0 0 1];

   
   
MRR=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rotty4*rottx4*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz5*rotty5*rottx5*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

VRR=MRR(:,4);

plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'r');
hold on
plot3([0 1],[0 0],[0 0],'m');
plot3([0 0],[0 1],[0 0],'m');
plot3([0 0],[0 0],[0 1],'m');
plot3([0 Vsa(1)],[0 Vsa(2)],[0 Vsa(3)],'B');
plot3([0 Vsb(1)],[0 Vsb(2)],[0 Vsb(3)],'g');
plot3([0 VRR(1)],[0 VRR(2)],[0 VRR(3)],'black');
plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
plot3([Vsn(1) Vsnn(1)],[Vsn(2) Vsnn(2)],[Vsn(3) Vsnn(3)],'y');
grid on
axis on

xlabel('eje_x');
ylabel('eje_y');
zlabel('eje_z');


