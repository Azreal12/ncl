C
C	$Id: markl.f,v 1.2 2000-07-12 17:24:00 haley Exp $
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
      SUBROUTINE MARKL (MX1,MY1,MX2,MY2)
C
C MARKL MARKS A LINE FROM POINT (MX1,MY1) TO POINT (MX2,MY2) IN THE
C MODEL PICTURE.
C
C ***********************************
C
C NOTE: LINES OF LENGTH LESS OR EQUAL 2 ARE NOT MARKED.
C       THE VERY FIRST POINT OF A LINE IS NOT MARKED, BUT IT WAS
C        MARKED WITH THE PRECEEDING LINE SEGMENT.
C
C ***********************************
C
C ISKIP IS USED TO ADJUST DASHSUPR TO THE SIZE OF THE MODEL PICTURE AS
C DEFINED IN THE SUBROUTINE REMOVE. ISKIP IS INITIALIZED IN DASHBD.
C
      COMMON /DSUP1/ ISKIP
C
      LOGICAL LDUMMY
      SAVE
C
      DATA LDUMMY /.TRUE./
C
      DX = MX2-MX1
      DY = MY2-MY1
      IF (ABS(DX)-ABS(DY)) 60,50,10
C
C DX IS LONGER THAN DY.
C
   10 SLOPE = DY/DX
      IF (DX .LT. 0.) GO TO 30
      MX1S = MX1+2*ISKIP
      MX2S = MX2-1*ISKIP
      IF (MX1S .GT. MX2S) RETURN
C
      DO 20 MX=MX1S,MX2S,ISKIP
         MY = IFIX(FLOAT(MY1)+FLOAT(MX-MX1)*SLOPE+.5)
         CALL REMOVE (MX,MY,LDUMMY,2)
   20 CONTINUE
      RETURN
C
   30 MX1S = MX1-2*ISKIP
      MX2S = MX2+1*ISKIP
      IF (MX1S .LT. MX2S) RETURN
      DO 40 MX=MX2S,MX1S,ISKIP
         MY = IFIX(FLOAT(MY2)+FLOAT(MX-MX2)*SLOPE+.5)
         CALL REMOVE (MX,MY,LDUMMY,2)
   40 CONTINUE
      RETURN
C
C DX AND DY HAVE SAME LENGTH.
C
   50 IF (DX .NE. 0.) GO TO 10
      CALL REMOVE (MX2,MY2,LDUMMY,2)
      RETURN
C
C DY IS LONGER THAN DX.
C
   60 SLOPE = DX/DY
      IF (DY .LT. 0.) GO TO 80
      MY1S = MY1+2*ISKIP
      MY2S = MY2-1*ISKIP
      IF (MY1S .GT. MY2S) RETURN
C
      DO 70 MY=MY1S,MY2S,ISKIP
         MX = IFIX(FLOAT(MX1)+FLOAT(MY-MY1)*SLOPE+.5)
         CALL REMOVE (MX,MY,LDUMMY,2)
   70 CONTINUE
      RETURN
C
   80 MY1S = MY1-2*ISKIP
      MY2S = MY2+1*ISKIP
      IF (MY1S .LT. MY2S) RETURN
C
      DO 90 MY=MY2S,MY1S,ISKIP
         MX = IFIX(FLOAT(MX2)+FLOAT(MY-MY2)*SLOPE+.5)
         CALL REMOVE (MX,MY,LDUMMY,2)
   90 CONTINUE
C
      RETURN
      END
