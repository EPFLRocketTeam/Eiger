from comm_lib.PCANBasic import *        ## PCAN-Basic library import
import comm_lib.CAN as CAN

import string                  ## String functions
import time                    ## Time-related library
import select                  ## Waiting for I/O completion
import signal                  ## Set handlers for asynchronous events
import sys                     ## System-specific parameters and functions


t0 = None

def getTime():
    global t0

    if t0 == None:
        t0 = time.perf_counter()

    return time.perf_counter() - t0
    

def sigterm(signo, frame):
    ''' Graceful exit on ^C
    '''
    PCANBasic().Uninitialize(PCAN_NONEBUS)
    sys.exit(0)

def PCBUSB_Recv():
    pcan = PCANBasic()
    channel = PCAN_USBBUS1
    baudrate = PCAN_BAUD_250K
    result = pcan.Initialize(channel,baudrate)
    if result != PCAN_ERROR_OK:
        print("Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    result = pcan.GetValue(channel,PCAN_RECEIVE_EVENT)
    if result[0] == PCAN_ERROR_OK:
        fd = result[1]
    else:
        fd = -1

    signal.signal(signal.SIGTERM, sigterm)
    signal.signal(signal.SIGINT,  sigterm)


    while 1:
        result = pcan.Read(channel)
        if result[0] == PCAN_ERROR_OK:
            CANmsg = result[1]
            msg=CAN.Message.fromTPCANMsg(CANmsg)
            time = getTime()

            print ("{:8.3f} {}".format(time, msg))

            buf = ""
            buf = buf + "{:8.3f} ".format(time)
            buf = buf + "ID {:03X} len={} [ ".format(CANmsg.ID, CANmsg.LEN)
            for i in range(0,CANmsg.LEN):
                buf = buf + "{:02X} ".format(CANmsg.DATA[i])
            buf = buf + "]"
            # print (buf)
        elif result[0] == PCAN_ERROR_QRCVEMPTY:
            if fd != -1:
                select.select([fd],[],[]) # blocking call
            else:
                time.sleep(1)

PCBUSB_Recv()
