/******************************************************************************\
********************************************************************************
**                                                                            **
**                  [ V N K  -  V I N A  K N O W L E D G E ]                  **
**                                                                            **
**                   SITE  : https://www.vinaknowledge.com                    **
**                   EMAIL : hvloi@vinaknowledge.com                          **
**                                                                            **
**                        TAN BINH DST, HCMC, VIET NAM                        **
**                                                                            **
**                 Copyright © 2019-2020 VNK - Vina Knowledge                 **
**                                                                            **
********************************************************************************
\******************************************************************************/

#ifndef VNK_VNKSOC_UTILITIES_H
#define VNK_VNKSOC_UTILITIES_H

/******************************************************************************\
*******************************I*N*C*L*U*D*E*S**********************************
\******************************************************************************/

/**
 * Global includes
 **/

#include <sys/un.h>
#include <sys/socket.h>

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/* UNIX Domain Socket Path */
#define SOC_PATH "/tmp/vnksoc_socket"

/* Be used for forEVER loop, only while() */
#define EVER 1

/* Be used for forEVER loop, only for() */
#define EVEREVER ;;

#define BUF_SIZE 128

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

/**
 * Parsing Command Line Arguments
 **/
int OptsParsing(int argc, char *argv[], vnksoc_config_t *config);

/**
 * Preparing Utilities For Socket
 * Note:
 * - r_*: indicate references
 **/
int PrepareSocket(int *r_soc_fd, struct sockaddr_un *r_addr);

/**
 * Validating UNIX Domain Socket Path
 *
 * Function Name:
 * SockPathIsExisted_Fopen()
 *
 * Description:
 * Validate if the unix domain socket is existed.
 *
 **/
bool SockPathIsExisted_Fopen(const char *soc_path);

/**
 * Validating UNIX Domain Socket Path
 *
 * Function Name:
 * SockPathIsExisted_Stat()
 *
 * Description:
 * Validate if the unix domain socket is existed.
 *
 **/
bool SockPathIsExisted_Stat(const char *soc_path);

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/

#endif /* VNK_VNKSOC_UTILITIES_H */
