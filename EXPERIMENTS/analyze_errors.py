import sys
random_register=0xace1
expected_sequence_number=0
bit_errors=0
packet_errors=0
packet_length=14
def convert_hex_to_bool(str):
    switcher={
        "0":"0000",
        "1":"0001",
        "2":"0010",
        "3":"0011",
        "4":"0100",
        "5":"0101",
        "6":"0110",
        "7":"0111",
        "8":"1000",
        "9":"1001",
        "a":"1010",
        "b":"1011",
        "c":"1100",
        "d":"1101",
        "e":"1110",
        "f":"1111",
    }
    return (switcher.get(str[0],"nothing")+switcher.get(str[1],"nothing"))

def convert_hex_to_int(str):
    switcher={
        "0": 0,
        "1": 1,
        "2": 2,
        "3": 3,
        "4": 4,
        "5": 5,
        "6": 6,
        "7": 7,
        "8": 8,
        "9": 9,
        "a": 10,
        "b": 11,
        "c": 12,
        "d": 13,
        "e": 14,
        "f": 15,
    }
    return (switcher.get(str[0],"nothing")*16+switcher.get(str[1],"nothing"))

def update_random_register():
    global random_register
    for i in range(14):
        new_bit=((random_register)^(random_register>>2)^(random_register>>3)^(random_register>>5))&1
        random_register=random_register>>1|new_bit<<15

def generate_random_8_bit_string():
    update_random_register()
    return bin(random_register)[-8:]
def generate_random_32_bit_string():
    str=""
    for i in range(4):
        str+=generate_random_8_bit_string()
    return str
def difference_between_104_bit_strings(string1,string2):
    unmatched_bits=0
    for i in range(8*13):
        if (string1[i]!=string2[i]):
            unmatched_bits+=1
    return unmatched_bits

# This is the code to generate the table
# original_stdout=sys.stdout
# with open('output.txt','w') as f:
#     sys.stdout= f
#     for i in range(65536):
#         print("   \""+str(i)+"\":\""+generate_random_32_bit_string()+"\",")
# sys.stdout=original_stdout

# This is the code to veryfy from the table
# f = open("output.txt", "r")
# curr_line=f.readline
# while(curr_line!=None):
#     element_arr=curr_line.split(" ")
#     seq_number=convert_hex_to_int(element_arr[0])*256+convert_hex_to_int(element_arr[1])
#     for i in range(2,packet_length):
#         bit_errors+=difference_between_8_bit_strings(table.sequence_number_bit_sequence_mapping(seq_number),convert_hex_to_bool(element_arr[i]))
#     curr_line=f.readline
# print("The number of bit_errors= "+bit_errors)


# This is the code to veryfy the dummy sequency (1,2,3,4,5,6...)
f = open("freerunning-B20-D20/freerunning-B20-D20-5.txt", "r")
answer="00000000000000010000001000000011000001000000010100000110000001110000100000001001000010100000101100001100" 
bit_errors=0
total_bits=0
for i in range (1000):
    curr_line=f.readline()
    curr_input=curr_line.split("|")[1]
    curr_input=curr_input.split(" ")
    bool_string=""
    for i in range(1,14):
        bool_string+=convert_hex_to_bool(curr_input[i])
    total_bits+=8*13
    bit_errors+=difference_between_104_bit_strings(answer,bool_string)
print("Total number of bit errors =", bit_errors)
print("Total number of bits ",total_bits )
print("The bit error rate is :", bit_errors/total_bits)



    