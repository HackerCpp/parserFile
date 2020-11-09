print("script begin")
import math

band_step_USEC = 2;

nun = float('nan')
pos_inf = float('inf')  
neg_inf = float('-inf') 

def findT(acu,t,left,amp,bandStep):
    if left < 1 :
        left = 1
    for indexY in range(0, acu.size() // acu.sizeOffset()) :
        for indexX in range(left,acu.sizeOffset() - 1) :
            ind = (indexY * acu.sizeOffset()) + indexX;
            if ((amp < acu.data(ind - 1)) and (amp > acu.data(ind + 1))) or ((amp > acu.data(ind - 1)) and (amp < acu.data(ind + 1))) :
                t.setData( indexX * bandStep,indexY) 
                break
        else : t.setData( nun,indexY)
        
def findA(acu,a,left,right) :
    for indexY in range(0, acu.size() // acu.sizeOffset()) :
        maximum = -65536;
        for indexX in range(left,right) :
            ind = (indexY * acu.sizeOffset()) + indexX
            if acu.data(ind)  > maximum :
                maximum = acu.data(ind)
        a.setData(maximum,indexY)
    
def calcADCUToDB(a_adcu,a_db,acp_max):
    for indexY in range(0, a_adcu.size()) :
        divider = a_adcu.data(indexY)
        if divider == 0 :
            divider = 1
        a_db.setData(20 * math.log10(acp_max / divider))

if(acu1,acu2,t1,t2,delta_t) :       
    findT(acu1,t1,left_band_acu1,amp_acu1,band_step_USEC)
    findT(acu2,t2,left_band_acu2,amp_acu2,band_step_USEC)

    for indexY in range(t2.size()) :
        delta_t.setData((t2.data(indexY) - t1.data(indexY)) / base,indexY)

if(acu1 and acu2 and a1_adcu and a2_adcu and a1_db and a2_db and alpha_db_m) :
    findA(acu1,a1_adcu,left_band_acu1,right_band_acu1)
    findA(acu2,a2_adcu,left_band_acu2,right_band_acu2)

    calcADCUToDB(a1_adcu,a1_db,32767)
    calcADCUToDB(a2_adcu,a2_db,32767)
    
    for indexY in range(alpha_db_m.size()) :
        alpha_db_m.setData((a2_db.data(indexY) - a1_db.data(indexY)) / base,indexY)


print("script end")