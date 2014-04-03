#ifndef _CSS_H
#define _CSS_H

#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/workqueue.h>
#include <linux/device.h>
#include <linux/types.h>

#include <asm/cio.h>
#include <asm/chpid.h>
#include <asm/schid.h>

#include "cio.h"

#define SPID_FUNC_SINGLE_PATH	   0x00
#define SPID_FUNC_MULTI_PATH	   0x80
#define SPID_FUNC_ESTABLISH	   0x00
#define SPID_FUNC_RESIGN	   0x40
#define SPID_FUNC_DISBAND	   0x20

#define SNID_STATE1_RESET	   0
#define SNID_STATE1_UNGROUPED	   2
#define SNID_STATE1_GROUPED	   3

#define SNID_STATE2_NOT_RESVD	   0
#define SNID_STATE2_RESVD_ELSE	   2
#define SNID_STATE2_RESVD_SELF	   3

#define SNID_STATE3_MULTI_PATH	   1
#define SNID_STATE3_SINGLE_PATH	   0

struct path_state {
	__u8  state1 : 2;	
	__u8  state2 : 2;	
	__u8  state3 : 1;	
	__u8  resvd  : 3;	
} __attribute__ ((packed));

struct extended_cssid {
	u8 version;
	u8 cssid;
} __attribute__ ((packed));

struct pgid {
	union {
		__u8 fc;   	
		struct path_state ps;	
	} __attribute__ ((packed)) inf;
	union {
		__u32 cpu_addr	: 16;	
		struct extended_cssid ext_cssid;
	} __attribute__ ((packed)) pgid_high;
	__u32 cpu_id	: 24;	
	__u32 cpu_model : 16;	
	__u32 tod_high;		
} __attribute__ ((packed));

struct subchannel;
struct chp_link;
struct css_driver {
	struct css_device_id *subchannel_type;
	struct device_driver drv;
	void (*irq)(struct subchannel *);
	int (*chp_event)(struct subchannel *, struct chp_link *, int);
	int (*sch_event)(struct subchannel *, int);
	int (*probe)(struct subchannel *);
	int (*remove)(struct subchannel *);
	void (*shutdown)(struct subchannel *);
	int (*prepare) (struct subchannel *);
	void (*complete) (struct subchannel *);
	int (*freeze)(struct subchannel *);
	int (*thaw) (struct subchannel *);
	int (*restore)(struct subchannel *);
	int (*settle)(void);
};

#define to_cssdriver(n) container_of(n, struct css_driver, drv)

extern int css_driver_register(struct css_driver *);
extern void css_driver_unregister(struct css_driver *);

extern void css_sch_device_unregister(struct subchannel *);
extern int css_probe_device(struct subchannel_id);
extern struct subchannel *get_subchannel_by_schid(struct subchannel_id);
extern int css_init_done;
extern int max_ssid;
int for_each_subchannel_staged(int (*fn_known)(struct subchannel *, void *),
			       int (*fn_unknown)(struct subchannel_id,
			       void *), void *data);
extern int for_each_subchannel(int(*fn)(struct subchannel_id, void *), void *);
extern void css_reiterate_subchannels(void);
void css_update_ssd_info(struct subchannel *sch);

#define __MAX_SUBCHANNEL 65535
#define __MAX_SSID 3

struct channel_subsystem {
	u8 cssid;
	int valid;
	struct channel_path *chps[__MAX_CHPID + 1];
	struct device device;
	struct pgid global_pgid;
	struct mutex mutex;
	
	int cm_enabled;
	void *cub_addr1;
	void *cub_addr2;
	
	struct subchannel *pseudo_subchannel;
};
#define to_css(dev) container_of(dev, struct channel_subsystem, device)

extern struct channel_subsystem *channel_subsystems[];

void channel_subsystem_reinit(void);

void css_schedule_eval(struct subchannel_id schid);
void css_schedule_eval_all(void);
int css_complete_work(void);

int sch_is_pseudo_sch(struct subchannel *);
struct schib;
int css_sch_is_valid(struct schib *);

extern struct workqueue_struct *cio_work_q;
void css_wait_for_slow_path(void);
void css_sched_sch_todo(struct subchannel *sch, enum sch_todo todo);
#endif