 �seidat basBALKENDIAGRAMM   ��� � � � �  +    ����"���"�  X���������������������������������������������������������������������������������������� 1 0  /D D  3 0 0 0��  �0  �{��0� � + ��]�   >�  �    �  �     � �  � a �  ��0�0�0 REM BALKENDIAGRAMM
 OUTCH.12 P."........BALKENDIAGRAMM........"# P.( P."UEBERSCHRIFT:",2 GOSUB 1000d P."GROESSE 1.  2.  3.  4.  5."x GOSUB 1000� P."EINHEIT"� GOSUB 1000� A=HEX(2B)  � L=PEEK(A);A=A+1;H=PEEK(A)� FOR I=1 TO 5� P."WERT VON",I,� INPUT" "C� @(I)=C� NEXT I� REM MAXIMUM FINDENI=1;X=@(I)FOR I=2 TO 5IF X<@(I) GOTO 300"NEXT I'GOTO 350,X=@(I);M=I;GOTO 290^V=X/20+1hF=V*20rPOKE A,H;A=A-1;POKE A,L|FOR K=1 TO 11�P.#1,F�F=F-2*V�P.�NEXT K�B=HEX(ECE6)�FOR K=1 TO 10�POKE B,193 �B=B+32�POKE B,159�B=B+32NEXT KB=HEX(EF66)&FOR K=1 TO 260POKE B,1585B=B+1:NEXT KDGOSUB 2000NK=1XP.#12,@(K),bFOR K=3 TO 5 STEP 2lP.#10,@(K),vNEXT K�K=2�P.#17,@(K),�K=4�P.#10,@(K)�INPUT W�IF W=1 GOTO 10�STOP�W=INCH.;OUTCH.W�IF W#13 GOTO 1000�RETURN�C=HEX(EF44)�FOR K=1 TO 5�C=C+5�B=C�Q=@(K)/V�IF Q=0 GOTO 2320�FOR J=1 TO Q�POKE B,255�B=B-32	NEXT J	R=@(K)-Q*V	M=R*10/V	IFM<=3POKEB,248;GOTO2400	IFM<=4POKEB,249;GOTO2400$	IFM<=5POKEB,250;GOTO2400)	IFM<=6POKEB,251;GOTO2400.	IFM<=7POKEB,252;GOTO24003	IFM<=8POKEB,253;GOTO24008	IFM<=9POKEB,254;GOTO2400`	NEXT K�RETURNGOTR S=U+1 TO