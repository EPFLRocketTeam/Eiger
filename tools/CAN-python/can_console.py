''' Console to monitor CAN messages
Logs all incomming CAN message to a log file log_rx.txt (overwritten at each run)
Display human readable names for CAN messages IDs (see comm_lib/protocol.txt)

Usage:
- Basic: python can_console.py
- To replay a CAN log contained in my_log_file: python can_console.py my_log_file

Author: Alexandre Devienne, June 2019
'''

import comm_lib.PCANBasic as PCANBasic ## PCAN-Basic library import
import sys
import threading
import time
import signal
import time       ## Time-related library
import select     ## Waiting for I/O completion
import curses

import comm_lib.CAN as CAN
from comm_lib.parser import log_dict, board_dict
from comm_lib.helper import safe_list_get, dict_str_to_key


OUTPUT_FILE = 'log_rx.txt'
DEFAULT_INPUT_FILE = None
state = {}

_time_t0 = None
def getTime():
    global _time_t0
    if _time_t0 == None: _time_t0 = time.perf_counter()
    return time.perf_counter() - _time_t0

def cleanup(signo=None, frame=None):
    ''' Graceful exit
    '''
    curses.echo()
    curses.endwin()
    PCANBasic.PCANBasic().Uninitialize(PCANBasic.PCAN_NONEBUS)
    state['logger'].save(OUTPUT_FILE)

    sys.exit(0)

def init_pcan(channel, baudrate):
    pcan = PCANBasic.PCANBasic()
    result = pcan.Initialize(channel,baudrate)
    if result != PCANBasic.PCAN_ERROR_OK:
        print("Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    return pcan

def add_msg(cache, msg, special=False):
    cache.update([(msg.code_field,
        {'can_id':msg.ID, 'data':msg.data_field, 'self_time':msg.timestamp_field, 'update_time':getTime(),
        'special':special})])


def monitor(state):
    pcan = state['pcan']
    channel = state['pcan_channel']
    logger = state['logger']
    
    message_cache = state['message_cache']

    result = pcan.GetValue(channel,PCANBasic.PCAN_RECEIVE_EVENT)
    if result[0] != PCANBasic.PCAN_ERROR_OK:
        print("Monitor Init Error!", pcan.GetErrorText(result))
        sys.exit(1)

    fd = result[1] # event queue for new CAN frame

    while 1:
        result = pcan.Read(channel)
        if result[0] == PCANBasic.PCAN_ERROR_OK:
            msg=CAN.Message.fromTPCANMsg(result[1])
            time = getTime()
            # logger.addMsg(msg, time)

            # print (msg)
            add_msg(message_cache, msg)

        elif result[0] == PCANBasic.PCAN_ERROR_QRCVEMPTY:
            select.select([fd],[],[]) # blocking call until frame ready


def replayLog(state):
    pcan = state['pcan']
    channel = state['pcan_channel']
    log_file = state['log_file']
    message_cache = state['message_cache']

    if log_file == None: return

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
            add_msg(message_cache, m, special=True)
            # print(t_now, m)
            if rst != PCANBasic.PCAN_ERROR_OK: print("Transmit Error!", pcan.GetErrorText(rst))

        next_t = log.nextMsgTAfterT(t_now)

        if next_t == None:
            finished = True
        else:
            t_previous = t_now
            sleep_delta = next_t-t_now
            time.sleep(sleep_delta)
            t_now = getTime()-t0

# Thread to redraw the UI every so often
def console_drawer(state):
    while(True):
        time.sleep(0.2)
        redraw(state)

# Display the ncurse UI with the latest info received
def redraw(state):
    screen = state["screen"]
    message_cache = state["message_cache"]
    
    screen.clear()
    screen.border(0)

    (max_y, max_x) = screen.getmaxyx()

    row_id = 1

    # write data
    screen.addstr(row_id, 2, '{:^20} {:^12} {:^20}'.format("", "", ""), curses.A_UNDERLINE)
    screen.addstr(row_id+1, 2, '{:^20}|{:^15}|{:^11} [{:^6}] |{:^15}|{:^15}'.format("Message", 'Board ID', 'Data', 'unit', 'Self Time [s]', 'Time [s]'), curses.A_UNDERLINE)
    row_id = row_id+2
    for mid in message_cache.keys():
        mid_str   = log_dict.get(mid, ["MID {}".format(mid)])
        can_id =  message_cache[mid]["can_id"]
        board_str = board_dict.get(can_id, ["BOARD {}".format(mid)])

        if mid_str[0] == "MSG":
            compilation_str = "{:} [ {:.2f} ]".format(message_cache[mid]["data"],        # data
                                                      message_cache[mid]["update_time"]) # time
        else:
            s = "{:20}|{:^15}|{:>11} [{:^6}] |{:15.3f}|{:15.3f}".format(safe_list_get(mid_str, 0, ""), # id name
                                                    safe_list_get(board_str, 0, ""), # can id
                                                    message_cache[mid]["data"],        # data
                                                    safe_list_get(mid_str, 1, ""),     # id unit
                                                    message_cache[mid]["self_time"]/1000, # self time, from ms to s
                                                    message_cache[mid]["update_time"]) # time
            if message_cache[mid]['special']:
                s = s + " !Sent! "
            screen.addstr(row_id, 2, s)
            row_id = row_id + 1
    
    screen.refresh()

    return None

def main():
    global state
    channel  = PCANBasic.PCAN_USBBUS1
    baudrate = PCANBasic.PCAN_BAUD_250K
    pcan = init_pcan(channel, baudrate)
    
    log_file = DEFAULT_INPUT_FILE
    
    if len(sys.argv)>=2:
        log_file = sys.argv[1]

    # setup global variable and window
    state = {
        "message_cache": {},
        "pcan": pcan,
        "pcan_channel": channel,
        "screen": curses.initscr(),
        "log_file":log_file,
        "logger": CAN.CanLog(),
    }
    curses.noecho() # turn off echo of type in character
    screen = state["screen"].keypad(True)

    # kill the main thread on sigint
    signal.signal(signal.SIGTERM, cleanup)
    signal.signal(signal.SIGINT,  cleanup)

    # receive data thread
    monitor_thread = threading.Thread(target=monitor, name='CAN-Monitor', args=(state,), daemon=True)
    # send data thread
    send_thread = threading.Thread(target=replayLog, name='CAN-replay', args=(state,), daemon=True)
    # redraw thread
    drawer = threading.Thread(target=console_drawer, name='Drawer', args=(state,), daemon=True)


    monitor_thread.start()
    send_thread.start()
    drawer.start()

    monitor_thread.join() # wait for thread to finish (blocking)
    send_thread.join()
    drawer.join()

    cleanup()

if __name__ == '__main__':
    main()
