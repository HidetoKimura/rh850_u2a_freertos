#ifndef __SHARED_H__
#define __SHARED_H__

typedef volatile enum {
    PE_UNDEF    = 0x000,
    PE0_STOP    = 0x002,
    PE0_RDY     = 0x004,
    PE0_RUN     = 0x008,
    PE1_STOP    = 0x012,
    PE1_RDY     = 0x014,
    PE1_RUN     = 0x018,
    PE2_STOP    = 0x022,
    PE2_RDY     = 0x024,
    PE2_RUN     = 0x028,
    PE3_STOP    = 0x042,
    PE3_RDY     = 0x044,
    PE3_RUN     = 0x048,
    PE4_STOP    = 0x082,
    PE4_RDY     = 0x084,
    PE4_RUN     = 0x088,
    PE5_STOP    = 0x102,
    PE5_RDY     = 0x104,
    PE5_RUN     = 0x108,
    PE6_STOP    = 0x112,
    PE6_RDY     = 0x114,
    PE6_RUN     = 0x118,
    PE_FAIL     = -1
} T_STATE;

typedef struct {
    unsigned char lock:1,
                  owner:7;
} T_LOCK;

extern __FARFUNC void initSharedMemory( unsigned int);
extern __FARFUNC void init( int);
extern __FARFUNC void initV( int*, int);
extern __FARFUNC void swreset( void);
extern __FARFUNC int swreset0( int);
extern __FARFUNC void DelayMS( unsigned long );

__FAR( extern volatile unsigned int, ThreadLocked)  // for mutual exclusion
__FAR( extern volatile unsigned int, PE_Started)    // for mutual exclusion
__SHARED( extern T_STATE, statePE0)
__SHARED( extern T_STATE, statePE1)
__SHARED( extern T_STATE, statePE2)
__SHARED( extern T_STATE, statePE3)
__SHARED( extern T_STATE, statePE4)
__SHARED( extern T_STATE, statePE5)
__SHARED( extern T_STATE, statePE6)

T_STATE GetState( int );

__FARFUNC void ThdSyncReq( unsigned long *);
__FARFUNC void ThdSyncRel( unsigned long *);

__FARFUNC int R_lock( int , T_LOCK *, unsigned int max_tries);
__FARFUNC int R_unlock( int, T_LOCK *);
__FARFUNC int R_lock_linked( int , T_LOCK *, unsigned int max_tries);
__FARFUNC int R_unlock_linked( int, T_LOCK *);

#pragma ghs startdata
#pragma ghs section bss=".slsync"
extern T_LOCK __re_lock0;
extern T_LOCK __re_lock1;
extern T_LOCK __re_lock2;
extern T_LOCK __re_lock3;
#pragma ghs section bss=default
#pragma ghs enddata

#endif  /* __SHARED_H__ */
