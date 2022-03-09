#!/usr/bin/python
line = 1


EB = 1024 * 1024 * 1024 * 1024 * 1024 * 1024
PB = 1024 * 1024 * 1024 * 1024 * 1024
TB = 1024 * 1024 * 1024 * 1024
GB = 1073741824         #(1024X1024X1024)
MB = 1048576            #(1024X1024)
KB = 1024               #(1024)

KB_HEX = 0x1000
MB_HEX = 0x100000
GB_HEX = 0x40000000

memory_list = {
    "B": 1,
    "KB": 1024,
    "MB": 1024 ** 2,
    "GB": 1024 ** 3,
    "TB": 1024 ** 4,
    "PB": 1024 ** 5,
    "EB": 1024 ** 6
}


def mbtohex():
    str = ''
    print("")
    print("输入一个内存大小，我们将其转化为内存地址，输入s反之，输入q退出:")
    str=input('Please input:')
    if str == 'q':
        exit()
    if str == 'Q':
        exit()
    if str == '':
        mbtohex()
    if str == 's':
        str = ''
        main()
    if __name__ == "__main__":
        #while(True):
            #str = input("input a string, if exit press q or Q: ")

            #if str.lower() == 'q':break
            input_list = str.split(" ")
            all_memory = 0

            for i in range(0, len(input_list)):

                if input_list[i] == "":
                    continue

                #print(input_list[i])
                sub_str = input_list[i][:-1]
                #print(sub_str)
                num = 0
                unit = 'B'
                try:
                    num = int(sub_str)
                except:
                    num = int(sub_str[:-1])
                    unit = sub_str[-1].upper() + "B"
                
                all_memory += num * memory_list[unit]

    print(hex(all_memory))
    
    #print("Thank you for using this program! ")
    mbtohex()
    return

def main():
    hexnumber = ''
    print("")
    print("请输入一个16进制的数字，我们将其转化为一个可读的内存大小，输入s反之，输入h为接收十进制，输入q退出:")
    print("Please enter a hexnumber. We will convert it to comprehensible computer memory size，converse is entering 's'. enter 'q' exit:")
    hexnumber=input('Please input:')
    if hexnumber == 'q':
        exit()
    if hexnumber == 'Q':
        exit()
    if hexnumber == '':
        main()
    if hexnumber == 'h':
        Dec = input("请输入十进制数字:")
        Dec = int(Dec)
        hexnumber = hex(Dec)
    if hexnumber == 's':
        hexnumber = ''
        mbtohex()
    decimal=int(hexnumber,16)
    if decimal >= EB:
        eb = decimal//EB
        TMP = decimal%EB
        pb = TMP//PB
        TMP = TMP%PB
        tb = TMP//TB
        TMP = TMP%TB
        gb = TMP//GB
        TMP = TMP%GB
        mb =  TMP//MB  
        TMP = TMP%MB
        kb = TMP//KB
        TMP = TMP%KB
        print("内存地址是:")
        print(f"The memory address is:\n",eb,"EB ",pb,"PB ",tb,"TB ",gb,"GB ",mb,"MB ",kb,"KB ",TMP,"Byte\n")
        main()
    if decimal >= PB:
        pb = decimal//PB
        TMP = decimal%PB
        tb = TMP//TB
        TMP = TMP%TB
        gb = TMP//GB
        TMP = TMP%GB
        mb =  TMP//MB  
        TMP = TMP%MB
        kb = TMP//KB
        TMP = TMP%KB
        print("内存地址是:")
        print(f"The memory address is:\n",pb,"PB ",tb,"TB ",gb,"GB ",mb,"MB ",kb,"KB ",TMP,"Byte\n")
        main()
    elif decimal >= TB:
        tb = decimal//TB
        TMP = decimal%TB
        gb = TMP//GB
        TMP = TMP%GB
        mb =  TMP//MB  
        TMP = TMP%MB
        kb = TMP//KB
        TMP = TMP%KB
        print("内存地址是:")
        print(f"The memory address is:\n",tb,"TB ",gb,"GB ",mb,"MB ",kb,"KB ",TMP,"Byte\n")
        main()
    elif decimal >= GB:
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
    else :
        TMP = decimal%KB
        print("内存地址是:")
        print(f"The memory address is:\n",TMP,"Byte\n")
        main()
    return
main()




        



