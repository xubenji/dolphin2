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


def goto(linenum):
    global line
    line = linenum


def mbtohex():
    print("")
    print("输入一个内存大小，我们将其转化为内存地址，输入s反之，输入q退出:")
    total=0
    str=input('Please input:')
    if str == 'q':
        exit()
    if str == 'Q':
        exit()
    if str == '':
        mbtohex()
    if str == 's':
        main()
    if  "eb" in str.split()[0]:
        goto(49)
    elif "pb" in str.split()[0]:
        goto(54)
    elif "tb" in str.split()[0]:
        goto(59)
    elif "gb" in str.split()[0]:
        goto(64)
    elif "mb" in str.split()[0]:
        goto(65)
    elif "kb" in str.split()[0]:
        goto(74)

    str1=str.split()[0]
    str1=str1.strip('eb')
    str1=int(str1)
    total=str1 * EB

    str1=str.split()[1]
    str1=str1.strip('pb')
    str1=int(str1)
    total=str1 * PB + total

    str1=str.split()[2]
    str1=str1.strip('tb')
    str1=int(str1)
    total=str1 * TB + total

    str1=str.split()[3]
    str1=str1.strip('gb')
    str1=int(str1)
    total=str1 * GB + total

    str1=str.split()[4]
    str1=str1.strip('mb')
    str1=int(str1)
    total=str1 * MB + total

    str1=str.split()[0]
    str1=str1.strip('kb')
    str1=int(str1)
    total=str1 * EB

    print(total)
    mbtohex()
    return

def main():
    print("")
    print("请输入一个16进制的数字，我们将其转化为一个可读的内存大小，输入s反之，输入q退出:")
    print("Please enter a hexnumber. We will convert it to comprehensible computer memory size，converse is entering 's'. enter 'q' exit:")
    hexnumber=input('Please input:')
    if hexnumber == 'q':
        exit()
    if hexnumber == 'Q':
        exit()
    if hexnumber == '':
        main()
    if hexnumber == 's':
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




        



