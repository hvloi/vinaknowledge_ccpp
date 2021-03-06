/******************************************************************************\
********************************************************************************
**                                                                            **
**                  [ V N K - V I N A  K N O W L E D G E ]                    **
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

/**
 * Standard Libraries.
 **/
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>

/**
 * Local Headers.
 **/
#include "vnk_mq_sigNoti.h"
#include "vnk_notify.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

#define NOTIFY_SIG SIGUSR1

#define SLEEP_BE4_DIE 3

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
 * FUNCTION    :
 * VNK_SigHandler
 *
 * SCOPE       :
 * Local
 *
 * DESCRIPTION :
 * Signal Handler
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 *
 **/
static void VNK_SigHandler(int signal)
{

    return;
}

/**
 * FUNCTION    :
 * VNK_SigReadingMessage
 *
 * SCOPE       :
 * Local
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * r_mqd: r means reference
 *
 **/
static int VNK_SigReadingMessage(sigset_t *r_emptyMask, mqd_t *r_mqd,
            struct sigevent *r_sev)
{
    // Return code //
    int RetCode = 0;

    struct mq_attr attr;
    void *buffer;
    ssize_t numRead;

    /**
     * Do not intend to validate r_mqd again because it was validated in the time
     * of openning, if there was any error, the program exited at that time.
     **/

    if (mq_getattr(*r_mqd, &attr) == -1)
    {
        vnk_error_notify(NO_ERRNO, "in function %s", __FUNCTION__);
        RetCode = -1;
        goto vnk_black_hole;
    }

    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
    {
        vnk_error_notify(NO_ERRNO, "malloc() in function %s", __FUNCTION__);
        goto vnk_black_hole;
    }

    vnk_info_notify("%s is listening for message notification signal...", IAM);

    for(;;)
    {
        // Wait for notification signal //
        sigsuspend(r_emptyMask);

        if(ctrlC_IsHit == YES)
        {
            vnk_info_notify("Ctrl + C was hit, exiting,...");
            RetCode = 0;
            sleep(SLEEP_BE4_DIE);
            goto vnk_black_hole;
        }

        if (mq_notify(*r_mqd, r_sev) == -1)
        {
            vnk_error_notify(NO_ERRNO, "in function %s", __FUNCTION__);
            RetCode = -1;
            goto vnk_black_hole;
        }

        while ((numRead = mq_receive(*r_mqd, buffer, attr.mq_msgsize,
                    NULL)) >= 0)
        {
            vnk_info_notify("Read %ld bytes\n", (long) numRead);
        }

        if (errno != EAGAIN)
        {
            vnk_error_notify(errno, "in function %s", __FUNCTION__);
            RetCode = -1;
            goto vnk_black_hole;
        }
    }

vnk_black_hole:
    // Clean up before return //
    if(buffer != NULL)
    {
        free(buffer);
    }

    return RetCode;
}

/**
 * FUNCTION    :
 * VNK_SignalNotification
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * c_vnkmq_config: c means copy, passing copy of struct to fucntion.
 *
 **/
int VNK_SignalNotification(struct vnkmq_config c_vnkmq_config)
{
    int RetCode = 0;
    struct sigevent sev;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;
    mqd_t mqd;

    mqd = mq_open(c_vnkmq_config.mq_name, O_RDONLY | O_NONBLOCK);
    if(mqd == (mqd_t)-1)
    {
        vnk_error_notify(errno, "inside %s", __FUNCTION__);
        goto VNK_BlHl;

    }

    sigemptyset(&blockMask);
    sigaddset(&blockMask, NOTIFY_SIG);
    if(sigprocmask(SIG_BLOCK, &blockMask, NULL) == -1)
    {
        vnk_error_notify(NO_ERRNO, "sigprocmask inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = VNK_SigHandler;
    if (sigaction(NOTIFY_SIG, &sa, NULL) == -1)
    {
        vnk_error_notify(NO_ERRNO, "sigaction inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;
    if (mq_notify(mqd, &sev) == -1)
    {
        vnk_error_notify(NO_ERRNO, "mq_notify inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    // Call function to read message from queue //
    if ((RetCode = VNK_SigReadingMessage(&emptyMask, &mqd, &sev)) != 0)
    {
        goto VNK_BlHl;
    }

VNK_BlHl:
    return RetCode;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
