from LogData.Curves import*
from array import*
from random import*
from math import*
index_begin = left
index_end = right
curves = curve
i=0
j=0
k=0
w=[]
out_data=[]
array_disp=[]
index=0
size = curves.size()
sizeOffset = curves.sizeOffset()
if index_begin>sizeOffset:
	print("index begin  > size offset")
if index_end>sizeOffset:
	print("index end > size offset")
while index<size:
	w.append(curves.data(index))
	index=index+1

qantityBlock=0
qantityBlock=size/sizeOffset	


def means(array):
	variable = 0
	count = len(array)
	for elem in array:
		if elem != elem:
			count = count-1
		else:
			variable = variable+elem
	return variable/count

def dispersion(array,mean):
	variable =0
	elem = 0
	sqrtVariable =0
	for elem in array:
		sqrtVariable =sqrtVariable + elem*elem
	variable = sqrtVariable/len(array) - mean*mean
	return variable
	
while i<qantityBlock:
	array_disp=[]
	while k<sizeOffset:
		array_disp.append(w[i*sizeOffset+k])
		k=k+1
	k=0
	means_value = means(array_disp)
	disp_value = sqrt(dispersion(array_disp,means_value))
	while k<sizeOffset:
		if k>index_begin and k<index_end and (w[i*sizeOffset+k] - means_value) > disp_value / 2:
			out_data.append(means_value+uniform(0,disp_value))
			k=k+1
		else:
			out_data.append(w[i*sizeOffset+k])
			k=k+1
	i=i+1
	k=0
	
index=0
while index<size:
	curves.setData(out_data[index],index)
	index=index+1
print("script end")


