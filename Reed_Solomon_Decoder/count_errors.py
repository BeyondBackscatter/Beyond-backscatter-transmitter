#This code is made under the assumption that the very first packet transmitted is not missing
import heapq
import reed_solomon_decoder
from array import array
file=open("reed_solomon_experiments/7mread2.txt","r")
rows=14
columns=28
elementArray=[[0]*columns for i in range(rows)]

def convert_int_to_bool_string(number):
    output_string=""
    for i in range(8):
        if (number%2==1):
            output_string="1"+output_string
        else:
            output_string="0"+output_string
        number=number//2
    return output_string

def difference_between_8_bit_strings(string1,string2):
    unmatched_bits=0
    for i in range(8):
        if (string1[i]!=string2[i]):
            unmatched_bits+=1
    return unmatched_bits

def countF(inputString):
    count =0
    for i in range(len(inputString)):
        currentCharacter=inputString[i]
        if (currentCharacter=='f'):
            count +=1
    return count

    

def textToInt(byteInText):
    switcher={
        "0":0,
        "1":1,
        "2":2,
        "3":3,
        "4":4,
        "5":5,
        "6":6,
        "7":7,
        "8":8,
        "9":9,
        "a":10,
        "b":11,
        "c":12,
        "d":13,
        "e":14,
        "f":15
    }
    return (switcher.get(byteInText[0])*16+switcher.get(byteInText[1]))
time=0
def stringToTime(timeString):
    hour=int(timeString.split(":")[0])
    minute=int(timeString.split(":")[1])
    second=int((timeString.split(":")[2]).split(".")[0])
    millisecond=int((timeString.split(":")[2]).split(".")[1])
    time = hour*3600000+minute*60000+second*1000+millisecond
    return time
    
isFirstTime=True
currentTime=0 
packetNumber=0
nonFixablePackets=0
lostPackets=0
bit_errors=0
for unit_number in range (35):

    missingPackets=[]
    naughtyPackets=[]
    for i in range (packetNumber):
        missingPackets.append(i)
    elementArray=[[0]*28 for i in range (14)]
    while(packetNumber<28):
        lineFromText=file.readline()
        numberOfF=countF(lineFromText)
        if (numberOfF>10):
            naughtyPackets.append((packetNumber))
        timeOfMessage=lineFromText.split("|")[0]
        timeInMilliseconds=stringToTime(timeOfMessage)
        interleavedText=lineFromText.split("|")[1]
        interleavedBytesInText=interleavedText.split()
        if (isFirstTime):
            for k in range(14):
                elementArray[k][packetNumber]=textToInt(interleavedBytesInText[k])
            currentTime=timeInMilliseconds
            isFirstTime=False
        else:
            timeDifference=timeInMilliseconds-currentTime
            currentTime=timeInMilliseconds
            numberOfMissingPackets=0

            if (timeDifference>200):
                numberOfMissingPackets=(timeDifference//200)-1
            else :
                numberOfMissingPackets=0
            for i in range(numberOfMissingPackets):
                if(packetNumber<28):
                    missingPackets.append(packetNumber)
                lostPackets+=1
                packetNumber+=1
            if(packetNumber<28):
                for k in range(14):
                    elementArray[k][packetNumber]=textToInt(interleavedBytesInText[k])
        packetNumber+=1
    packetNumber=(packetNumber)%28
    for i in range (14):
        try:
            print(reed_solomon_decoder.rs_correct_msg(elementArray[i],14,missingPackets)[0])
            original_byte_array=reed_solomon_decoder.rs_correct_msg(elementArray[i],14,missingPackets)[0][0:14]
            for j in range(14):
                if (elementArray[i][j]!=0):
                    bit_errors+=difference_between_8_bit_strings(convert_int_to_bool_string(elementArray[i][j]),convert_int_to_bool_string(original_byte_array[j]))
        except:
            try:
                reed_solomon_decoder.rs_correct_msg(elementArray[i],14,heapq.merge(missingPackets,naughtyPackets))
            except:
                # print("The ",i,"th packet of the ",unit_number," unit cannot be corrected with ",len(missingPackets)," missing packets and ",len(naughtyPackets)," naughty packets at line number ",28*unit_number+lostPackets)
                # print("The packet is",elementArray[i])
                nonFixablePackets+=1
print("The bit error rate before coding is ", bit_errors/(8*14*490))
print("The number of missed packets is",nonFixablePackets)
print("The number of lost packets is ",lostPackets)


        

