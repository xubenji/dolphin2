#!/usr/bin/python

GB = 1073741824         #(1024X1024X1024)
MB = 1048576            #(1024X1024)
KB = 1024               #(1024)

KB_HEX = 0x1000
MB_HEX = 0x100000
GB_HEX = 0x40000000

print("请输入一个16进制的数字，我们将其转化为一个可读的内存大小，输入q退出:")
print("Please enter a hexnumber. We will convert it to comprehensible computer memory size，enter 'q' exit:")
def main():
    hexnumber=input('Please input:')
    if hexnumber == 'q':
        return
    if hexnumber == 'Q':
        return
    decimal=int(hexnumber,16)
    #hexnumber=int(hexnumber)
    if decimal >= GB:
        gb = decimal//GB
        TMP = decimal%GB
        mb =  TMP//MB  
        TMP = TMP%MB
        kb = TMP//KB
        TMP = TMP%KB
        print("内存地址是:")
        print(f"The memory address is:\n",gb,"GB ",mb,"MB ",kb,"KB ",TMP,"Byte\n")
        main()
    elif decimal >= MB:
        mb =  decimal//MB  
        TMP = decimal%MB
        kb = TMP//KB
        TMP = TMP%KB
        print("内存地址是:")
        print(f"The memory address is:\n",mb,"MB ",kb,"KB ",TMP,"Byte\n")
        main()
    elif decimal >= KB:
        kb = decimal//KB
        TMP = decimal%KB
        print("内存地址是:")
        print(f"The memory address is:\n",kb,"KB ",TMP,"Byte\n")
        main()
    return
main()



