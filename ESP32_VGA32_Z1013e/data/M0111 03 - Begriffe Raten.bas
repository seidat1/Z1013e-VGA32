 зseidat basBEGRIFFE RATEN   џџџ џ џ џ д  +    @!nЏжџ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ ф џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ џ /Sёђ/c(9 1 3 0ря  Ќ0  ь{ь0џ џ   џ џ   џ џ џ  ђ     џ џ џ 
 џ a!џ @!   №     џ00ж0 OUTC. 12 E=HEX(2000) P.;P."ERRATEN VON BEGRIFFEN";P. P."DATEI NEU ?(J/ENT):",( W=INCHAR;OUTC. W;P.;P.2 IF W=13 G.140< IF W#'J'G.30F INP."MAX. SATZLAENGE"VP IF V<1 G.70Z INP."MAX. ANZAHL DATENSAETZE"Qd IF Q<1 G.90i U=E+(Q*V)n F.I=E TO Us POKE I,32x N.I POKE E,'*' F.K=E TO U STEP V IF PEEK(K)='*'G.160 N.K  A=(K-E)/VЊ P."VON",#4,Q,"DATENSAETZEN"Д P."SIND",#4,A,"ERFASST"О P.Ш P."AUSWAHL DURCH KENNZIFFER"в P.;P."AUFBAU............0"м P.;P."ANZEIGEN..........1"ц P.;P."BEGRIFF RATEN.....2"№ P.;P."AENDERN...........3"њ P.;P."STATUS............4"P.;P."DATEN RETTEN......7"
P.;P."DATEN EINLESEN....8"P.INP."EINGABE KENNZIFFER"WIF W<0 GOTO 200"IF W>8 GOTO 200,GOTO(W*300+400)REM DATEIAUFBAUIF K=U P."DATEI VOLL !";P.;GOTO 160ЄX=KЎGOSUB 8000ИK=K+VТPOKE K,'*'ЬGOTO 160МREM ANZEIGENСIF K=E P."DATEI LEER !";P.;GOTO 160ЦGOSUB 5000аGOSUB 5200кGOSUB 7000фIF Y=B GOTO 1890юX=X+VјZ=Z+1;Y=Y+1IF Z=20 GOSUB 1850IF X>=K GOTO 1890GOTO 730шREM BEGRIFF RATENэOUTCH.12ђGOSUB 5000ќFOR S=U+1 TO U+VPOKE S,32NEXT SS=U+1FOR J=X TO H$IF PEEK(J)#32 POKE S,45)S=S+1.NEXT J1M=10;L=03P.8FOR S=U+1 TO U+VBOUTCH.(PEEK(S))LNEXT SQP.SIF M=0 GOTO 1250VW=INCH.;OUTCH.WWP.;M=0;L=L+1YIF W=13 GOTO 1240[S=U+1`FOR J=X TO HjIF PEEK(J)=W POKE S,WmIF PEEK(J)#PEEK(S) GOTO 1200oS=S+1tN.JІGOTO 1075АM=M+1КG.1135иL=L-1тF.J=X TO HьOUTC.(PEEK(J))іN.JћP.;P."NACH",#3,L," VERSUCHEN !" P.;GOTO 200REM AENDERNIF K=E GOTO705GOSUB 5000(GOSUB 80002GOTO 200@REM STATUSJP."DATEISTATUS";P.TF.I=E TO U STEP V^WORD(I);P." ",hOUTC.(PEEK(I))rOUTC.(PEEK(I+1))|P." ",N.IP.;GOTO 160:REM ENDE SEIE<TAB(20)?P.">ENTER<",DW=INCHAR;OUTC. WIIFW#13 GOTO 1860NZ=0XRETURNbTAB(15);P."ENDE",;GOSUB 1850gGOTO 200lGOTO 200GOTO 200Ф	REM DATEN RETTENЮ	F.J=HEX(F0) TO HEX(FF)и	POKE J,32т	N.Jч	P."FILENAME:",ь	X=HEX(F0);H=X+15і	GOSUB 8020 
POKE HEX(E0),E

POKE HEX(E1),E/256
POKE HEX(E2),K
POKE HEX(E3),K/256(
CALL HEX(A0C)2
CALL HEX(10C)<
CALL HEX(A19)F
CALL HEX(10C)P
GOTO 160№
REM DATEN EINLESENњ
CALL HEX(A0C)CALL HEX(10F)F.I=HEX(F0) TO HEX(FF)OUTC.(PEEK(I))"N.I,CALL HEX(A19)6CALL HEX(10F)@P.;GOTO 140REM ABFRAGE VONP.;Z=0INP."AB POS."W;Y=W-1ЁIF Y<0 GOTO 5020ІX=E+(Y*V);H=X+V-1АIF X>=K GOTO 5020КRETURNPREM ABFRAGE BISdINP."BIS PO."W;B=W-1nIF B>A-1 GOTO 5220IF B<Y GOTO 5220№RETURNXREM AUSGABE DATENSATZbP.lF.J=X TO X+V-1vOUTC.(PEEK(J))N.JRETURN@REM EINGABE DATENSATZJP."BEGRIFF"TF.J=X TO H^IF PEEK(J)='*' GOTO 9000hIF PEEK(J)#32 GOTO 8070rIF PEEK(J+1)=32 GOTO 9000OUTC.(PEEK(J))N.J(#W=INC.<#IF W=8 J=J-1;GOTO 9100F#IF W=9 J=J+1;GOTO 9120P#IF W=13 OUTC.W;RETURNZ#POKE J,Wd#J=J+1n#OUTC.Wx#IF J#H GOTO 9000#P.;RETURN#IF J<X J=J+1;GOTO 9000#GOTO 9070 #IF J>H J=J-1;GOTO 9000Њ#GOTO 9070 џ X+83а