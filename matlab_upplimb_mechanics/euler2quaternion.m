fi = 0;
theta = pi/2;
psi = 0;
% funcion que pasa de una rotacion en angulos euler a 
% quaternion.

% se calculan cada una de las cuatro componentes del cuternion
r = cos(fi/2)*cos(theta/2)*cos(psi/2) + sin(fi/2)*sin(theta/2)*sin(psi/2);
i = sin(fi/2)*cos(theta/2)*cos(psi/2) - cos(fi/2)*sin(theta/2)*sin(psi/2);
j = cos(fi/2)*sin(theta/2)*cos(psi/2) + sin(fi/2)*cos(theta/2)*sin(psi/2);
k = cos(fi/2)*cos(theta/2)*sin(psi/2) - sin(fi/2)*sin(theta/2)*cos(psi/2);


q = [r i j k]
