Draw    MACRO
      PUSHA
      MOV AX,1301H
      MOV CH,00H
      INT 10H
      POPA            
ENDM    Draw
    
Delay MACRO
       PUSHA
        Mov Ah,86H
        Mov Cx,0h
        Mov Dx,053e8H
        int 15h  
     POPA   
ENDM    Delay 

;--------------SEND WORD--------------------------
SEND_WORD MACRO 
    LOCAL AGAIN 
    CLD
    mov dx , 3FDH		; Line Status Register
    AGAIN: 
    IN al , dx 			;Read Line Status
    AND al , 00100000b
    JZ AGAIN
    mov dx , 3F8H  ; Transmit data register		
  	OUTSB                                          
ENDM SEND_WORD                                             
;-------------------------------------------- 

;------------------RECIEVE WORD-------------------
RECIEVE_WORD MACRO VALUE
    LOCAL CHK
    CLD
    mov dx , 3FDH		; Line Status Register	
	in al , dx
	AND al , 1
  	JZ chk	
    mov dx , 03F8H
  	INSB
  	chk:
ENDM RECIEVE_WORD
;--------------------------------------------

;-----------------------------------DRAW MISSILE------------------------------------
DRAW_MISSILE MACRO LOCATION,COLOR  
    LOCAL L1  
    PUSHA    
    MOV DX,LOCATION
    MOV BP,44H
    MOV CL,1 
    MOV BX, Color   
    MOV SI,DX
    ADD SI,3             
    L1:
    DRAW
    MOV AH,2
    INC DL    
    INT 10h  
    CMP DX,SI
    JNZ L1
    POPA
ENDM DRAW_MISSILE                           
;---------------------------------------------------------------------------------------
;------------------------------MOVE MISSILE----------------------------------------- 
;-----------------------------------------------------------------------------------------
MOVE_MISSILE_P1 MACRO STARTLOCATION,DIRECTION,CNT  ;0 MOVE RIGHT, 1 MOVE LEFT 
    LOCAL L1
    LOCAL L2
    PUSHA
    mov di,cnt
    MOV AH,DIRECTION
    MOV BX,STARTLOCATION 
    PUSHA
    ;DELAY 
    POPA         
    DRAW_MISSILE STARTLOCATION,0 
    CMP AH,0
    JNZ L1
    INC BX
    JMP L2
    L1:
    DEC BX
    L2:
    DRAW_MISSILE BX,0CCH  
   
    MOV MISSILES_LOC_P1X[di],BL
    POPA 
ENDM MOVE_MISSILE_P1
;----------------------------------------------------------------------------------------------------
MOVE_MISSILE_P2 MACRO STARTLOCATION,DIRECTION,CNT  ;0 MOVE RIGHT, 1 MOVE LEFT 
    LOCAL L1
    LOCAL L2
    PUSHA
    mov di,cnt
    MOV AH,DIRECTION
    MOV BX,STARTLOCATION 
    PUSHA
    ;DELAY
    popa          
    DRAW_MISSILE STARTLOCATION,0 
    
    CMP AH,0
    JNZ L1
    INC BX
    JMP L2
    L1:
    DEC BX
    L2:
    DRAW_MISSILE BX,0CCH 
    MOV MISSILES_LOC_P2X[di],BL
    POPA 
ENDM MOVE_MISSILE_P2 

;--------------------------------------------------------------------------------------- 
;-------------------------------DrawPlayer1----------------------------------------------#
Drawplayer1 MACRO LocationY,Color                                                    
      LOCAL PRINT
      PushA       
      MOV DL,0
      MOV DH,LocationY
      MOV BP,44H
      MOV CL,1 
      MOV BX, Color 
      MOV SI,3
      PRINT:   
      PUSH CX
      Draw  ;hna push w apop 3ashan b3ml fel proc ta7t CH
      POP CX
      MOV AH,2
      INC DH  
      int 10h 
      DEC SI
      JNZ PRINT 
      MOV AH,2 
      MOV DH,LocationY   
      INC DL
      ADD DH,1  
      int 10h
      Draw
      POPA
ENDM Drawplayer1    

;-------------------------------DrawPlayer2----------------------------------------------#
Drawplayer2 MACRO LocationY,Color 
    LOCAL PRINT2
      PushA   
      MOV DL,4FH
      MOV DH,LocationY
      MOV BP,44H
      MOV CL,1 
      MOV BX, Color 
      MOV SI,3
      PRINT2:
      PUSH CX
      Draw 
      POP CX
      MOV AH,2
      INC DH  
      int 10h 
      DEC SI
      JNZ PRINT2 
      MOV AH,2 
      MOV DH,LocationY   
      DEC DL      ;DAH EL FAR2 EL WA7ED 3N DRAW PLAYER 1
      ADD DH,1  
      int 10h
      Draw
      POPA
ENDM Drawplayer2    

;-------------------------------DrawObjects----------------------------------------------#
DRAWOBJECTS MACRO Locationy,Color
    LOCAL PRINT3
      PushA   
      MOV Dh,Locationy
      MOV Dl,27h
      MOV BP,44H
      MOV CL,1 
      MOV BX, Color 
      MOV SI,2
      PRINT3:
      push cx
        Draw
      pop cx 
      MOV AH,2
      INC DH  
      int 10h 
      DEC SI
      JNZ PRINT3 
      POPA
ENDM DRAWOBJECTS    
;-------------------------------MovePlayer1----------------------------------------------#

Moveplayer1 Macro currloc,direction
    LOCAL ENZEL
    LOCAL goawaay
    LOCAL ETLA3
    PUSHA  
    MOV CH,currloc
    PUSHA  
    PopA
    mov si,0048H                      
    CMP si,direction 
    JE ETLA3                          
    mov si,0050H
    cmp si,direction
    JE Enzel 
    jmp goawaay 
    ENZEL:
    cmp ch,14h
    jge goawaay
    Drawplayer1 CH,0h 
    inc CH
    Drawplayer1 CH,0EEH
    jmp goawaay  
    ETLA3:
    cmp ch,03h
    jle goawaay
    Drawplayer1 CH,0h 
    DEC CH
    Drawplayer1 CH,0EEH
    cmp CH,currloc 
    goawaay: 
    MOV CURRLOC,CH
    POPA 
ENDM Moveplayer1 
;-----------------------------------------------------------------

;-------------------------------MovePlayer2----------------------------------------------#
Moveplayer2 Macro currloc,direction
    LOCAL ENZEL
    LOCAL ETLA3
    LOCAL goaway
    PUSHA  
    MOV CH,currloc  
    PUSHA  
    ;Delay
    POPA
    mov si,0048H
    CMP si,direction 
    JE ETLA3
    mov si,0050H
    cmp si,direction
    JE  Enzel
     
    JMP goaway
    ENZEL:
    cmp ch,14h
    jge goaway 
    Drawplayer2 CH,0h 
    inc CH
    Drawplayer2 CH,033H 
    JMP goaway 
    ETLA3:
    cmp ch,03h
    jle goaway
    Drawplayer2 CH,0h 
    DEC CH
    Drawplayer2 CH,033H
    
    goaway:   
    MOV CURRLOC,CH 
    POPA
ENDM Moveplayer2     
                      
;-----------------------------------------------------------------------------------------                 
;-------------------------------MoveObjects----------------------------------------------#
;-----------------------------------------------------------------------------------------                 
;---------------------------------GetRandom---------------------------- 
GET_RANDOM_NO   Macro
LOCAL GETOUTTT
PUSHA  
    MOV AH, 2CH                   ;BA5OD EL SECONDS BTA3T L SA3A W ANDAHA MA3A 3
    INT 21H    
    MOV AL, DH                    
    AND AL,00000011b 
    CMP AL,3
    JNZ  GETOUTTT
    DEC AL
    GETOUTTT:                 
    MOV TYPEE,AL
POPA
ENDM GET_RANDOM_NO               
;---------------------------------GeNRandomOBJS---------------------------- 
GEN_RAND_OBJS   Macro 
    LOCAL ZYMANTA
    LOCAL L1
    LOCAL L2
    LOCAL LTANI
    LOCAL LTANI1
    LOCAL ENZL
    PUSHA
    MOV AH,10    
    CMP AH,TYPEE
    JNZ ZYMANTA             ; LW EL TYPEE BA2A 10 ELY HWA MSH HYB2A KDA ELA FEL BDAYA AW LW EL OBJECT WESEL LEL NHAYA
    GET_RANDOM_NO   
    
    MOV SI,OFFSET TYPEE    ;SEND RANDOM OBJECT TO THE OTHER PLAYER
    MOV DI,OFFSET TYPEE
    MOV BX,SI 
    MOV BP,DI
    MOV CH,INVITER
    CMP CH,0               ;INVITER IS THE ONE WHO GENERATE OBJS
    JZ LTANI
    L2:                 ;loop to detect overrun errors 
    SEND_WORD
    CMP BX,SI
    JNC L2
    JMP ENZL
    LTANI:                 ;loop to detect overrun errors 
    RECIEVE_WORD        ;THE RECIEVER RECIEVE GENERATED OBJS
    CMP BP,DI
    JNC LTANI
    ;JMP LTANI1
    
    ENZL:
    MOV AH,03h
    MOV OBJECT_LOC_Y,AH 
    ZYMANTA:
    MoveObjects OBJECT_LOC_Y,TYPEE 
    POPA
ENDM GEN_RAND_OBJS    
;-----------------------------------MoveObjects----------------------------
MoveObjects Macro  currloc,TYPEE 
    LOCAL kamel
    LOCAL GETOUTTA 
    LOCAL drawtype0 
    LOCAL drawtype1
    LOCAL drawtype2
    PUSHA  
    MOV CH,currloc
    ;PUSHA  
    ;Delay
    ;PopA
    DRAWOBJECTS CH,0h  
    inc CH
    MOV BL,2
    cmp BL,TYPEE
    jz  drawtype2 
    MOV BL,1
    cmp BL,TYPEE
    jz  drawtype1
    jnz drawtype0
    drawtype0:
    DRAWOBJECTS CH,22h      ;HEALTH BAR
    OBJECTS_STATUS HEALTH_BAR_LBL
    jmp kamel
    drawtype1:
    DRAWOBJECTS CH,0FFh     ;REFLECTING WALL
    OBJECTS_STATUS REFLECTING_WALL_LBL
    jmp kamel
    drawtype2:
    DRAWOBJECTS CH,55h      ;DECREASE PLAYER HEALTH
    OBJECTS_STATUS DECREMENT_HEALTH_LBL
    kamel:
    cmp CH,15h
    jnz GETOUTTA 
    DRAWOBJECTS CH,0h  
    MOV bl,10
    MOV TYPEE,bl   
    GETOUTTA: 
    MOV currloc,CH 
    POPA 
ENDM MoveObjects           
            
 
;--------------------------------------CHECK KEY PRESSED----------------------------------#
CHECK MACRO KEY ,P
    LOCAL GOAWAY1
    LOCAL HANDLEMP1
    LOCAL PLAYER1UP
    LOCAL PLAYER1DOWN
    LOCAL HANDLEMP2 
    LOCAL PLAYER2DOWN 
    LOCAL PLAYER2UP  
    LOCAL chkmainplayer
    PUSHA
    cmp P,1
    jz chkmainplayer  
    CMP KEY,48H  ;CHECK IF UP ARROW IS PRESSED
    JZ PLAYER2UP          
    
    CMP KEY,50H     ;CHECK IF DOWN ARROW IS PRESSED
    JZ PLAYER2DOWN
     
    CMP KEY,25H  ; BA CHECK LW K
    JE  HANDLEMP2 
    
    JMP GOAWAY1 
         
    chkmainplayer:
    CMP KEY,48H
    JZ PLAYER1UP   ;CHECK IF W KEY IS PRESSESD
   
    CMP KEY,50H
    JZ PLAYER1DOWN 
    
    CMP KEY,25H  ; BA CHECK LW F
    JE HANDLEMP1
    
  
    JMP GOAWAY1
       ;CHECK S KEY IS PRESSED     
    PLAYER1UP:
    PLAYER1_STATUS MOVE_UP_LBL
    MOVEPLAYER1 LOCP1,KEY
    JMP GOAWAY1
    PLAYER1DOWN:
    PLAYER1_STATUS MOVE_DOWN_LBL
    MOVEPLAYER1 LOCP1,KEY
    JMP GOAWAY1 
    PLAYER2UP:
    PLAYER2_STATUS MOVE_UP_LBL
    MOVEPLAYER2 LOCP2,KEY
    JMP GOAWAY1 
    PLAYER2DOWN:
    PLAYER2_STATUS MOVE_DOWN_LBL
    MOVEPLAYER2 LOCP2,KEY
    JMP GOAWAY1  
    HANDLEMP1:
    PUSHA
    MOV BX,MISSILES_P1_CNT
    INC BX
    MOV MISSILES_P1_CNT,BX
    mov bl,LOCP1
    add bl,1
    MOV DH,bl
    MOV DL,02H;x for player 1
    MOV BX,MISSILES_P1_CNT
    MOV MISSILES_LOC_P1X[BX-1],Dl
    MOV MISSILES_LOC_P1y[BX-1],Dh
    MOV MISSILE_DIRECTIONP1[BX-1],0 
    PLAYER1_STATUS FIRE_LBL
    JMP GOAWAY1
    POPA 
    HANDLEMP2:
    PUSHA 
    MOV BX,MISSILES_P2_CNT
    INC BX
    MOV MISSILES_P2_CNT,BX 
    mov bl,LOCP2
    add bl,1
    MOV DH,bl
    MOV DL,4BH ;x for player 2
    MOV BX,MISSILES_P2_CNT
    MOV MISSILES_LOC_P2x[BX-1],Dl   
    MOV MISSILES_LOC_P2y[BX-1],Dh
    MOV MISSILE_DIRECTIONP2[BX-1],1
    PLAYER2_STATUS FIRE_LBL    
    POPA             
                 
    GOAWAY1:
    POPA
ENDM CHECK 
 
 
;--------------------------------------PLAYERS HEALTH BAR----------------------------------#
DRAW_HEALTH_BAR MACRO 
    LOCAL REFLECT
    LOCAL UPDATE
    PUSHA    
    MOV AH,INVITER
    CMP AH,1
    JNZ REFLECT
    MOV AH,2
    MOV DX,0101h
    INT 10H                       ;MOVE CURSER TO WRITE PLAYER 1 NAME
    MOV AH, 9
    MOV DX, offset P1NAME[2]    ;WRITING PLAYER NAME
    INT 21h
    MOV AH,2
    MOV DX,0135h
    INT 10H                    ;MOVE CURSOR TO WRITE PLAYER2 NAME 
    MOV AH, 9
    MOV DX, offset P2NAME[2]    ;WRITING PLAYER NAME
    INT 21h
    JMP UPDATE
    REFLECT:
    MOV AH,2
    MOV DX,0101h
    INT 10H                       ;MOVE CURSER TO WRITE PLAYER 1 NAME
    MOV AH, 9
    MOV DX, offset P2NAME[2]    ;WRITING PLAYER NAME
    INT 21h
    MOV AH,2
    MOV DX,0135h
    INT 10H                    ;MOVE CURSOR TO WRITE PLAYER2 NAME 
    MOV AH, 9
    MOV DX, offset P1NAME[2]    ;WRITING PLAYER NAME
    INT 21h
    UPDATE: 
    UPDATE_HEALTH_BAR
    MOV AH,2
    MOV DX,0200H
    INT 10H
    MOV AH, 9
    MOV DX, offset END_OF_HEALTH_BAR
    INT 21h    
    POPA
ENDM DRAW_HEALTH_BAR 

;---------------------------------UPDATE HEALTH BAR----------------------------
UPDATE_HEALTH_BAR MACRO 
    LOCAL A
    LOCAL B
    PUSHA    
    MOV AH,2
    MOV DX,0111h 
    INT 10H         ;MOVING CURSOR TO DRAW PLAYER1 HEALTH BAR
    MOV BP,44H
    MOV CL,10  
    MOV BX,0H       ;CLEAR HEALTHBAR TO DRAW THE NEW ONE
    DRAW
    MOV DX,0111h    ;DRAW THE NEW HEALTHBAR
    INT 10H
    MOV BP,44H
    MOV CL,PLAYER1_HEALTH    
    CMP CL,10
    JL A             ;IF PLAYER 1 HEALTH > 10 SET HEALTH TO 10
    MOV CL,10
    MOV PLAYER1_HEALTH,CL
    A: 
    MOV BX,0EEH
    DRAW
    MOV AH,2
    MOV DX,0145h
    INT 10H            ;MOVE CURSER TO DRAW PLAYER2 HEALTHBAR
    MOV BP,44H         ;CLEAR HEALTHBAR TO DRAW THE NEW ONE
    MOV CL,10 
    MOV BX,00H
    DRAW
    MOV BP,44H         ;DRAW THE NEW HEALTHBAR
    MOV CL,PLAYER2_HEALTH 
    CMP CL,10
    JL B             ;IF PLAYER 2 HEALTH > 10 SET HEALTH TO 10
    MOV CL,10
    MOV PLAYER2_HEALTH,CL
    B:
    MOV BX,033H
    DRAW
    POPA
ENDM UPDATE_HEALTH_BAR
;---------------------------------MOVE ALL MISSILES----------------------------
move_all_missiles   Macro 
    LOCAL SHOFELTANNY
    LOCAL movemissilesP1
    LOCAL movemissilesP2
    LOCAL GETOUT
    LOCAL INC_PTR2
    LOCAL INC_PTR1 
    LOCAL SKIP1
    LOCAL SKIP2
    PUSHA    
    MOV BX,MISSILES_P1_PTR
    DEC BX
    MOV DX,MISSILES_P1_CNT
    MOV SI,MISSILES_P1_CNT
    DEC SI
    CMP DX,MISSILES_P1_PTR              ;LW L COUNT = PTR YB2A MAFESH MISSILES HTTRSM L PLAYER 1
    JZ SHOFELTANNY
    movemissilesP1:
    INC BX 
    MOV CL,MISSILES_LOC_P1X[BX]
    MOV CH,MISSILES_LOC_P1Y[BX]
    CMP CL,77
    JE INC_PTR1
    CMP CL,0
    JE INC_PTR1
    MOVE_MISSILE_P1 CX,MISSILE_DIRECTIONP1[BX],BX 
    JMP SKIP1
    INC_PTR1:   
    MOV DI,1
    ADD MISSILES_P1_PTR,DI  
    DRAW_MISSILE CX,0 
    SKIP1:
    CMP BX,SI
    JNZ movemissilesP1
    SHOFELTANNY:
    MOV BX,MISSILES_P2_PTR
    DEC BX 
    MOV DX,MISSILES_P2_CNT
    MOV SI,MISSILES_P2_CNT
    DEC SI
    CMP DX,MISSILES_P2_PTR                  ;LW L COUNT = PTR YB2A MAFESH MISSILES HTTRSM L PLAYER 2
    JZ GETOUT
    movemissilesP2:
    INC BX 
    MOV CL,MISSILES_LOC_P2X[BX]
    MOV CH,MISSILES_LOC_P2Y[BX]
    CMP CL,0
    JE INC_PTR2
    CMP CL,77
    JE INC_PTR2
    MOVE_MISSILE_P2 CX,MISSILE_DIRECTIONP2[BX],BX
    JMP SKIP2
    INC_PTR2:
    MOV DI,1 
    ADD MISSILES_P2_PTR,DI
    DRAW_MISSILE CX,0
    SKIP2:
    CMP BX,SI
    JNZ movemissilesP2
    GETOUT:     
    POPA      
ENDM move_all_missiles

;------------------------------------------------------------------------------------------
;------------------------------------CHECK ALL MISSILES MACROS-----------------------------
;------------------------------------------------------------------------------------------

;--------------------------CHECK PLAYER 1 HEALTH------------------------------
CHECK_P1_HEALTH MACRO
    LOCAL CHECK_P1_HEALTH
    LOCAL IN_RANGE_P1
    LOCAL EXIT
    LOCAL DECREMENT_P1_HEALTH
    LOCAL L
    PUSHA
    CMP CL,1                             ;CHECK P1
    JZ CHECK_P1_HEALTH                   ;CHECK IF THE MISSILE AT THE SAME X POSITION OF PLAYER1
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T REACH PLAYER1
    CHECK_P1_HEALTH:                     
    CMP CH,LOCP1                         ;CHECK IF THE MISSILE AT THE SAME Y POSITION OF PLAYER1
    JGE IN_RANGE_P1
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T TOUCH PLAYER1
    IN_RANGE_P1:
    MOV AH,2                             ;CHECK IF THE MISSILE HITS PLAYER 1
    ADD AH,LOCP1
    CMP AH,CH
    JGE DECREMENT_P1_HEALTH    
    JMP EXIT                             ;IF NOT RETURN
    DECREMENT_P1_HEALTH:
    MOV AH,PLAYER1_HEALTH
    DEC AH                               ;DECREMENT P1 HEALTH
    CMP AH,0
    JG L
    MOV AH,0
    L:
    MOV PLAYER1_HEALTH,AH
    EXIT:
    POPA                
ENDM CHECK_P1_HEALTH 


;------------------------CHECK PLAYER 2 HEALTH-----------------------------

CHECK_P2_HEALTH MACRO
    LOCAL CHECK_P2_HEALTH
    LOCAL EXIT
    LOCAL DECREMENT_P2_HEALTH
    LOCAL IN_RANGE_P2
    LOCAL L
    PUSHA
    CMP CL,76                            ;CHECK P2
    JZ CHECK_P2_HEALTH                   ;CHECK IF THE MISSILE AT THE SAME X POSITION OF PLAYER2
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T REACH PLAYER1
    CHECK_P2_HEALTH:                     
    CMP CH,LOCP2                         ;CHECK IF THE MISSILE AT THE SAME Y POSITION OF PLAYER2
    JGE IN_RANGE_P2
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T TOUCH PLAYER1
    IN_RANGE_P2:
    MOV AH,2                             ;CHECK IF THE MISSILE HITS PLAYET 2
    ADD AH,LOCP2
    CMP AH,CH
    JGE DECREMENT_P2_HEALTH    
    JMP EXIT                             ;IF NOT GO AND CHECK PLAYER1 HEALTH
    DECREMENT_P2_HEALTH:
    MOV AH,PLAYER2_HEALTH
    DEC AH
    CMP AH,0
    JG L
    MOV AH,0
    L:
    MOV PLAYER2_HEALTH,AH                ;DECREMENT P2 HEALTH
    EXIT:                
    POPA
ENDM CHECK_P2_HEALTH

;----------------------------CHECK OBJECT TOUCHED THE MISSILE OF PLAYER 1--------------------------
CHECK_OBJECT_P1 MACRO
    LOCAL CHECK_X_RANGE
    LOCAL EXIT
    LOCAL CHECK_Y_RANGE_1
    LOCAL CHECK_Y_RANGE_2
    LOCAL OBJECT_TYPE
    LOCAL TYPE1
    LOCAL TYPE2 
    LOCAL H
    LOCAL L
    PUSHA
    CMP CL,25H                           
    JGE  CHECK_X_RANGE                   ;CHECK IF THE MISSILE IN RANGE OF X OF OBJECT
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T REACH OBJECT
    CHECK_X_RANGE:                     
    CMP CL,27H                         
    JLE CHECK_Y_RANGE_1
    JMP EXIT                             
    CHECK_Y_RANGE_1:
    CMP CH,OBJECT_LOC_Y                          
    JGE CHECK_Y_RANGE_2
    JMP EXIT                            
    CHECK_Y_RANGE_2:
    MOV AH,2                             
    ADD AH,OBJECT_LOC_Y 
    CMP AH,CH
    JGE OBJECT_TYPE    
    JMP EXIT
    OBJECT_TYPE:
    MOV CL,TYPEE
    CMP CL,1
    JZ TYPE1                           ;IF THE OBJECT IS HEALTH BAR
    CMP CL,2
    JZ TYPE2
    CMP CL,0
    JNZ EXIT
    MOV AH,PLAYER1_HEALTH
    INC AH 
    CMP AH,10
    JL L
    MOV AH,10
    L:
    MOV PLAYER1_HEALTH,AH              ;INCREMENT HEALTH
    JMP EXIT
    TYPE1:                             ;IF THE OBJECT IS REFLECTING WALL                               
    MOV MISSILE_DIRECTIONP1[BX],1      ;INVERT MISSILE DIRECTION
    JMP EXIT
    TYPE2:
    MOV AH,PLAYER1_HEALTH              ;IF THE OBJECT IS DECREASE HEALTH
    DEC AH
    CMP AH,0
    JG H
    MOV AH,0 
    PLAYER1_STATUS LOSER_LBL
    PLAYER2_STATUS WINNER_LBL
    H:
    MOV PLAYER1_HEALTH,AH              ;DECREMENT HEALTH
    EXIT:
    POPA
ENDM CHECK_OBJECT_P1  

;----------------------------CHECK OBJECT TOUCHED THE MISSILE OF PLAYER 2--------------------------
CHECK_OBJECT_P2 MACRO
    LOCAL CHECK_X_RANGE
    LOCAL EXIT
    LOCAL CHECK_Y_RANGE_1
    LOCAL CHECK_Y_RANGE_2
    LOCAL OBJECT_TYPE
    LOCAL TYPE1
    LOCAL TYPE2
    LOCAL H
    LOCAL L
    PUSHA
    CMP CL,25H                           
    JGE  CHECK_X_RANGE                   ;CHECK IF THE MISSILE IN RANGE OF X OF OBJECT
    JMP EXIT                             ;EXIT IF MISSILE DIDN'T REACH OBJECT
    CHECK_X_RANGE:                     
    CMP CL,27H                         
    JLE CHECK_Y_RANGE_1
    JMP EXIT                             
    CHECK_Y_RANGE_1:
    CMP CH,OBJECT_LOC_Y                          
    JGE CHECK_Y_RANGE_2
    JMP EXIT                            
    CHECK_Y_RANGE_2:
    MOV AH,2                             
    ADD AH,OBJECT_LOC_Y 
    CMP AH,CH
    JGE OBJECT_TYPE    
    JMP EXIT
    OBJECT_TYPE:
    MOV CL,TYPEE
    CMP CL,1
    JZ TYPE1                           ;IF THE OBJECT IS HEALTH BAR
    CMP CL,2
    JZ TYPE2 
    CMP CL,0
    JNZ EXIT
    MOV AH,PLAYER2_HEALTH
    INC AH 
    CMP AH,10
    JL L
    MOV AH,10
    L:
    MOV PLAYER2_HEALTH,AH              ;INCREMENT HEALTH
    JMP EXIT
    TYPE1:                            ;IF THE OBJECT IS REFLECTING WALL
    MOV MISSILE_DIRECTIONP2[BX],0      ;INVERT MISSILE DIRECTION
    JMP EXIT
    TYPE2:
    MOV AH,PLAYER2_HEALTH              ;IF THE OBJECT IS DECREASE HEALTH
    DEC AH
    CMP AH,0
    JG H
    MOV AH,0
    PLAYER1_STATUS WINNER_LBL
    PLAYER2_STATUS LOSER_LBL
    H:
    MOV PLAYER2_HEALTH,AH              ;DECREMENT HEALTH
    EXIT:
    POPA
ENDM CHECK_OBJECT_P2 

;----------------------------------CHECK ALL MISSILES MACRO-------------------------
CHECK_ALL_MISSILES MACRO 
    LOCAL SHOFELTANNY
    LOCAL CHECKP1_MISSILES
    LOCAL EXIT
    LOCAL CHECKP2_MISSILES
    PUSHA                               
    MOV BX,MISSILES_P1_PTR              ;FOR PLAYER1 MISSILES
    DEC BX
    MOV DX,MISSILES_P1_CNT
    MOV SI,MISSILES_P1_CNT
    DEC SI
    CMP DX,MISSILES_P1_PTR              ;IF PTR == CNT DON'T LOOP
    JZ SHOFELTANNY
    CHECKP1_MISSLES:                    ;LOOP ON PLAYER 1 ALL MISSILES
    INC BX 
    MOV CL,MISSILES_LOC_P1X[BX]
    MOV CH,MISSILES_LOC_P1Y[BX]
    CHECK_OBJECT_P1                     ;OBJECT EFFECT ON MISSILES OF PLAYER 1
    CHECK_P1_HEALTH
    CHECK_P2_HEALTH     
    CMP BX,SI          
    JNZ CHECKP1_MISSLES
                                        ;FOR PLAYER 2 MISSILES
    SHOFELTANNY:
    MOV BX,MISSILES_P2_PTR
    DEC BX
    MOV DX,MISSILES_P2_CNT
    MOV SI,MISSILES_P2_CNT
    DEC SI
    CMP DX,MISSILES_P2_PTR              ;IF PTR == CNT DON'T LOOP
    JZ EXIT
    CHECKP2_MISSILES:                    ;LOOP ON PLAYER 1 ALL MISSILES
    INC BX 
    MOV CL,MISSILES_LOC_P2X[BX]
    MOV CH,MISSILES_LOC_P2Y[BX]
    CHECK_OBJECT_P2                      ;OBJECT EFFECT ON MISSILES OF PLAYER 2
    CHECK_P1_HEALTH
    CHECK_P2_HEALTH 
                         
    CMP BX,SI          
    JNZ CHECKP2_MISSILES
    EXIT:
    POPA 
ENDM CHECK_ALL_MISSILES 


;--------------------------------------------------------------------------
;---------------------------------STATUS BAR-------------------------------
;--------------------------------------------------------------------------

;-----------------------------DRAW STATUS BAR------------------------------
DRAW_STATUS_BAR MACRO
    PUSHA
    mov ah,2
    mov dx,1700h
    int 10h
    mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR  ;DRAW STATUS BAR HEADER LIKE THAT "______"
    INT 21H
    mov ah,2
    mov dx,181Ah
    INT 10H
    mov dl,'|'          ;SPLIT STATUS BAR INTO 3
    int 21h
    mov dx,1834h 
    INT 10H
    mov dl,'|'
    INT 21H
    POPA
ENDM DRAW_STATUS_BAR 

;---------------------------PLAYER 1 STATUS BAR----------------------------
PLAYER1_STATUS MACRO MSG
    PUSHA
    mov ax,0600h
    mov bh,07
    mov cx,1800H     ;CLEAR PLAYER STATUS BAR
    mov dx,1819H
    int 10h
    MOV BH,0
    MOV AH,2
    MOV DX,180Ah
    INT 10H 
    mov ah, 9
    mov dx, offset MSG
    int 21h
    POPA
ENDM PLAYER1_STATUS
;--------------------------PLAYE 2 STATUS BAR-------------------------------         
PLAYER2_STATUS MACRO MSG
    PUSHA
    mov ax,0600h
    mov bh,07
    mov cx,1835H     ;CLEAR PLAYER STATUS BAR
    mov dx,184FH
    int 10h
    MOV BH,0
    MOV AH,2
    MOV DX,183Fh
    INT 10H  
    mov ah, 9
    mov dx,OFFSET MSG
    int 21h
    POPA
ENDM PLAYER2_STATUS
;----------------------------OBJECTS STATUS BAR-------------------------------         
OBJECTS_STATUS MACRO MSG
    PUSHA
    mov ax,0600h
    mov bh,07
    mov cx,181BH     ;CLEAR OBJECTS STATUS BAR
    mov dx,1833H
    int 10h
    MOV BH,0
    MOV AH,2
    MOV DX,1820h
    INT 10H  
    mov ah, 9
    mov dx, offset MSG
    int 21h
    POPA
ENDM OBJECTS_STATUS     
;-----------------------------------------Main Menu-----------------------------------------
MainMenu Macro 
    LOCAL EXIT
    LOCAL GOTOGAME
    LOCAL GETANOTHERKEY 
    LOCAL TMAMCAPITAL
    LOCAL GETname1again
    LOCAL GETname2again 
    LOCAL safarp1name
    GETname1again:
    ;raga3 p1name b esfar tany 
    pusha
    mov cx,15
    safarp1name:
    mov di,cx
    mov p1name[di],'$'
    loop safarp1name
    popa
    mov ah,2 
    MOV BH,0
    mov dx,0
    int 10h
    ;CLEAR SCREEN
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h 
    ;GET PLAYER 1 NAME
    ;MOVE CURSOR 
    MOV BH,0
    mov ah,2
    mov dx,0B1Ah
    int 10h
    mov ah, 9
    mov dx, offset mesP1
    int 21h
    ;MOVE CURSOR
    mov ah,2
    mov dx,0C1Fh
    int 10h   
    mov ah,0AH
    mov dx,offset P1NAME
    int 21h 
    ;Check awl 7arf  
    cmp P1NAME[2],65
    jl GETname1again
    cmp P1NAME[2],90
    jle GETname2again
    cmp P1NAME[2],97
    jl GETname1again
    cmp P1NAME[2],122
    jg  GETname1again
    GETname2again:   
    ;CLEAR SCREEN
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
    ;EL3AB AW O5ROG
     ;MOVE CURSOR 
    MOV BH,0
    mov ah,2
    mov dx,0B18h
    int 10h
    mov bh,0   
    mov ah, 9
    mov dx, offset startg
    int 21h 
    ;move cursor
    MOV BH,0
    mov ah,2
    mov dx,0D18h
    int 10h  
    mov ah, 9
    mov dx, offset EXITG
    int 21h 
    ;WAIT FOR KEY 
    GETANOTHERKEY:
    mov ah,0
    int 16h 
    ;CHECK L KEY
    CMP AH,01H
    JZ EXIT
    CMP AH,3CH
    JZ GOTOGAME
    JNZ GETANOTHERKEY
    EXIT:
    mov ah,04CH ;DOS "terminate" function
    int 021H 
    GOTOGAME:
    Invitation
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h   
    POPA
ENDM MainMenu
;--------------------------------------------

;----------PORT INITIALIZATION---------------
PORT MACRO 
    PUSHA
    mov dx,3fdh 			; Line Control Register
    mov al,10000000b		;Set Divisor Latch Access Bit
    out dx,al			;Out it
    mov dx,3f8h			
    mov al,0ch			
    out dx,al
    mov dx,3f9h
    mov al,00h
    out dx,al
    mov dx,3fbh
    mov al,00011011b
    out dx,al
    POPA                                             
ENDM PORT
                                             
;--------------------------------------------  

;--------------SEND--------------------------
SEND MACRO VALUE 
    LOCAL AGAIN
    pusha
    mov dx , 3FDH		; Line Status Register
    AGAIN:
    PUSH AX 
    In al , dx 			;Read Line Status
    AND al , 00100000b
    JZ AGAIN
    mov dx , 3F8H
    POP AX		; Transmit data register
    mov  al,VALUE
  	out dx , al
  	popa                                          
ENDM SEND                                             
;-------------------------------------------- 

;------------------RECIEVE-------------------
RECIEVE MACRO VALUE
    LOCAL CHK
    mov dx , 3FDH		; Line Status Register	
	in al , dx
	;push ax
	AND al , 1
  	JZ chk	
    mov dx , 03F8H
  	in al , dx 
  	mov VALUE , al
  	chk:
ENDM RECIEVE
;------------------------------------------------------------

;--------------SEND YOUR NAME TO THE OTHER PLAYER------------
SEND_NAME MACRO
    LOCAL LOOOP
    LOCAL L1
    LOCAL L2
    PUSHA
    ;send player name to the other player
    MOV CX,16
    MOV SI,OFFSET P1NAME
    MOV DI,OFFSET P2NAME
    ADD SI,2
    ADD DI,2  
    LOOOP:
    MOV BX,SI
    MOV BP,DI 
    L1:                 ;loop to detect overrun errors 
    SEND_WORD
    CMP BX,SI
    JNC L1
    L2:
    RECIEVE_WORD
    CMP BP,DI
    JNC L2
    LOOP LOOOP
    POPA
ENDM SEND_NAME 
;------------------------------------------------------------

;------------------Invitatioon key------------------- 
SendInvitation MACRO 
    local skip
  pusha 
    mov ah,1                                     ;TAKE A KEY FROM THE USER
    int 16h
    CMP AH,	3Ch  
    JNZ SKIP
    MOV AL,0
    XCHG AL,AH                                   ;USE THE KEY TAKEN FROM THE USER
    send al 
    mov sent,1
    skip:
  	popa
ENDM SendInvitation    
;------------------Invitatioon key------------------- 
RecieveInvitation MACRO 
     local skip
  pusha 
  recieve al
  CMP al,	3Ch 
  jnz skip 
  mov recieved ,1
    skip:
  	popa
ENDM RecieveInvitation        
;------------------Invitatioon key together-------------------
Invitation MACRO 
  local SendToStartTheGame
  local CheckRecOnly
  local checkall
  local outt 
  local CheckRec1Only
  local sendtostart1thegame  
  
  pusha
   MOV AH,2
    MOV DX,1600h
    INT 10H  
     mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR
    int 21h    
   checkall:
   mov ax,0 
   mov bl,recieved
   mov bh,sent
   cmp bl,bh
   jg sendtostart1thegame      ;recieved and doesn't send
   jl CheckRec1Only            ;sent but doesn't recieve
   
   cmp si,1                   ;here they are equal 
   jz outt                    ;but i don't know having value or not
                              ;so i'll check 
                              ;if either of them if have value 
                              ;then both are 1 and i'll go to game 
                              ;if not i'll loop 
   mov ax,0 
   RecieveInvitation
   SendInvitation
   jmp checkall
   
   
  sendtostart1thegame: 
  MOV AWAY,1
  MOV INVITER,0 
    MOV AH,2
    MOV DX,1700h
    INT 10H    
    mov ah, 9
    mov dx, offset sendtostartmsg
    int 21h           
    sendtostartthegame:
     SendInvitation
     cmp sent,1
     jz outt
     jnz sendtostartthegame
  
  
  CheckRec1Only:
  MOV INVITER,1 
  MOV AWAY,0
      MOV AH,2
    MOV DX,1700h
    INT 10H    
    mov ah, 9
    mov dx, offset reconlymsg
    int 21h   
  CheckRecOnly:  
  mov ax,0
  RecieveInvitation
  cmp recieved,1
  jnz CheckRecOnly

    outt:
  	popa
ENDM Invitation 
;-------------------------------------------------------

;-------------------------------------------------------
;----------------------CHATTING-------------------------
;-------------------------------------------------------

;--------------SEND_AX--------------------------
SEND_AX MACRO VALUE 
    LOCAL AGAIN
    pusha
    mov dx , 3FDH		; Line Status Register
    PUSH AX 
    AGAIN:
    In AX , dx 			;Read Line Status
    AND AX , 00100000b
    JZ AGAIN
    mov dx , 3F8H
    POP AX		; Transmit data register
    mov  aX,VALUE
  	out dx , aX
  	popa                                          
ENDM SEND_AX                                             
;-------------------------------------------- 

;------------------RECIEVE_AX-------------------
RECIEVE_AX MACRO VALUE
    LOCAL CHK
    mov dx , 3FDH		; Line Status Register	
	in AX , dx
	AND AX , 1
  	JZ chk	
    mov dx , 03F8H
  	in aX , dx 
  	mov VALUE , aX
  	chk:
ENDM RECIEVE
;------------------------------------------------------------

DRAW_CHATTING MACRO
    PUSHA
    ;CLEAR SCREEN
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h 
    MOV BH,0
    mov ah,2       ;MOVE CURSOR
    mov dx,0002h
    int 10h
    mov ah, 9          ;DISPLAY PLAYER1 NAME 
    mov dx, offset P1NAME+2
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,0B00h
    int 10h
    mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR  ;DRAW SCREEN SPLITTER LIKE THAT "______"
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,0C02h
    int 10h
    mov ah, 9          ;DISPLAY PLAYER2 NAME 
    mov dx, offset P2NAME+2
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,1700h
    int 10h
    mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR  ;DRAW SCREEN SPLITTER LIKE THAT "______"
    INT 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,1800h
    int 10h
    mov ah, 9          ;DISPLAY PLAYER2 NAME 
    mov dx, offset ENDCHATTING
    int 21H
    mov ah, 9          ;DISPLAY PLAYER2 NAME 
    mov dx, offset P2NAME+2
    int 21H 
    mov ah, 9          ;DISPLAY PLAYER2 NAME 
    mov dx, offset ENDCHATTING2
    int 21H
    POPA
ENDM DRAW_CHATTING    
;-------------------------------------------------------------
;-------------------------CHATTING----------------------------
CHATTING MACRO
    LOCAL LOOOP
    LOCAL EXIT
    LOCAL REC 
    LOCAL LOOPTANI
    LOCAL ENTER1
    LOCAL ENTER2
    LOCAL P1 
    LOCAL REC2
    LOCAL KML
    PUSHA
    DRAW_CHATTING
    LOOOP:
    SCROLL
    
    
    mov ah,1                                     ;TAKE A KEY FROM THE USER
    int 16h       
    CMP AH,1
    JZ REC2 
    CMP AH,3DH
    JNZ KML
    MOV AL,0B2H
    KML:
    SEND_AX AX                  ;SEND THE CHAR TO THE OTHER PLAYER
    CMP AH,3DH                  ;IF F3 IS PRESSED EXIT CHATTING MODE
    JZ EXIT
    CMP AH,1CH
    JZ ENTER1                ;IF ENTER KEY IS PRESSED GOTO THE NEXT LINE 
    PUSH AX              
    MOV AH,2
    MOV DX,P1CURSOR
    INT 10H
    INC DX
    MOV P1CURSOR,DX      ;INCREMENT CURSOR FOR THIS PLAYER
    POP AX
    mov ah,2
    MOV DL,AL
    int 21h
        
    REC:                 ;CHECK IF THE OTHER PLAYER SEND CHAR TO THIS PLAYER
    mov ah,0                    ;CLEAR BUFFER
    int 16h
    REC2: 
    MOV AX,0
    MOV DX,AX
    PUSH DX
    RECIEVE_AX AX    
    POP DX
    CMP DX,AX
    JZ LOOPTANI
    PUSH AX
    CMP AL,0B2H
    JZ EXIT
    CMP AL,0DH
    JZ ENTER2
    MOV AH,2
    MOV DX,P2CURSOR
    INT 10H
    INC DX
    MOV P2CURSOR,DX      ;INCREMENT CURSOR FOR THE OTHER PLAYER
    POP AX               ;DISPLAY RECIEVED CHAR
    MOV DL,AL
    MOV AH,2
    int 21h 
    JMP LOOPTANI
    
    ENTER1:              ;IF THE PLAYER CLICK ON ENTER HANDLE PLAYER1 CURSOR
    MOV DX,P1CURSOR
    INC DH
    MOV DL,6
    MOV P1CURSOR,DX
    JMP REC
    
    ENTER2:
    MOV DX,P2CURSOR
    INC DH
    MOV DL,6
    MOV P2CURSOR,DX    
    LOOPTANI:      
    JMP LOOOP    
    EXIT: 
    POPA
ENDM CHATTING 
;----------------------------------------------------------
;--------------------SCROLL--------------------------------
SCROLL MACRO
    LOCAL DHOOFLTANI
    LOCAL EXIT
    PUSHA
    MOV AX,P1CURSOR      ;SCROLL P1 CHAT IF THE CURSOR IN LINE # B
    CMP AH,0BH
    JL DHOOFLTANI
    mov ax,0601h
    mov bh,07
    mov cx,0100H
    mov dx,0A50H
    int 10h   
    MOV DX,0A06H
    MOV P1CURSOR,DX
    MOV BH,0
    DHOOFLTANI:
    MOV AX,P2CURSOR      ;SCROLL P2 CHAT IF THE CURSOR IN LINE # B
    CMP AH,017H
    JL EXIT
    mov ax,0601h
    mov bh,07
    mov cx,0D00H
    mov dx,1650H
    int 10h 
    MOV DX,1606H
    MOV P2CURSOR,DX
    MOV BH,0
    EXIT:
    POPA
ENDM SCROLL
;------------------------------------------------------------
;----------------DRAW IN APP CHATTING------------------------
DRAW_IN_APP MACRO
    PUSHA
    mov ah,2       ;MOVE CURSOR
    mov dx,1400h
    int 10h
    mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR  ;DRAW SCREEN SPLITTER LIKE THAT "______"
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,1500h
    int 10h
    mov ah, 9
    mov dx, offset P1NAME+2
    int 21H
    mov dx, offset NO2TTEN
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,1600h
    int 10h
    mov ah, 9
    mov dx, offset P2NAME+2
    int 21H
    mov dx, offset NO2TTEN
    int 21H
    mov ah,2       ;MOVE CURSOR
    mov dx,1700h
    int 10h
    mov ah, 9
    mov dx, offset END_OF_HEALTH_BAR
    INT 21H
    POPA
ENDM DRAW_IN_APP
;------------------------------------------------------------
;----------------------CHAT IN APP---------------------------
CHAT_IN MACRO
    LOCAL LOOOP
    LOCAL EXIT
    LOCAL REC 
    LOCAL LOOPTANI
    LOCAL ENTER1
    LOCAL ENTER2
    LOCAL P1 
    LOCAL REC2
    LOCAL KML
    PUSHA
    DRAW_IN_APP
    LOOOP:
    SCROLL_IN
    
    
    mov ah,1                                     ;TAKE A KEY FROM THE USER
    int 16h       
    CMP AH,1
    JZ REC2 
    CMP AH,3FH
    JNZ KML
    MOV AL,0B2H
    KML:
    SEND_AX AX                  ;SEND THE CHAR TO THE OTHER PLAYER
    CMP AH,3FH                  ;IF F3 IS PRESSED EXIT CHATTING MODE
    JZ EXIT
    CMP AH,1CH
    JZ ENTER1                ;IF ENTER KEY IS PRESSED GOTO THE NEXT LINE 
    PUSH AX              
    MOV AH,2
    MOV DX,P1_IN_CURSOR
    INT 10H
    INC DX
    MOV P1_IN_CURSOR,DX      ;INCREMENT CURSOR FOR THIS PLAYER
    POP AX
    mov ah,2
    MOV DL,AL
    int 21h
        
    REC:                 ;CHECK IF THE OTHER PLAYER SEND CHAR TO THIS PLAYER
    mov ah,0                    ;CLEAR BUFFER
    int 16h
    REC2: 
    MOV AX,0
    MOV DX,AX
    PUSH DX
    RECIEVE_AX AX    
    POP DX
    CMP DX,AX
    JZ LOOPTANI
    PUSH AX
    CMP AL,0B2H
    JZ EXIT
    CMP AL,0DH
    JZ ENTER2
    MOV AH,2
    MOV DX,P2_IN_CURSOR
    INT 10H
    INC DX
    MOV P2_IN_CURSOR,DX      ;INCREMENT CURSOR FOR THE OTHER PLAYER
    POP AX               ;DISPLAY RECIEVED CHAR
    MOV DL,AL
    MOV AH,2
    int 21h 
    JMP LOOPTANI
    
    ENTER1:              ;IF THE PLAYER CLICK ON ENTER HANDLE PLAYER1 CURSOR
    MOV DX,P1_IN_CURSOR
    INC DH
    MOV P1_IN_CURSOR,DX
    JMP REC
    
    ENTER2:
    MOV DX,P2_IN_CURSOR
    INC DH
    MOV P2_IN_CURSOR,DX    
    LOOPTANI:      
    JMP LOOOP    
    EXIT: 
    POPA
ENDM CHAT_IN
;-----------------------------------------------------------
;---------------------------SCROLL IN-----------------------
SCROLL_IN MACRO
    LOCAL ASD
    LOCAL EXIT
    LOCAL ENZL2
    LOCAL ENZL
    PUSHA
    MOV AX,P1_IN_CURSOR      ;SCROLL P1 CHAT 
    CMP AL,50H
    JL ENZL
    INC AH
    ENZL:
    CMP AH,16H
    JL DHOOFLTANI
    mov ax,0600h
    mov bh,07
    mov cx,1511H
    mov dx,1550H
    int 10h   
    MOV DX,1511H
    MOV P1_IN_CURSOR,DX
    MOV BH,0
    DHOOFLTANI:
    MOV AX,P2_IN_CURSOR      ;SCROLL P2 CHAT
    CMP AL,50H
    JL ENZL2
    INC AH
    ENZL2:
    CMP AH,17H
    JL EXIT
    mov ax,0600h
    mov bh,07
    mov cx,1611H
    mov dx,1650H
    int 10h 
    MOV DX,1611H
    MOV P2_IN_CURSOR,DX
    MOV BH,0
    EXIT:
    POPA
ENDM SCROLL_IN
;-----------------------------------------------------------