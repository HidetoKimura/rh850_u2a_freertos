/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "modules\sdcard\r_SDIO.h"

static volatile DRESULT res = RES_ERROR;

/*****************************************************************************
** Function:    disk_status
** Description: The disk_status function is called to inquire the current 
                drive status
** Parameter:   pdrv -> Physical drive number to identify the target device. 
						Always zero in single drive system.
** Return:      The current drive status is returned in combination of 
				status flags described below. 
				FatFs refers only STA_NOINIT and STA_PROTECT.
				
				STA_NOINIT -> Indicates that the device has not been initialized
				and not ready to work. This flag is set on system reset, media 
				removal or failure of disk_initialize function. It is cleared
				on disk_initialize function succeeded. Any media change that 
				occurs asynchronously must be captured and reflect it to the 
				status flags, or auto-mount function will not work correctly. 
				If the system does not support media change detection, 
				application program needs to explicitly re-mount the volume 
				with f_mount function after each media change.

				STA_NODISK -> Indicates that no medium in the drive.
				This is always cleared when the drive is non-removable class.
				Note that FatFs does not refer this flag.

				STA_PROTECT -> Indicates that the medium is write protected.
				This is always cleared when the drive has no write protect 
				function. Not valid if STA_NODISK is set.

******************************************************************************/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {

	case DEV_MMC :

		stat = 0;
		return stat;	
	}
	return stat;
}



/*****************************************************************************
** Function:    disk_initialize
** Description: This function initializes the storage device and put it ready 
				to generic read/write. When the function succeeded, STA_NOINIT 
				flag in the return value is cleared.
				Remarks: This function needs to be under control of FatFs module. 
				Application program MUST NOT call this function while FatFs is 
				in use, or FAT structure on the volume can be broken. 
				To re-initialize the filesystem, use f_mount function instead.
** Parameter:   pdrv -> Physical drive number to identify the target device. 
						Always zero in single drive system.
** Return:      This function returns the current drive status flags as the result. 
				For details of the drive status, refer to the disk_status function.

******************************************************************************/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	
	case DEV_MMC :
		SDIO_Init();
		stat &= ~STA_NOINIT;	/* Clear STA_NOINIT */
		return stat;	
	}
	
	return stat;
}



/*****************************************************************************
** Function:    disk_read
** Description: The disk_read function is called to read data from the storage 
				device.
** Parameter:   pdrv -> Physical drive number to identify the target device. 
				buff -> Pointer to the first item of the byte array to store 
						read data. Size of read data will be the 
						sector size * count bytes.
				sector -> Start sector number in LBA. The data type LBA_t is 
						  an alias of DWORD or QWORD depends on the 
						  configuration option.
				count -> Number of sectors to read.
						
** Return:      RES_OK (0) -> The function succeeded.
				RES_ERROR ->  An unrecoverable hard error occured during the 
							  read operation.
				RES_PARERR -> Invalid parameter.
				RES_NOTRDY -> The device has not been initialized.

******************************************************************************/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	LBA_t sector,	/* Start sector number in LBA */
	UINT count		/* Number of sectors to read (1..128)*/
)
{

	switch (pdrv) {

	case DEV_MMC :
		run_SD_read(DEV_MMC,(uint32_t *)&buff[0], sector, count);	
		return RES_OK;
	}

	return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{

	switch (pdrv) {

	case DEV_MMC :
		run_SD_write(DEV_MMC,(uint32_t *)&buff[0], sector, count);
		return RES_OK;
	}

	return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	// return RES_PARERR;
	return RES_OK; /* CS+ for CC compiler specific */
}

/*---------------------------------------------------------*/
/* User provided RTC function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called back     */
/* from FatFs module.                                      */

#if !FF_FS_NORTC && !FF_FS_READONLY
DWORD get_fattime (void)
{
	// RTCTIME rtc;

	// /* Get local time */
	// if (!rtc_gettime(&rtc)) return 0;

	// /* Pack date and time into a DWORD variable */
	// return	  ((DWORD)(rtc.year - 1980) << 25)
	// 		| ((DWORD)rtc.month << 21)
	// 		| ((DWORD)rtc.mday << 16)
	// 		| ((DWORD)rtc.hour << 11)
	// 		| ((DWORD)rtc.min << 5)
	// 		| ((DWORD)rtc.sec >> 1);

	//dummy implementation for code building.
	return 0;
}
#endif
