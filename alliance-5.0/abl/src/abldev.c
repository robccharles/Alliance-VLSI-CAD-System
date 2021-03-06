/*------------------------------------------------------------\
|                                                             |
| This file is part of the Alliance CAD System Copyright      |
| (C) Laboratoire LIP6 - Département ASIM Universite P&M Curie|
|                                                             |
| Home page      : http://www-asim.lip6.fr/alliance/          |
| E-mail         : mailto:alliance-users@asim.lip6.fr       |
|                                                             |
| This progam is  free software; you can redistribute it      |
| and/or modify it under the  terms of the GNU Library General|
| Public License as published by the Free Software Foundation |
| either version 2 of the License, or (at your option) any    |
| later version.                                              |
|                                                             |
| Alliance VLSI  CAD System  is distributed  in the hope that |
| it  will be useful, but WITHOUT  ANY WARRANTY;              |
| without even the  implied warranty of MERCHANTABILITY or    |
| FITNESS FOR A PARTICULAR PURPOSE. See the GNU General       |
| Public License for more details.                            |
|                                                             |
| You should have received a copy  of the GNU General Public  |
| License along with the GNU C Library; see the file COPYING. |
| If not, write to the Free Software Foundation, Inc.,        |
| 675 Mass Ave, Cambridge, MA 02139, USA.                     |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
| Tool    :                     Abl                           |
|                                                             |
| File    :                   abldev.c                        |
|                                                             |
| Date    :                   03.12.96                        |
|                                                             |
| Author  :               Jacomme Ludovic                     |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                         Include Files                       |
|                                                             |
\------------------------------------------------------------*/

# include "mut.h"
# include "aut.h"
# include "abl.h"

# include <stdio.h>
# include "abldev.h"
# include "ablerror.h"

/*------------------------------------------------------------\
|                                                             |
|                           Constants                         |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                            Types                            |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                          Variables                          |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                          Functions                          |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                       Develop Functions                     |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                 Develop Duplicate Abl Xor Expr              |
|                                                             |
\------------------------------------------------------------*/

ablexpr *devdupablxorexpr( Expr )

  ablexpr *Expr;
{
  ablexpr *ExprDev;
  ablexpr *ExprQueue;
  long        Oper;

  if ( ABL_ATOM( Expr ) )
  {
    return( addchain( (ablexpr *)0, ABL_CAR( Expr ) ) );
  }

  Oper = ABL_OPER( Expr );

  if ( ( Oper == ABL_XOR  ) ||
       ( Oper == ABL_NXOR ) )
  {
    Expr    = ABL_CDR( Expr );
    ExprDev = dupablexpr( ABL_CAR( Expr ) );

    while ( ( Expr = ABL_CDR( Expr ) ) != (ablexpr *)0 )
    {
      ExprDev = optimablxorbinexpr( Oper, 
                                    ExprDev,
                                    devdupablxorexpr( ABL_CAR( Expr ) ) );
    }
  }
  else
  {
    ExprDev = addchain( (ablexpr *)0,
                        (void *)addchain( (ablexpr *)0,
                                          (void *)Oper ) );
    ExprQueue = ExprDev;

    while ( ( Expr = ABL_CDR( Expr ) ) != (ablexpr *)0 )
    {
      ABL_CDR( ExprQueue ) = addchain( (ablexpr *)0,
                                       (void *)devdupablxorexpr( ABL_CAR( Expr ) ) );
      ExprQueue = ABL_CDR( ExprQueue );
    }
  }

  return( ExprDev );
}

/*------------------------------------------------------------\
|                                                             |
|                      Develop Abl Xor Expr                   |
|                                                             |
\------------------------------------------------------------*/

ablexpr *devablxorexpr( Expr )

  ablexpr *Expr;
{
  ablexpr *ExprDev;
  ablexpr *ScanExpr;
  long        Oper;

  if ( ABL_ATOM( Expr ) )
  {
    return( Expr );
  }

  Oper = ABL_OPER( Expr );

  if ( ( Oper == ABL_XOR  ) ||
       ( Oper == ABL_NXOR ) )
  {
    ScanExpr = ABL_CDR( Expr );
    ExprDev  = ABL_CAR( ScanExpr );

    while ( ( ScanExpr = ABL_CDR( ScanExpr ) ) != (ablexpr *)0 )
    {
      ExprDev = optimablxorbinexpr( Oper, 
                                    ExprDev,
                                    devablxorexpr( ABL_CAR( ScanExpr ) ) );
    }

    freechain( Expr );
  }
  else
  {
    ExprDev = Expr;

    while ( ( Expr = ABL_CDR( Expr ) ) != (ablexpr *)0 )
    {
      ABL_CAR_L( Expr ) = (void *)devablxorexpr( ABL_CAR( Expr ) );
    }
  }

  return( ExprDev );
}
