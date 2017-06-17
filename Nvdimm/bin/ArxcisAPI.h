/* $Header: ArxcisAPI.h: Revision: 4: Author: brian_stark: Date: Tuesday, October 01, 2013 4:34:13 PM$ */

/***********************************************************************************************************************
*                                                                                             
* Copyright 2003-2013 Viking Technology, All Rights Reserved.        
*                                                                                             
* This software is furnished under license and may be used and      
* copied only in accordance with the following terms and conditions. 
* Subject to these conditions, you may download, copy, install,  
* use, modify and distribute modified or unmodified copies of this
* software in source and/or binary form.  No title or ownership is
* transferred hereby.
*  
*  1) Any source code used, modified or distributed must reproduce 
*     and retain this copyright notice and list of conditions 
*     as they appear in the source file.
*  
*  2) No right is granted to use any trade name, trademark, or 
*     logo of Viking Technology.  The " Viking Technology " 
*     name may not be used to endorse or promote products derived 
*     from this software without the prior written permission of 
*     Viking Technology.
*  
*  3) THIS SOFTWARE IS PROVIDED "AS-IS" AND ANY EXPRESS OR
*     IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED TO, ANY IMPLIED
*     WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
*     PURPOSE, OR NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT 
*     SHALL VIKING TECHNOLOGY BE LIABLE FOR ANY DAMAGES WHATSOEVER, AND IN 
*     PARTICULAR, VIKING TECHNOLOGY SHALL NOT BE LIABLE FOR DIRECT, INDIRECT,
*     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
*     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
*     GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
*     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
*     OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
*     TORT (INCLUDING NEGLIGENCE OR OTHERWISE), EVEN IF ADVISED OF 
*     THE POSSIBILITY OF SUCH DAMAGE.
*                                                                          
********************************************************************************************************************/
/*
 * ArxcisAPI.h
 *
 * This file will provides the definitions for an Application Programming Interface to be used with Arxcis NVDIMMs
 * Version: 1.0
 * Version: 1.1 - Added new return types to support new API commands
 *              - Added Save trigger type definitions for updated ArxEnableSave prototype
 *              - Added prototypes: ArxStartSCHealthTest, ArxGetCapacitorHealth, ArxGetTemp
 * Version: 1.2 - Added a new Error code that is returned if malloc fails
 *              - Changed DRIVER_VERSION to reflect the need to use a driver that supports BLOCK register reads
 */
#define ARX_DRIVER_NOT_FOUND        1
#define ARX_GETINFO_FAILED          2
#define ARX_INVALID_DIMM_NUMBER     3
#define ARX_GETREG_FAILED           4
#define ARX_PUTREG_FAILED           5
#define ARX_INVALID_DRIVER_VERSION  6
#define ARX_NO_NVDIMMS_FOUND        7
#define ARX_CAP_NOT_READY           8
#define ARX_TIMEOUT_EXPIRED         9
#define ARX_INVALID_PARAMETER	    10
#define ARX_INVALID_REG_NUMBER      11
#define ARX_MEM_NOT_ALLOCATED       12
#define ARX_COMMAND_FAILED          13
#define ARX_NOT_SUPPORTED           14
#define ARX_GETSLOT_FAILED          15

#define ARX_SUCCESS                 0
#define ARX_HM_PASSED               0
#define ARX_EOL_WARNING             1
#define ARX_HM_EOL                  2
#define ARX_HM_INPROGRESS           4
#define ARX_HM_NOT_STARTED          5

#define ON 1
#define OFF 0

#define SPD_SIZE 0x200

#define DDR_3   3
#define DDR_4   4

/*Save Types*/
#define DISABLE_SAVE                0
#define HOST_INTERRUPT_SAVE         1
#define POWER_FAIL_SAVE             2
#define CKE_SAVE                    4
#define FORCE_SAVE_ONLY             8

/*charge states*/
#define ARX_CHARGE                  1
#define ARX_DISCHARGE               2

/*prototypes*/
int32_t ArxNVDimmsDetected(uint64_t *Address,uint64_t *Length);
/********************************************************************
/*                                                                  *
/*  ArxNVDimmsDetected                                              *
/*                                                                  *
/*  used to retrieve the number of NVDIMMs present and the physical *
/*  address and length of NV Memory.                                *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  If the function returns a value greater then or equal to 0 then *
/*  the value is equal to the number of NVDIMMs detected            *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  Address (pointer to an unsigned 64 bit integer output):         *
/*      Address will contain the physical start address of NV Memory*
/*                                                                  *
/*  Length (pointer to an unsigned 64 bit integer output):          *
/*      Length will contain the size of NV Memory detected          *
/********************************************************************/ 
int32_t ArxEnableSave(int dimm_number,int SaveType);
/********************************************************************
/*                                                                  *
/*  ArxEnableSave                                                   *
/*                                                                  *
/*  Enables and Disables save                                       *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 -On success                                                   *
/*  the value is equal to the number of NVDIMMs detected            *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*  -ARX_PUTREG_FAILED - Could not write register                   *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will be    *
/*      acted on, if non zero then the value represents a specific  *
/*      NVDIMM                                                      *
/*                                                                  *
/*  On (integer input):                                             *
/*      1 - Enable the NVDIMM(s) for Save                           *
/*      0 - Disable Save on the NVDIMM(s)                           *
/********************************************************************/ 
int32_t ArxSaveArmed(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxSaveArmed                                                    *
/*                                                                  *
/*  Used to detect if NVDIMM(s) are configured to Save              *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 - If any NVDIMM is not armed for a Save                       *
/*  1 - NVDIMM(s) are armed for a Save                              *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will have  *
/*      save enabled or disabled according to teh value of On, if   *
/*      non zero then the value represents a specific VNDIMM        *
/********************************************************************/ 
int32_t ArxClearImage(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxClearImage                                                   *
/*                                                                  *
/*  Clears the Save Data Valid bit                                  *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 -On success                                                   *
/*  the value is equal to the number of NVDIMMs detected            *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_PUTREG_FAILED - Could not write register                   *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will be    *
/*      acted on, if non zero then the value represents a specific  *
/*      NVDIMM                                                      *
/********************************************************************/ 
int32_t ArxCapReady(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArCapReady                                                      *
/*                                                                  *
/*  Used to detect if Cap is ready to support a save                *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 - Cap(s) is/are not ready to support a Save                   *
/*      Note: The value will be 0 if any cap is not ready           *
/*  1 - Cap is/are ready to support a Save                          *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will be    *
/*      acted on, if non zero then the value represents a specific  *
/*      NVDIMM                                                      *
/********************************************************************/ 
int32_t ArxCapPresent(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxCapPresent                                                   *
/*                                                                  *
/*  Used to detect Caps are present                                 *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 - If any Cap is not detected                                  *
/*  1 - All Caps are detected                                       *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will have  *
/*      save enabled or disabled according to teh value of On, if   *
/*      non zero then the value represents a specific VNDIMM        *
/********************************************************************/ 
int32_t ArxValidImageRestored(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxValidImageRestored                                           *
/*                                                                  *
/*  Used to detect if a valid image was restored on last boot.      *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 - If any NVDIMM did not restore an image                      *
/*  1 - All NVDIMMs retored and image                               *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will have  *
/*      save enabled or disabled according to teh value of On, if   *
/*      non zero then the value represents a specific VNDIMM        *
/********************************************************************/ 
int32_t ArxValidImageAvailable(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxValidImageAvailable                                          *
/*                                                                  *
/*  Used to detect if a valid image is available                    *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  0 - If any NVDIMM does not have a valid image                   *
/*  1 - All NVDIMMs have a valid image                              *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_GETINFO_FAILED - Could not get info                        *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      if dimm_number is 0 then all the NVDIMMs present will have  *
/*      save enabled or disabled according to teh value of On, if   *
/*      non zero then the value represents a specific VNDIMM        *
/********************************************************************/ 
int32_t ArxStartSCHealthTest(int dimm_number);
/********************************************************************
/*                                                                  *
/*  ArxStartSCHealthTest                                            *
/*                                                                  *
/*  Used to start health monitoring sequence                        *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  ARX_HM_INPROGRESS - If NVDIMM has entered the Super Capacitor   *
/*      Health Monitoring Sequence                                  *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*  -ARX_HM_NOT_ENTERED                                             *
/*  -ARX_CAP_NOT_READY                                              *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      This function does not support mulitple NVDIMMs the valid   *
/*      range is 1-number of NVDIMMs present.                       *
/********************************************************************/ 
int32_t ArxGetCapacitorHealth(int dimm_number,uint16_t *capacity,uint16_t *esr);
/********************************************************************
/*                                                                  *
/*  ArxGetCapacitorHealth                                           *
/*                                                                  *
/*  Returns the health statistics of the capacitor based on the     *
/*  last health monitoring sequence completed.                      *
/*  It also returns whether or not a health sequence is in progress *
/*  or if one has not been started                                  *
/*  Note: if ArxStartSCHealthTest is called in a separate thread    *
/*  it should be synchronized with this function                    *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  ARX_HM_PASSED - if Super cap is healthy                         *
/*  ARX_HM_INPROGRESS - Health monitoring is in progress            *
/*  ARX_HM_NOT_STARTED - Health monitoring has not been done.       *
/*  ARX_EOL_WARNING - if health monitoring sequence detected an EOL *
/*                    warning                                       *
/*  ARX_EOL - if health monitoring detected super capacitor is at   *
/*            End Of Life (can not guarantee capacity to support    *
/*            a save)                                               *                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      This function does not support mulitple NVDIMMs the valid   *
/*      range is 1-number of NVDIMMs present.                       *
/*                                                                  *
/*  capacity (16 bit unsigned integer):                             *
/*      This value will contain the value in CentiFarads of the     *
/*      capacity calculated in the last health monitoring sequence  *
/*      Example a value of 0x1388 = 5000 decimal = 50.00 Farads     *
*********************************************************************/ 
int32_t ArxGetTemp(int dimm_number, int8_t *temperature);
/********************************************************************
/*                                                                  *
/*  ArxGetTemp                                                      *
/*                                                                  *
/*  Used to return temperature of Super Cap                         *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  ARX_SUCCESS - A valid temperature is returned in the temperature*
/*              parameter.                                          *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      This function does not support mulitple NVDIMMs the valid   *
/*      range is 1-number of NVDIMMs present.                       *
/*                                                                  *
/*  temperature: (8 bit integer output):                            *
/*      The current temperature of the super cap is returned in     *
/*      degrees Centigrade valid range is -128 to 128 degrees       * 
/********************************************************************/ 
int32_t ArxDimmType();
/********************************************************************
/*                                                                  *
/*  ArxDimmType                                                     *
/*                                                                  *
/*  Used to return NVDIMM type discovered                           *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  none                                                            *
/*                                                                  *
/********************************************************************/ 
int32_t ArxGetRegs(int dimm_number, uint8_t offset, uint8_t length, uint8_t *buffer);
/********************************************************************
/*                                                                  *
/*  ArxGetRegs                                                      *
/*                                                                  *
/*  Returns the registers requested in buffer                       *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  ARX_SUCCESS - buffer contains the register(s) requested.        *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_INVALID_REG_NUMBER - A register outside the valid range was*
/*          Requested.                                              *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      This function does not support mulitple NVDIMMs the valid   *
/*      range is 1-number of NVDIMMs present.                       *
/*                                                                  *
/*  offset: (8 bit integer input):                                  *
/*      The offset of the first register to be read                 * 
/*  length: (8 bit integer input):                                  *
/*      The number of registers to read (in bytes)                  * 
/*  buffer: (8 bit integer pointer output):                         *
/*      A pointer to a buffer allocated by the caller that will be  *
/*      used to store the returned values                           * 
/********************************************************************/ 
int32_t ArxGetSPDRegs(int dimm_number, uint16_t offset, uint16_t length, uint8_t *buffer);
/********************************************************************
/*                                                                  *
/*  ArxGetSPDRegs                                                   *
/*                                                                  *
/*  Returns the SPD registers requested in buffer                   *
/*                                                                  *
/*  returns unsigned 32 bit integer:                                *
/*                                                                  *
/*  ARX_SUCCESS - buffer contains the register(s) requested.        *
/*  -ARX_DRIVER_NOT_FOUND - Could not connect to device             *
/*  -ARX_INVALID_DIMM_NUMBER - An invalid dimm number was passed    *
/*  -ARX_INVALID_REG_NUMBER - A register outside the valid range was*
/*          Requested.                                              *
/*  -ARX_MEM_NOT_ALLOCATED - Could not allocate memory              *
/*  -ARX_GETREG_FAILED - Could not read register                    *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  dimm_number (integer input):                                    *
/*      This function does not support mulitple NVDIMMs the valid   *
/*      range is 1-number of NVDIMMs present.                       *
/*                                                                  *
/*  offset: (16 bit integer input):                                 *
/*      The offset of the first register to be read                 * 
/*  length: (16 bit integer input):                                 *
/*      The number of registers to read (in bytes)                  * 
/*  buffer: (8 bit integer pointer output):                         *
/*      A pointer to a buffer allocated by the caller that will be  *
/*      used to store the returned values                           * 
/********************************************************************/ 
void *ArxMalloc(uint32_t Regions,uint64_t *Length);
/********************************************************************
/*                                                                  *
/*  ArxMalloc                                                       *
/*                                                                  *
/*  Used to return a virtual address mapped to the physical memory  *
/*  of the Non-Volatile Memory                                      *
/*                                                                  *
/*  returns a void pointer:                                         *
/*                                                                  *
/*  if the function succeeds a valid pointer will be returned       *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  Region (unsigned 8 bit integer input):                          *
/*         A bit map used to determine which memory regions to map  *
/*              bit 0 - Map a virtual address to the first region   *
/*                      detected				    *
/*              bit 1 - Map the second memory region to a virtual   *
/*                      address if it exists		            *
/*              bit 2-31 - Don't care, will be used for platforms   *
/*                      that support over 2 memory/CPU nodes.       *
/*  Length (pointer to 64 bit unsigned integer)                     *
/*	   Will contain the length of Memory mapped.		    *
/*      Returns a pointer to the memory region(s) to map.           * 
/********************************************************************/ 
void ArxFree(uint32_t Regions, void *va,uint64_t Length);
/********************************************************************
/*                                                                  *
/*  ArxFree                                                         *
/*                                                                  *
/*  Used to free (unmap) memory from an applications address space  *
/*                                                                  *
/*  returns none:                                                   *
/*                                                                  *
/*  Parameters:                                                     *
/*                                                                  *
/*  Regions (unsigned 32 bit integer input):                        *
/*         A bit map used to determine which memory regions to map  *
/*              bit 0 - Map a virtual address to the first region   *
/*                      detected                                    *
/*              bit 1 - Map the second memory region to a virtual   *
/*                      address if it exists                        *
/*              bit 2-31 - Don't care, will be used for platforms   *
/*                      that support over 2 memory/CPU nodes.       *
/*                                                                  *
/*                                                                  *
/*  va:                                                             *
/*      pointer to virtual address mapped into user space by call to*
/*      ArxMalloc
/*                                                                  *
/*  length (unsigned 64 bit integer input):                         *
/*      for future developement, currently the entire NV Memory     *
/*      space will be mapped.
/********************************************************************/ 
void ArxCloseDev(void);
/********************************************************************
/*                                                                  *
/*  ArxCloseDev                                                     *
/*                                                                  *
/*  Used to free (unmap) memory from an applications address space  *
/*                                                                  *
/*  returns: none                                                   *
/*                                                                  *
/*  Parameters: none                                                *
/********************************************************************/ 

