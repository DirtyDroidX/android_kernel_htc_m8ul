#ifndef __SUN3_MMU_H__
#define __SUN3_MMU_H__

#include <linux/types.h>
#include <asm/movs.h>
#include <asm/sun3-head.h>

#define SUN3_SEGMAPS_PER_CONTEXT	2048
#define SUN3_PMEGS_NUM			256
#define SUN3_CONTEXTS_NUM               8

#define SUN3_PMEG_SIZE_BITS	 17
#define SUN3_PMEG_SIZE		 (1 << SUN3_PMEG_SIZE_BITS)
#define SUN3_PMEG_MASK		 (SUN3_PMEG_SIZE - 1)

#define SUN3_PTE_SIZE_BITS       13
#define SUN3_PTE_SIZE		 (1 << SUN3_PTE_SIZE_BITS)
#define SUN3_PTE_MASK		 (SUN3_PTE_SIZE - 1)

#define SUN3_CONTROL_MASK       (0x0FFFFFFC)
#define SUN3_INVALID_PMEG	255
#define SUN3_INVALID_CONTEXT 255

#define AC_IDPROM     0x00000000    
#define AC_PAGEMAP    0x10000000    
#define AC_SEGMAP     0x20000000    
#define AC_CONTEXT    0x30000000    
#define AC_SENABLE    0x40000000    
#define AC_UDVMA_ENB  0x50000000    
#define AC_BUS_ERROR  0x60000000    
#define AC_SYNC_ERR   0x60000000    
#define AC_SYNC_VA    0x60000004    
#define AC_ASYNC_ERR  0x60000008    
#define AC_ASYNC_VA   0x6000000c    
#define AC_LEDS       0x70000000    
#define AC_CACHETAGS  0x80000000    
#define AC_CACHEDDATA 0x90000000    
#define AC_UDVMA_MAP  0xD0000000    
#define AC_VME_VECTOR 0xE0000000    
#define AC_BOOT_SCC   0xF0000000    

#define SUN3_PAGE_CHG_MASK (SUN3_PAGE_PGNUM_MASK \
			    | SUN3_PAGE_ACCESSED | SUN3_PAGE_MODIFIED)

#define SUN3_PAGE_TYPE_MASK   (0x0c000000)
#define SUN3_PAGE_TYPE_MEMORY (0x00000000)
#define SUN3_PAGE_TYPE_IO     (0x04000000)
#define SUN3_PAGE_TYPE_VME16  (0x08000000)
#define SUN3_PAGE_TYPE_VME32  (0x0c000000)

#define SUN3_PAGE_PGNUM_MASK (0x0007FFFF)

#define SUN3_BUSERR_WATCHDOG	(0x01)
#define SUN3_BUSERR_unused	(0x02)
#define SUN3_BUSERR_FPAENERR	(0x04)
#define SUN3_BUSERR_FPABERR	(0x08)
#define SUN3_BUSERR_VMEBERR	(0x10)
#define SUN3_BUSERR_TIMEOUT	(0x20)
#define SUN3_BUSERR_PROTERR	(0x40)
#define SUN3_BUSERR_INVALID	(0x80)

#ifndef __ASSEMBLY__

static inline unsigned char sun3_get_buserr(void)
{
	unsigned char sfc, c;

	GET_SFC (sfc);
	SET_SFC (FC_CONTROL);
	GET_CONTROL_BYTE (AC_BUS_ERROR, c);
	SET_SFC (sfc);

	return c;
}

static inline unsigned long sun3_get_segmap(unsigned long addr)
{
        register unsigned long entry;
        unsigned char c, sfc;

        GET_SFC (sfc);
        SET_SFC (FC_CONTROL);
        GET_CONTROL_BYTE (AC_SEGMAP | (addr & SUN3_CONTROL_MASK), c);
        SET_SFC (sfc);
        entry = c;

        return entry;
}

static inline void sun3_put_segmap(unsigned long addr, unsigned long entry)
{
        unsigned char sfc;

        GET_DFC (sfc);
        SET_DFC (FC_CONTROL);
        SET_CONTROL_BYTE (AC_SEGMAP | (addr & SUN3_CONTROL_MASK), entry);
	SET_DFC (sfc);

        return;
}

static inline unsigned long sun3_get_pte(unsigned long addr)
{
        register unsigned long entry;
        unsigned char sfc;

        GET_SFC (sfc);
        SET_SFC (FC_CONTROL);
        GET_CONTROL_WORD (AC_PAGEMAP | (addr & SUN3_CONTROL_MASK), entry);
        SET_SFC (sfc);

        return entry;
}

static inline void sun3_put_pte(unsigned long addr, unsigned long entry)
{
        unsigned char sfc;

        GET_DFC (sfc);
        SET_DFC (FC_CONTROL);
        SET_CONTROL_WORD (AC_PAGEMAP | (addr & SUN3_CONTROL_MASK), entry);
	SET_DFC (sfc);

        return;
}

static inline unsigned char sun3_get_context(void)
{
	unsigned char sfc, c;

	GET_SFC(sfc);
	SET_SFC(FC_CONTROL);
	GET_CONTROL_BYTE(AC_CONTEXT, c);
	SET_SFC(sfc);

	return c;
}

static inline void sun3_put_context(unsigned char c)
{
	unsigned char dfc;
	GET_DFC(dfc);
	SET_DFC(FC_CONTROL);
	SET_CONTROL_BYTE(AC_CONTEXT, c);
	SET_DFC(dfc);

	return;
}

extern void __iomem *sun3_ioremap(unsigned long phys, unsigned long size,
			  unsigned long type);

extern int sun3_map_test(unsigned long addr, char *val);

#endif	

#endif	
