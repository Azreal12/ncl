C
C	$Id: remove32.f,v 1.2 2000-07-12 17:24:00 haley Exp $
C                                                                      
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU Lesser General Public License as
C published by the Free Software Foundation; either version 2.1 of the
C License, or (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C Lesser General Public License for more details.
C
C You should have received a copy of the GNU Lesser General Public
C License along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
      SUBROUTINE REMOVE (MX,MY,HIDDEN,IND)
C
C SUBROUTINE REMOVE CONTAINS THE DATA STRUCTURES FOR THE MODEL PICTURE
C WHICH IS USED TO DETERMINE IF A LINE WILL BE DRAWN OR REMOVED.
C ALL MANIPULATIONS ON THESE DATA STRUCTURES ARE DONE EXCLUSIVLY IN
C SUBROUTINE REMOVE.
C
C
C INPUT-OUTPUT-SPECIFICATIONS:
C
C  INPUT:
C   MX,MY: X- AND Y-COOORDINATES OF A POINT IN THE PLOTTING AREA.
C          MX AND MY RANGE FROM 0 TO 2**15-1.
C          NOTE: MX AND MY MAY BE LESS THAN 0 OR GREATER THAN 2**15-1
C                IN SOME SPECIAL CASES.
C   IND =1: REMOVE CALLED FROM RESET.
C          SET ALL ELEMENTS IN THE MODEL PICTURE TO NONMARKED.
C        =2: MARK THE POINT (MX,MY) AND THE POINTS NEXT TO IT.
C        =3: CHECK IF THE POINT (MX,MY) IS ALREADY MARKED. RETURN RESULT
C           IN HIDDEN.
C  OUTPUT:
C   MX, MY, AND IND ARE UNCHANGED.
C   HIDDEN: LOGICAL, ONLY RELEVANT IF IND=3.
C          RETURNS .TRUE. IF THE POINT WITH COORDINATES (MX,MY) IS
C          ALREADY MARKED, OTHERWISE .FALSE.
C  COMMON-BLOCKS:
C   ARRAY ISCREN IS CHANGED AS DEFINED ABOVE IF IND IS 1 OR 2.
C
C
C NOTE
C   THE IMPLEMENTATION OF THE MODEL PICTURE MAY BE CHANGED NOT HOWEVER
C   THE INPUT-OUTPUT SPECIFICATIONS STATED ABOVE.
C
C
C ALGORITHM
C THIS IMPLEMENTATION OF A MODEL PICTURE USES A BIT MAP. EACH PLOTTER
C ADDRESS (POINT) IS REPRESENTED BY A BIT IN THE ARRAY ISCREN. INITIALLY
C EACH BIT IS SET TO 0 BY A CALL TO THE SUBROUTINE RESET. WHEN A LINE
C IS DRAWN ALL BITS REPRESENTING POINTS ON THE LINE ARE SET TO 1. BEFORE
C A LINE IS DRAWN THE MODEL PICTURE IS CHECKED. IF THE BITS IN THE
C MODEL PICTURE REPRESENTING THE POINTS ON THE LINE ARE ALREADY 1 THEN
C THE LINE IS NOT DRAWN, OTHERWISE THE LINE IS DRAWN AND THE
C CORRESPONDING BITS ARE SET TO 1.
C
C
C
C
      LOGICAL HIDDEN
      SAVE
C
      DIMENSION MASK(64),MASK3(64)
C
C
C *********************************************************************
C
C MACHINE AND MODEL DEPENDENT DECLARATIONS AND CONSTANT DEFINITIONS
C
C
C CHOOSE NOW THE SIZE OF YOUR MODEL PICTURE AS NX BY NY.
C ONLY SIZES WITH NX EQUAL TO NY HAVE BEEN TESTED SO FAR.
C ALSO ONLY SIZES WITH NX AND NY POWERS OF 2 ARE POSSIBLE.
C MODEL PICTURES IN SIZE EQUAL TO OR CLOSE TO YOUR PLOTTER ADDRESS SPACE
C ARE RECOMMENDED.
C ASSUME THE MODEL PICTURE IS OF SIZE NX BY NY. THEN ARRAY ISCREN NEEDS
C NY COLUMNS AND NX/NBWD+1 ROWS WHERE NBWD IS THE NUMBER OF BITS PER
C INTEGER STORAGE UNIT.
      DIMENSION ISCREN(33,1024)
C E.G. FOR A 1024 BY 1024 MODEL PICTURE ON A 60 BIT MACHINE
C     DIMENSION ISCREN(18,1024)
C
C NX AND NY ARE THE LENGTHS OF THE MODEL PICTURE IN X AND Y DIRECTION.
C LX AND NY ARE THE DIMENSIONS OF THE ARRAY ISCREN WHICH IS USED TO
C REPRESENT THE MODEL PICTURE.
C FOR ANY SIZE OF A MODEL PICTURE THE NUMBER OF COLUMNS IN ISCREN IS
C ALWAYS EQUAL TO THE LENGTH OF THE MODEL PICTURE IN Y DIRECTION.
C
      DATA NX,NY,LX /1024,1024,33/
C E.G. FOR A 1024 BY 1024 MODEL PICTURE ON A 60 BIT MACHINE
C     DATA NX,NY,LX /1024,1024,18/
C
C NXSIZE IS AN INTEGER SUCH THAT 2**NXSIZE = NX
C NYSIZE IS AN INTEGER SUCH THAT 2**NYSIZE = NY
C
      DATA NXSIZE,NYSIZE /10,10/
C E. G. FOR A 1024 BY 1024 MODEL PICTURE
C     DATA NXSIZE,NYSIZE /10,10/
C
C
C END OF MACHINE AND MODEL DEPENDENT DECLARATIONS AND CONSTANT
C DEFINITIONS
C
C **********************************************************************
C
C ARRAY MASK CONTAINS SINGLE BIT MASKS FOR EACH BIT IN THE WORD.
C ENTRY I IN ARRAY MASK CONTAINS A WORD WITH THE I-TH BIT FROM THE RIGHT
C A 1 AND ALL OTHER BITS 0.
C THESE MASKS ARE USED TO CHECK IF A GIVEN POINT IN THE MODEL PICTURE
C HAS ALREADY BEEN MARKED.
C
C ARRAY MASK3 ALSO CONTAINS A MASK FOR EACH BIT IN THE WORD, BUT THE
C BIT TO THE LEFT AND THE BIT TO THE RIGHT ARE NOW SET AS WELL (EXCEPT
C AT THE EDGES). ENTRY I IN THE ARRAY MASK3 CONTAINS A WORD WITH THE
C (I-1)-TH,I-TH, AND(I+1)-TH BITS FROM THE RIGHT 1'S AND ALL OTHER BITS
C ZEROES.
C THESE MASKS ARE USED TO MARK 3 POINTS IN THE MODEL PICTURE AT THE SAME
C TIME.
C
C     FLAG FOR FIRST CALL (USED TO DETERMINE IF MASKS SHOULD
C     BE DEFINED BY CALLING INTMSK)
C
      DATA IFSTC/0/
C
C     DEFINE MASKS IF THIS IS THE FIRST CALL TO REMOVE
C
      IF (IFSTC .GT. 0) GO TO 5
C
C     CHECK IF THE IMPLEMENTATION-DEPENDENT CONSTANTS HAVE BEEN SET
C
      IF (NX .EQ. 0) THEN
        WRITE(6,500)
        STOP
      ENDIF
  500 FORMAT('     IN SUBROUTINE REMOVE OF DASHSUPR:',/
     -'       IMPLEMENTATION-DEPENDENT CONSTANTS NOT SET--',/
     -'       SEE INSTRUCTIONS AFTER INITIAL COMMENT CARDS.')
      CALL INTMSK(MASK,MASK3)
      IFSTC = 1
    5 CONTINUE
C
C IF COORDINATES ARE OUT OF RANGE, QUIT.  (DJK, 04/27/88)
C
      IF (MX.LT.0.OR.MX.GT.32767.OR.MY.LT.0.OR.MY.GT.32767) THEN
        IF (IND.EQ.3) HIDDEN=.TRUE.
        RETURN
      END IF
C
C RETRIEVE THE NUMBER OF BITS PER INTEGER STORAGE UNIT.
C
      NBPW = I1MACH(5)
C
C TRANSFORM THE INPUT COORDINATES INTO MODEL PICTURE COORDINATES.
C
      IX = ISHIFT (MX,NXSIZE-15)
      IY = ISHIFT (MY,NYSIZE-15) + 1
C
C FIND THE ELEMENT IN THE ISCREN ARRAY REPRESENTING THE POINT (MX,MY).
C
      IBIT = MOD(IX,NBPW)+1
      IX = IX/NBPW+1
C
C BRANCH DEPENDING ON FUNCTION TO BE PERFORMED
C
      GOTO (1,2,3) , IND
C
C ***********************************************
C
C CHECK IF THE POINT (MX,MY) IS ALREADY MARKED
C
    3 CONTINUE
      HIDDEN = .TRUE.
      ITEMP = IAND(ISCREN(IX,IY),MASK(IBIT))
      IF (ITEMP .EQ. 0) HIDDEN = .FALSE.
      RETURN
C
C ***********************************************
C
C MARK THE POINT (MX,MY) AND THE POINTS NEXT TO IT
C
    2 CONTINUE
C
C MARK THE POINTS (MX,MY) , (MX,MY+1) AND (MX,MY-1) IF THEY ARE IN
C THE PLOTTING AREA.
C MARK ALSO 3 POINTS FOR MX+1 AND MX-1 IN MOST CASES.
C
      ISCREN(IX,IY) = IOR(ISCREN(IX,IY),MASK3(IBIT))
      IF (IY .LT. NY) ISCREN(IX,IY+1) = IOR(ISCREN(IX,IY+1),MASK3(IBIT))
      IF (IY .GT. 1) ISCREN(IX,IY-1) = IOR(ISCREN(IX,IY-1),MASK3(IBIT))
      IF (IBIT .EQ. 1) GO TO 10
      IF (IBIT .EQ. NBPW) GO TO 20
      RETURN
C RETURN IF THE LEFT EDGE OF THE PLOTTING AREA IS REACHED.
   10 IF (IX .EQ. 1) RETURN
C
C MARK 3 POINTS TO THE LEFT OF (MX,MY)
C
      ISCREN(IX-1,IY) = IOR(ISCREN(IX-1,IY),MASK(NBPW))
      IF (IY .GT. 1) ISCREN(IX-1,IY-1) = IOR(ISCREN(IX-1,IY-1),
     1                                       MASK(NBPW))
      IF (IY .LT. NY)
     1    ISCREN(IX-1,IY+1) = IOR(ISCREN(IX-1,IY+1),MASK(NBPW))
      RETURN
C RETURN IF THE RIGHT EDGE OF THE PLOTTING AREA IS REACHED.
   20 IF (IX .EQ. LX) RETURN
C
C MARK 3 POINTS TO THE RIGHT OF (MX,MY).
C
      ISCREN(IX+1,IY) = IOR(ISCREN(IX+1,IY),MASK(1))
      IF (IY .GT. 1) ISCREN(IX+1,IY-1) =  IOR(ISCREN(IX+1,IY-1),MASK(1))
      IF (IY .LT. NY) ISCREN(IX+1,IY+1) = IOR(ISCREN(IX+1,IY+1),MASK(1))
      RETURN
C
C ***********************************************
C
C ENTRY RESET . SET ALL THE ELEMENTS IN THE ARRAY ISCREN TO 0.
C
    1 CONTINUE
      DO 40 J = 1,NY
      DO 30 I = 1,LX
         ISCREN(I,J) = 0
   30 CONTINUE
   40 CONTINUE
      RETURN
C
      END
