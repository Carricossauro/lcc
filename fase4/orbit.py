import sys
k = 0.7071
d = float(sys.argv[1])
m = d*k
text = f'''\
<translate time = "***" align="True" >
    <point x="{m}" y="0" z="{m}"/>
    <point x="0" y="0" z="{d}"/>
    <point x="-{m}" y="0" z="{m}"/>
    <point x="-{d}" y="0" z="0"/>
    <point x="-{m}" y="0" z="-{m}"/>
    <point x="0" y="0" z="-{d}"/>
    <point x="{m}" y="0" z="-{m}"/>
    <point x="{d}" y="0" z="0"/>
</translate>\
'''
print(text)