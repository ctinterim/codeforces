import math

# try to solve following:
# ax + by = c
# px + qy = r
def stupidSolve(a,b,c,p,q,r):
	# a == p == 0 cannot happen
	# it could happen only if x1 == x2 == x3, which means 3 points are on 1 line
	# this cannot happen on outcircle
	#
	# --> solve for x
	# aqx + bqy = cq
	# bpx + bqy = br
	# x(aq-bp) = (cq-br)
	# x = (cq-br)/(aq-bp)
	#
	# --> solve for y 
	# apx + bpy = cp
	# apx + aqy = ar
	# y(bp-aq) = (cp-ar)   
	# y = (cp-ar)/(bp-aq)

	x0 = (c*q - b*r)/(a*q - b*p)
	y0 = (c*p - a*r)/(b*p - a*q)

	return x0, y0

def angleBetween3Points(x0, y0, x1, y1, x2, y2):
	# x0, y0 is the middle point
	result = math.atan2(y2 - y0, x2 - x0) - math.atan2(y1 - y0, x1 - x0)
	result = abs(result)
	if result > math.pi:
		result = (2*math.pi) - result
	return result


def areaRegularPolygonCircumradius(radius, numsides):
	area = (radius*radius)*numsides
	area *= math.sin((math.pi*2)/numsides)
	area /= 2
	return area

def smallestPossibleNumberOfSides(a1, a2, a3):
	for numsides in range(3,101):
		a0 = (2*math.pi) / numsides

		c1 = round(a1/a0,5)
		c2 = round(a2/a0,5)
		c3 = round(a3/a0,5)

		if c1 == int(c1) and c2 == int(c2) and c3 == int(c3):
			return numsides

if __name__ == '__main__':
	x1,y1 = tuple(map(float,input().split())) # A
	x2,y2 = tuple(map(float,input().split())) # B
	x3,y3 = tuple(map(float,input().split())) # C

	# Get origin of outcircle
	a = 2*(x2-x1)
	b = 2*(y2-y1)
	c = ((x2*x2) + (y2*y2)) - ((x1*x1) + (y1*y1))

	p = 2*(x3-x1)
	q = 2*(y3-y1)
	r = ((x3*x3) + (y3*y3)) - ((x1*x1) + (y1*y1))

	x0, y0 = stupidSolve(a,b,c,p,q,r)

	# Get angle between A0B0, A0C0, B0C0
	OAB = angleBetween3Points(x0,y0,x1,y1,x2,y2)
	OAC = angleBetween3Points(x0,y0,x1,y1,x3,y3)
	OBC = angleBetween3Points(x0,y0,x2,y2,x3,y3)

	# Get smallest possible number of sides
	numsides = smallestPossibleNumberOfSides(OAB,OAC,OBC)

	# Get radius
	radius = math.sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0))

	res = areaRegularPolygonCircumradius(radius, numsides)
	print("{:.6f}".format(res))