#медианный фильтр
from LogData.Curves import*
from array import*
count = 6 # количество точек для расчета
curves = curve# название кривой
i=0
j=0
k=0
median_filter=[]
w=[]
out_data=[]
index=0
size = curves.size()
sizeOffset = curves.sizeOffset()
while index<size:
	w.append(curves.data(index))
	index=index+1


def bubble_sort_array(array,count_pts):
	for i in range(count_pts-1):
		for j in range(count_pts-i-1):	
			if array[j]>array[j+1]:
				buff = array[j]
				array[j] = array[j+1]
				array[j+1] = buff
 
qantityBlock=0
qantityBlock=size/sizeOffset

while i<qantityBlock:
	while k<sizeOffset:
		while j<count:
			if(k<sizeOffset - count):
				median_filter.append(w[i*sizeOffset+k+j])
				j=j+1
			else:
				median_filter.append(w[(i+1)*(sizeOffset)-count+j])
				j=j+1
				
		k=k+1
		j=0
		bubble_sort_array(median_filter,count)
		out_data.append(median_filter[count//2])
		median_filter=[]
	k=0
	i=i+1
	
index=0
while index<size:
	curves.setData(out_data[index],index)
	index=index+1




