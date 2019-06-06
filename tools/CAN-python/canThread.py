# import atexit
# import curses
import PCANBasic  ## PCAN-Basic library import
import sys
import threading
import time
import signal
import time       ## Time-related library
import select     ## Waiting for I/O completion

import CAN


OUTPUT_FILE = 'log_rx.txt'
INPUT_FILE = 'test.txt'
logger = CAN.CanLog()

_time_t0 = None
def getTime():
    global _time_t0
    if _time_t0 == None: _time_t0 = time.perf_counter()
    return time.perf_counter() - _time_t0

def cleanup(signo=None, frame=None):
    ''' Graceful exit
    '''
    PCANBasic.PCANBasic().Uninitialize(PCANBasic.PCAN_NONEBUS)
    logger.save(OUTPUT_FILE)
    sys.exit(0)

def init_pcan(channel, baudrate):
    pcan = PCANBasic.PCANBasic()
    result = pcan.Initialize(channel,baudrate)
    if result != PCANBasic.PCAN_ERROR_OK:
        print("Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    return pcan


def monitor(pcan, channel, logger):
    result = pcan.GetValue(channel,PCAN_RECEIVE_EVENT)
    if result[0] != PCAN_ERROR_OK:
        print("Monitor Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    fd = result[1] # event queue for new CAN frame

    while 1:
        result = pcan.Read(channel)
        if result[0] == PCAN_ERROR_OK:
            msg=Message.fromTPCANMsg(result[1])
            time = getTime()
            logger.addMsg(msg, time)

            buf = ""
            buf = buf + "{:15.3f} ".format(time)
            buf = buf + "ID {:03X} len={} [ ".format(msg.ID, msg.LEN)
            for i in range(0,msg.LEN):
                buf = buf + "{:02X} ".format(msg.DATA[i])
            buf = buf + "]"
            print (buf)

        elif result[0] == PCAN_ERROR_QRCVEMPTY:
            select.select([fd],[],[]) # blocking call until frame ready


def replayLog(pcan, channel, log_file):
    log = CAN.CanLog()
    log.load(log_file)

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
            time.sleep(sleep_delta/1000)
            t_now = getTime()-t0


def main():
    channel  = PCANBasic.PCAN_USBBUS1
    baudrate = PCANBasic.PCAN_BAUD_250K
    # pcan = init_pcan(channel, baudrate)
    pcan= None
    
    log_file = INPUT_FILE

    # kill the main thread on sigint ???
    signal.signal(signal.SIGTERM, cleanup)
    signal.signal(signal.SIGINT,  cleanup)

    # receive data thread
    monitor_thread = threading.Thread(target=monitor, name='CAN-Monitor', args=(pcan, channel, logger,), daemon=True)

    # send data thread
    send_thread = threading.Thread(target=replayLog, name='CAN-replay', args=(pcan, channel, log_file,), daemon=True)

    monitor_thread.start()
    send_thread.start()

    send_thread.join() # wait for thread to finish (blocking)
    monitor_thread.join()

    cleanup()

if __name__ == '__main__':
    main()
