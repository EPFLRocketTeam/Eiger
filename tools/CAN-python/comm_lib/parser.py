# SPDX-License-Identifier: Zlib
#
# This file is licensed under the terms of the zlib license.
# See the LICENSE.md file in the root of this repository
# for complete details. The contributors to this file maybe
# found in the SCM logs or in the AUTHORS.md file.
#
# Parser of the protocol config file
#
# Author: Alexandre Devienne <deviennealexandre@gmail.com>

import sys
import os

# =================================
# Parsing config file
# =================================
# Create a dictionary of message headers
# startOfValues is the comment before start of values for dict
# prefix_takeout is what needs to be taken out from the beginning of the values in dict
def parse_config_file(filepath, start_of_values, prefix_takeout=""):
    dict = {}
    settings_file = None
    try:
        settings_file = open(filepath)
    except:
        print('Error! Unable to find configuration file "{:}"'.format(filepath))
        sys.exit(1)

    headers_found = False # when the correct headers found
    end_headers = False # when to stop looking for headers

    # go through each line to find the message headers
    for line_num, line in enumerate(settings_file):
        # remove prefix
        if(line[0:len(prefix_takeout)] == prefix_takeout):
            line = line[len(prefix_takeout):]
        # key is in the part after , and value is before
        if(headers_found):
            definition = line.strip().split(", ")
            definition = [s.strip() for s in definition]

            # if there are not enough values then line is assumed to be end of section
            if(len(definition)<2):
                end_headers = True
                break
            # sets the key to equal the message header, value as the header name and unit
            key_str = definition[1].split("+")
            key = sum([int(s, 0) for s in key_str])
            dict[key] = definition[:1] + definition[2:]
        elif(line[0:len(start_of_values)+3]=="// " + start_of_values):
            # the string that is found is what symbolizes when message headers begin on
            # next line
            headers_found = True
        # when the headers end do not care about anything else so breaks
        if(end_headers):
            break
    return dict


# =================================
# Global variable
# =================================
CONFIG_FILE   = "protocol.txt"
CONFIG_LOGGING    = ["Data ID", "DATA_ID_"]
CONFIG_BOARD = ["Board CAN ID", "CAN_ID_"]

config_file_path = os.path.join(os.path.dirname(__file__), CONFIG_FILE)

board_dict  = parse_config_file(config_file_path, CONFIG_BOARD[0],        CONFIG_BOARD[1])
log_dict    = parse_config_file(config_file_path, CONFIG_LOGGING[0],    CONFIG_LOGGING[1])

