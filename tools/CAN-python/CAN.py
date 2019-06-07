from PCANBasic import *        ## PCAN-Basic library import

import struct
import ctypes
import pandas as pd

CAN_PACK_FORMAT = "!ibi"

class Message(TPCANMsg):
    def __init__(self, can_id=0):
        self.data_field = 0
        self.code_field = 0
        self.timestamp_field = 0

        self.LEN = 8
        self.ID = can_id
        self.MSGTYPE = PCAN_MESSAGE_STANDARD

    def fromTPCANMsg(msg):
        self = Message()
        self.LEN = msg.LEN
        self.ID = msg.ID
        self.MSGTYPE = msg.MSGTYPE
        self.DATA = msg.DATA

        self.unpackData(self.DATA)
        return self
        
    def setData(self, data):
        self.data_field = data
        self._update_DATA()

    def setTimestamp(self, timestamp):
        self.timestamp_field = timestamp
        self._update_DATA()

    def setCode(self, code):
        self.code_field = code
        self._update_DATA()

    def _update_DATA(self):
        packed = struct.pack(CAN_PACK_FORMAT, self.data_field,
                                              self.code_field,
                                              self.timestamp_field)
        
        buf = bytearray(8)
        buf[0:5] = packed[0:5]
        buf[5:8] = packed[6:9]

        self.DATA = (ctypes.c_ubyte * self.LEN).from_buffer_copy(buf)

    def unpackData(self, data_packed):
        buf = bytearray(9) # add a null byte in the bufffer for timestamp
        buf[0:5] = data_packed[0:5]
        buf[6:9] = data_packed[5:8]

        unpacked = struct.unpack(CAN_PACK_FORMAT, buf)
        self.data_field      = unpacked[0]
        self.code_field      = unpacked[1]
        self.timestamp_field = unpacked[2]

    def __str__(self):
        self._update_DATA()
        return "ID:{}, DATA:{}, CODE:{}, TIME:{}, HEX:{}".format(
            self.ID, self.data_field, self.code_field,
            self.timestamp_field, [hex(b) for b in self.DATA])


def msgToDict(msg, time):
    idx = CanLog.columns
    data = {idx[0]:time,
            idx[1]:msg.ID,
            idx[2]:msg.code_field,
            idx[3]:msg.data_field,
            idx[4]:msg.timestamp_field}
    return data
    
def dictToMsg(row):
    idx = CanLog.columns
    m = Message(int(row[idx[1]]))
    m.setCode(int(row[idx[2]]))
    m.setData(int(row[idx[3]]))
    m.setTimestamp(int(row[idx[4]]))
    return m

class CanLog:
    columns = ['time', 'id', 'code', 'data', 'timestamp']

    def __init__(self):
        self.df = pd.DataFrame(columns=CanLog.columns)

    def load(self, filepath):
        self.df = pd.read_csv(filepath)
        self.df = self.df.sort_values('time')

    def save(self, filepath):
        if len(self.df.index) > 0:
            print(self.df, len(self.df.index))
            self.df = self.df.sort_values('time')
            self.df.to_csv(filepath, index=False)
        else:
            print('Empty log. Nothing was saved to {}'.format(filepath))

    def addMsg(self, message, time):
        self.add(msgToDict(message, time))

    def add(self, row):
        self.df = self.df.append(row, ignore_index=True)

    def getMsgInDelta(self, time_start, time_stop):
        # return msg with t: time_start < t <= time_stop
        # if time_start == time_top, then with t==time_start
        if time_start == time_stop:
            sub_df = self.df.query('time == @time_start')
        else:
            sub_df = self.df.query('@time_start < time <= @time_stop')

        msg_list = []
        for index, row in sub_df.iterrows():
            msg_list = msg_list + [dictToMsg(row)]

        return msg_list

    def nextMsgTAfterT(self, time):
        # return msg T with t > time
        # None if no new message
        sub_df = self.df.query('time > @time')
        if sub_df.size == 0:
            return None
        else:
            return sub_df.iloc[0]['time']

    def __str__(self):
        return self.df.__str__()



def _testMessage():
    def check(m):
        print(m)
        m.unpackData(m.DATA)
        print(m)
    m = Message(5)

    check(m)
    m.setData(0x0FFFFFFF)
    check(m)
    m.setTimestamp(0x11FF11)
    check(m)
    m.setCode(0x33)
    check(m)

def _testCanLog():
    log = CanLog()

    log.load('test.txt')

    print(log)

    m = Message(5)
    m.setData(255)
    m.setTimestamp(3)
    m.setCode(12)

    log.addMsg(m, 300)
    print(log)
    log.save('test2.txt')

    print('next t after 100 is:', log.nextMsgTAfterT(100))
    print('next t after 5000 is:', log.nextMsgTAfterT(5000))
    print('msg between 500 and 1000 are:')
    m_list = log.getMsgInDelta(500,1000)
    for m in m_list: print(m)
    print('msg between 1000 and 2000 are:')
    m_list = log.getMsgInDelta(1000,2000)
    for m in m_list: print(m)

if __name__ == "__main__":
    print('================ Test Message =================')
    _testMessage()
    print('================ Test CAN log =================')
    _testCanLog()
