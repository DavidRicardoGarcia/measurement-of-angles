
clear all;
clc;


theta=-180:0.01:180;
result=zeros(1,4);
result1=zeros(1,4);
result2=zeros(1,4);
y1=zeros(3,length(theta));
cont=1;
cont1=1;
cont2=1;
y1(1,:)=theta;

for i=1:1:length(theta)
y1(2,i)=sind(y1(1,i));
y1(3,i)=cosd(y1(1,i));
end


xi1=10;%rot en z psi 90, -90
xi2=0;%rot en x phi 180, 0
xi3=0;%rot en y theta 180, -90 


xi1a=0;%rot en z psi 180,-10
xi2a=10;%rot en x phi 180,0
xi3a=95;%rot en y theta 180,0

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


pf1=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf2=Mr2*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
pf3=Mr3*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];

Vs=pf1(:,4);%coordenada brazo
Vsa=pf2(:,4);
Vsb=pf3(:,4);
Vsn=[Vs(1)+Vsa(1) Vs(2)+Vsa(2) Vs(3)+Vsa(3)]; %coordenada antebrazo
Vsnn=[Vsn(1)+Vsb(1) Vsn(2)+Vsb(2) Vsn(3)+Vsb(3)]; %coordenada mano

%rotacion del primer segmento por la rotacion en z del segundo segmento

pfz=rottz2*[1 0 0 1;0 1 0 0;0 0 1 0;0 0 0 1]; % rotar el segundo segmento y desplazar en x
Vsz=pfz(:,4); %Coordenadas en x y z
pruebarotz=[Vs(1)+Vsz(1) Vs(2)+Vsz(2) Vs(3)+Vsz(3)]; % ubicar el vector del segundo segmento en el espacio relativo a al primer segmento

%rotacion del primer segmento por la rotacion en z y la rotacion en y del segundo segmento

pfy=rottz2*rotty2*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]; % rotar el segundo segmento y desplazar en x
Vsy=pfy(:,4); %Coordenadas en x y z
pruebaroty=[Vs(1)+Vsy(1) Vs(2)+Vsy(2) Vs(3)+Vsy(3)]; % ubicar el vector del segundo segmento en el espacio relativo a al primer segmento





%-------------Inversa del sistema coordenadas 1----------------

Inv_Mr1=inv(Mr1);

%-------------Inversa del sistema coordenadas 2----------------

Inv_Mr2=inv(Mr2);
%--------------Sistema de referencia 1 con respecto a 2----------------

Mr12=Inv_Mr1*Mr2;

%--------------Sistema de referencia 1 con respecto a 2----------------

Mr23=Inv_Mr2*Mr3;


%y12=asind(-Mr12(3,1));
%y12=-91;

%--------------------------prueba busqueda de angulos------------

f1=0;
j=1;
auxx=0;
auxy=0;
auxz=0;

%VALORES POSIBLES DE Y12
for j=1:1:length(theta)
   
if(abs(y1(2,j)-(-Mr12(3,1)))<0.0001)
 result(1,cont)=round(y1(1,j));
 cont=cont+1;
%j
end 

end

%SACAR VALORES REPETIDOS


%-------SE ENCUENTRA EL VALOR DE Z12
%SE RECORRE CADA VALOR POSIBLE DE Y12
for i=1:1:length(result)

auxy=result(i);    
    
%VALORES POSIBLES DE Z12
for k=1:1:length(theta)

valz=(Mr12(2,1)/cosd(auxy));    

if isnan(valz)
    valz=0;
end

if(abs(y1(2,k)-valz)<0.0001)
 result2(1,cont2)=round(y1(1,k));
 cont2=cont2+1;
 
end 

end


for g=1:1:length(result2)
    
 auxz=result2(g);

%--------Eje coordenado z sistema4-------------


rottzl=[cosd(auxz) -sind(auxz) 0 0;
       sind(auxz) cosd(auxz) 0 0;
       0 0 1 0;
       0 0 0 1];
   
 vpa=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottzl*[1 0 0 1;0 1 0 0;0 0 1 0;0 0 0 1];
 VRR=vpa(:,4); 

if abs(pruebarotz(1)-VRR(1))<0.001 && abs(pruebarotz(2)-VRR(2))<0.001 && abs(pruebarotz(3)-VRR(3))<0.001
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

f1=0;
auxx=0;
auxy=0;
auxz=0;
%--------Eje coordenado z sistema4-------------


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
      
      
 vpb=Mr1*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1]*rottz4*rottyl*[1 0 0 0;0 1 0 0;0 0 1 -1;0 0 0 1];
 VRR=vpb(:,4); 

if abs(pruebaroty(1)-VRR(1))<0.001 && abs(pruebaroty(2)-VRR(2))<0.001 && abs(pruebaroty(3)-VRR(3))<0.001
y12=auxy;
%f1=1;
break;
end

end
 

%--------Eje coordenado y sistema4-------------


rotty4=[cosd(y12) 0 sind(y12) 0;
       0 1 0 0;
       -sind(y12) 0 cosd(y12) 0;
       0 0 0 1];


%------SE ENCUENTRA EL VALOR DE X12
% POSIBLES VALORES DE X12
for T=1:1:length(theta)

valx=(Mr12(3,2)/cosd(y12));    

if isnan(valx)
    valx=0;
end

if(abs(y1(2,T)-valx)<0.0001)
 result1(1,cont2)=round(y1(1,T));
 cont1=cont1+1;
 
end 

end
%SE RECORRE EL VECTOR DE POSIBLES VALORES DE X12 PROBANDO HASTA ENCONTRAR
%EL VALOR INDICADO
for B=1:1:length(result1)
    
 auxx=result1(B);


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

plot3([0 Vs(1)],[0 Vs(2)],[0 Vs(3)],'r');
hold on
plot3([0 1],[0 0],[0 0],'m');
plot3([0 0],[0 1],[0 0],'m');
plot3([0 0],[0 0],[0 1],'m');
plot3([0 Vsa(1)],[0 Vsa(2)],[0 Vsa(3)],'B');
plot3([0 Vsb(1)],[0 Vsb(2)],[0 Vsb(3)],'g');
plot3([0 VRR(1)],[0 VRR(2)],[0 VRR(3)],'black');
plot3([Vs(1) Vsn(1)],[Vs(2) Vsn(2)],[Vs(3) Vsn(3)],'c');
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


