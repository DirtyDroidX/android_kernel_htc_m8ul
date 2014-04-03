/*
	Based on skeleton.c,
	Written 1993-94 by Donald Becker.
	See the skeleton.c file for further copyright information.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached as hamish@zot.apana.org.au

	This file is a network device driver for the SEEQ 8005 chipset and
	the Linux operating system.

*/

static const char version[] =
	"seeq8005.c:v1.00 8/07/95 Hamish Coleman (hamish@zot.apana.org.au)\n";


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/bitops.h>
#include <linux/jiffies.h>

#include <asm/io.h>
#include <asm/dma.h>

#include "seeq8005.h"

static unsigned int seeq8005_portlist[] __initdata =
   { 0x300, 0x320, 0x340, 0x360, 0};

#ifndef NET_DEBUG
#define NET_DEBUG 1
#endif
static unsigned int net_debug = NET_DEBUG;

struct net_local {
	unsigned short receive_ptr;		
	long open_time;				
};

#define SA_ADDR0 0x00
#define SA_ADDR1 0x80
#define SA_ADDR2 0x4b


static int seeq8005_probe1(struct net_device *dev, int ioaddr);
static int seeq8005_open(struct net_device *dev);
static void seeq8005_timeout(struct net_device *dev);
static netdev_tx_t seeq8005_send_packet(struct sk_buff *skb,
					struct net_device *dev);
static irqreturn_t seeq8005_interrupt(int irq, void *dev_id);
static void seeq8005_rx(struct net_device *dev);
static int seeq8005_close(struct net_device *dev);
static void set_multicast_list(struct net_device *dev);

#define tx_done(dev)	(inw(SEEQ_STATUS) & SEEQSTAT_TX_ON)
static void hardware_send_packet(struct net_device *dev, char *buf, int length);
extern void seeq8005_init(struct net_device *dev, int startp);
static inline void wait_for_buffer(struct net_device *dev);



static int io = 0x320;
static int irq = 10;

struct net_device * __init seeq8005_probe(int unit)
{
	struct net_device *dev = alloc_etherdev(sizeof(struct net_local));
	unsigned *port;
	int err = 0;

	if (!dev)
		return ERR_PTR(-ENODEV);

	if (unit >= 0) {
		sprintf(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
		io = dev->base_addr;
		irq = dev->irq;
	}

	if (io > 0x1ff) {	
		err = seeq8005_probe1(dev, io);
	} else if (io != 0) {	
		err = -ENXIO;
	} else {
		for (port = seeq8005_portlist; *port; port++) {
			if (seeq8005_probe1(dev, *port) == 0)
				break;
		}
		if (!*port)
			err = -ENODEV;
	}
	if (err)
		goto out;
	err = register_netdev(dev);
	if (err)
		goto out1;
	return dev;
out1:
	release_region(dev->base_addr, SEEQ8005_IO_EXTENT);
out:
	free_netdev(dev);
	return ERR_PTR(err);
}

static const struct net_device_ops seeq8005_netdev_ops = {
	.ndo_open		= seeq8005_open,
	.ndo_stop		= seeq8005_close,
	.ndo_start_xmit 	= seeq8005_send_packet,
	.ndo_tx_timeout		= seeq8005_timeout,
	.ndo_set_rx_mode	= set_multicast_list,
	.ndo_change_mtu		= eth_change_mtu,
	.ndo_set_mac_address 	= eth_mac_addr,
	.ndo_validate_addr	= eth_validate_addr,
};


static int __init seeq8005_probe1(struct net_device *dev, int ioaddr)
{
	static unsigned version_printed;
	int i,j;
	unsigned char SA_prom[32];
	int old_cfg1;
	int old_cfg2;
	int old_stat;
	int old_dmaar;
	int old_rear;
	int retval;

	if (!request_region(ioaddr, SEEQ8005_IO_EXTENT, "seeq8005"))
		return -ENODEV;

	if (net_debug>1)
		printk("seeq8005: probing at 0x%x\n",ioaddr);

	old_stat = inw(SEEQ_STATUS);					
	if (old_stat == 0xffff) {
		retval = -ENODEV;
		goto out;						
	}
	if ( (old_stat & 0x1800) != 0x1800 ) {				
		if (net_debug>1) {
			printk("seeq8005: reserved stat bits != 0x1800\n");
			printk("          == 0x%04x\n",old_stat);
		}
	 	retval = -ENODEV;
		goto out;
	}

	old_rear = inw(SEEQ_REA);
	if (old_rear == 0xffff) {
		outw(0,SEEQ_REA);
		if (inw(SEEQ_REA) == 0xffff) {				
			retval = -ENODEV;
			goto out;
		}
	} else if ((old_rear & 0xff00) != 0xff00) {			
		if (net_debug>1) {
			printk("seeq8005: unused rear bits != 0xff00\n");
			printk("          == 0x%04x\n",old_rear);
		}
		retval = -ENODEV;
		goto out;
	}

	old_cfg2 = inw(SEEQ_CFG2);					
	old_cfg1 = inw(SEEQ_CFG1);
	old_dmaar = inw(SEEQ_DMAAR);

	if (net_debug>4) {
		printk("seeq8005: stat = 0x%04x\n",old_stat);
		printk("seeq8005: cfg1 = 0x%04x\n",old_cfg1);
		printk("seeq8005: cfg2 = 0x%04x\n",old_cfg2);
		printk("seeq8005: raer = 0x%04x\n",old_rear);
		printk("seeq8005: dmaar= 0x%04x\n",old_dmaar);
	}

	outw( SEEQCMD_FIFO_WRITE | SEEQCMD_SET_ALL_OFF, SEEQ_CMD);	
	outw( 0, SEEQ_DMAAR);						
	outw( SEEQCFG1_BUFFER_PROM, SEEQ_CFG1);				


	j=0;
	for(i=0; i <32; i++) {
		j+= SA_prom[i] = inw(SEEQ_BUFFER) & 0xff;
	}

#if 0
	
	if ( (j&0xff) != 0 ) {						
		if (net_debug>1) {					
			printk("seeq8005: prom sum error\n");
		}
		outw( old_stat, SEEQ_STATUS);
		outw( old_dmaar, SEEQ_DMAAR);
		outw( old_cfg1, SEEQ_CFG1);
		retval = -ENODEV;
		goto out;
	}
#endif

	outw( SEEQCFG2_RESET, SEEQ_CFG2);				
	udelay(5);
	outw( SEEQCMD_SET_ALL_OFF, SEEQ_CMD);

	if (net_debug) {
		printk("seeq8005: prom sum = 0x%08x\n",j);
		for(j=0; j<32; j+=16) {
			printk("seeq8005: prom %02x: ",j);
			for(i=0;i<16;i++) {
				printk("%02x ",SA_prom[j|i]);
			}
			printk(" ");
			for(i=0;i<16;i++) {
				if ((SA_prom[j|i]>31)&&(SA_prom[j|i]<127)) {
					printk("%c", SA_prom[j|i]);
				} else {
					printk(" ");
				}
			}
			printk("\n");
		}
	}

#if 0
	if (net_debug>1) {					
		printk("seeq8005: testing packet buffer ... ");
		outw( SEEQCFG1_BUFFER_BUFFER, SEEQ_CFG1);
		outw( SEEQCMD_FIFO_WRITE | SEEQCMD_SET_ALL_OFF, SEEQ_CMD);
		outw( 0 , SEEQ_DMAAR);
		for(i=0;i<32768;i++) {
			outw(0x5a5a, SEEQ_BUFFER);
		}
		j=jiffies+HZ;
		while ( ((inw(SEEQ_STATUS) & SEEQSTAT_FIFO_EMPTY) != SEEQSTAT_FIFO_EMPTY) && time_before(jiffies, j) )
			mb();
		outw( 0 , SEEQ_DMAAR);
		while ( ((inw(SEEQ_STATUS) & SEEQSTAT_WINDOW_INT) != SEEQSTAT_WINDOW_INT) && time_before(jiffies, j+HZ))
			mb();
		if ( (inw(SEEQ_STATUS) & SEEQSTAT_WINDOW_INT) == SEEQSTAT_WINDOW_INT)
			outw( SEEQCMD_WINDOW_INT_ACK | (inw(SEEQ_STATUS)& SEEQCMD_INT_MASK), SEEQ_CMD);
		outw( SEEQCMD_FIFO_READ | SEEQCMD_SET_ALL_OFF, SEEQ_CMD);
		j=0;
		for(i=0;i<32768;i++) {
			if (inw(SEEQ_BUFFER) != 0x5a5a)
				j++;
		}
		if (j) {
			printk("%i\n",j);
		} else {
			printk("ok.\n");
		}
	}
#endif

	if (net_debug  &&  version_printed++ == 0)
		printk(version);

	printk("%s: %s found at %#3x, ", dev->name, "seeq8005", ioaddr);

	
	dev->base_addr = ioaddr;
	dev->irq = irq;

	
	for (i = 0; i < 6; i++)
		dev->dev_addr[i] = SA_prom[i+6];
	printk("%pM", dev->dev_addr);

	if (dev->irq == 0xff)
		;			
	else if (dev->irq < 2) {	
		unsigned long cookie = probe_irq_on();

		outw( SEEQCMD_RX_INT_EN | SEEQCMD_SET_RX_ON | SEEQCMD_SET_RX_OFF, SEEQ_CMD );

		dev->irq = probe_irq_off(cookie);

		if (net_debug >= 2)
			printk(" autoirq is %d\n", dev->irq);
	} else if (dev->irq == 2)
	  dev->irq = 9;

#if 0
	{
		 int irqval = request_irq(dev->irq, seeq8005_interrupt, 0, "seeq8005", dev);
		 if (irqval) {
			 printk ("%s: unable to get IRQ %d (irqval=%d).\n", dev->name,
					 dev->irq, irqval);
			 retval = -EAGAIN;
			 goto out;
		 }
	}
#endif
	dev->netdev_ops = &seeq8005_netdev_ops;
	dev->watchdog_timeo	= HZ/20;
	dev->flags &= ~IFF_MULTICAST;

	return 0;
out:
	release_region(ioaddr, SEEQ8005_IO_EXTENT);
	return retval;
}


static int seeq8005_open(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);

	{
		 int irqval = request_irq(dev->irq, seeq8005_interrupt, 0, "seeq8005", dev);
		 if (irqval) {
			 printk ("%s: unable to get IRQ %d (irqval=%d).\n", dev->name,
					 dev->irq, irqval);
			 return -EAGAIN;
		 }
	}

	
	seeq8005_init(dev, 1);

	lp->open_time = jiffies;

	netif_start_queue(dev);
	return 0;
}

static void seeq8005_timeout(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	printk(KERN_WARNING "%s: transmit timed out, %s?\n", dev->name,
		   tx_done(dev) ? "IRQ conflict" : "network cable problem");
	
	seeq8005_init(dev, 1);
	dev->trans_start = jiffies; 
	netif_wake_queue(dev);
}

static netdev_tx_t seeq8005_send_packet(struct sk_buff *skb,
					struct net_device *dev)
{
	short length = skb->len;
	unsigned char *buf;

	if (length < ETH_ZLEN) {
		if (skb_padto(skb, ETH_ZLEN))
			return NETDEV_TX_OK;
		length = ETH_ZLEN;
	}
	buf = skb->data;

	
	netif_stop_queue(dev);

	hardware_send_packet(dev, buf, length);
	dev->stats.tx_bytes += length;
	dev_kfree_skb (skb);
	

	return NETDEV_TX_OK;
}

inline void wait_for_buffer(struct net_device * dev)
{
	int ioaddr = dev->base_addr;
	unsigned long tmp;
	int status;

	tmp = jiffies + HZ;
	while ( ( ((status=inw(SEEQ_STATUS)) & SEEQSTAT_WINDOW_INT) != SEEQSTAT_WINDOW_INT) && time_before(jiffies, tmp))
		cpu_relax();

	if ( (status & SEEQSTAT_WINDOW_INT) == SEEQSTAT_WINDOW_INT)
		outw( SEEQCMD_WINDOW_INT_ACK | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
}

static irqreturn_t seeq8005_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct net_local *lp;
	int ioaddr, status, boguscount = 0;
	int handled = 0;

	ioaddr = dev->base_addr;
	lp = netdev_priv(dev);

	status = inw(SEEQ_STATUS);
	do {
		if (net_debug >2) {
			printk("%s: int, status=0x%04x\n",dev->name,status);
		}

		if (status & SEEQSTAT_WINDOW_INT) {
			handled = 1;
			outw( SEEQCMD_WINDOW_INT_ACK | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
			if (net_debug) {
				printk("%s: window int!\n",dev->name);
			}
		}
		if (status & SEEQSTAT_TX_INT) {
			handled = 1;
			outw( SEEQCMD_TX_INT_ACK | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
			dev->stats.tx_packets++;
			netif_wake_queue(dev);	
		}
		if (status & SEEQSTAT_RX_INT) {
			handled = 1;
			
			seeq8005_rx(dev);
		}
		status = inw(SEEQ_STATUS);
	} while ( (++boguscount < 10) && (status & SEEQSTAT_ANY_INT)) ;

	if(net_debug>2) {
		printk("%s: eoi\n",dev->name);
	}
	return IRQ_RETVAL(handled);
}

static void seeq8005_rx(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	int boguscount = 10;
	int pkt_hdr;
	int ioaddr = dev->base_addr;

	do {
		int next_packet;
		int pkt_len;
		int i;
		int status;

		status = inw(SEEQ_STATUS);
	  	outw( lp->receive_ptr, SEEQ_DMAAR);
		outw(SEEQCMD_FIFO_READ | SEEQCMD_RX_INT_ACK | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
	  	wait_for_buffer(dev);
	  	next_packet = ntohs(inw(SEEQ_BUFFER));
	  	pkt_hdr = inw(SEEQ_BUFFER);

		if (net_debug>2) {
			printk("%s: 0x%04x recv next=0x%04x, hdr=0x%04x\n",dev->name,lp->receive_ptr,next_packet,pkt_hdr);
		}

		if ((next_packet == 0) || ((pkt_hdr & SEEQPKTH_CHAIN)==0)) {	
			return;							
		}

		if ((pkt_hdr & SEEQPKTS_DONE)==0)
			break;

		if (next_packet < lp->receive_ptr) {
			pkt_len = (next_packet + 0x10000 - ((DEFAULT_TEA+1)<<8)) - lp->receive_ptr - 4;
		} else {
			pkt_len = next_packet - lp->receive_ptr - 4;
		}

		if (next_packet < ((DEFAULT_TEA+1)<<8)) {			
			printk("%s: recv packet ring corrupt, resetting board\n",dev->name);
			seeq8005_init(dev,1);
			return;
		}

		lp->receive_ptr = next_packet;

		if (net_debug>2) {
			printk("%s: recv len=0x%04x\n",dev->name,pkt_len);
		}

		if (pkt_hdr & SEEQPKTS_ANY_ERROR) {				
			dev->stats.rx_errors++;
			if (pkt_hdr & SEEQPKTS_SHORT) dev->stats.rx_frame_errors++;
			if (pkt_hdr & SEEQPKTS_DRIB) dev->stats.rx_frame_errors++;
			if (pkt_hdr & SEEQPKTS_OVERSIZE) dev->stats.rx_over_errors++;
			if (pkt_hdr & SEEQPKTS_CRC_ERR) dev->stats.rx_crc_errors++;
			
			outw( SEEQCMD_FIFO_WRITE | SEEQCMD_DMA_INT_ACK | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
			outw( (lp->receive_ptr & 0xff00)>>8, SEEQ_REA);
		} else {
			
			struct sk_buff *skb;
			unsigned char *buf;

			skb = netdev_alloc_skb(dev, pkt_len);
			if (skb == NULL) {
				printk("%s: Memory squeeze, dropping packet.\n", dev->name);
				dev->stats.rx_dropped++;
				break;
			}
			skb_reserve(skb, 2);	
			buf = skb_put(skb,pkt_len);

			insw(SEEQ_BUFFER, buf, (pkt_len + 1) >> 1);

			if (net_debug>2) {
				char * p = buf;
				printk("%s: recv ",dev->name);
				for(i=0;i<14;i++) {
					printk("%02x ",*(p++)&0xff);
				}
				printk("\n");
			}

			skb->protocol=eth_type_trans(skb,dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		}
	} while ((--boguscount) && (pkt_hdr & SEEQPKTH_CHAIN));

}

static int seeq8005_close(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;

	lp->open_time = 0;

	netif_stop_queue(dev);

	
	outw( SEEQCMD_SET_ALL_OFF, SEEQ_CMD);

	free_irq(dev->irq, dev);

	

	return 0;

}

static void set_multicast_list(struct net_device *dev)
{

#if 0
	int ioaddr = dev->base_addr;

	if (num_addrs) {			
		outw( (inw(SEEQ_CFG1) & ~SEEQCFG1_MATCH_MASK)| SEEQCFG1_MATCH_ALL,  SEEQ_CFG1);
		dev->flags|=IFF_PROMISC;
	} else {				
		outw( (inw(SEEQ_CFG1) & ~SEEQCFG1_MATCH_MASK)| SEEQCFG1_MATCH_BROAD, SEEQ_CFG1);
	}
#endif
}

void seeq8005_init(struct net_device *dev, int startp)
{
	struct net_local *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	int i;

	outw(SEEQCFG2_RESET, SEEQ_CFG2);	
	udelay(5);

	outw( SEEQCMD_FIFO_WRITE | SEEQCMD_SET_ALL_OFF, SEEQ_CMD);
	outw( 0, SEEQ_DMAAR);			
		
	outw( SEEQCFG1_BUFFER_MAC0, SEEQ_CFG1);

	for(i=0;i<6;i++) {			
		outb(dev->dev_addr[i], SEEQ_BUFFER);
		udelay(2);
	}

	outw( SEEQCFG1_BUFFER_TEA, SEEQ_CFG1);	
	outb( DEFAULT_TEA, SEEQ_BUFFER);	

	lp->receive_ptr = (DEFAULT_TEA+1)<<8;	
	outw( lp->receive_ptr, SEEQ_RPR);	

	outw( 0x00ff, SEEQ_REA);		

	if (net_debug>4) {
		printk("%s: SA0 = ",dev->name);

		outw( SEEQCMD_FIFO_READ | SEEQCMD_SET_ALL_OFF, SEEQ_CMD);
		outw( 0, SEEQ_DMAAR);
		outw( SEEQCFG1_BUFFER_MAC0, SEEQ_CFG1);

		for(i=0;i<6;i++) {
			printk("%02x ",inb(SEEQ_BUFFER));
		}
		printk("\n");
	}

	outw( SEEQCFG1_MAC0_EN | SEEQCFG1_MATCH_BROAD | SEEQCFG1_BUFFER_BUFFER, SEEQ_CFG1);
	outw( SEEQCFG2_AUTO_REA | SEEQCFG2_CTRLO, SEEQ_CFG2);
	outw( SEEQCMD_SET_RX_ON | SEEQCMD_TX_INT_EN | SEEQCMD_RX_INT_EN, SEEQ_CMD);

	if (net_debug>4) {
		int old_cfg1;
		old_cfg1 = inw(SEEQ_CFG1);
		printk("%s: stat = 0x%04x\n",dev->name,inw(SEEQ_STATUS));
		printk("%s: cfg1 = 0x%04x\n",dev->name,old_cfg1);
		printk("%s: cfg2 = 0x%04x\n",dev->name,inw(SEEQ_CFG2));
		printk("%s: raer = 0x%04x\n",dev->name,inw(SEEQ_REA));
		printk("%s: dmaar= 0x%04x\n",dev->name,inw(SEEQ_DMAAR));

	}
}


static void hardware_send_packet(struct net_device * dev, char *buf, int length)
{
	int ioaddr = dev->base_addr;
	int status = inw(SEEQ_STATUS);
	int transmit_ptr = 0;
	unsigned long tmp;

	if (net_debug>4) {
		printk("%s: send 0x%04x\n",dev->name,length);
	}

	
	outw( SEEQCMD_FIFO_WRITE | (status & SEEQCMD_INT_MASK), SEEQ_CMD);
	outw( transmit_ptr, SEEQ_DMAAR);

	
	outw( htons(length + 4), SEEQ_BUFFER);
	outw( SEEQPKTH_XMIT | SEEQPKTH_DATA_FOLLOWS | SEEQPKTH_XMIT_INT_EN, SEEQ_BUFFER );

	
	outsw( SEEQ_BUFFER, buf, (length +1) >> 1);
	
	outw( 0, SEEQ_BUFFER);
	outw( 0, SEEQ_BUFFER);

	
	outw( transmit_ptr, SEEQ_TPR);

	
	tmp = jiffies;
	while ( (((status=inw(SEEQ_STATUS)) & SEEQSTAT_FIFO_EMPTY) == 0) && time_before(jiffies, tmp + HZ))
		mb();

	
	outw( SEEQCMD_WINDOW_INT_ACK | SEEQCMD_SET_TX_ON | (status & SEEQCMD_INT_MASK), SEEQ_CMD);

}


#ifdef MODULE

static struct net_device *dev_seeq;
MODULE_LICENSE("GPL");
module_param(io, int, 0);
module_param(irq, int, 0);
MODULE_PARM_DESC(io, "SEEQ 8005 I/O base address");
MODULE_PARM_DESC(irq, "SEEQ 8005 IRQ number");

int __init init_module(void)
{
	dev_seeq = seeq8005_probe(-1);
	if (IS_ERR(dev_seeq))
		return PTR_ERR(dev_seeq);
	return 0;
}

void __exit cleanup_module(void)
{
	unregister_netdev(dev_seeq);
	release_region(dev_seeq->base_addr, SEEQ8005_IO_EXTENT);
	free_netdev(dev_seeq);
}

#endif 