/*
 * Copyright 2007-2010 Analog Devices Inc.
 *
 * Licensed under the ADI BSD license or the GPL-2 (or later)
 */

#ifndef _DEF_BF542_H
#define _DEF_BF542_H

#include "defBF54x_base.h"



#define                    ATAPI_CONTROL  0xffc03800   
#define                     ATAPI_STATUS  0xffc03804   
#define                   ATAPI_DEV_ADDR  0xffc03808   
#define                  ATAPI_DEV_TXBUF  0xffc0380c   
#define                  ATAPI_DEV_RXBUF  0xffc03810   
#define                   ATAPI_INT_MASK  0xffc03814   
#define                 ATAPI_INT_STATUS  0xffc03818   
#define                   ATAPI_XFER_LEN  0xffc0381c   
#define                ATAPI_LINE_STATUS  0xffc03820   
#define                   ATAPI_SM_STATE  0xffc03824   
#define                  ATAPI_TERMINATE  0xffc03828   
#define                 ATAPI_PIO_TFRCNT  0xffc0382c   
#define                 ATAPI_DMA_TFRCNT  0xffc03830   
#define               ATAPI_UMAIN_TFRCNT  0xffc03834   
#define             ATAPI_UDMAOUT_TFRCNT  0xffc03838   
#define                  ATAPI_REG_TIM_0  0xffc03840   
#define                  ATAPI_PIO_TIM_0  0xffc03844   
#define                  ATAPI_PIO_TIM_1  0xffc03848   
#define                ATAPI_MULTI_TIM_0  0xffc03850   
#define                ATAPI_MULTI_TIM_1  0xffc03854   
#define                ATAPI_MULTI_TIM_2  0xffc03858   
#define                ATAPI_ULTRA_TIM_0  0xffc03860   
#define                ATAPI_ULTRA_TIM_1  0xffc03864   
#define                ATAPI_ULTRA_TIM_2  0xffc03868   
#define                ATAPI_ULTRA_TIM_3  0xffc0386c   


#define                      SDH_PWR_CTL  0xffc03900   
#define                      SDH_CLK_CTL  0xffc03904   
#define                     SDH_ARGUMENT  0xffc03908   
#define                      SDH_COMMAND  0xffc0390c   
#define                     SDH_RESP_CMD  0xffc03910   
#define                    SDH_RESPONSE0  0xffc03914   
#define                    SDH_RESPONSE1  0xffc03918   
#define                    SDH_RESPONSE2  0xffc0391c   
#define                    SDH_RESPONSE3  0xffc03920   
#define                   SDH_DATA_TIMER  0xffc03924   
#define                    SDH_DATA_LGTH  0xffc03928   
#define                     SDH_DATA_CTL  0xffc0392c   
#define                     SDH_DATA_CNT  0xffc03930   
#define                       SDH_STATUS  0xffc03934   
#define                   SDH_STATUS_CLR  0xffc03938   
#define                        SDH_MASK0  0xffc0393c   
#define                        SDH_MASK1  0xffc03940   
#define                     SDH_FIFO_CNT  0xffc03948   
#define                         SDH_FIFO  0xffc03980   
#define                     SDH_E_STATUS  0xffc039c0   
#define                       SDH_E_MASK  0xffc039c4   
#define                          SDH_CFG  0xffc039c8   
#define                   SDH_RD_WAIT_EN  0xffc039cc   
#define                         SDH_PID0  0xffc039d0   
#define                         SDH_PID1  0xffc039d4   
#define                         SDH_PID2  0xffc039d8   
#define                         SDH_PID3  0xffc039dc   
#define                         SDH_PID4  0xffc039e0   
#define                         SDH_PID5  0xffc039e4   
#define                         SDH_PID6  0xffc039e8   
#define                         SDH_PID7  0xffc039ec   


#define                        USB_FADDR  0xffc03c00   
#define                        USB_POWER  0xffc03c04   
#define                       USB_INTRTX  0xffc03c08   
#define                       USB_INTRRX  0xffc03c0c   
#define                      USB_INTRTXE  0xffc03c10   
#define                      USB_INTRRXE  0xffc03c14   
#define                      USB_INTRUSB  0xffc03c18   
#define                     USB_INTRUSBE  0xffc03c1c   
#define                        USB_FRAME  0xffc03c20   
#define                        USB_INDEX  0xffc03c24   
#define                     USB_TESTMODE  0xffc03c28   
#define                     USB_GLOBINTR  0xffc03c2c   
#define                   USB_GLOBAL_CTL  0xffc03c30   


#define                USB_TX_MAX_PACKET  0xffc03c40   
#define                         USB_CSR0  0xffc03c44   
#define                        USB_TXCSR  0xffc03c44   
#define                USB_RX_MAX_PACKET  0xffc03c48   
#define                        USB_RXCSR  0xffc03c4c   
#define                       USB_COUNT0  0xffc03c50   
#define                      USB_RXCOUNT  0xffc03c50   
#define                       USB_TXTYPE  0xffc03c54   
#define                    USB_NAKLIMIT0  0xffc03c58   
#define                   USB_TXINTERVAL  0xffc03c58   
#define                       USB_RXTYPE  0xffc03c5c   
#define                   USB_RXINTERVAL  0xffc03c60   
#define                      USB_TXCOUNT  0xffc03c68   /* Number of bytes to be written to the selected endpoint Tx FIFO */


#define                     USB_EP0_FIFO  0xffc03c80   
#define                     USB_EP1_FIFO  0xffc03c88   
#define                     USB_EP2_FIFO  0xffc03c90   
#define                     USB_EP3_FIFO  0xffc03c98   
#define                     USB_EP4_FIFO  0xffc03ca0   
#define                     USB_EP5_FIFO  0xffc03ca8   
#define                     USB_EP6_FIFO  0xffc03cb0   
#define                     USB_EP7_FIFO  0xffc03cb8   


#define                  USB_OTG_DEV_CTL  0xffc03d00   
#define                 USB_OTG_VBUS_IRQ  0xffc03d04   
#define                USB_OTG_VBUS_MASK  0xffc03d08   


#define                     USB_LINKINFO  0xffc03d48   
#define                        USB_VPLEN  0xffc03d4c   
#define                      USB_HS_EOF1  0xffc03d50   
#define                      USB_FS_EOF1  0xffc03d54   
#define                      USB_LS_EOF1  0xffc03d58   


#define                   USB_APHY_CNTRL  0xffc03de0   


#define                   USB_APHY_CALIB  0xffc03de4   
#define                  USB_APHY_CNTRL2  0xffc03de8   


#define                     USB_PHY_TEST  0xffc03dec   
#define                  USB_PLLOSC_CTRL  0xffc03df0   
#define                   USB_SRP_CLKDIV  0xffc03df4   


#define                USB_EP_NI0_TXMAXP  0xffc03e00   
#define                 USB_EP_NI0_TXCSR  0xffc03e04   
#define                USB_EP_NI0_RXMAXP  0xffc03e08   
#define                 USB_EP_NI0_RXCSR  0xffc03e0c   
#define               USB_EP_NI0_RXCOUNT  0xffc03e10   
#define                USB_EP_NI0_TXTYPE  0xffc03e14   
#define            USB_EP_NI0_TXINTERVAL  0xffc03e18   
#define                USB_EP_NI0_RXTYPE  0xffc03e1c   
#define            USB_EP_NI0_RXINTERVAL  0xffc03e20   


#define               USB_EP_NI0_TXCOUNT  0xffc03e28   /* Number of bytes to be written to the endpoint0 Tx FIFO */
#define                USB_EP_NI1_TXMAXP  0xffc03e40   
#define                 USB_EP_NI1_TXCSR  0xffc03e44   
#define                USB_EP_NI1_RXMAXP  0xffc03e48   
#define                 USB_EP_NI1_RXCSR  0xffc03e4c   
#define               USB_EP_NI1_RXCOUNT  0xffc03e50   
#define                USB_EP_NI1_TXTYPE  0xffc03e54   
#define            USB_EP_NI1_TXINTERVAL  0xffc03e58   
#define                USB_EP_NI1_RXTYPE  0xffc03e5c   
#define            USB_EP_NI1_RXINTERVAL  0xffc03e60   


#define               USB_EP_NI1_TXCOUNT  0xffc03e68   /* Number of bytes to be written to the+H102 endpoint1 Tx FIFO */
#define                USB_EP_NI2_TXMAXP  0xffc03e80   
#define                 USB_EP_NI2_TXCSR  0xffc03e84   
#define                USB_EP_NI2_RXMAXP  0xffc03e88   
#define                 USB_EP_NI2_RXCSR  0xffc03e8c   
#define               USB_EP_NI2_RXCOUNT  0xffc03e90   
#define                USB_EP_NI2_TXTYPE  0xffc03e94   
#define            USB_EP_NI2_TXINTERVAL  0xffc03e98   
#define                USB_EP_NI2_RXTYPE  0xffc03e9c   
#define            USB_EP_NI2_RXINTERVAL  0xffc03ea0   


#define               USB_EP_NI2_TXCOUNT  0xffc03ea8   /* Number of bytes to be written to the endpoint2 Tx FIFO */
#define                USB_EP_NI3_TXMAXP  0xffc03ec0   
#define                 USB_EP_NI3_TXCSR  0xffc03ec4   
#define                USB_EP_NI3_RXMAXP  0xffc03ec8   
#define                 USB_EP_NI3_RXCSR  0xffc03ecc   
#define               USB_EP_NI3_RXCOUNT  0xffc03ed0   
#define                USB_EP_NI3_TXTYPE  0xffc03ed4   
#define            USB_EP_NI3_TXINTERVAL  0xffc03ed8   
#define                USB_EP_NI3_RXTYPE  0xffc03edc   
#define            USB_EP_NI3_RXINTERVAL  0xffc03ee0   


#define               USB_EP_NI3_TXCOUNT  0xffc03ee8   /* Number of bytes to be written to the H124endpoint3 Tx FIFO */
#define                USB_EP_NI4_TXMAXP  0xffc03f00   
#define                 USB_EP_NI4_TXCSR  0xffc03f04   
#define                USB_EP_NI4_RXMAXP  0xffc03f08   
#define                 USB_EP_NI4_RXCSR  0xffc03f0c   
#define               USB_EP_NI4_RXCOUNT  0xffc03f10   
#define                USB_EP_NI4_TXTYPE  0xffc03f14   
#define            USB_EP_NI4_TXINTERVAL  0xffc03f18   
#define                USB_EP_NI4_RXTYPE  0xffc03f1c   
#define            USB_EP_NI4_RXINTERVAL  0xffc03f20   


#define               USB_EP_NI4_TXCOUNT  0xffc03f28   /* Number of bytes to be written to the endpoint4 Tx FIFO */
#define                USB_EP_NI5_TXMAXP  0xffc03f40   
#define                 USB_EP_NI5_TXCSR  0xffc03f44   
#define                USB_EP_NI5_RXMAXP  0xffc03f48   
#define                 USB_EP_NI5_RXCSR  0xffc03f4c   
#define               USB_EP_NI5_RXCOUNT  0xffc03f50   
#define                USB_EP_NI5_TXTYPE  0xffc03f54   
#define            USB_EP_NI5_TXINTERVAL  0xffc03f58   
#define                USB_EP_NI5_RXTYPE  0xffc03f5c   
#define            USB_EP_NI5_RXINTERVAL  0xffc03f60   


#define               USB_EP_NI5_TXCOUNT  0xffc03f68   /* Number of bytes to be written to the H145endpoint5 Tx FIFO */
#define                USB_EP_NI6_TXMAXP  0xffc03f80   
#define                 USB_EP_NI6_TXCSR  0xffc03f84   
#define                USB_EP_NI6_RXMAXP  0xffc03f88   
#define                 USB_EP_NI6_RXCSR  0xffc03f8c   
#define               USB_EP_NI6_RXCOUNT  0xffc03f90   
#define                USB_EP_NI6_TXTYPE  0xffc03f94   
#define            USB_EP_NI6_TXINTERVAL  0xffc03f98   
#define                USB_EP_NI6_RXTYPE  0xffc03f9c   
#define            USB_EP_NI6_RXINTERVAL  0xffc03fa0   


#define               USB_EP_NI6_TXCOUNT  0xffc03fa8   /* Number of bytes to be written to the endpoint6 Tx FIFO */
#define                USB_EP_NI7_TXMAXP  0xffc03fc0   
#define                 USB_EP_NI7_TXCSR  0xffc03fc4   
#define                USB_EP_NI7_RXMAXP  0xffc03fc8   
#define                 USB_EP_NI7_RXCSR  0xffc03fcc   
#define               USB_EP_NI7_RXCOUNT  0xffc03fd0   
#define                USB_EP_NI7_TXTYPE  0xffc03fd4   
#define            USB_EP_NI7_TXINTERVAL  0xffc03fd8   
#define                USB_EP_NI7_RXTYPE  0xffc03fdc   
#define            USB_EP_NI7_RXINTERVAL  0xffc03ff0   
#define               USB_EP_NI7_TXCOUNT  0xffc03ff8   /* Number of bytes to be written to the endpoint7 Tx FIFO */
#define                USB_DMA_INTERRUPT  0xffc04000   


#define                  USB_DMA0CONTROL  0xffc04004   
#define                  USB_DMA0ADDRLOW  0xffc04008   
#define                 USB_DMA0ADDRHIGH  0xffc0400c   
#define                 USB_DMA0COUNTLOW  0xffc04010   
#define                USB_DMA0COUNTHIGH  0xffc04014   


#define                  USB_DMA1CONTROL  0xffc04024   
#define                  USB_DMA1ADDRLOW  0xffc04028   
#define                 USB_DMA1ADDRHIGH  0xffc0402c   
#define                 USB_DMA1COUNTLOW  0xffc04030   
#define                USB_DMA1COUNTHIGH  0xffc04034   


#define                  USB_DMA2CONTROL  0xffc04044   
#define                  USB_DMA2ADDRLOW  0xffc04048   
#define                 USB_DMA2ADDRHIGH  0xffc0404c   
#define                 USB_DMA2COUNTLOW  0xffc04050   
#define                USB_DMA2COUNTHIGH  0xffc04054   


#define                  USB_DMA3CONTROL  0xffc04064   
#define                  USB_DMA3ADDRLOW  0xffc04068   
#define                 USB_DMA3ADDRHIGH  0xffc0406c   
#define                 USB_DMA3COUNTLOW  0xffc04070   
#define                USB_DMA3COUNTHIGH  0xffc04074   


#define                  USB_DMA4CONTROL  0xffc04084   
#define                  USB_DMA4ADDRLOW  0xffc04088   
#define                 USB_DMA4ADDRHIGH  0xffc0408c   
#define                 USB_DMA4COUNTLOW  0xffc04090   
#define                USB_DMA4COUNTHIGH  0xffc04094   


#define                  USB_DMA5CONTROL  0xffc040a4   
#define                  USB_DMA5ADDRLOW  0xffc040a8   
#define                 USB_DMA5ADDRHIGH  0xffc040ac   
#define                 USB_DMA5COUNTLOW  0xffc040b0   
#define                USB_DMA5COUNTHIGH  0xffc040b4   


#define                  USB_DMA6CONTROL  0xffc040c4   
#define                  USB_DMA6ADDRLOW  0xffc040c8   
#define                 USB_DMA6ADDRHIGH  0xffc040cc   
#define                 USB_DMA6COUNTLOW  0xffc040d0   
#define                USB_DMA6COUNTHIGH  0xffc040d4   


#define                  USB_DMA7CONTROL  0xffc040e4   
#define                  USB_DMA7ADDRLOW  0xffc040e8   
#define                 USB_DMA7ADDRHIGH  0xffc040ec   
#define                 USB_DMA7COUNTLOW  0xffc040f0   
#define                USB_DMA7COUNTHIGH  0xffc040f4   


#define                         KPAD_CTL  0xffc04100   
#define                    KPAD_PRESCALE  0xffc04104   
#define                        KPAD_MSEL  0xffc04108   
#define                      KPAD_ROWCOL  0xffc0410c   
#define                        KPAD_STAT  0xffc04110   
#define                    KPAD_SOFTEVAL  0xffc04114   




#define                   KPAD_EN  0x1        
#define              KPAD_IRQMODE  0x6        
#define                KPAD_ROWEN  0x1c00     
#define                KPAD_COLEN  0xe000     


#define         KPAD_PRESCALE_VAL  0x3f       


#define                DBON_SCALE  0xff       
#define              COLDRV_SCALE  0xff00     


#define                  KPAD_ROW  0xff       
#define                  KPAD_COL  0xff00     


#define                  KPAD_IRQ  0x1        
#define              KPAD_MROWCOL  0x6        
#define              KPAD_PRESSED  0x8        


#define           KPAD_SOFTEVAL_E  0x2        


#define                 PIO_START  0x1        
#define               MULTI_START  0x2        
#define               ULTRA_START  0x4        
#define                  XFER_DIR  0x8        
#define                  IORDY_EN  0x10       
#define                FIFO_FLUSH  0x20       
#define                  SOFT_RST  0x40       
#define                   DEV_RST  0x80       
#define                TFRCNT_RST  0x100      
#define               END_ON_TERM  0x200      
#define               PIO_USE_DMA  0x400      
#define          UDMAIN_FIFO_THRS  0xf000     


#define               PIO_XFER_ON  0x1        
#define             MULTI_XFER_ON  0x2        
#define             ULTRA_XFER_ON  0x4        
#define               ULTRA_IN_FL  0xf0       


#define                  DEV_ADDR  0x1f       


#define        ATAPI_DEV_INT_MASK  0x1        
#define             PIO_DONE_MASK  0x2        
#define           MULTI_DONE_MASK  0x4        
#define          UDMAIN_DONE_MASK  0x8        
#define         UDMAOUT_DONE_MASK  0x10       
#define       HOST_TERM_XFER_MASK  0x20       
#define           MULTI_TERM_MASK  0x40       
#define          UDMAIN_TERM_MASK  0x80       
#define         UDMAOUT_TERM_MASK  0x100      


#define             ATAPI_DEV_INT  0x1        
#define              PIO_DONE_INT  0x2        
#define            MULTI_DONE_INT  0x4        
#define           UDMAIN_DONE_INT  0x8        
#define          UDMAOUT_DONE_INT  0x10       
#define        HOST_TERM_XFER_INT  0x20       
#define            MULTI_TERM_INT  0x40       
#define           UDMAIN_TERM_INT  0x80       
#define          UDMAOUT_TERM_INT  0x100      


#define                ATAPI_INTR  0x1        
#define                ATAPI_DASP  0x2        
#define                ATAPI_CS0N  0x4        
#define                ATAPI_CS1N  0x8        
#define                ATAPI_ADDR  0x70       
#define              ATAPI_DMAREQ  0x80       
#define             ATAPI_DMAACKN  0x100      
#define               ATAPI_DIOWN  0x200      
#define               ATAPI_DIORN  0x400      
#define               ATAPI_IORDY  0x800      


#define                PIO_CSTATE  0xf        
#define                DMA_CSTATE  0xf0       
#define             UDMAIN_CSTATE  0xf00      
#define            UDMAOUT_CSTATE  0xf000     


#define           ATAPI_HOST_TERM  0x1        


#define                    T2_REG  0xff       
#define                  TEOC_REG  0xff00     


#define                    T1_REG  0xf        
#define                T2_REG_PIO  0xff0      
#define                    T4_REG  0xf000     


#define              TEOC_REG_PIO  0xff       


#define                        TD  0xff       
#define                        TM  0xff00     


#define                       TKW  0xff       
#define                       TKR  0xff00     


#define                        TH  0xff       
#define                      TEOC  0xff00     


#define                      TACK  0xff       
#define                      TENV  0xff00     


#define                      TDVS  0xff       
#define                 TCYC_TDVS  0xff00     


#define                       TSS  0xff       
#define                      TMLI  0xff00     


#define                      TZAH  0xff       
#define               READY_PAUSE  0xff00     


#define          FUNCTION_ADDRESS  0x7f       


#define           ENABLE_SUSPENDM  0x1        
#define              SUSPEND_MODE  0x2        
#define               RESUME_MODE  0x4        
#define                     RESET  0x8        
#define                   HS_MODE  0x10       
#define                 HS_ENABLE  0x20       
#define                 SOFT_CONN  0x40       
#define                ISO_UPDATE  0x80       


#define                    EP0_TX  0x1        
#define                    EP1_TX  0x2        
#define                    EP2_TX  0x4        
#define                    EP3_TX  0x8        
#define                    EP4_TX  0x10       
#define                    EP5_TX  0x20       
#define                    EP6_TX  0x40       
#define                    EP7_TX  0x80       


#define                    EP1_RX  0x2        
#define                    EP2_RX  0x4        
#define                    EP3_RX  0x8        
#define                    EP4_RX  0x10       
#define                    EP5_RX  0x20       
#define                    EP6_RX  0x40       
#define                    EP7_RX  0x80       


#define                  EP0_TX_E  0x1        
#define                  EP1_TX_E  0x2        
#define                  EP2_TX_E  0x4        
#define                  EP3_TX_E  0x8        
#define                  EP4_TX_E  0x10       
#define                  EP5_TX_E  0x20       
#define                  EP6_TX_E  0x40       
#define                  EP7_TX_E  0x80       


#define                  EP1_RX_E  0x2        
#define                  EP2_RX_E  0x4        
#define                  EP3_RX_E  0x8        
#define                  EP4_RX_E  0x10       
#define                  EP5_RX_E  0x20       
#define                  EP6_RX_E  0x40       
#define                  EP7_RX_E  0x80       


#define                 SUSPEND_B  0x1        
#define                  RESUME_B  0x2        
#define          RESET_OR_BABLE_B  0x4        
#define                     SOF_B  0x8        
#define                    CONN_B  0x10       
#define                  DISCON_B  0x20       
#define             SESSION_REQ_B  0x40       
#define              VBUS_ERROR_B  0x80       


#define                SUSPEND_BE  0x1        
#define                 RESUME_BE  0x2        
#define         RESET_OR_BABLE_BE  0x4        
#define                    SOF_BE  0x8        
#define                   CONN_BE  0x10       
#define                 DISCON_BE  0x20       
#define            SESSION_REQ_BE  0x40       
#define             VBUS_ERROR_BE  0x80       


#define              FRAME_NUMBER  0x7ff      


#define         SELECTED_ENDPOINT  0xf        


#define                GLOBAL_ENA  0x1        
#define                EP1_TX_ENA  0x2        
#define                EP2_TX_ENA  0x4        
#define                EP3_TX_ENA  0x8        
#define                EP4_TX_ENA  0x10       
#define                EP5_TX_ENA  0x20       
#define                EP6_TX_ENA  0x40       
#define                EP7_TX_ENA  0x80       
#define                EP1_RX_ENA  0x100      
#define                EP2_RX_ENA  0x200      
#define                EP3_RX_ENA  0x400      
#define                EP4_RX_ENA  0x800      
#define                EP5_RX_ENA  0x1000     
#define                EP6_RX_ENA  0x2000     
#define                EP7_RX_ENA  0x4000     


#define                   SESSION  0x1        
#define                  HOST_REQ  0x2        
#define                 HOST_MODE  0x4        
#define                     VBUS0  0x8        
#define                     VBUS1  0x10       
#define                     LSDEV  0x20       
#define                     FSDEV  0x40       
#define                  B_DEVICE  0x80       


#define             DRIVE_VBUS_ON  0x1        
#define            DRIVE_VBUS_OFF  0x2        
#define           CHRG_VBUS_START  0x4        
#define             CHRG_VBUS_END  0x8        
#define        DISCHRG_VBUS_START  0x10       
#define          DISCHRG_VBUS_END  0x20       


#define         DRIVE_VBUS_ON_ENA  0x1        
#define        DRIVE_VBUS_OFF_ENA  0x2        
#define       CHRG_VBUS_START_ENA  0x4        
#define         CHRG_VBUS_END_ENA  0x8        
#define    DISCHRG_VBUS_START_ENA  0x10       
#define      DISCHRG_VBUS_END_ENA  0x20       


#define                  RXPKTRDY  0x1        
#define                  TXPKTRDY  0x2        
#define                STALL_SENT  0x4        
#define                   DATAEND  0x8        
#define                  SETUPEND  0x10       
#define                 SENDSTALL  0x20       
#define         SERVICED_RXPKTRDY  0x40       
#define         SERVICED_SETUPEND  0x80       
#define                 FLUSHFIFO  0x100      
#define          STALL_RECEIVED_H  0x4        
#define                SETUPPKT_H  0x8        
#define                   ERROR_H  0x10       
#define                  REQPKT_H  0x20       
#define               STATUSPKT_H  0x40       
#define             NAK_TIMEOUT_H  0x80       


#define              EP0_RX_COUNT  0x7f       


#define             EP0_NAK_LIMIT  0x1f       


#define         MAX_PACKET_SIZE_T  0x7ff      


#define         MAX_PACKET_SIZE_R  0x7ff      


#define                TXPKTRDY_T  0x1        
#define          FIFO_NOT_EMPTY_T  0x2        
#define                UNDERRUN_T  0x4        
#define               FLUSHFIFO_T  0x8        
#define              STALL_SEND_T  0x10       
#define              STALL_SENT_T  0x20       
#define        CLEAR_DATATOGGLE_T  0x40       
#define                INCOMPTX_T  0x80       
#define              DMAREQMODE_T  0x400      
#define        FORCE_DATATOGGLE_T  0x800      
#define              DMAREQ_ENA_T  0x1000     
#define                     ISO_T  0x4000     
#define                 AUTOSET_T  0x8000     
#define                  ERROR_TH  0x4        
#define         STALL_RECEIVED_TH  0x20       
#define            NAK_TIMEOUT_TH  0x80       


#define                  TX_COUNT  0x1fff     /* Number of bytes to be written to the selected endpoint Tx FIFO */


#define                RXPKTRDY_R  0x1        
#define               FIFO_FULL_R  0x2        
#define                 OVERRUN_R  0x4        
#define               DATAERROR_R  0x8        
#define               FLUSHFIFO_R  0x10       
#define              STALL_SEND_R  0x20       
#define              STALL_SENT_R  0x40       
#define        CLEAR_DATATOGGLE_R  0x80       
#define                INCOMPRX_R  0x100      
#define              DMAREQMODE_R  0x800      
#define                 DISNYET_R  0x1000     
#define              DMAREQ_ENA_R  0x2000     
#define                     ISO_R  0x4000     
#define               AUTOCLEAR_R  0x8000     
#define                  ERROR_RH  0x4        
#define                 REQPKT_RH  0x20       
#define         STALL_RECEIVED_RH  0x40       
#define               INCOMPRX_RH  0x100      
#define             DMAREQMODE_RH  0x800      
#define                AUTOREQ_RH  0x4000     


#define                  RX_COUNT  0x1fff     


#define            TARGET_EP_NO_T  0xf        
#define                PROTOCOL_T  0xc        


#define          TX_POLL_INTERVAL  0xff       


#define            TARGET_EP_NO_R  0xf        
#define                PROTOCOL_R  0xc        


#define          RX_POLL_INTERVAL  0xff       


#define                  DMA0_INT  0x1        
#define                  DMA1_INT  0x2        
#define                  DMA2_INT  0x4        
#define                  DMA3_INT  0x8        
#define                  DMA4_INT  0x10       
#define                  DMA5_INT  0x20       
#define                  DMA6_INT  0x40       
#define                  DMA7_INT  0x80       


#define                   DMA_ENA  0x1        
#define                 DIRECTION  0x2        
#define                      MODE  0x4        
#define                   INT_ENA  0x8        
#define                     EPNUM  0xf0       
#define                  BUSERROR  0x100      


#define             DMA_ADDR_HIGH  0xffff     


#define              DMA_ADDR_LOW  0xffff     


#define            DMA_COUNT_HIGH  0xffff     


#define             DMA_COUNT_LOW  0xffff     




#endif 
