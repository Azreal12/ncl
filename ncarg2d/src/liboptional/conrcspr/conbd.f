C
C	$Id: conbd.f,v 1.2 2000-07-12 17:23:49 haley Exp $
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
C
C
      BLOCK DATA CONBD
      COMMON /CONRE1/ IOFFP      ,SPVAL      ,IHILO
      COMMON /CONRE2/ IX         ,IY         ,IDX        ,IDY        ,
     1                IS         ,ISS        ,NP         ,CV         ,
     2                INX(8)     ,INY(8)     ,IR(2000)   ,NR
      COMMON /SPRINT/ ISPRMJ     ,ISPRMN     ,ISPRTX
      DATA IOFFP,SPVAL,IHILO/0,0.0,3/
      DATA INX(1),INX(2),INX(3),INX(4),INX(5),INX(6),INX(7),INX(8)/
     1        -1 ,   -1 ,    0 ,    1 ,    1 ,    1 ,    0 ,   -1 /
      DATA INY(1),INY(2),INY(3),INY(4),INY(5),INY(6),INY(7),INY(8)/
     1         0 ,    1 ,    1 ,    1 ,    0 ,   -1 ,   -1 ,   -1 /
      DATA NR/2000/
      DATA ISPRMJ,ISPRMN,ISPRTX/ 1 , 1 , 1 /
C
C
C-------------------------------------------------------------------------
C
C REVISION HISTORY
C
C JUNE 1984                          CONVERTED TO FORTRAN 77 AND GKS
C
C NOVEMBER 1989                      CHANGED THE LENGTH OF IR TO 2000.
C
C MARCH 1990                         CORRECTED USE OF SET CALLS.
C
C------------------------------------------------------------------------
      END
