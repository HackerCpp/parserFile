#медианный фильтр в границах
from LogData.Curves import*
from array import*
count = int(param1) # количество точек
if count == 0:
    count = 4;
print(count)
curves = curve #название кривой

borders =[left + 6,right + 6] #границы по индексам два числа - один участок обработки
i=0

def bubble_sort_array(array,count_pts):
	for i in range(count_pts - 1):
		for j in range(count_pts - i - 1 ):	
			if array[j] > array[j+1]:
				buff = array[j]
				array[j] = array[j + 1]
				array[j + 1] = buff
								
def medianFilterBoard(index_begin,index_end):				
	w=[]
	index=0
	out_data=[]
	size = curves.size()
	sizeOffset = curves.sizeOffset()

	while index<size:
		w.append(curves.data(index))
		index=index+1

	qantityBlock=0
	qantityBlock=size/sizeOffset
	i=0
	j=0
	k=0
	median_filter=[]
	out_data=[]
	while i<qantityBlock:
		while k<sizeOffset:
			if k>=index_begin and k<=index_end:
				while j<count:
					if(k<sizeOffset - count):
						median_filter.append(w[i*sizeOffset+k+j])
						j=j+1
					else:
						median_filter.append(w[(i + 1)*(sizeOffset)-count+j])
						j=j+1
				k=k+1
				j=0
				bubble_sort_array(median_filter,count)
				out_data.append(median_filter[count//2])
				median_filter=[]
			else:
				out_data.append(w[i*sizeOffset+k])
				k=k+1
		k=0
		i=i+1

	index=0
	while index<size:
		curves.setData(out_data[index],index)
		index=index+1

while i<len(borders):
	medianFilterBoard(borders[i],borders[i+1])
	i=i+2

	