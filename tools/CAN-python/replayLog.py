''' Replay CAN communication from a txt file onto a bus
File to replay hardcoded in script: test.txt
CAN replay format (csv file)
time, id, code, data, timestamp

time: time in s at which the packet should be sent (t=0 is programm startup)
id: CAN_ID with which the message should be sent. Payload of message composed from the code, data, and timestamp field
code: field in payload of CAN message 8 bit
data: field in payload of CAN message 32 bit
timestamp: field in payload of CAN message 24bit

Author: Alexandre Devienne, June 2019
'''

from comm_lib.PCANBasic import *        ## PCAN-Basic library import

import string                  ## String functions
import time                    ## Time-related library
import select                  ## Waiting for I/O completion
import signal                  ## Set handlers for asynchronous events
import sys                     ## System-specific parameters and functions

import comm_lib.CAN as utils

def getTime():
    return time.perf_counter()

def sigterm(signo, frame):
    ''' Graceful exit on ^C
    '''
    PCANBasic().Uninitialize(PCAN_NONEBUS)
    sys.exit(0)

def PCBUSB_Send(log_file):
    log = utils.CanLog()
    log.load(log_file)

    pcan = PCANBasic()
    channel = PCAN_USBBUS1
    baudrate = PCAN_BAUD_250K
    result = pcan.Initialize(channel,baudrate)
    if result != PCAN_ERROR_OK:
        print("Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    signal.signal(signal.SIGTERM, sigterm)
    signal.signal(signal.SIGINT,  sigterm)

    t0 = getTime()
    t_now = 0
    t_previous = t_now

    finished = False

    while not finished:
        msgs = log.getMsgInDelta(t_previous, t_now)
        for m in msgs: 
            rst = pcan.Write(channel, m)
            print(t_now, m)
            if rst != PCAN_ERROR_OK: print("Transmit Error!", pcan.GetErrorText(rst))

        next_t = log.nextMsgTAfterT(t_now)

        if next_t == None:
            finished = True
        else:
            t_previous = t_now
            sleep_delta = next_t-t_now
            time.sleep(sleep_delta)
            t_now = getTime()-t0

PCBUSB_Send('test.txt')
