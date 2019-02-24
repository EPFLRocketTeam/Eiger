from PCANBasic import *
import time
import struct

if __name__ == '__main__':
    # ------------------------------- READING TEXT FILE --------------------------------------
    # This should ideally happen in another script but the execution time is so small that it does not really matter.
    # The data is stored in a dictionary called data
    with open('SENSORS.TXT') as f:
        arr = f.read().split('\n')

    # Seq num, timestamp, pressure, temperature, altitude, acc (mg) xyz, gyro(rps) xyz, mag(uT) xyz
    names = ['seq_num', 'timestamp', 'pressure', 'temperature', 'altitude', 'acc_x', 'acc_y', 'acc_z', 'gyro_x',
             'gyro_y', 'gyro_z', 'mag_x', 'mag_y', 'mag_z']

    data = {}
    for name in names:
        data[name] = []

    for line in arr:
        elem = line.split(',')
        if len(elem) == 14:
            for i, val in enumerate(elem):
                if i == 1 or i == 0:
                    data[names[i]].append(int(val.strip()))
                else:
                    data[names[i]].append(float(val.strip()))

    ID_BOARD = 0x03
    data_send = ['altitude', 'acc_x', 'acc_y', 'acc_z', 'gyro_x', 'gyro_y', 'gyro_z']

    print("............STARTED.............")
    msg = TPCANMsg()
    payload = 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  # random values
    msg._fields_ = [("ID", ID_BOARD), ("MSGTYPE", PCAN_MESSAGE_STANDARD), ("LEN",    8), ("DATA", payload)]

# ______________________________________________________________________________________________
# ----------------Initialize---------------------------
# ______________________________________________________________________________________________

    can = PCANBasic()
    result = can.Initialize(PCAN_USBBUS1, PCAN_BAUD_250K)
    print(result)
    if result == PCAN_ERROR_OK:
        print("Initialization OK")
        print("Getstatus:-", can.GetStatus(PCAN_USBBUS1))

# _________________________________________________________________________________________________
# ------------- Writing ----------------------
# _________________________________________________________________________________________________
        can.FilterMessages(PCAN_USBBUS1, 0x00, 0xFF, PCAN_MESSAGE_STANDARD)  # filter nothing
        status = PCAN_ERROR_QRCVEMPTY  # receive queue is empty
        print("beforeloop:-", status)

        # loop over the sequence numbers
        for i in range(len(data[names[0]])):
            begin_time = time.time()
            # loop over the different values for 1 sequence number
            for index, value in enumerate(data_send):
                third = divmod(data['timestamp'][i], 256)[1]
                second = divmod(data['timestamp'][i], 256 * 256)[1]
                first = divmod(data['timestamp'][i], 256 * 256 * 256)[1]

                # 32 bit value that is being sent in 4 bytes
                packed = struct.pack('!f', data[value][i])
                byte_1 = int(packed[0])
                byte_2 = int(packed[1])
                byte_3 = int(packed[2])
                byte_4 = int(packed[3])

                data_type = index  # see excel file

                msg.setData([byte_1, byte_2, byte_3, byte_4, data_type, first, second, third])

                wrtstat = can.Write(PCAN_USBBUS1, msg)
                if wrtstat != PCAN_ERROR_OK:
                    print("Error Occured during writing")  # ------------------------------------ADD MORE HANDLING

            end_time = time.time()
            diff = end_time - begin_time
            if diff < 0.02:  # +-50 Hz
                time.sleep(0.02 - diff)
            else:
                print(1.0/diff)
# _________________________________________________________________________________________________

    else:
        print("Init error!")

    can.Uninitialize(PCAN_USBBUS1)
