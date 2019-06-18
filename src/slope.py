print " "
def slope(x1,y1,x2,y2):
    slope = (y2-y1)/(x2-x1)
    return slope

print " "
x1 = float(raw_input("Enter x1: "))
y1 = float(raw_input("Enter y1: "))
x2 = float(raw_input("Enter x2: "))
y2 = float(raw_input("Enter y2: "))
intercept = float(raw_input("Enter the y-intercept: "))
print " "
print 'Calculating the slope for HT vs Dphi:'
print " "

print "slope: {}".format(slope(x1,y1,x2,y2))
print " Eqn for HT(y) vs DPhi(x): y = {0}x+{1}".format((slope(x1,y1,x2,y2)),(intercept))
print "Cut: x >= {0}y-{1}".format((1/slope(x1,y1,x2,y2)),(intercept/slope(x1,y1,x2,y2)))
print " "

