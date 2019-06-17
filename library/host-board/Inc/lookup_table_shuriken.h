#ifndef SHURIKEN_LOOKUP_TABLE 
#define SHURIKEN_LOOKUP_TABLE 

#define TABLE_LENGTH 500
#define TABLE_WIDTH 3 
#define TABLE_DIFF_SPEEDS_SAME_ALTITUDE 5
static const float32_t SimData[TABLE_LENGTH][TABLE_WIDTH] = {
{ 802.3683, 236.4013, 0 },
{ 802.3683, 240.2356, 53.5 },
{ 802.3683, 245.8027, 107 },
{ 802.3683, 252.2737, 160.5 },
{ 802.3683, 259.1565, 214 },
{ 825.0515, 234.8838, 0 },
{ 825.0515, 238.6746, 53.5 },
{ 825.0515, 244.1057, 107 },
{ 825.0515, 250.4485, 160.5 },
{ 825.0515, 257.2027, 214 },
{ 847.7346, 233.3651, 0 },
{ 847.7346, 237.1081, 53.5 },
{ 847.7346, 242.4092, 107 },
{ 847.7346, 248.6257, 160.5 },
{ 847.7346, 255.2733, 214 },
{ 870.4178, 231.8451, 0 },
{ 870.4178, 235.5355, 53.5 },
{ 870.4178, 240.7131, 107 },
{ 870.4178, 246.81, 160.5 },
{ 870.4178, 253.344, 214 },
{ 893.1009, 230.3229, 0 },
{ 893.1009, 233.9563, 53.5 },
{ 893.1009, 239.0172, 107 },
{ 893.1009, 244.9986, 160.5 },
{ 893.1009, 251.4146, 214 },
{ 915.7841, 228.7993, 0 },
{ 915.7841, 232.3666, 53.5 },
{ 915.7841, 237.3114, 107 },
{ 915.7841, 243.1872, 160.5 },
{ 915.7841, 249.4853, 214 },
{ 938.4672, 227.274, 0 },
{ 938.4672, 230.7542, 53.5 },
{ 938.4672, 235.6056, 107 },
{ 938.4672, 241.3758, 160.5 },
{ 938.4672, 247.5559, 214 },
{ 961.1504, 225.7191, 0 },
{ 961.1504, 229.134, 53.5 },
{ 961.1504, 233.8997, 107 },
{ 961.1504, 239.5643, 160.5 },
{ 961.1504, 245.6266, 214 },
{ 983.8335, 224.1584, 0 },
{ 983.8335, 227.5138, 53.5 },
{ 983.8335, 232.1939, 107 },
{ 983.8335, 237.7529, 160.5 },
{ 983.8335, 243.6972, 214 },
{ 1006.5167, 222.5977, 0 },
{ 1006.5167, 225.8936, 53.5 },
{ 1006.5167, 230.4881, 107 },
{ 1006.5167, 235.9415, 160.5 },
{ 1006.5167, 241.7679, 214 },
{ 1029.1998, 221.0371, 0 },
{ 1029.1998, 224.2734, 53.5 },
{ 1029.1998, 228.7822, 107 },
{ 1029.1998, 234.1301, 160.5 },
{ 1029.1998, 239.8385, 214 },
{ 1051.883, 219.4764, 0 },
{ 1051.883, 222.6532, 53.5 },
{ 1051.883, 227.0764, 107 },
{ 1051.883, 232.3187, 160.5 },
{ 1051.883, 237.9091, 214 },
{ 1074.5661, 217.9157, 0 },
{ 1074.5661, 221.033, 53.5 },
{ 1074.5661, 225.3706, 107 },
{ 1074.5661, 230.5073, 160.5 },
{ 1074.5661, 235.9798, 214 },
{ 1097.2493, 216.3551, 0 },
{ 1097.2493, 219.4128, 53.5 },
{ 1097.2493, 223.6647, 107 },
{ 1097.2493, 228.6959, 160.5 },
{ 1097.2493, 234.0504, 214 },
{ 1119.9324, 214.7944, 0 },
{ 1119.9324, 217.7926, 53.5 },
{ 1119.9324, 221.9589, 107 },
{ 1119.9324, 226.8845, 160.5 },
{ 1119.9324, 232.1211, 214 },
{ 1142.6156, 213.2337, 0 },
{ 1142.6156, 216.1724, 53.5 },
{ 1142.6156, 220.2531, 107 },
{ 1142.6156, 225.0731, 160.5 },
{ 1142.6156, 230.1917, 214 },
{ 1165.2987, 211.6731, 0 },
{ 1165.2987, 214.5522, 53.5 },
{ 1165.2987, 218.5472, 107 },
{ 1165.2987, 223.2616, 160.5 },
{ 1165.2987, 228.2624, 214 },
{ 1187.9818, 210.1124, 0 },
{ 1187.9818, 212.9319, 53.5 },
{ 1187.9818, 216.8414, 107 },
{ 1187.9818, 221.4502, 160.5 },
{ 1187.9818, 226.333, 214 },
{ 1210.665, 208.5517, 0 },
{ 1210.665, 211.3117, 53.5 },
{ 1210.665, 215.1356, 107 },
{ 1210.665, 219.6388, 160.5 },
{ 1210.665, 224.4037, 214 },
{ 1233.3481, 206.9911, 0 },
{ 1233.3481, 209.6915, 53.5 },
{ 1233.3481, 213.4297, 107 },
{ 1233.3481, 217.8274, 160.5 },
{ 1233.3481, 222.4743, 214 },
{ 1256.0313, 205.4304, 0 },
{ 1256.0313, 208.0713, 53.5 },
{ 1256.0313, 211.7239, 107 },
{ 1256.0313, 216.016, 160.5 },
{ 1256.0313, 220.545, 214 },
{ 1278.7144, 203.8697, 0 },
{ 1278.7144, 206.4511, 53.5 },
{ 1278.7144, 210.0181, 107 },
{ 1278.7144, 214.2046, 160.5 },
{ 1278.7144, 218.6156, 214 },
{ 1301.3976, 202.3091, 0 },
{ 1301.3976, 204.8309, 53.5 },
{ 1301.3976, 208.3122, 107 },
{ 1301.3976, 212.3932, 160.5 },
{ 1301.3976, 216.6863, 214 },
{ 1324.0807, 200.7484, 0 },
{ 1324.0807, 203.2107, 53.5 },
{ 1324.0807, 206.6064, 107 },
{ 1324.0807, 210.5818, 160.5 },
{ 1324.0807, 214.7569, 214 },
{ 1346.7639, 199.1877, 0 },
{ 1346.7639, 201.5905, 53.5 },
{ 1346.7639, 204.9006, 107 },
{ 1346.7639, 208.7703, 160.5 },
{ 1346.7639, 212.8276, 214 },
{ 1369.447, 197.6271, 0 },
{ 1369.447, 199.9703, 53.5 },
{ 1369.447, 203.1947, 107 },
{ 1369.447, 206.9589, 160.5 },
{ 1369.447, 210.8982, 214 },
{ 1392.1302, 196.0664, 0 },
{ 1392.1302, 198.3501, 53.5 },
{ 1392.1302, 201.4889, 107 },
{ 1392.1302, 205.1475, 160.5 },
{ 1392.1302, 208.9689, 214 },
{ 1414.8133, 194.5057, 0 },
{ 1414.8133, 196.7299, 53.5 },
{ 1414.8133, 199.7831, 107 },
{ 1414.8133, 203.3361, 160.5 },
{ 1414.8133, 207.0387, 214 },
{ 1437.4965, 192.9451, 0 },
{ 1437.4965, 195.1097, 53.5 },
{ 1437.4965, 198.0772, 107 },
{ 1437.4965, 201.4933, 160.5 },
{ 1437.4965, 205.1082, 214 },
{ 1460.1796, 191.3844, 0 },
{ 1460.1796, 193.459, 53.5 },
{ 1460.1796, 196.3001, 107 },
{ 1460.1796, 199.642, 160.5 },
{ 1460.1796, 203.1777, 214 },
{ 1482.8628, 189.7303, 0 },
{ 1482.8628, 191.7423, 53.5 },
{ 1482.8628, 194.5221, 107 },
{ 1482.8628, 197.7907, 160.5 },
{ 1482.8628, 201.2471, 214 },
{ 1505.5459, 188.0572, 0 },
{ 1505.5459, 190.0256, 53.5 },
{ 1505.5459, 192.7442, 107 },
{ 1505.5459, 195.9393, 160.5 },
{ 1505.5459, 199.3166, 214 },
{ 1528.2291, 186.3842, 0 },
{ 1528.2291, 188.309, 53.5 },
{ 1528.2291, 190.9663, 107 },
{ 1528.2291, 194.088, 160.5 },
{ 1528.2291, 197.386, 214 },
{ 1550.9122, 184.7111, 0 },
{ 1550.9122, 186.5923, 53.5 },
{ 1550.9122, 189.1883, 107 },
{ 1550.9122, 192.2367, 160.5 },
{ 1550.9122, 195.4555, 214 },
{ 1573.5954, 183.0381, 0 },
{ 1573.5954, 184.8757, 53.5 },
{ 1573.5954, 187.4104, 107 },
{ 1573.5954, 190.3853, 160.5 },
{ 1573.5954, 193.525, 214 },
{ 1596.2785, 181.365, 0 },
{ 1596.2785, 183.159, 53.5 },
{ 1596.2785, 185.6324, 107 },
{ 1596.2785, 188.534, 160.5 },
{ 1596.2785, 191.5944, 214 },
{ 1618.9617, 179.692, 0 },
{ 1618.9617, 181.4424, 53.5 },
{ 1618.9617, 183.8545, 107 },
{ 1618.9617, 186.6827, 160.5 },
{ 1618.9617, 189.6639, 214 },
{ 1641.6448, 178.0189, 0 },
{ 1641.6448, 179.7257, 53.5 },
{ 1641.6448, 182.0765, 107 },
{ 1641.6448, 184.8313, 160.5 },
{ 1641.6448, 187.7333, 214 },
{ 1664.328, 176.3458, 0 },
{ 1664.328, 178.009, 53.5 },
{ 1664.328, 180.2986, 107 },
{ 1664.328, 182.98, 160.5 },
{ 1664.328, 185.8028, 214 },
{ 1687.0111, 174.6728, 0 },
{ 1687.0111, 176.2924, 53.5 },
{ 1687.0111, 178.5207, 107 },
{ 1687.0111, 181.1287, 160.5 },
{ 1687.0111, 183.8723, 214 },
{ 1709.6943, 172.9997, 0 },
{ 1709.6943, 174.5757, 53.5 },
{ 1709.6943, 176.7427, 107 },
{ 1709.6943, 179.2773, 160.5 },
{ 1709.6943, 181.9417, 214 },
{ 1732.3774, 171.3267, 0 },
{ 1732.3774, 172.8591, 53.5 },
{ 1732.3774, 174.9648, 107 },
{ 1732.3774, 177.426, 160.5 },
{ 1732.3774, 180.0112, 214 },
{ 1755.0606, 169.6536, 0 },
{ 1755.0606, 171.1424, 53.5 },
{ 1755.0606, 173.1868, 107 },
{ 1755.0606, 175.5747, 160.5 },
{ 1755.0606, 178.0806, 214 },
{ 1777.7437, 167.9806, 0 },
{ 1777.7437, 169.4258, 53.5 },
{ 1777.7437, 171.4089, 107 },
{ 1777.7437, 173.7233, 160.5 },
{ 1777.7437, 176.1501, 214 },
{ 1800.4268, 166.3075, 0 },
{ 1800.4268, 167.7091, 53.5 },
{ 1800.4268, 169.6309, 107 },
{ 1800.4268, 171.872, 160.5 },
{ 1800.4268, 174.2195, 214 },
{ 1823.11, 164.6345, 0 },
{ 1823.11, 165.9924, 53.5 },
{ 1823.11, 167.853, 107 },
{ 1823.11, 170.0207, 160.5 },
{ 1823.11, 172.289, 214 },
{ 1845.7931, 162.9614, 0 },
{ 1845.7931, 164.2758, 53.5 },
{ 1845.7931, 166.075, 107 },
{ 1845.7931, 168.1693, 160.5 },
{ 1845.7931, 170.3585, 214 },
{ 1868.4763, 161.2884, 0 },
{ 1868.4763, 162.5591, 53.5 },
{ 1868.4763, 164.2971, 107 },
{ 1868.4763, 166.318, 160.5 },
{ 1868.4763, 168.4279, 214 },
{ 1891.1594, 159.6153, 0 },
{ 1891.1594, 160.8425, 53.5 },
{ 1891.1594, 162.4937, 107 },
{ 1891.1594, 164.3865, 160.5 },
{ 1891.1594, 166.3784, 214 },
{ 1913.8426, 157.8299, 0 },
{ 1913.8426, 158.9751, 53.5 },
{ 1913.8426, 160.5478, 107 },
{ 1913.8426, 162.3878, 160.5 },
{ 1913.8426, 164.3237, 214 },
{ 1936.5257, 155.9611, 0 },
{ 1936.5257, 157.074, 53.5 },
{ 1936.5257, 158.602, 107 },
{ 1936.5257, 160.3891, 160.5 },
{ 1936.5257, 162.269, 214 },
{ 1959.2089, 154.0923, 0 },
{ 1959.2089, 155.1729, 53.5 },
{ 1959.2089, 156.6561, 107 },
{ 1959.2089, 158.3904, 160.5 },
{ 1959.2089, 160.2143, 214 },
{ 1981.892, 152.2235, 0 },
{ 1981.892, 153.2718, 53.5 },
{ 1981.892, 154.7102, 107 },
{ 1981.892, 156.3917, 160.5 },
{ 1981.892, 158.1596, 214 },
{ 2004.5752, 150.3547, 0 },
{ 2004.5752, 151.3707, 53.5 },
{ 2004.5752, 152.7643, 107 },
{ 2004.5752, 154.393, 160.5 },
{ 2004.5752, 156.105, 214 },
{ 2027.2583, 148.4859, 0 },
{ 2027.2583, 149.4696, 53.5 },
{ 2027.2583, 150.8184, 107 },
{ 2027.2583, 152.3943, 160.5 },
{ 2027.2583, 154.0503, 214 },
{ 2049.9415, 146.6171, 0 },
{ 2049.9415, 147.5684, 53.5 },
{ 2049.9415, 148.8725, 107 },
{ 2049.9415, 150.3956, 160.5 },
{ 2049.9415, 151.9956, 214 },
{ 2072.6246, 144.7483, 0 },
{ 2072.6246, 145.6673, 53.5 },
{ 2072.6246, 146.9266, 107 },
{ 2072.6246, 148.3968, 160.5 },
{ 2072.6246, 149.9409, 214 },
{ 2095.3078, 142.8795, 0 },
{ 2095.3078, 143.7662, 53.5 },
{ 2095.3078, 144.9807, 107 },
{ 2095.3078, 146.3981, 160.5 },
{ 2095.3078, 147.8862, 214 },
{ 2117.9909, 141.0107, 0 },
{ 2117.9909, 141.8651, 53.5 },
{ 2117.9909, 143.0349, 107 },
{ 2117.9909, 144.3994, 160.5 },
{ 2117.9909, 145.8315, 214 },
{ 2140.6741, 139.1418, 0 },
{ 2140.6741, 139.964, 53.5 },
{ 2140.6741, 141.089, 107 },
{ 2140.6741, 142.4007, 160.5 },
{ 2140.6741, 143.7769, 214 },
{ 2163.3572, 137.273, 0 },
{ 2163.3572, 138.0629, 53.5 },
{ 2163.3572, 139.1431, 107 },
{ 2163.3572, 140.402, 160.5 },
{ 2163.3572, 141.7222, 214 },
{ 2186.0404, 135.4042, 0 },
{ 2186.0404, 136.1618, 53.5 },
{ 2186.0404, 137.1972, 107 },
{ 2186.0404, 138.4033, 160.5 },
{ 2186.0404, 139.6675, 214 },
{ 2208.7235, 133.5354, 0 },
{ 2208.7235, 134.2606, 53.5 },
{ 2208.7235, 135.2513, 107 },
{ 2208.7235, 136.4046, 160.5 },
{ 2208.7235, 137.6128, 214 },
{ 2231.4067, 131.6666, 0 },
{ 2231.4067, 132.3595, 53.5 },
{ 2231.4067, 133.3054, 107 },
{ 2231.4067, 134.4059, 160.5 },
{ 2231.4067, 135.5581, 214 },
{ 2254.0898, 129.7978, 0 },
{ 2254.0898, 130.4584, 53.5 },
{ 2254.0898, 131.3595, 107 },
{ 2254.0898, 132.3626, 160.5 },
{ 2254.0898, 133.4103, 214 },
{ 2276.773, 127.7002, 0 },
{ 2276.773, 128.3, 53.5 },
{ 2276.773, 129.1204, 107 },
{ 2276.773, 130.0778, 160.5 },
{ 2276.773, 131.0836, 214 },
{ 2299.4561, 125.5121, 0 },
{ 2299.4561, 126.0878, 53.5 },
{ 2299.4561, 126.875, 107 },
{ 2299.4561, 127.793, 160.5 },
{ 2299.4561, 128.757, 214 },
{ 2322.1393, 123.3239, 0 },
{ 2322.1393, 123.8755, 53.5 },
{ 2322.1393, 124.6295, 107 },
{ 2322.1393, 125.5082, 160.5 },
{ 2322.1393, 126.4303, 214 },
{ 2344.8224, 121.1358, 0 },
{ 2344.8224, 121.6633, 53.5 },
{ 2344.8224, 122.384, 107 },
{ 2344.8224, 123.2234, 160.5 },
{ 2344.8224, 124.1036, 214 },
{ 2367.5056, 118.9476, 0 },
{ 2367.5056, 119.4511, 53.5 },
{ 2367.5056, 120.1385, 107 },
{ 2367.5056, 120.9386, 160.5 },
{ 2367.5056, 121.7769, 214 },
{ 2390.1887, 116.7594, 0 },
{ 2390.1887, 117.2389, 53.5 },
{ 2390.1887, 117.893, 107 },
{ 2390.1887, 118.6538, 160.5 },
{ 2390.1887, 119.4503, 214 },
{ 2412.8719, 114.5713, 0 },
{ 2412.8719, 115.0266, 53.5 },
{ 2412.8719, 115.6476, 107 },
{ 2412.8719, 116.369, 160.5 },
{ 2412.8719, 117.1236, 214 },
{ 2435.555, 112.3831, 0 },
{ 2435.555, 112.8144, 53.5 },
{ 2435.555, 113.4021, 107 },
{ 2435.555, 114.0842, 160.5 },
{ 2435.555, 114.7969, 214 },
{ 2458.2381, 110.195, 0 },
{ 2458.2381, 110.6022, 53.5 },
{ 2458.2381, 111.1566, 107 },
{ 2458.2381, 111.7994, 160.5 },
{ 2458.2381, 112.4702, 214 },
{ 2480.9213, 108.0068, 0 },
{ 2480.9213, 108.39, 53.5 },
{ 2480.9213, 108.9111, 107 },
{ 2480.9213, 109.5146, 160.5 },
{ 2480.9213, 110.1436, 214 },
{ 2503.6044, 105.8187, 0 },
{ 2503.6044, 106.1777, 53.5 },
{ 2503.6044, 106.6656, 107 },
{ 2503.6044, 107.2298, 160.5 },
{ 2503.6044, 107.8169, 214 },
{ 2526.2876, 103.6305, 0 },
{ 2526.2876, 103.9655, 53.5 },
{ 2526.2876, 104.4202, 107 },
{ 2526.2876, 104.945, 160.5 },
{ 2526.2876, 105.4902, 214 },
{ 2548.9707, 101.4364, 0 },
{ 2548.9707, 101.7279, 53.5 },
{ 2548.9707, 102.1239, 107 },
{ 2548.9707, 102.5815, 160.5 },
{ 2548.9707, 103.0576, 214 },
{ 2571.6539, 98.7825, 0 },
{ 2571.6539, 99.0565, 53.5 },
{ 2571.6539, 99.4287, 107 },
{ 2571.6539, 99.8586, 160.5 },
{ 2571.6539, 100.3058, 214 },
{ 2594.337, 96.1286, 0 },
{ 2594.337, 96.3851, 53.5 },
{ 2594.337, 96.7334, 107 },
{ 2594.337, 97.1357, 160.5 },
{ 2594.337, 97.554, 214 },
{ 2617.0202, 93.4746, 0 },
{ 2617.0202, 93.7137, 53.5 },
{ 2617.0202, 94.0382, 107 },
{ 2617.0202, 94.4128, 160.5 },
{ 2617.0202, 94.8022, 214 },
{ 2639.7033, 90.8207, 0 },
{ 2639.7033, 91.0424, 53.5 },
{ 2639.7033, 91.343, 107 },
{ 2639.7033, 91.6899, 160.5 },
{ 2639.7033, 92.0504, 214 },
{ 2662.3865, 88.1668, 0 },
{ 2662.3865, 88.371, 53.5 },
{ 2662.3865, 88.6477, 107 },
{ 2662.3865, 88.967, 160.5 },
{ 2662.3865, 89.2986, 214 },
{ 2685.0696, 85.5129, 0 },
{ 2685.0696, 85.6996, 53.5 },
{ 2685.0696, 85.9525, 107 },
{ 2685.0696, 86.2441, 160.5 },
{ 2685.0696, 86.5468, 214 },
{ 2707.7528, 82.8589, 0 },
{ 2707.7528, 83.0282, 53.5 },
{ 2707.7528, 83.2573, 107 },
{ 2707.7528, 83.5211, 160.5 },
{ 2707.7528, 83.795, 214 },
{ 2730.4359, 80.2023, 0 },
{ 2730.4359, 80.3426, 53.5 },
{ 2730.4359, 80.5327, 107 },
{ 2730.4359, 80.7518, 160.5 },
{ 2730.4359, 80.9794, 214 },
{ 2753.1191, 76.8591, 0 },
{ 2753.1191, 76.9867, 53.5 },
{ 2753.1191, 77.1595, 107 },
{ 2753.1191, 77.3587, 160.5 },
{ 2753.1191, 77.5655, 214 },
{ 2775.8022, 73.5159, 0 },
{ 2775.8022, 73.6308, 53.5 },
{ 2775.8022, 73.7863, 107 },
{ 2775.8022, 73.9655, 160.5 },
{ 2775.8022, 74.1516, 214 },
{ 2798.4854, 70.1727, 0 },
{ 2798.4854, 70.2749, 53.5 },
{ 2798.4854, 70.4131, 107 },
{ 2798.4854, 70.5723, 160.5 },
{ 2798.4854, 70.7377, 214 },
{ 2821.1685, 66.8295, 0 },
{ 2821.1685, 66.9189, 53.5 },
{ 2821.1685, 67.0399, 107 },
{ 2821.1685, 67.1792, 160.5 },
{ 2821.1685, 67.3237, 214 },
{ 2843.8517, 63.4864, 0 },
{ 2843.8517, 63.563, 53.5 },
{ 2843.8517, 63.6667, 107 },
{ 2843.8517, 63.786, 160.5 },
{ 2843.8517, 63.9098, 214 },
{ 2866.5348, 60.1432, 0 },
{ 2866.5348, 60.2071, 53.5 },
{ 2866.5348, 60.2935, 107 },
{ 2866.5348, 60.3928, 160.5 },
{ 2866.5348, 60.4959, 214 },
{ 2889.218, 55.7353, 0 },
{ 2889.218, 55.7835, 53.5 },
{ 2889.218, 55.8487, 107 },
{ 2889.218, 55.9237, 160.5 },
{ 2889.218, 56.0017, 214 },
{ 2911.9011, 51.1253, 0 },
{ 2911.9011, 51.165, 53.5 },
{ 2911.9011, 51.2185, 107 },
{ 2911.9011, 51.2802, 160.5 },
{ 2911.9011, 51.3442, 214 },
{ 2934.5843, 46.5154, 0 },
{ 2934.5843, 46.5465, 53.5 },
{ 2934.5843, 46.5884, 107 },
{ 2934.5843, 46.6366, 160.5 },
{ 2934.5843, 46.6867, 214 },
{ 2957.2674, 41.9055, 0 },
{ 2957.2674, 41.928, 53.5 },
{ 2957.2674, 41.9582, 107 },
{ 2957.2674, 41.9931, 160.5 },
{ 2957.2674, 42.0293, 214 },
{ 2979.9506, 35.8797, 0 },
{ 2979.9506, 35.8922, 53.5 },
{ 2979.9506, 35.9092, 107 },
{ 2979.9506, 35.9286, 160.5 },
{ 2979.9506, 35.9489, 214 },
{ 3002.6337, 28.2753, 0 },
{ 3002.6337, 28.2831, 53.5 },
{ 3002.6337, 28.2935, 107 },
{ 3002.6337, 28.3054, 160.5 },
{ 3002.6337, 28.3178, 214 },
{ 3025.3169, 20.671, 0 },
{ 3025.3169, 20.6739, 53.5 },
{ 3025.3169, 20.6778, 107 },
{ 3025.3169, 20.6822, 160.5 },
{ 3025.3169, 20.6868, 214 },
{ 3048, 0, 0 },
{ 3048, 0, 53.5 },
{ 3048, 0, 107 },
{ 3048, 0, 160.5 },
{ 3048, 0, 214 },
};
#endif