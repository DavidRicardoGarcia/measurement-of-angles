ax_v = []
ay_v = []
az_v = []
qw = []
qx = []
qy = []
qz = []
sEMG_v = []
sMMG_v = []
qw1 = []
qx1 = []
qy1 = []
qz1 = []
sEMG_b2_v = []
sMMG_b2_v = []
TS=[]

a = open('test.txt', 'r')
max=len(a.readlines())
i=0
a.seek(0)
while i < max-1:

    frame = a.readline()
    if(frame!="\n"):
        if(i>10):
            ant = frame.split()
            ax_v.append(float(ant[1]))
            ay_v.append(float(ant[2]))
            az_v.append(float(ant[3]))
            qw.append(float(ant[4]))
            qx.append(float(ant[5]))
            qy.append(float(ant[6]))
            sEMG_v.append(float(ant[7]))
            sMMG_v.append(float(ant[8]))
            qz.append(float(ant[9]))
            qw1.append(float(ant[10]))
            qx1.append(float(ant[11]))
            qy1.append(float(ant[12]))
            sEMG_b2_v.append(float(ant[13]))
            sMMG_b2_v.append(float(ant[14]))
            qz1.append(float(ant[15]))

            #TS.append(i*0.01-0.1)
    i=i+1


ti = 0
grabar = ""

f = open("variables.txt", 'w')
while (ti < len(ax_v)):
    grabar = str(ax_v[ti])+" "+str(ay_v[ti])+ " " + str(az_v[ti]) + " " + str(qw[ti]) + " " + str(qx[ti]) + " " + str(qy[ti]) + " " + str(sEMG_v[ti]) + " " + str(sMMG_v[ti]) + " " + str(qz[ti]) + " " + str(qw1[ti]) + " " + str(qx1[ti])+ " " + str(qy1[ti]) + " " + str(sEMG_b2_v[ti])+" "+str(sMMG_b2_v[ti])+" "+str(qz1[ti])+" "+"\n"    #print grabar

    f.write(grabar)
    #f.write('\n')

    ti += 1


f.close()