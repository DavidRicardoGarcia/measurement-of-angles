from math import*
import numpy
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def normalize(v, tolerance=0.00001):
    mag2 = sum(n * n for n in v)
    if abs(mag2 - 1.0) > tolerance:
        mag = sqrt(mag2)
        v = tuple(n / mag for n in v)
    return v

def q_mult(q1, q2):
    w1, x1, y1, z1 = q1
    w2, x2, y2, z2 = q2
    w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
    x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
    y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2
    z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2
    return w, x, y, z

def q_conjugate(q):
    w, x, y, z = q
    return (w, -x, -y, -z)

def qv_mult(q1, v1):
    q2 = (0.0,) + v1
    return q_mult(q_mult(q1, q2), q_conjugate(q1))[1:]

def axisangle_to_q(v, theta):
    v = normalize(v)
    x, y, z = v
    theta /= 2
    w = cos(theta)
    x = x * sin(theta)
    y = y * sin(theta)
    z = z * sin(theta)
    return w, x, y, z

def q_to_axisangle(q):
    w, v = q[0], q[1:]
    theta = acos(w) * 2.0
    return normalize(v), theta*180/pi

def quat_inverse(q):
    w, x, y, z = q
    return (w/(w*w+x*x+y*y+z*z), -x/(w*w+x*x+y*y+z*z), -y/(w*w+x*x+y*y+z*z), -z/(w*w+x*x+y*y+z*z))

def quaternion_to_euler(x, y, z, w):

    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + y * y)
    roll = atan2(t0, t1)
    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    pitch = asin(t2)
    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (y * y + z * z)
    yaw = atan2(t3, t4)
    return [yaw*180/pi, pitch*180/pi, roll*180/pi]

def deltaq(q1,q0):
    q = q_mult(quat_inverse(q1), q0)
    return q


qw = []
qx = []
qy = []
qz = []
qw1 = []
qx1 = []
qy1 = []
qz1 = []
dq=[]
TSa=[]
roll=[]
pitch=[]
yaw=[]

a = open('variables.txt', 'r')
max=len(a.readlines())
i=0
a.seek(0)
while i < max-1:

    frame = a.readline()
    ant = frame.split()
    q=(deltaq([float(ant[3]),float(ant[4]),float(ant[5]),float(ant[8])],[float(ant[9]),float(ant[10]),float(ant[11]),float(ant[14])]))
    #cuaternio antebrazo
    qw.append(float(ant[3]))
    qx.append(float(ant[4]))
    qy.append(float(ant[5]))
    qz.append(float(ant[8]))
    #print(q_to_axisangle([qw[i],qx[i],qy[i],qz[i]]))
    #cuaternio mano
    qw1.append(float(ant[9]))
    qx1.append(float(ant[10]))
    qy1.append(float(ant[11]))
    qz1.append(float(ant[14]))
    eul=quaternion_to_euler(q[1], q[2], q[3], q[0])
    yaw.append(eul[0])
    pitch.append(eul[1])
    roll.append(eul[2])
    #print(quaternion_to_euler(q[1],q[2],q[3],q[0]))
    TSa.append(i * 0.01)
    i=i+1
print(max)

ti = 0
grabar = ""

f = open("data.txt", 'w')
while (ti < len(roll)):
    grabar = str(yaw[ti])+" "+str(pitch[ti])+" "+str(roll[ti])\
             +" "+str(qw[ti])+" "+str(qx[ti])+" "+str(qy[ti])+" "+str(qz[ti])\
             +" "+str(qw1[ti])+" "+str(qx1[ti])+" "+str(qy1[ti])+" "+str(qz1[ti])+" "+"\n"

    f.write(grabar)
    #f.write('\n')

    ti += 1


f.close()

'''
fig = plt.figure()
plt.subplot(2, 2, 1)
plt.plot(TSa, roll)
plt.title('roll')


plt.subplot(2, 2, 2)
plt.plot(TSa, pitch)
plt.title('pitch')
plt.xlabel('time (s)')


plt.subplot(2, 2, 3)
plt.plot(TSa, yaw)
plt.title('yaw')

plt.subplot(2, 2, 4)
plt.plot(TSa, dq[3])
plt.title('z')



plt.show()
'''