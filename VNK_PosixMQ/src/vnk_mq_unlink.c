/******************************************************************************\
********************************************************************************
**                                                                            **
**                          VNK - VINA KNOWLEDGE                              **
**                                                                            **
**                   Site : https://www.vinaknowledge.com                     **
**                   Email: hvloi@vinaknowledge.com                           **
**                                                                            **
**                     Copyright © 2019 Vina Knowledge                        **
**                                                                            **
********************************************************************************
\******************************************************************************/

/*******************************************************************************
 *********************************INCLUDES**************************************
 ******************************************************************************/

#include <stdio.h>
#include <mqueue.h>

#include "vnk_mq_poxis.h"
#include "vnk_notify.h"

/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/


/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

/*
 * Some description,....
 */
int vnk_mq_unlink(const char *mq_name)
{
    bool hasErr = false;

    if(mq_unlink(mq_name) < 0)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_unlink()");
        goto byee;
    }

    vnk_info_notify("un-linked mq named %s", mq_name);

byee:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }
    return RETURN_SUCCESS;
}
