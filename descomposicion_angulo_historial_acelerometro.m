% el eje de rotacion x del sensor es el eje z del ideal
% el eje de rotacion y del sensor es el eje x del ideal
% el eje de rotacion z del sensor es el eje y del ideal

%x y z sensor antebrazo
%x1 y1 z1 sensor mano
%x2 y2 z2 sensor bicep
% clear all;
% clc;

%mano
velx=gx;
vely=gy;
velz=gz;

%antebrazo
velx1=gx1;
vely1=gy1;
velz1=gz1;


%bicep
velx2=gx2;
vely2=gy2;
velz2=gz2;


thetax=0;
thetay=0;
thetaz=0;


thetax1=0;
thetay1=0;
thetaz1=0;


thetax2=0;
thetay2=0;
thetaz2=0;

x12=zeros(1,length(velx));
y12=zeros(1,length(velx));
z12=zeros(1,length(velx));
x23=zeros(1,length(velx));
y23=zeros(1,length(velx));
z23=zeros(1,length(velx));

VRR=zeros(1,3,length(velx));

txaux=0;
tyaux=0;
tzaux=0;

txaux1=0;
tyaux1=0;
tzaux1=0;

txaux2=zeros(1,length(velx));
tyaux2=zeros(1,length(velx));
tzaux2=zeros(1,length(velx));

xaux=0;
yaux=0;
zaux=0;

xaux1=0;
yaux1=0;
zaux1=0;
%cambiar la dimension del for de acuerdo al tamaño del array
for i=1:1:length(velx)

 
 %---antebrazo   
    
 thetax=velx(i,2)*0.01*0.5114;
 
 thetay=vely(i,2)*0.01*0.5114;
 
 thetaz=velz(i,2)*0.01*0.5114;
 
 %---mano
 thetax1=velx1(i,2)*0.01*0.5114;
 
 thetay1=vely1(i,2)*0.01*0.5114;
 
 thetaz1=velz1(i,2)*0.01*0.5114;
 
 %---bicep
 thetax2=velx2(i,2)*0.01*0.5114;
 
 thetay2=vely2(i,2)*0.01*0.5114;
 
 thetaz2=velz2(i,2)*0.01*0.5114;
 thetax2=0;%velx2(i,2)*0.01*0.5114;
 
 thetay2=0;%vely2(i,2)*0.01*0.5114;
 
 thetaz2=0;%velz2(i,2)*0.01*0.5114;
 
%bicep
xi1=0+thetax2;%rot en z psi
xi2=0+thetay2;%rot en x phi
xi3=0+thetaz2;%rot en y theta

%antebrazo
xi1a=0+thetax;%rot en z psi 
xi2a=0+thetay;%rot en x phi 
xi3a=0+thetaz;%rot en y theta

%mano
xi1b=0+thetax1;%rot en z psi 
xi2b=0+thetay1;%rot en x phi 
xi3b=0+thetaz1;%rot en y theta

txaux=thetax+txaux;
tyaux=thetay+tyaux;
tzaux=thetaz+tzaux;

txaux1=thetax1+txaux1;
tyaux1=thetay1+tyaux1;
tzaux1=thetaz1+tzaux1;

txaux2(1,i)=thetax2+txaux2(1,i);
tyaux2(1,i)=thetay2+tyaux2(1,i);
tzaux2(1,i)=thetaz2+tzaux2(1,i);
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
Mr3=rottz3*rotty3*rottx3;%gR3

% pf1=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
% pf2=Mr2*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
% pf3=Mr3*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
% 
% Vs=pf1(:,4);
% Vsa=pf2(:,4);
% Vsb=pf3(:,4);
% Vsn=[Vs(1)+Vsa(1) Vs(2)+Vsa(2) Vs(3)+Vsa(3)];
% Vsnn=[Vsn(1)+Vsb(1) Vsn(2)+Vsb(2) Vsn(3)+Vsb(3)];
%-------------Inversa del sistema coordenadas 1----------------

Inv_Mr1=inv(Mr1);%1Rg

%-------------Inversa del sistema coordenadas 2----------------

Inv_Mr2=inv(Mr2);%2Rg
%--------------Sistema de referencia 1 con respecto a 2----------------

Mr12=Inv_Mr1*Mr2;%1Rg*gR2=1R2

%--------------Sistema de referencia 1 con respecto a 2----------------

Mr23=Inv_Mr2*Mr3;%2Rg*gR3=2R3


% [ cos(y)*cos(z), cos(z)*sin(x)*sin(y) - cos(x)*sin(z), sin(x)*sin(z) + cos(x)*cos(z)*sin(y)]
% [ cos(y)*sin(z), cos(x)*cos(z) + sin(x)*sin(y)*sin(z), cos(x)*sin(y)*sin(z) - cos(z)*sin(x)]
% [       -sin(y),                        cos(y)*sin(x),                        cos(x)*cos(y)]
%  

y12(1,i)=asind(-Mr12(3,1));
x12(1,i)=asind(Mr12(3,2)/cosd(y12(1,i)));
z12(1,i)=asind(Mr12(2,1)/cosd(y12(1,i)));

if isnan(Mr12(3,2)/cosd(y12(1,i)))
    x12=0;
end
if isnan(-Mr12(3,1))
    y12=0;
end
if isnan(Mr12(2,1)/cosd(y12(1,i)))
    z12=0;
end


y23(1,i)=asind(-Mr23(3,1));
x23(1,i)=asind(Mr23(3,2)/cosd(y23(1,i)));
z23(1,i)=asind(Mr23(2,1)/cosd(y23(1,i)));

if isnan(Mr23(3,2)/cosd(y23(1,i)))
    x23=0;
end
if isnan(-Mr23(3,1))
    y23=0;
end
if isnan(Mr23(2,1)/cosd(y23(1,i)))
    z23=0;
end


    
x12(1,i)=x12(1,i)+xaux;
y12(1,i)=y12(1,i)+yaux;
z12(1,i)=z12(1,i)+zaux;


z23(1,i)=z23(1,i)+zaux1;
x23(1,i)=x23(1,i)+xaux1;
y23(1,i)=y23(1,i)+yaux1;




xaux=x12(1,i);
yaux=y12(1,i);
zaux=z12(1,i);
xaux1=x23(1,i);
yaux1=y23(1,i);
zaux1=z23(1,i);
end

%-----------------reconstruccion del modelo---------------

%--------Eje coordenado z sistema1-------------



rottz1=[cosd(tzaux) -sind(tzaux) 0 0;
       sind(tzaux) cosd(tzaux) 0 0;
       0 0 1 0;
       0 0 0 1];

%--------Eje coordenado x sistema1-------------


rottx1=[1 0 0 0;
       0 cosd(txaux) -sind(txaux) 0;
       0 sind(txaux) cosd(txaux) 0;
       0 0 0 1];
%--------Eje coordenado y sistema1-------------


   
rotty1=[cosd(tyaux) 0 sind(tyaux) 0;
       0 1 0 0;
       -sind(tyaux) 0 cosd(tyaux) 0;
       0 0 0 1];


%--------Eje coordenado z sistema4-------------


rottz4=[cosd(zaux) -sind(zaux) 0 0;
       sind(zaux) cosd(zaux) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema4-------------
%xaux=xaux+90;

rottx4=[1 0 0 0;
       0 cosd(xaux) -sind(xaux) 0;
       0 sind(xaux) cosd(xaux) 0;
       0 0 0 1];

%--------Eje coordenado y sistema4-------------


rotty4=[cosd(yaux) 0 sind(yaux) 0;
       0 1 0 0;
       -sind(yaux) 0 cosd(yaux) 0;
       0 0 0 1];

%--------Eje coordenado z sistema4-------------


rottz5=[cosd(zaux1) -sind(zaux1) 0 0;
       sind(zaux1) cosd(zaux1) 0 0;
       0 0 1 0;
       0 0 0 1];


%--------Eje coordenado x sistema4-------------

%xaux1=xaux1+0;
rottx5=[1 0 0 0;
       0 cosd(xaux1) -sind(xaux1) 0;
       0 sind(xaux1) cosd(xaux1) 0;
       0 0 0 1];

%--------Eje coordenado y sistema4-------------

%yaux1=180;
rotty5=[cosd(yaux1) 0 sind(yaux1) 0;
       0 1 0 0;
       -sind(yaux1) 0 cosd(yaux1) 0;
       0 0 0 1];

   
MRR=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rotty4*rottx4*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz5*rotty5*rottx5*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];


VRR(:,:,i)=[MRR(1,4) MRR(2,4) MRR(3,4)];
   
   
 X(:,1)=t;
 Y(:,1)=t;
 Z(:,1)=t;

 X12(:,1)=t;
 Y12(:,1)=t;
 Z12(:,1)=t;

 X23(:,1)=t;
 Y23(:,1)=t;
 Z23(:,1)=t;
   
 X(:,2)=txaux2';
 Y(:,2)=tyaux2';
 Z(:,2)=tzaux2';

 X12(:,2)=x12';
 Y12(:,2)=y12';
 Z12(:,2)=z12';

 X23(:,2)=x23';
 Y23(:,2)=y23';
 Z23(:,2)=z23'; 
 

 

Mr1=rottz1*rotty1*rottx1;%gR1
Mr12a=rottz4*rotty4*rottx4;%1R2
Mr23a=rottz5*rotty5*rottx5;%2R3

pf1=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf2=Mr12a*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf3=Mr23a*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

AB=pf1*pf2;
MA=pf1*pf2*pf3;


Vs=pf1(:,4);
Vsa=AB(:,4);
Vsb=MA(:,4);
Vsn=[Vs(1)+Vsa(1) Vs(2)+Vsa(2) Vs(3)+Vsa(3)];
Vsnn=[Vsn(1)+Vsb(1) Vsn(2)+Vsb(2) Vsn(3)+Vsb(3)];

plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'r');
hold on
plot3([0 1],[0 0],[0 0],'m');
plot3([0 0],[0 1],[0 0],'m');
plot3([0 0],[0 0],[0 1],'m');
plot3([0 Vsa(1)],[0 Vsa(2)],[0 Vsa(3)],'B');
%plot3([0 Vsb(1)],[0 Vsb(2)],[0 Vsb(3)],'g');
%plot3([0 VRR(1,1,length(VRR))],[0 VRR(1,2,length(VRR))],[0 VRR(1,3,length(VRR))],'black');
plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
plot3([Vsn(1) Vsnn(1)],[Vsn(2) Vsnn(2)],[Vsn(3) Vsnn(3)],'black');
grid on
axis on

xlabel('eje_x');
ylabel('eje_y');
zlabel('eje_z');

