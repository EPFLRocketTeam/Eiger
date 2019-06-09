# SPDX-License-Identifier: Zlib
#
# This file is licensed under the terms of the zlib license.
# See the LICENSE.md file in the root of this repository
# for complete details. The contributors to this file maybe
# found in the SCM logs or in the AUTHORS.md file.
#
# Basic helper functions definitions
#
# Author: Alexandre Devienne <deviennealexandre@gmail.com>


def safe_list_get(l, idx, default):
    try:
        return l[idx]
    except IndexError:
        return default

def dict_str_to_key(d, s):
    for key in d.keys():
        if(d[key][0]==s):
            return key
    raise Exception("String '{:}' not in dict".format(s))
