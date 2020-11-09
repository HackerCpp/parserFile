from LogData.Curves import*
from array import*
count = 6
curves = curve
i=0
j=0
k=0
point_filter=[]
w=[]
out_data=[]
index=0
size = curves.size()
sizeOffset = curves.sizeOffset()
while index<size:
	w.append(curves.data(index))
	index=index+1
	
def means(array):
	variable = 0
	count = len(array)
	for elem in array:
		if elem != elem:
			count = count-1
		else:
			variable = variable+elem
	return variable/count

qantityBlock=0
qantityBlock=size/sizeOffset

while i<qantityBlock:
	while k<sizeOffset:
		while j<count:
			if(k<sizeOffset - count):
				point_filter.append(w[i*sizeOffset+k+j])
				j=j+1
			else:
				point_filter.append(w[(i + 1)*(sizeOffset)-count+j])
				j=j+1
		k=k+1
		j=0
		out_data.append(means(point_filter))
		point_filter=[]
	k=0
	i=i+1

index=0
while index<size:
	curves.setData(out_data[index],index)
	index=index+1



