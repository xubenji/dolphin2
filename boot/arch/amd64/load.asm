[BITS 16]
[ORG 0x7e00]

VIRTUAL_BASE_ADDR equ 0xffff800000000000
PAGE_DIR_INIT   equ 0x70000 
PAGE_DIR_FIRST  equ 0x73000
PAGE_DIR_SECOND equ 0x74000

start:
    mov [DriveId],dl

    mov eax,0x80000000
    cpuid
    cmp eax,0x80000001
    jb NotSupport

    mov eax,0x80000001
    cpuid
    test edx,(1<<29)
    jz NotSupport
    test edx,(1<<26)
    jz NotSupport

LoadKernel:
    mov si,ReadPacket
    mov word[si],0x10
    mov word[si+2],100
    mov word[si+4],0
    mov word[si+6],0x1000
    mov dword[si+8],6
    mov dword[si+0xc],0
    mov dl,[DriveId]
    mov ah,0x42
    int 0x13
    jc  ReadError

GetMemInfoStart:
    mov eax,0xe820
    mov edx,0x534d4150
    mov ecx,20
    mov dword[0x9000],0
    mov edi,0x9008
    xor ebx,ebx
    int 0x15
    jc NotSupport

GetMemInfo:
    add edi,20
    inc dword[0x9000]
    test ebx,ebx
    jz GetMemDone

    mov eax,0xe820
    mov edx,0x534d4150
    mov ecx,20
    int 0x15
    jnc GetMemInfo

GetMemDone:
TestA20:
    mov ax,0xffff
    mov es,ax
    mov word[ds:0x7c00],0xa200
    cmp word[es:0x7c10],0xa200
    jne SetA20LineDone
    mov word[0x7c00],0xb200
    cmp word[es:0x7c10],0xb200
    je End
    

SetA20LineDone:
    xor ax,ax
    mov es,ax

SetVideoMode:
    mov ax,3
    int 0x10
    
    cli
    lgdt [Gdt32Ptr]
    lidt [Idt32Ptr]

    mov eax,cr0
    or eax,1
    mov cr0,eax

    jmp 8:PMEntry

ReadError:
NotSupport:
End:
    hlt
    jmp End


[BITS 32]
PMEntry:
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov esp,0x7c00

    cld
    mov edi,0x70000
    xor eax,eax
    mov ecx,0x10000/4
    rep stosd

;                       0 1 1 = 3
;                       U W P 
;   We want the memory to be readable, writable and only accessed by the kernel. 


    ;  mov dword[0x70000],0x71007
    ;  mov dword[0x71000],10000111b

    ;  mov eax,(0xffff800000000000>>39)
    ;  and eax,0x1ff

    ;  mov dword[0x70000+eax*8],0x72003
    ;  mov dword[0x72000],10000011b

    mov dword[0x70000],0x71007
    mov dword[0x71000],0x72007

    mov esi,0x72000
    mov eax,10000111b
    mov ecx,512

.loop1:
    mov [esi],eax
    add eax,2*1024*1024
    add esi,8
    loop .loop1

;     mov dword[0x71008],0x76007

;     mov esi,0x76000
;     mov ecx,512

; .loop2:
;     mov [esi],eax
;     add eax,2*1024*1024
;     add esi,8
;     loop .loop2

;----------------------------------setting first 1G paging, each page is 2m, loop 512 times--------------------
    mov eax,(0xffff800000000000>>39)
    and eax,0x1ff
    mov dword[0x70000+eax*8],0x73000+3 

    mov eax,(0xffff800000000000>>30)
    and eax,0x1ff
    mov dword[0x73000+eax*8],0x74000+3

    mov esi,0x74000 
    mov eax,10000011b
    mov ecx,3   ;512 is 1gb, 3 refers 6mb, so 0~6mb is occupied by kernel.
    mov dword[0x90000],ecx
.loop3:
    mov [esi],eax
    add eax, 2*1024*1024
    add esi,8
    loop .loop3
;---------------------------------------------------------------------------------------------------------------
    mov eax,0x70000
    mov dword[0x90008],eax
    mov dword[0x9000a],0x73000
    mov dword[0x90018],0x74000
    mov dword[0x90020],0x71000


    lgdt [Gdt64Ptr]

    mov eax,cr4
    or eax,(1<<5)
    mov cr4,eax

    mov eax,0x70000
    mov cr3,eax

    mov ecx,0xc0000080
    rdmsr
    or eax,(1<<8)
    wrmsr

    mov eax,cr0
    or eax,(1<<31)
    mov cr0,eax

    jmp 8:LMEntry

PEnd:
    hlt
    jmp PEnd

[BITS 64]
LMEntry:
    mov rsp,0x7c00

    cld
    mov rdi,0x400000 ;kernel was supposed in the 0x100000(1MB). Now we copy it into the 0x400000
    mov rsi,0x10000
    mov rcx,51200/8
    rep movsq

    mov rax,0xffff800000400000
    jmp rax
    
LEnd:
    hlt
    jmp LEnd
    

DriveId:    db 0
ReadPacket: times 16 db 0

Gdt32:
    dq 0
Code32:
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 0xcf
    db 0
Data32:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 0xcf
    db 0
    
Gdt32Len: equ $-Gdt32

Gdt32Ptr: dw Gdt32Len-1
          dd Gdt32

Idt32Ptr: dw 0
          dd 0


Gdt64:
    dq 0
    dq 0x0020980000000000

Gdt64Len: equ $-Gdt64


Gdt64Ptr: dw Gdt64Len-1
          dd Gdt64
