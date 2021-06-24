#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pyqtgraph import PlotWidget
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import (QApplication, QOpenGLWidget)
from PyQt5 import QtCore, QtGui, QtWidgets

from shutil import copyfile #Lo hizo criss

import OpenGL.GL as gl
from OpenGL.GLUT import *
import numpy as np
import pyrr
import time
import math


try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)



class GLWidget(QOpenGLWidget):
    xRotationChanged = pyqtSignal(int)
    yRotationChanged = pyqtSignal(int)
    zRotationChanged = pyqtSignal(int)

    #ready
    def __init__(self, parent=None):
        super(GLWidget, self).__init__(parent)

        self.object = 0
        self.xRot = 1500
        self.yRot = 0
        self.zRot = 0
        self.grosor=0.02
        self.estado=0
        self.lastPos = QPoint()

        #self.a=0
        #self.b=0
        #self.arrancar = 0

        self.trolltechGreen = QColor.fromCmykF(0.0, 0.13, 0.27, 0.0)
        self.trolltechPurple = QColor.fromCmykF(0.14, 0, 0.06, 0.23)

        self.timer = QtCore.QTimer(self)
        self.timer.timeout.connect(self.moverbrazo)
        self.x = []
        self.y = []
        self.z = []
        self.qw1 = []
        self.qx1 = []
        self.qy1 = []
        self.qz1 = []
        self.qw2 = []
        self.qx2 = []
        self.qy2 = []
        self.qz2 = []

        self.qwins1 = 0
        self.qxins1 = 0
        self.qyins1 = 0
        self.qzins1 = 0
        self.qwins2 = 0
        self.qxins2 = 0
        self.qyins2 = 0
        self.qzins2 = 0

        a = open('data.txt', 'r')
        max = len(a.readlines())
        self.max=max
        i = 0
        a.seek(0)
        while i < max - 1:

            frame = a.readline()
            ant = frame.split()
            self.z.append(float(ant[0]))
            self.y.append(float(ant[1]))
            self.x.append(float(ant[2]))
            self.qw1.append(float(ant[3]))
            self.qx1.append(float(ant[4]))
            self.qy1.append(float(ant[5]))
            self.qz1.append(float(ant[6]))
            self.qw2.append(float(ant[7]))
            self.qx2.append(float(ant[8]))
            self.qy2.append(float(ant[9]))
            self.qz2.append(float(ant[10]))


            # TS.append(i*0.01-0.1)
            i = i + 1



    # ready
    def getOpenglInfo(self):
        info = """
            Vendor: {0}
            Renderer: {1}
            OpenGL Version: {2}
            Shader Version: {3}
        """.format(
            gl.glGetString(gl.GL_VENDOR),
            gl.glGetString(gl.GL_RENDERER),
            gl.glGetString(gl.GL_VERSION),
            gl.glGetString(gl.GL_SHADING_LANGUAGE_VERSION)
        )

        return info

    # ready
    def minimumSizeHint(self):
        return QSize(50, 50)

    # ready
    def sizeHint(self):
        return QSize(400, 400)

    # ready
    def setXRotation(self, angle):
        print ("setXRotation")
        angle = self.normalizeAngle(angle)
        if angle != self.xRot:
            self.xRot = angle
            self.xRotationChanged.emit(angle)
            self.update()

    # ready
    def setYRotation(self, angle):
        print("setYRotation")
        angle = self.normalizeAngle(angle)
        if angle != self.yRot:
            self.yRot = angle
            self.yRotationChanged.emit(angle)
            self.update()

    # ready
    def setZRotation(self, angle):
        print("setZRotation")
        angle = self.normalizeAngle(angle)
        if angle != self.zRot:
            self.zRot = angle
            self.zRotationChanged.emit(angle)
            self.update()

    # ready
    def initializeGL(self):
        print("initializeGL")
        print(self.getOpenglInfo())
        print("antes de ... glutInit")

        glutInit() #aqui se esta quedando
        print("despues de ... glutInit")
        self.setClearColor(self.trolltechPurple.darker())
        self.object = self.makeObject()
        #self.object=self.loadObj()
        gl.glShadeModel(gl.GL_FLAT)
        gl.glEnable(gl.GL_DEPTH_TEST)
        gl.glEnable(gl.GL_CULL_FACE)

    #ready
    def paintGL(self):
        print("paintGL")
        gl.glClear(
            gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        gl.glLoadIdentity()
        gl.glTranslatef(0.0, 0.0, -9.0)
        gl.glRotated(self.xRot / 16.0, 1.0, 0.0, 0.0)
        gl.glRotated(self.yRot / 16.0, 0.0, 1.0, 0.0)
        gl.glRotated(self.zRot / 16.0, 0.0, 0.0, 1.0)
        self.object = self.makeObject()
        gl.glCallList(self.object)


    #ready
    def resizeGL(self, width, height):
        print("resizeGL")
        side = min(width, height)
        if side < 0:
            return

        gl.glViewport((width - side) // 2, (height - side) // 2, side,
                           side)

        gl.glMatrixMode(gl.GL_PROJECTION)
        gl.glLoadIdentity()
        gl.glOrtho(-0.5, +0.5, +1, -0.2, 4, 15.0)
        gl.glMatrixMode(gl.GL_MODELVIEW)

    #no hace nada esta parte
    def  spiralmove(self,i,max):
        print ("spiralmove ")
        gl.glEnableClientState(gl.GL_VERTEX_ARRAY)

        spiral_array = []

        # Second Spiral using "array immediate mode" (i.e. Vertex Arrays)
        radius = i/max
        x = radius * math.sin(0)
        y = radius * math.cos(0)
        gl.glColor(1.0, 0.0, 0.0)
        for deg in range(820):
            spiral_array.append([x, y])
            rad = math.radians(deg)
            radius -= 0.001
            x = radius * math.sin(rad)
            y = radius * math.cos(rad)

        gl.glVertexPointerf(spiral_array)
        gl.glDrawArrays(gl.GL_LINE_STRIP, 0, len(spiral_array))
        gl.glFlush()

    # ready
    def mousePressEvent(self, event):
        print("mousePressEvent ")
        self.lastPos = event.pos()

    # ready
    def mouseMoveEvent(self, event):
        print("mouseMoveEvent")
        dx = event.x() - self.lastPos.x()
        dy = event.y() - self.lastPos.y()

        if event.buttons() & Qt.LeftButton:
            self.setXRotation(self.xRot - 8 * dy)
            self.setYRotation(self.yRot + 8 * dx)
        elif event.buttons() & Qt.RightButton:
           # self.setXRotation(self.xRot + 8 * dy)
            self.setZRotation(self.zRot + 8 * dx)

        self.lastPos = event.pos()

    def makeObject(self):
        print("makeObject")
        genList = gl.glGenLists(1)
        gl.glNewList(genList, gl.GL_COMPILE)

        gl.glBegin(gl.GL_QUADS)
        if(self.estado==0):
            #arm
            x1 = 0.05*100
            z1 = 0*100
            x2 = -0.05*100
            z2 = 0*100
            x3 = -0.03*100
            z3 = -0.4*100
            x4 = 0.03*100
            z4 = -0.4*100
            ya=+self.grosor*100
            yb=-self.grosor*100
            v1 = [x1, ya, z1]
            v2 = [x2, ya, z2]
            v3 = [x3, ya, z3]
            v4 = [x4, ya, z4]
            v1a = [x1, yb, z1]
            v2a = [x2, yb, z2]
            v3a = [x3, yb, z3]
            v4a = [x4, yb, z4]

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)

            #forearm
            x5 = 0.03*100
            z5 = -0.4*100
            x6 = -0.03*100
            z6 = -0.4*100
            x7 = -0.036*100
            z7 = -0.55*100
            x8 = 0.036*100
            z8 = -0.55*100

            v1 = [x5, ya, z5]
            v2 = [x6, ya, z6]
            v3 = [x7, ya, z7]
            v4 = [x8, ya, z8]
            v1a = [x5, yb, z5]
            v2a = [x6, yb, z6]
            v3a = [x7, yb, z7]
            v4a = [x8, yb, z8]

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)


            x9 = 0.036*100
            z9 = -0.55*100
            x10 = -0.036*100
            z10 = -0.55*100
            x11 = -0.02*100
            z11 = -0.73*100
            x12 = 0.02*100
            z12 = -0.73*100

            v1 = [x9, ya, z9]
            v2 = [x10, ya, z10]
            v3 = [x11, ya, z11]
            v4 = [x12, ya, z12]
            v1a = [x9, yb, z9]
            v2a = [x10, yb, z10]
            v3a = [x11, yb, z11]
            v4a = [x12, yb, z12]

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)
            # hand
            x13 = 0.03*100
            z13 = -0.73*100
            x14 = -0.03*100
            z14 = -0.73*100
            x15 = -0.05*100
            z15 = -0.93*100
            x16 = 0.05*100
            z16 = -0.93*100

            v1 = [x13, ya, z13]
            v2 = [x14, ya, z14]
            v3 = [x15, ya, z15]
            v4 = [x16, ya, z16]
            v1a = [x13, yb, z13]
            v2a = [x14, yb, z14]
            v3a = [x15, yb, z15]
            v4a = [x16, yb, z16]

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)

            x17 = 0.03*100
            z17= -0.73*100
            x18 = 0.02*100
            z18 = -0.73*100
            x19 = 0.04*100
            z19 = -0.83*100
            x20 = 0.06*100
            z20 = -0.83*100

            v1 = [x17, ya, z17]
            v2 = [x18, ya, z18]
            v3 = [x19, ya, z19]
            v4 = [x20, ya, z20]
            v1a = [x17, yb, z17]
            v2a = [x18, yb, z18]
            v3a = [x19, yb, z19]
            v4a = [x20, yb, z20]

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)


        else:
            # arm
            x1 = 0.05
            z1 = 0
            x2 = -0.05
            z2 = 0
            x3 = -0.03
            z3 = -0.4
            x4 = 0.03
            z4 = -0.4
            ya=+self.grosor
            yb=-self.grosor
            v1,v2,v3,v4,v1a,v2a,v3a,v4a=self.rotatearm(x1,z1,x2,z2,x3,z3,x4,z4,ya,yb)
            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)


            #forearm
            x5 = 0.03
            y5=+self.grosor
            z5 = 0
            x6 = -0.03
            y6 = +self.grosor
            z6 = 0
            x7 = -0.036
            y7 = +self.grosor
            z7 = -0.15
            x8 = 0.036
            y8 = +self.grosor
            z8 = -0.15

            v1,v2,v3,v4,v1a,v2a,v3a,v4a=self.rotateforearm(x5,y5,z5,x6,y6,z6,x7,y7,z7,x8,y8,z8,x5,-y5,z5,x6,-y6,z6,x7,-y7,z7,x8,-y8,z8)

            v1 = np.array([v1[0],v1[1],v1[2]+z4*100])
            v2 = np.array([v2[0], v2[1], v2[2] + z4*100])
            v3 = np.array([v3[0], v3[1], v3[2] + z4*100])
            v4 = np.array([v4[0], v4[1], v4[2] + z4*100])
            v1a = np.array([v1a[0], v1a[1], v1a[2] + z4*100])
            v2a = np.array([v2a[0], v2a[1], v2a[2] + z4*100])
            v3a = np.array([v3a[0], v3a[1], v3a[2] + z4*100])
            v4a = np.array([v4a[0], v4a[1], v4a[2] + z4*100])
            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)

            vatemp = v3
            vbtemp = v4
            vctemp = v3a
            vdtemp = v4a

            x9 = 0
            y9 = 0
            z9 = 0
            x10 = 0
            y10 = 0
            z10 = 0
            x11 = 0.016
            y11 = 0
            z11 = -0.18
            x12 = -0.016
            y12 = 0
            z12 = -0.18
            v1, v2, v3, v4, v1a, v2a, v3a, v4a = self.rotateforearm(x9, y9, z9, x10, y10, z10, x11, y11, z11, x12, y12, z12, x9, -y9, z9, x10, -y10, z10, x11, -y11, z11, x12, -y12, z12)
            v1 = np.array([vbtemp[0],vbtemp[1],vbtemp[2]])
            v2 = np.array([vatemp[0], vatemp[1], vatemp[2] ])

            v3 = np.array([v3[0]+vatemp[0], v3[1]+vatemp[1], v3[2]+vatemp[2] ])
            v4 = np.array([v4[0]+vbtemp[0], v4[1]+vbtemp[1], v4[2]+vbtemp[2] ])

            v1a = np.array([vdtemp[0], vdtemp[1], vdtemp[2] ])
            v2a = np.array([vctemp[0], vctemp[1], vctemp[2] ])

            v3a = np.array([v3a[0]+vctemp[0], v3a[1]+vctemp[1], v3a[2]+vctemp[2] ])
            v4a = np.array([v4a[0]+vdtemp[0], v4a[1]+vdtemp[1], v4a[2]+vdtemp[2] ])
            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)
            vatemp = v3
            vbtemp = v4
            vctemp = v3a
            vdtemp = v4a
            #hand
            x13 = 0.01
            y13=0
            z13 = -0.
            x14 = -0.01
            y14 = 0
            z14 = -0.
            x15 = -0.03
            y15 = 0
            z15 = -0.2
            x16 = +0.03
            y16 = 0
            z16 = -0.2

            v1, v2, v3, v4, v1a, v2a, v3a, v4a = self.rotatehand(x13,y13,z13,x14,y14,z14,x15,y15,z15,x16,y16,z16,x13,-y13,z13,x14,-y14,z14,x15,-y15,z15,x16,-y16,z16)

            v1 = np.array([v1[0] +vbtemp[0], v1[1] +vbtemp[1], v1[2] +vbtemp[2]])
            v2 = np.array([v2[0] +vatemp[0], v2[1] +vatemp[1], v2[2] +vatemp[2]])

            v3 = np.array([v3[0] + vatemp[0], v3[1] + vatemp[1], v3[2] + vatemp[2]])
            v4 = np.array([v4[0] + vbtemp[0], v4[1] + vbtemp[1], v4[2] + vbtemp[2]])


            v1a = np.array([v1a[0] +vdtemp[0],v1a[1] + vdtemp[1],v1a[2] + vdtemp[2]])
            v2a = np.array([v2a[0] +vctemp[0],v2a[1] + vctemp[1], v2a[2] +vctemp[2]])

            v3a = np.array([v3a[0] + vctemp[0], v3a[1] + vctemp[1], v3a[2] + vctemp[2]])
            v4a = np.array([v4a[0] + vdtemp[0], v4a[1] + vdtemp[1], v4a[2] + vdtemp[2]])

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)

            x17 = 0.01
            y17 = 0
            z17= -0.
            x18 = +0.02
            y18 = 0
            z18 = -0.
            x19 = 0
            y19 = 0
            z19 = -0.1
            x20 = +0.04
            y20 = 0
            z20 = -0.1
            v1, v2, v3, v4, v1a, v2a, v3a, v4a = self.rotatehand(x17,y17,z17,x18,y18,z18,x19,y19,z19,x20,y20,z20,x17,-y17,z17,x18,-y18,z18,x19,-y19,z19,x20,-y20,z20)


            v1 = np.array([v1[0] + vbtemp[0], v1[1] + vbtemp[1], v1[2] + vbtemp[2]])
            v2 = np.array([v2[0] + vatemp[0], v2[1] + vatemp[1], v2[2] + vatemp[2]])

            v3 = np.array([v3[0] + vatemp[0], v3[1] + vatemp[1], v3[2] + vatemp[2]])
            v4 = np.array([v4[0] + vbtemp[0], v4[1] + vbtemp[1], v4[2] + vbtemp[2]])

            v1a = np.array([v1a[0] + vdtemp[0], v1a[1] + vdtemp[1], v1a[2] + vdtemp[2]])
            v2a = np.array([v2a[0] + vctemp[0], v2a[1] + vctemp[1], v2a[2] + vctemp[2]])

            v3a = np.array([v3a[0] + vctemp[0], v3a[1] + vctemp[1], v3a[2] + vctemp[2]])
            v4a = np.array([v4a[0] + vdtemp[0], v4a[1] + vdtemp[1], v4a[2] + vdtemp[2]])

            self.cubo(v1, v2, v3, v4, v1a, v2a, v3a, v4a)


        gl.glEnd()
        gl.glEndList()

        return genList

    def rotatearm(self,x1,z1,x2,z2,x3,z3,x4,z4,ya,yb):
        print("rotatearm")

        v1 = pyrr.quaternion.apply_to_vector( pyrr.quaternion.create_from_eulers([0,0,0]) ,
                                             pyrr.Vector4([x1*100, ya*100, z1*100, 1*100]))

        v2 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x2*100, ya*100, z2*100, 1*100]))
        v3 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x3*100, ya*100, z3*100, 1*100]))
        v4 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x4*100, ya*100, z4*100, 1*100]))

        v1a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x1*100, yb*100, z1*100, 1*100]))
        v2a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x2*100, yb*100, z2*100, 1*100]))
        v3a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x3*100, yb*100, z3*100, 1*100]))
        v4a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0, 0, 0]),
                                             pyrr.Vector4([x4*100, yb*100, z4*100, 1*100]))

        return v1,v2,v3,v4,v1a,v2a,v3a,v4a

    def rotateforearm(self, x1, y1 , z1, x2, y2 ,z2, x3, y3, z3, x4, y4,z4,x1a, y1a , z1a, x2a, y2a ,z2a, x3a, y3a, z3a, x4a, y4a,z4a):
        print("rotateforearm")

        v1 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                             pyrr.Vector4([x1 * 100, y1 * 100, z1 * 100, 1 * 100]))

        v2 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                             pyrr.Vector4([x2 * 100, y2 * 100, z2 * 100, 1 * 100]))

        v3 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins1,self.qyins1,self.qzins1,self.qwins1),
                                             pyrr.Vector4([x3 * 100, y3 * 100, z3 * 100, 1 * 100]))
        #v3=np.array([v3[0],v3[1],v3[2]+v2[2]])
        print(v3)
        v4 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins1,self.qyins1,self.qzins1,self.qwins1),
                                             pyrr.Vector4([x4 * 100, y4 * 100, z4 * 100, 1 * 100]))
        #v4 = np.array([v4[0], v4[1], v4[2] + v1[2]])
        print(v4)
        v1a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                              pyrr.Vector4([x1a * 100, y1a * 100, z1a * 100, 1 * 100]))

        v2a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                              pyrr.Vector4([x2a * 100, y2a * 100, z2a * 100, 1 * 100]))

        v3a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins1,self.qyins1,self.qzins1,self.qwins1),
                                              pyrr.Vector4([x3a * 100, y3a * 100, z3a * 100, 1 * 100]))
        #v3a = np.array([v3a[0] , v3a[1], v3a[2] + v2a[2]])
        print(v3a)
        v4a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins1,self.qyins1,self.qzins1,self.qwins1),
                                              pyrr.Vector4([x4a * 100, y4a * 100, z4a * 100, 1 * 100]))
        #v4a = np.array([v4a[0] , v4a[1] , v4a[2] + v1a[2]])
        print(v4a)
        return v1, v2, v3, v4, v1a, v2a, v3a, v4a

    def rotatehand(self, x1, y1 , z1, x2, y2 ,z2, x3, y3, z3, x4, y4,z4,x1a, y1a , z1a, x2a, y2a ,z2a, x3a, y3a, z3a, x4a, y4a,z4a):
        print("rotatehand")

        v1 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                             pyrr.Vector4([x1 * 100, y1 * 100, z1 * 100, 1 * 100]))

        v2 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                             pyrr.Vector4([x2 * 100, y2 * 100, z2 * 100, 1 * 100]))

        v3 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins2,self.qyins2,self.qzins2,self.qwins2),
                                             pyrr.Vector4([x3 * 100, y3 * 100, z3 * 100, 1 * 100]))


        v4 = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins2,self.qyins2,self.qzins2,self.qwins2),
                                             pyrr.Vector4([x4 * 100, y4 * 100, z4 * 100, 1 * 100]))


        v1a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                              pyrr.Vector4([x1a * 100, y1a * 100, z1a * 100, 1 * 100]))

        v2a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create_from_eulers([0,0,0]),
                                              pyrr.Vector4([x2a * 100, y2a * 100, z2a * 100, 1 * 100]))

        v3a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins2,self.qyins2,self.qzins2,self.qwins2),
                                              pyrr.Vector4([x3a * 100, y3a * 100, z3a * 100, 1 * 100]))

        v4a = pyrr.quaternion.apply_to_vector(pyrr.quaternion.create(self.qxins2,self.qyins2,self.qzins2,self.qwins2),
                                              pyrr.Vector4([x4a * 100, y4a * 100, z4a * 100, 1 * 100]))

        return v1, v2, v3, v4, v1a, v2a, v3a, v4a

    def quad(self, x1, y1, x2, y2, x3, y3, x4, y4):
        print("quad")
        self.setColor(self.trolltechGreen)

        gl.glVertex3f(x1, y1, -self.grosor)
        gl.glVertex3f(x2, y2, -self.grosor)
        gl.glVertex3f(x3, y3, -self.grosor)
        gl.glVertex3f(x4, y4, -self.grosor)

        gl.glVertex3f(x4, y4, +self.grosor)
        gl.glVertex3f(x3, y3, +self.grosor)
        gl.glVertex3f(x2, y2, +self.grosor)
        gl.glVertex3f(x1, y1, +self.grosor)

    def cubo(self, v1,v2,v3,v4,v1a,v2a,v3a,v4a):
        #print("cubo")
        self.setColor(self.trolltechGreen)
        gl.glVertex3f(v1[0] / 100.0, v1[1] / 100.0, v1[2] / 100.0)
        gl.glVertex3f(v2[0] / 100.0, v2[1] / 100.0, v2[2] / 100.0)
        gl.glVertex3f(v3[0] / 100.0, v3[1] / 100.0, v3[2] / 100.0)
        gl.glVertex3f(v4[0] / 100.0, v4[1] / 100.0, v4[2] / 100.0)

        gl.glVertex3f(v4a[0] / 100.0, v4a[1] / 100.0, v4a[2] / 100.0)
        gl.glVertex3f(v3a[0] / 100.0, v3a[1] / 100.0, v3a[2] / 100.0)
        gl.glVertex3f(v2a[0] / 100.0, v2a[1] / 100.0, v2a[2] / 100.0)
        gl.glVertex3f(v1a[0] / 100.0, v1a[1] / 100.0, v1a[2] / 100.0)

        self.setColor(self.trolltechGreen.darker(250 + int(100 *v1[0])))
        gl.glVertex3f(v1[0]/100, v1[1]/100, v1[2]/100)
        gl.glVertex3f(v1a[0]/100, v1a[1]/100, v1a[2]/100)
        gl.glVertex3f(v2a[0]/100, v2a[1]/100, v2a[2]/100)
        gl.glVertex3f(v2[0]/100, v2[1]/100, v2[2]/100)

        gl.glVertex3f(v4a[0]/100, v4a[1]/100, v4a[2]/100)
        gl.glVertex3f(v4[0]/100, v4[1]/100, v4[2]/100)
        gl.glVertex3f(v3[0]/100, v3[1]/100, v3[2]/100)
        gl.glVertex3f(v3a[0]/100, v3a[1]/100, v3a[2]/100)

        gl.glVertex3f(v2[0]/100, v2[1]/100, v2[2]/100)
        gl.glVertex3f(v2a[0]/100, v2a[1]/100, v2a[2]/100)
        gl.glVertex3f(v3a[0]/100, v3a[1]/100, v3a[2]/100)
        gl.glVertex3f(v3[0]/100, v3[1]/100, v3[2]/100)

        gl.glVertex3f(v1a[0] / 100, v1a[1] / 100, v1a[2] / 100)
        gl.glVertex3f(v1[0] / 100, v1[1] / 100, v1[2] / 100)
        gl.glVertex3f(v4[0]/100, v4[1]/100, v4[2]/100)
        gl.glVertex3f(v4a[0] / 100, v4a[1] / 100, v4a[2] / 100)

    def bloque(self,x1, y1, x2, y2, x3, y3, x4, y4):
        print("bloque")
        self.quad(x1, y1, x2, y2, x3, y3, x4, y4)
        self.extrude(x1, y1, x2, y2)
        self.extrude(x3, y3, x4, y4)
        self.extrude(x4, y4, x1, y1)
        self.extrude(x2, y2, x3, y3)
    # ready
    def extrude(self, x1, y1, x2, y2):
        print("extrude")
        self.setColor(self.trolltechGreen.darker(250 + int(100 * x1)))
        gl.glVertex3d(x1, y1, +self.grosor)
        gl.glVertex3d(x2, y2, +self.grosor)
        gl.glVertex3d(x2, y2, -self.grosor)
        gl.glVertex3d(x1, y1, -self.grosor)
    #ready
    def normalizeAngle(self, angle):
        print("normalizeAngle")
        while angle < 0:
            angle += 360 * 16
        while angle > 360 * 16:
            angle -= 360 * 16
        return angle

    def setClearColor(self, c):
        print("setClearColor")
        gl.glClearColor(c.redF(), c.greenF(), c.blueF(), c.alphaF())

    def setColor(self, c):
        #print("setColor")
        gl.glColor4f(c.redF(), c.greenF(), c.blueF(), c.alphaF())


    def moverbrazo(self):
        print("moverbrazo")
        self.a=self.a+1
        #print('a: ')
        #print(self.a)
        #print('b: ')
        #print(self.a)
        self.qwins1 = self.qw1[self.a]
        self.qxins1 = self.qx1[self.a]
        self.qyins1 = self.qy1[self.a]
        self.qzins1 = self.qz1[self.a]

        self.qwins2 = self.qw2[self.a]
        self.qxins2 = self.qx2[self.a]
        self.qyins2 = self.qy2[self.a]
        self.qzins2 = self.qz2[self.a]
        self.object = self.makeObject()
        self.update()
        if(self.b==self.a and self.arrancar==0):
            self.timer.stop()
            self.arrancar=0

    def arranque(self):
        print("arranque")
        if(self.arrancar==1):
            self.timer.start(10)
            self.arrancar=0



class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1350, 690)
        # MainWindow.setMinimumSize(QtCore.QSize(887, 578))
        # MainWindow.setMaximumSize(QtCore.QSize(77215, 16777215))

        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setMaximumSize(QtCore.QSize(1350, 16777215))
        self.centralwidget.setObjectName("centralwidget")
        self.centralwidget.showMaximized();

        self.centralwidget.setStyleSheet("color: #506175;"
                                         "font-size:14px;"
                                         "background-color: qlineargradient(x1: 1, y1: 1, x2: 0, y2: 1,stop: 0 #ECF3F1, stop: 1 #FFFFFF);"
                                         "font-family:Courier New;"
                                         "font-weight: bold;"
                                         "border-radius: 6px;"
                                         "QPushButton{border: 2px outset #8f8f91;}"
                                         "QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}")

        self.glWidget = GLWidget(self.centralwidget)
        self.glWidget.setGeometry(QtCore.QRect(50, 180, 400, 400))





        self.tiempomin = QtGui.QTextEdit(self.centralwidget)
        self.tiempomin.setGeometry(QtCore.QRect(250, 130, 60, 30))
        self.tiempomin.setObjectName(_fromUtf8("timemin"))
        self.tiempomin.setStyleSheet("border: 2px ridge #8f8f91;")

        self.tiempomax = QtGui.QTextEdit(self.centralwidget)
        self.tiempomax.setGeometry(QtCore.QRect(320, 130, 60, 30))
        self.tiempomax.setObjectName(_fromUtf8("timemax"))
        self.tiempomax.setStyleSheet("border: 2px ridge #8f8f91;")

        self.tiempo = QtGui.QTextEdit(self.centralwidget)
        self.tiempo.setGeometry(QtCore.QRect(200, 80, 60, 30))
        self.tiempo.setObjectName(_fromUtf8("time"))
        self.tiempo.setStyleSheet("border: 2px ridge #8f8f91;")

        self.ir1 = QtGui.QPushButton(self.centralwidget)
        self.ir1.setEnabled(True)
        self.ir1.setGeometry(QtCore.QRect(280, 80,60, 30))
        self.ir1.setObjectName(_fromUtf8("ir1"))
        self.ir1.setStyleSheet(
            "QPushButton{border: 2px outset #8f8f91;}QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}")
        self.ir1.clicked.connect(self.mover)

        self.ir2 = QtGui.QPushButton(self.centralwidget)
        self.ir2.setEnabled(True)
        self.ir2.setGeometry(QtCore.QRect(400, 130, 60, 30))
        self.ir2.setObjectName(_fromUtf8("ir2"))
        self.ir2.setStyleSheet(
            "QPushButton{border: 2px outset #8f8f91;}QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}")
        self.ir2.clicked.connect(self.cargardata)

        self.play = QtGui.QPushButton(self.centralwidget)
        self.play.setEnabled(True)
        self.play.setGeometry(QtCore.QRect(120, 600, 50, 50))
        self.play.setObjectName(_fromUtf8("ir2"))
        self.play.setStyleSheet(
            "QPushButton{border: 2px outset #8f8f91;}QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}")
        self.play.setText("►")
        self.play.clicked.connect(self.reproducir)

        self.lineEdit1 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit1.setGeometry(QtCore.QRect(60, 55, 120, 80))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(16)
        self.lineEdit1.setFont(font)
        self.lineEdit1.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit1.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit1.setAutoFillBackground(False)
        self.lineEdit1.setReadOnly(True)
        self.lineEdit1.setObjectName("lineEdit1")
        self.lineEdit1.setStyleSheet("background-color: transparent;"
                                    "font-size: 14px;")

        self.lineEdit2 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit2.setGeometry(QtCore.QRect(60, 105, 200, 80))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(16)
        self.lineEdit2.setFont(font)
        self.lineEdit2.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit2.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit2.setAutoFillBackground(False)
        self.lineEdit2.setReadOnly(True)
        self.lineEdit2.setObjectName("lineEdit2")
        self.lineEdit2.setStyleSheet("background-color: transparent;"
                                    "font-size: 14px;")




        self.lineEdit = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit.setGeometry(QtCore.QRect(60, 10, 400, 80))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(16)
        self.lineEdit.setFont(font)
        self.lineEdit.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit.setAutoFillBackground(False)
        self.lineEdit.setReadOnly(True)
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit.setStyleSheet("background-color: transparent;"
                                    "font-size: 15px;")

        self.lineEdit3 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit3.setGeometry(QtCore.QRect(360, 55, 200, 80))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(16)
        self.lineEdit3.setFont(font)
        self.lineEdit3.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit3.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit3.setAutoFillBackground(False)
        self.lineEdit3.setReadOnly(True)
        self.lineEdit3.setObjectName("lineEdit3")
        self.lineEdit3.setStyleSheet("background-color: transparent;"
                                     "font-size: 14px;")

        self.lineEdit4 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit4.setGeometry(QtCore.QRect(420, 80,60, 30))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(16)
        self.lineEdit4.setFont(font)
        self.lineEdit4.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit4.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit4.setAutoFillBackground(False)
        self.lineEdit4.setReadOnly(True)
        self.lineEdit4.setObjectName("lineEdit4")
        self.lineEdit4.setStyleSheet("border: 2px ridge #8f8f91;")
        self.lineEdit4.setText(str(self.glWidget.max*0.01))

        self.lineEdit5 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit5.setGeometry(QtCore.QRect(200, 600, 320, 50))
        font = QtGui.QFont()
        font.setFamily("Roboto")
        font.setPointSize(5)
        self.lineEdit5.setFont(font)
        self.lineEdit5.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.lineEdit5.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lineEdit5.setAutoFillBackground(False)
        self.lineEdit5.setReadOnly(True)
        self.lineEdit5.setObjectName("lineEdit5")
        self.lineEdit5.setStyleSheet("background-color: transparent;"
                                     "font-size: 13px;"
                                     "color: red")
        #self.lineEdit5.setText(str(self.glWidget.max * 0.01))


        self.MOVEX = PlotWidget(self.centralwidget)
        self.MOVEX.setGeometry(QtCore.QRect(550, 20, 750, 200))
        self.MOVEX.setObjectName(_fromUtf8("MOVEX"))
        self.MOVEX.setBackground(background=(255, 255, 255))
        #self.MOVEX.addLegend(offset=(-10, 50))
        self.MOVEX.setLabel('left', 'Grados', pen='k')
        self.MOVEX.setLabel('bottom', 'Tiempo', 's', pen='k')
        self.MOVEX.setTitle('FLEXIÓN(+)/EXTENSIÓN(-)', pen='k')
        # self.MOVEX.plot()

        self.MOVEY = PlotWidget(self.centralwidget)
        self.MOVEY.setGeometry(QtCore.QRect(550, 240, 750, 200))
        self.MOVEY.setObjectName(_fromUtf8("MOVEY"))
        self.MOVEY.setBackground(background=(255, 255, 255))
        #self.MOVEY.addLegend(offset=(-10, 50))
        self.MOVEY.setLabel('left', 'Grados', pen='k')
        self.MOVEY.setLabel('bottom', 'Tiempo', 's', pen='k')
        #self.MOVEY.setTitle('PRONACIÓN(+)/SUPINACIÓN(-)', pen='k')
        self.MOVEY.setTitle('DESVIACIÓN: ULNAR(+)/RADIAL(-)', pen='k')

        self.MOVEZ = PlotWidget(self.centralwidget)
        self.MOVEZ.setGeometry(QtCore.QRect(550, 460, 750, 200))
        self.MOVEZ.setObjectName(_fromUtf8("MOVEZ"))
        self.MOVEZ.setBackground(background=(255, 255, 255))
        #self.MOVEZ.addLegend(offset=(-10, 50))
        self.MOVEZ.setLabel('left', 'Grados', pen='k')
        self.MOVEZ.setLabel('bottom', 'Tiempo', 's', pen='k')
        #self.MOVEZ.setTitle('DESVIACIÓN: ULNAR(+)/RADIAL(-)', pen='k')
        self.MOVEZ.setTitle('PRONACIÓN(+)/SUPINACIÓN(-)', pen='k')

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 921, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        self.cargartodo()

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.lineEdit.setText(_translate("MainWindow", "Posturas de trabajo: Evaluación de riesgo"))
        self.lineEdit1.setText(_translate("MainWindow", "Instante (s):"))
        self.lineEdit2.setText(_translate("MainWindow", "Ventana de tiempo (s):"))
        self.lineEdit3.setText(_translate("MainWindow", "Tiempo"))
        self.ir1.setText(_translate("MainWindow", "Ir"))
        self.ir2.setText(_translate("MainWindow", "Ir"))

#carga los datos a las graficas
    def cargardata(self):
        print("cargardata")
        self.lineEdit5.setText("")
        #print(self.glWidget.x2[100:200])
        print('sssss')
        xn=[]
        yn=[]
        zn=[]
        ts=[]
        try:
            a=float(self.tiempomin.toPlainText())
            b=float(self.tiempomax.toPlainText())

            a = int(a / 0.01)
            b = int((b / 0.01) + 1)
            print(a)
            print(b)
            xn = self.glWidget.x[a:b]
            yn = self.glWidget.y[a:b]
            zn = self.glWidget.z[a:b]


            # print(self.glWidget.x2[a:b])
            print(xn)
            print(yn)
            print(zn)



            if (a < 0 or b > self.glWidget.max):
                self.lineEdit5.setText("El tiempo tiene que estar en el rango")
            else:
                for i in range(1, len(xn) + 1):
                    ts.append(a * 0.01 + i * 0.01)
                self.MOVEX.plot(ts, xn, pen='r', clear=True)
                self.MOVEY.plot(ts, yn, pen='c', clear=True)
                self.MOVEZ.plot(ts, zn, pen='y', clear=True)

        except:
            self.lineEdit5.setText("El tiempo tiene que estar en el rango")

    def cargartodo(self):

        # ------------------------------esto lo hizo criss -------------------------
        print("voy a leer txt")
        r = open("D:\Codigo_21_10_2019/Sistema_de_apoyo_a_la_estimacion_de_factores_de_riesgo_biomecanicos/Python27/ruta.txt", 'r')  # ("C:\Python27/ruta.txt", 'r')
        rutao = str(r.read())
        r.close()

        print("ruta 0 ..")
        print(rutao)
        path = "D:\Codigo_21_10_2019\Sistema_de_apoyo_a_la_estimacion_de_factores_de_riesgo_biomecanicos\Python27"  #C:\CASD
        ruta = path + "/" + rutao + "/"
        print(path)

        #copyfile('data.txt', ruta + 'data.txt')
        copyfile('data.txt', "D:\Codigo_21_10_2019"+ "/" + rutao + "/" + 'data.txt')
        # ------------------------------FIN esto lo hizo criss -------------------------


        x = []
        y = []
        z = []
        t=  []
        a = open('data.txt', 'r')
        max = len(a.readlines())

        i = 0
        a.seek(0)
        while i < max - 1:
            frame = a.readline()
            ant = frame.split()
            z.append(float(ant[0]))
            y.append(float(ant[1]))
            x.append(float(ant[2]))
            t.append(i*0.01)


            # TS.append(i*0.01-0.1)
            i = i + 1
        a.close()
        try:

            # ------------------------------FIN esto lo hizo criss -------------------------

            self.MOVEX.plot(t,x, pen='r', clear=True)
            self.MOVEY.plot(t,y, pen='c', clear=True)
            self.MOVEZ.plot(t,z, pen='y', clear=True)

        except:
            self.lineEdit5.setText("El tiempo tiene que estar en el rango")

#mueve el brazo al instante
    def mover(self):
        print("mover")
        self.lineEdit5.setText("")
        try:
            c=float(self.tiempo.toPlainText())
            c = int(c / 0.01)
            print(c)

            self.glWidget.qwins1 = self.glWidget.qw1[c]
            self.glWidget.qxins1 = self.glWidget.qx1[c]
            self.glWidget.qyins1 = self.glWidget.qy1[c]
            self.glWidget.qzins1 = self.glWidget.qz1[c]

            self.glWidget.qwins2 = self.glWidget.qw2[c]
            self.glWidget.qxins2 = self.glWidget.qx2[c]
            self.glWidget.qyins2 = self.glWidget.qy2[c]
            self.glWidget.qzins2 = self.glWidget.qz2[c]
            self.glWidget.estado = 1
            #self.glWidget.object = self.glWidget.makeObject()
            #print(self.glWidget.qw1[c])
            #print(self.glWidget.qx1[c])
            #print(self.glWidget.qy1[c])
            #print(self.glWidget.qz1[c])
            #print(self.glWidget.qw2[c])
            #print(self.glWidget.qx2[c])
            #print(self.glWidget.qy2[c])
            #print(self.glWidget.qz2[c])
            self.glWidget.update()
        except:
            self.lineEdit5.setText("El tiempo tiene que estar en el rango")
#reproduce el movimiento del brazo
    def reproducir(self):
        print("reproducir")
        self.lineEdit5.setText("")
        #self.play.setEnabled(False)
        self.glWidget.estado = 1
        try:
            a = float(self.tiempomin.toPlainText())
            b = float(self.tiempomax.toPlainText())

            a = int(a / 0.01)
            b = int((b / 0.01) + 1)
            print(a)
            print(b)


            if (a < 0 or b > self.glWidget.max):
                self.lineEdit5.setText("El tiempo tiene que estar en el rango")
            else:

                self.glWidget.a = a
                self.glWidget.b = b
                self.glWidget.arrancar=1
                self.glWidget.arranque()





        except:
            self.lineEdit5.setText("El tiempo tiene que estar en el rango")





class Window(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        print ("Voy a empezar a hacer todo")
        QtWidgets.QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)

if __name__ == '__main__':

    app = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec_())