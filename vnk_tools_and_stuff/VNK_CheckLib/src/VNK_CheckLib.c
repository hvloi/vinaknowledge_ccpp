/******************************************************************************\
********************************************************************************
**                                                                            **
**                    V N K - V I N A  K N O W L E D G E                      **
**                                                                            **
**                   SITE  : https://www.vinaknowledge.com                    **
**                   EMAIL : hvloi@vinaknowledge.com                          **
**                                                                            **
**                       TAN BINH DST, HCMC, VIET NAM                         **
**                                                                            **
**                      Copyright © 2019 Vina Knowledge                       **
**                                                                            **
********************************************************************************
\******************************************************************************/

/******************************************************************************\
*******************************I*N*C*L*U*D*E*S**********************************
\******************************************************************************/

#include <stdio.h>
#include "VNK_CheckLib.h"
#include "vnk_lib_notify.h"

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

int main(int argc, char *argv[])
{
    /*
     * Main Function
     */
    
    // Try to call function in lib
    // target_include_directories(vnk_checklib PRIVATE path/to/lib.a)
    vnk_info_notify("WELCOME TO %s", argv[0]);

    // Try to call function in this source
    // target_include_directories(vnk_checklib PRIVATE include)
    VNK_CheckLibShowInfo();

    return 0;
}