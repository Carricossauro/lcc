
#Recebe os semi-major axis e os semi-minor axis dos planetas e calcula n pontos da elipse 
import math
def elipse(major,minor,n):
    orbitas = {}
    for i in range(len(major)):
        a = major[i] * 150
        b = minor[i] * 150
        #c = sqrt(a**2-b**2)
        pontos = []
        pontos.append((a,0,0))
        for j in range(1,n+1):
            t = (j * 2 * math.pi) / n
            x , y , z = a * math.cos(t), 0 , b * math.sin(t)
            pontos.append((x,y,z))
        orbitas[i] = pontos
    return orbitas

major = [0.38700,0.72300,1.00000,1.52400,5.20440,9.58260,19.21840,30.11000]
minor = [0.37870,0.72298,0.99986,1.51740,5.19820,9.56730,19.19770,30.10870]
import pprint as pp
pp.pprint(elipse(major,minor,100))
