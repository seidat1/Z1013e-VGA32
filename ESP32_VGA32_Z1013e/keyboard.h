#define S0 0x00, 0x00
#define S1 0x00, 0x08
#define S2 0x01, 0x08
#define S3 0x02, 0x08
#define S4 0x03, 0x08


static const byte tasttable[][4] =
{ 
    {0x00, 0x00, S0        } // 0x00 
  , {0x00, 0x00, S0        } // 0x01 
  , {0x00, 0x00, S0        } // 0x02 
  , {0x00, 0x00, S0        } // 0x03 
  , {0x00, 0x00, S0        } // 0x04 
  , {0x00, 0x00, S0        } // 0x05 
  , {0x00, 0x00, S0        } // 0x06 
  , {0x00, 0x00, S0        } // 0x07 
  , {0x00, 0x00, S0        } // 0x08 
  , {0x00, 0x00, S0        } // 0x09 
  , {0x00, 0x00, S0        } // 0x0A LF
  , {0x00, 0x00, S0        } // 0x0B 
  , {0x00, 0x00, S0        } // 0x0C 
  , {0x07, 0x08, S0        } // 0x0D CR
  , {0x06, 0x02, S0        } // 0x0E 
  , {0x07, 0x02, S0        } // 0x0F 
  , {0x00, 0x04, S0        } // 0x10 
  , {0x01, 0x04, S0        } // 0x11 
  , {0x02, 0x04, S0        } // 0x12 
  , {0x03, 0x04, S0        } // 0x13 
  , {0x04, 0x04, S0        } // 0x14 
  , {0x05, 0x04, S0        } // 0x15 
  , {0x06, 0x04, S0        } // 0x16 
  , {0x07, 0x04, S0        } // 0x17 
  , {0x00, 0x01, S1        } // 0x18 
  , {0x01, 0x01, S1        } // 0x19 
  , {0x02, 0x01, S1        } // 0x1A 
  , {0x03, 0x01, S1        } // 0x1B 
  , {0x04, 0x01, S1        } // 0x1C 
  , {0x05, 0x01, S1        } // 0x1D 
  , {0x06, 0x01, S1        } // 0x1E 
  , {0x07, 0x01, S1        } // 0x1F 

  , {0x05, 0x08, S0        } // 0x20 SPACE
  , {0x01, 0x02, S2        } // 0x21 !
  , {0x02, 0x02, S2        } // 0x22 "
  , {0x03, 0x02, S2        } // 0x23 #
  , {0x04, 0x02, S2        } // 0x24 $
  , {0x05, 0x02, S2        } // 0x25 %
  , {0x06, 0x02, S2        } // 0x26 &
  , {0x07, 0x02, S2        } // 0x27 '
  , {0x00, 0x04, S2        } // 0x28 (
  , {0x01, 0x04, S2        } // 0x29 )
  , {0x02, 0x04, S2        } // 0x2A *
  , {0x03, 0x04, S2        } // 0x2B +
  , {0x04, 0x04, S2        } // 0x2C ,
  , {0x05, 0x04, S2        } // 0x2D -
  , {0x06, 0x04, S2        } // 0x2E .
  , {0x07, 0x04, S2        } // 0x2F /
  , {0x00, 0x02, S1        } // 0x30 0
  , {0x01, 0x02, S1        } // 0x31 1
  , {0x02, 0x02, S1        } // 0x32 2
  , {0x03, 0x02, S1        } // 0x33 3
  , {0x04, 0x02, S1        } // 0x34 4
  , {0x05, 0x02, S1        } // 0x35 5
  , {0x06, 0x02, S1        } // 0x36 6
  , {0x07, 0x02, S1        } // 0x37 7
  , {0x00, 0x04, S1        } // 0x38 8
  , {0x01, 0x04, S1        } // 0x39 9
  , {0x02, 0x04, S1        } // 0x3A :
  , {0x03, 0x04, S1        } // 0x3B ;
  , {0x04, 0x04, S1        } // 0x3C <
  , {0x05, 0x04, S1        } // 0x3D =
  , {0x06, 0x04, S1        } // 0x3E >
  , {0x07, 0x04, S1        } // 0x3F ?
  
  , {0x00, 0x00, S0        } // 0x40 @
  , {0x01, 0x01, S0        } // 0x41 A
  , {0x02, 0x01, S0        } // 0x42 B
  , {0x03, 0x01, S0        } // 0x43 C
  , {0x04, 0x01, S0        } // 0x44 D
  , {0x05, 0x01, S0        } // 0x45 E
  , {0x06, 0x01, S0        } // 0x46 F
  , {0x07, 0x01, S0        } // 0x47 G
  , {0x00, 0x02, S0        } // 0x48 H
  , {0x01, 0x02, S0        } // 0x49 I
  , {0x02, 0x02, S0        } // 0x4A J
  , {0x03, 0x02, S0        } // 0x4B K
  , {0x04, 0x02, S0        } // 0x4C L
  , {0x05, 0x02, S0        } // 0x4D M
  , {0x06, 0x02, S0        } // 0x4E N
  , {0x07, 0x02, S0        } // 0x4F O
  , {0x00, 0x04, S0        } // 0x50 P
  , {0x01, 0x04, S0        } // 0x51 Q
  , {0x02, 0x04, S0        } // 0x52 R
  , {0x03, 0x04, S0        } // 0x53 S
  , {0x04, 0x04, S0        } // 0x54 T
  , {0x05, 0x04, S0        } // 0x55 U
  , {0x06, 0x04, S0        } // 0x56 V
  , {0x07, 0x04, S0        } // 0x57 W
  , {0x00, 0x01, S1        } // 0x58 X
  , {0x01, 0x01, S1        } // 0x59 Y
  , {0x02, 0x01, S1        } // 0x5A Z
  , {0x03, 0x01, S1        } // 0x5B [
  , {0x04, 0x01, S1        } // 0x5C \ (Wichtig! der Backslash darf nicht am Ende der Zeile stehen)
  , {0x05, 0x01, S1        } // 0x5D ]
  , {0x06, 0x01, S1        } // 0x5E ^
  , {0x07, 0x01, S1        } // 0x5F _

  , {0x00, 0x01, S3        } // 0x60 `
  , {0x01, 0x01, S3        } // 0x61 a
  , {0x02, 0x01, S3        } // 0x62 b
  , {0x03, 0x01, S3        } // 0x63 c
  , {0x04, 0x01, S3        } // 0x64 d
  , {0x05, 0x01, S3        } // 0x65 e
  , {0x06, 0x01, S3        } // 0x66 f
  , {0x07, 0x01, S3        } // 0x67 g
  , {0x00, 0x02, S3        } // 0x68 h
  , {0x01, 0x02, S3        } // 0x69 i
  , {0x02, 0x02, S3        } // 0x6A j
  , {0x03, 0x02, S3        } // 0x6B k
  , {0x04, 0x02, S3        } // 0x6C l
  , {0x05, 0x02, S3        } // 0x6D m
  , {0x06, 0x02, S3        } // 0x6E n
  , {0x07, 0x02, S3        } // 0x6F o
  , {0x00, 0x04, S3        } // 0x70 p
  , {0x01, 0x04, S3        } // 0x71 q
  , {0x02, 0x04, S3        } // 0x72 r
  , {0x03, 0x04, S3        } // 0x73 s
  , {0x04, 0x04, S3        } // 0x74 t
  , {0x05, 0x04, S3        } // 0x75 u
  , {0x06, 0x04, S3        } // 0x76 v
  , {0x07, 0x04, S3        } // 0x77 w
  , {0x00, 0x01, S2        } // 0x78 x
  , {0x01, 0x01, S2        } // 0x79 y
  , {0x02, 0x01, S2        } // 0x7A z
  , {0x03, 0x01, S2        } // 0x7B {
  , {0x04, 0x01, S2        } // 0x7C |
  , {0x05, 0x01, S2        } // 0x7D }
  , {0x06, 0x01, S2        } // 0x7E ~
  , {0x07, 0x01, S2        } // 0x7F [DEL]
}
;