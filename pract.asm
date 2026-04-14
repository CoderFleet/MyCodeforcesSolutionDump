           LXI     H, 8200H
           MOV     E, M
           INX     H
           MOV     A, M
           CALL    MUL16

           PUSH    H
           LXI     H, 8202H
           MOV     E, M
           INX     H
           MOV     A, M
           CALL    MUL16

           POP     D
           DAD     D
           SHLD    8204H
           HLT

MUL16:     LXI     H, 0000H
           MVI     D, 00H
           ORA     A
           JZ      EXT
BCK:       DAD     D
           DCR     A
           JNZ     BCK
EXT:       RET
