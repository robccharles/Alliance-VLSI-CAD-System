#ifndef __P
# if defined(__STDC__) ||  defined(__GNUC__)
#  define __P(x) x
# else
#  define __P(x) ()
# endif
#endif
/*------------------------------------------------------------\
|                                                             |
| Tool    :                     RGS                           |
|                                                             |
| File    :                   rgs113.h                        |
|                                                             |
| Authors :                Jacomme Ludovic                    |
|                                                             |
| Date    :                   27.06.95                        |
|                                                             |
\------------------------------------------------------------*/

# ifndef RGS_113_H
# define RGS_113_H

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
|                      Global Variables                       |
|                                                             |
\------------------------------------------------------------*/
/*------------------------------------------------------------\
|                                                             |
|                          Functions                          |
|                                                             |
\------------------------------------------------------------*/

  extern   rdsfig_list * gdsloadrdsfig __P((rdsfig_list *Figure, char *Name, char Mode));
  extern           void  gdssaverdsfig __P((rdsfig_list *Figure));

# endif 
