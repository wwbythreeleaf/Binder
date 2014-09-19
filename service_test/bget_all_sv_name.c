/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binder.h"
#define LOG_TAG "#h#j#_getsvname"
#include <cutils/log.h>

void sv_show(struct binder_state *bs,void*target)
{
	uint16_t *s;
    int fd,status=0,len,index=1;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

	while(!status){
		bio_init(&msg, iodata, sizeof(iodata), 4);
		bio_put_uint32(&msg, 0);  // strict mode header
		bio_put_string16_x(&msg, SVC_MGR_NAME);
		bio_put_uint32(&msg,index++);
		if (binder_call(bs, &msg, &reply, target, SVC_MGR_LIST_SERVICES))
			return 0;
		s = bio_get_string16(&reply,&len);
		if(!len)
			break;
		ALOGE("%s",str8(s));
	}
}
int main(int argc, char **argv)
{
    int fd;
    struct binder_state *bs;
    void *svcmgr = BINDER_SERVICE_MANAGER;

    bs = binder_open(128*1024);
	sv_show(bs,svcmgr);

    return 0;
}
