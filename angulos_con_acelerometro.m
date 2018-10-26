

thetaxac=zeros(length(ax),2);

thetayac=zeros(length(ax),2);

thetazac=zeros(length(ax),2);



thetaxac1=zeros(length(ax),2);

thetayac1=zeros(length(ax),2);

thetazac1=zeros(length(ax),2);


thetaxac2=zeros(length(ax),2);

thetayac2=zeros(length(ax),2);

thetazac2=zeros(length(ax),2);





for i=1:1:length(ax)


thetaxac(i,2)=(180/pi)*atan2(ax(i,2),sqrt(ay(i,2)^2+az(i,2)^2));

thetayac(i,2)=(180/pi)*atan2(ay(i,2),sqrt(ax(i,2)^2+az(i,2)^2));

thetazac(i,2)=(180/pi)*atan2(sqrt(ax(i,2)^2+ay(i,2)^2),az(i,2));

thetaxac1(i,2)=(180/pi)*atan2(ax1(i,2),sqrt(ay1(i,2)^2+az1(i,2)^2));

thetayac1(i,2)=(180/pi)*atan2(ay1(i,2),sqrt(ax1(i,2)^2+az1(i,2)^2));

thetazac1(i,2)=(180/pi)*atan2(sqrt(ax1(i,2)^2+ay1(i,2)^2),az1(i,2));

thetaxac2(i,2)=(180/pi)*atan2(ax2(i,2),sqrt(ay2(i,2)^2+az2(i,2)^2));

thetayac2(i,2)=(180/pi)*atan2(ay2(i,2),sqrt(ax2(i,2)^2+az2(i,2)^2));

thetazac2(i,2)=(180/pi)*atan2(sqrt(ax2(i,2)^2+ay2(i,2)^2),az2(i,2));

end

thetaxac(:,1)=t';
thetayac(:,1)=t';
thetazac(:,1)=t';
thetaxac1(:,1)=t';
thetayac1(:,1)=t';
thetazac1(:,1)=t';
thetaxac2(:,1)=t';
thetayac2(:,1)=t';
thetazac2(:,1)=t';



