 c seidat basADRESSEN/TELEFON ���R � � �  '  d d!���b � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � //P P P cR W�5 ��  �   7 0(8 0  �0  �{��0� �     �  !   J"e!," !
    �    d � d!d  �!  ��0�0�0
 REM ADRESSEN U.TELFONNUMMERN OUTC.12 P.;P."ADRESSEN-UND TELEFONNUMMERN-"# P."    VERZEICHNIS"( P.;V=100;E=HEX(2100)2 P."DATEI NEU ? (J/ENT):",< W=INC.;OUTC.W;P.;P.F IF W=13 GOTO 160P IF W#'J' GOTO 50Z INP."MAX.ANZAHL DATENSAETZE"Qd IF Q<1 GOTO 90n U=E+(Q*V)x F.I=E TO U� POKE I,32� N.I� POKE E,'*'� F.K=E TO U STEP V� IF PEEK(K)='*' GOTO 190� N.K� A=(K-E)/V� P."VON ",#4,Q,"DATENSAETZEN"� P."SIND",#4,A,"ERFASST."� P.;P."AUSWAHL DURCH KENNZIFFER"� P.;P."AUFBAU............0"P.;P."ANZEIGEN..........1"P.;P."SUCHEN............2"P.;P."SORTIEREN.........3""P.;P."ANZEIGEN TEL.-NR..4",P.;P."AENDERN...........5"6P.;P."STATUS............6"8P.;P."DATEN RETTEN......7";P.;P."DATEN EINLESEN....8">P.@INP."EINGABE KENNZIFFER"WEIF W<0 GOTO 320JIF W>8 GOTO 320TGOTO (W*300+400)�REM DATEIAUFBAU�IF K=U P."DATEI VOLL !";P.;GOTO 190�X=K�GOSUB 8000�K=K+V�POKE K,'*';GOTO 190�REM ANZEIGEN�IF K=E P."DATEI LEER !";P.;GOTO 190�GOSUB 5000�GOSUB 5200 �GOSUB 7000�IF Y=B GOTO 1890�X=X+V�Z=Z+1;Y=Y+1IF Z=4 GOSUB 1850IF X>=K GOTO 1890GOTO 730�REM SUCHEN�F.S=U+10 TO U+30POKE S,32N.SP."NAME:",$G=20;I=U+10.GOSUB 100008F.J=E TO K STEP VBM=0LF.I=0 TO 19QIF PEEK(J+I)=32 GOTO 1130VIF PEEK(U+10+I)=PEEK(J+I) GOTO 1170`N.IjIF M=I GOTO 1200tN.J~P."NICHT GEFUNDEN";P.;GOTO190�M=M+1;GOTO 1120�P."GEFUNDEN"�X=J�P=(J-E)/V+1�GOSUB 7000�P.;GOTO 190REM SORTIERENFF.J=E TO K-(2*V) STEP VPF.I=J+V TO K-V STEP VZIF PEEK(J)>PEEK(I) GOTO 1450dN.InN.JxGOTO 190�F.S=0 TO V-1�F=PEEK(J+S);POKE(J+S),PEEK(I+S);POKE(I+S),F�N.S�GOTO 1380@REM ANZEIGEN TEL.-NR.EB=AJGOSUB 5000TP."TELEFON-NR. NAME"^FOR J=1 TO 32hOUTC.42rN.J|P.�F.J=X+84 TO X+94�OUTC.(PEEK(J))�N.J�OUTC.32�G=20;I=X�GOSUB 10300�X=X+V�Z=Z+1�IF Z=25 GOSUB 1850�IF X>=K GOSUB 1890�GOTO 1670:TAB(20)?P.">ENTER<",DW=INC.;OUTC.WIIF W#13 GOTO 1860NZ=0;RETURNbTAB(15);P."ENDE",;GOSUB 1855gGOTO 190lREM AENDERN�GOSUB 5000�GOSUB 8000�GOTO 190�REM STATUS�P."DATEISTATUS";P.�F.I=E TO U STEP V�WORD(I);P." ",�OUTC.(PEEK(I));OUTC.(PEEK(I+1))�TAB(1)�N.I�P.�GOTO 190�	REM DATEN RETTEN�	F.J=HEX(F0) TO HEX(FF)�	POKE J,32�	N.J�	P."FILENAME:",�	I=HEX(F0);G=16�	GOSUB 10000 
POKE HEX(E0),E

POKE HEX(E1),E/256
POKE HEX(E2),K
POKE HEX(E3),K/256(
CALL HEX(A0C)2
CALL HEX(10C)<
CALL HEX(A19)F
CALL HEX(10C)P
GOTO 200�
REM DATEN EINLESEN�
CALL HEX(A0C)CALL HEX(10F)F.I=HEX(F0) TO HEX(FF)OUTC.(PEEK(I))"N.I,CALL HEX(A19)6CALL HEX(10F)@P.;GOTO 160�REM ABFRAGE VON�P.;Z=0�INP."AB POS."P;Y=P-1�IF Y<0 GOTO 5020�X=E+(Y*V)�IF X>=K GOTO 5020�RETURNPREM ABFRAGE BISdINP."BIS POS."W;B=W-1nIF B>A-1 GOTO 5220xIF B<Y GOTO 5220�RETURNXREM AUSGABE DATENSATZbP.lP."LFD.NR.",#4,P," ",�G=20;I=X�GOSUB 10300�TAB(12)�I=X+20�GOSUB 10300�P."PLZ: ",�F.J=X+80 TO X+83�OUTC.(PEEK(J))�N.J�TAB(3)�G=20;I=X+40GOSUB 10300TAB(12)I=X+60 GOSUB 10300*P."TELEFON-NR. ",4G=16;I=X+84>GOSUB 10300HP.;P=P+1;RETURN@REM EINGABE POSJP."NAME    :",TG=20;I=X^GOSUB 10000hP."VORNAME :",rI=X+20|GOSUB 10000�P."PLZ     :",�G=4;I=X+80�GOSUB 10000�P."WOHNORT :",�G=20;I=X+40 �GOSUB 10000�P."STRASSE :",�I=X+60�GOSUB 10000�P."TELEFON :",�G=11;I=X+84�GOSUB 10000�RETURN'REM EINGABE DATENSATZ'Z=1;H=I+G$'IF PEEK(I)=32 GOTO 10100.'IF PEEK(I)='*' GOTO 101008'OUTC.(PEEK(I));I=I+1='IF I=H GOTO 10100B'IF PEEK(I)#32 GOTO 10040t'W=INC.~'IF W=8 I=I-1;GOTO 10200�'IF W=9 I=I+1;GOTO 10250�'IF W=13 OUTC.W;RETURN�'POKE I,W�'I=I+1�'OUTC.W�'IF I#H GOTO 10100�'P.;RETURN�'IF I<Z I=I+1;GOTO 10100�'GOTO 10160
(IF I>H I=I-1;GOTO 10100(GOTO 10160<(REM AUSGABE DATENSATZF(F.J=I TO I+G-1P(OUTC.(PEEK(J))Z(N.Jd(RETURN  ��������������������