%x=0.0035;

theta=-360:0.1:360;
result=zeros(1,4);
y1=zeros(2,length(theta));
 cont=1;
y1(1,:)=theta;

for i=1:1:length(theta)
y1(2,i)=sind(y1(1,i));
end

for j=1:1:length(theta)
    
if(abs(y1(2,j)-x)<0.001)
 y1(2,j)   
 result(1,cont)=y1(1,j);
 cont=cont+1;
end 

end

