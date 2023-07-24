; Interrupt 0x13 is a BIOS interrupt for disk services, such as reading from and writing to disk sectors. Here's a summary of how the registers are used:
; 
; - ah: The function number. This indicates the operation to be performed. (e.g., 0x02 for reading sectors)
; - al: For read/write operations, specifies the number of sectors to read/write. After the operation, al holds the number of sectors that were actually read/written.
; - ch: Lower 8 bits of the cylinder number, which indicates the starting location on the disk.
; - cl: Upper 2 bits of the cylinder number and sector number. Together with ch, forms a 10-bit cylinder number.
; - dh: Head number, indicating the disk head for the operation.
; - dl: Drive number, specifying which drive the operation is performed on.
; - es:bx: Buffer pointer. For read/write operations, points to the location in memory where the data to be written is stored, or where the read data should be placed.
; 
; After executing interrupt 0x13, the carry flag (CF) can be checked. If CF is set, an error occurred and the ah register will contain an error code.


disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0