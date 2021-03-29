#!/usr/bin/python

print("二进制转十六进制，输入q退出:")
print("binary number to hexadecimal，enter 'q' exit:")

def main():
    binary=input(':')
    if binary == 'q':
        return
    if binary == 'Q':
        return
    hexadecimal=hex(int(binary,2))
    print(f">",hexadecimal, "\n")
    main()
    return 
main()