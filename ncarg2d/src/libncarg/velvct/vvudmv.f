C
C	$Id: vvudmv.f,v 1.3 1993-01-15 22:47:13 dbrown Exp $
C
      SUBROUTINE VVUDMV(XCS,YCS,NCS,IAI,IAG,NAI)
C
      DIMENSION XCS(NCS),YCS(NCS),IAI(NAI),IAG(NAI)
C
C
C Example version of user masked drawing program
C
C XCS,YCS    - Arrays of X,Y coordinates
C NCS        - Number of points
C IAI        - Area identifier array
C IAG        - Area group array
C NAI        - number of area/group identifiers
C
C --------------------------------------------------------------------
C
      DO 101 I=1,NAI
         IF (IAI(I).LT.0) RETURN
 101  CONTINUE
C
C If drawing is turned on, draw the polyline.
C
      CALL CURVE(XCS,YCS,NCS)
C
C Done.
C
      RETURN
C
      END
