#ifndef SHURIKEN_LOOKUP_TABLE 
#define SHURIKEN_LOOKUP_TABLE 

#define TABLE_LENGTH 500
#define TABLE_WIDTH 3 
#define TABLE_DIFF_SPEEDS_SAME_ALTITUDE 5
static const float SimData[TABLE_LENGTH][TABLE_WIDTH] = {
{ 802.3013, 236.4456, 0 },
{ 802.3013, 240.2778, 53.5 },
{ 802.3013, 245.8492, 107 },
{ 802.3013, 252.3219, 160.5 },
{ 802.3013, 259.2061, 214 },
{ 824.9851, 234.9278, 0 },
{ 824.9851, 238.7173, 53.5 },
{ 824.9851, 244.1518, 107 },
{ 824.9851, 250.4962, 160.5 },
{ 824.9851, 257.2518, 214 },
{ 847.6689, 233.4088, 0 },
{ 847.6689, 237.1513, 53.5 },
{ 847.6689, 242.455, 107 },
{ 847.6689, 248.673, 160.5 },
{ 847.6689, 255.3221, 214 },
{ 870.3527, 231.8886, 0 },
{ 870.3527, 235.5791, 53.5 },
{ 870.3527, 240.7586, 107 },
{ 870.3527, 246.8569, 160.5 },
{ 870.3527, 253.3924, 214 },
{ 893.0366, 230.366, 0 },
{ 893.0366, 234.0001, 53.5 },
{ 893.0366, 239.0624, 107 },
{ 893.0366, 245.0451, 160.5 },
{ 893.0366, 251.4626, 214 },
{ 915.7204, 228.8422, 0 },
{ 915.7204, 232.4102, 53.5 },
{ 915.7204, 237.3563, 107 },
{ 915.7204, 243.2334, 160.5 },
{ 915.7204, 249.5329, 214 },
{ 938.4042, 227.3165, 0 },
{ 938.4042, 230.7976, 53.5 },
{ 938.4042, 235.6501, 107 },
{ 938.4042, 241.4216, 160.5 },
{ 938.4042, 247.6032, 214 },
{ 961.088, 225.7614, 0 },
{ 961.088, 229.1771, 53.5 },
{ 961.088, 233.9439, 107 },
{ 961.088, 239.6098, 160.5 },
{ 961.088, 245.6734, 214 },
{ 983.7719, 224.2004, 0 },
{ 983.7719, 227.5566, 53.5 },
{ 983.7719, 232.2377, 107 },
{ 983.7719, 237.798, 160.5 },
{ 983.7719, 243.7437, 214 },
{ 1006.4557, 222.6394, 0 },
{ 1006.4557, 225.9361, 53.5 },
{ 1006.4557, 230.5316, 107 },
{ 1006.4557, 235.9863, 160.5 },
{ 1006.4557, 241.814, 214 },
{ 1029.1395, 221.0785, 0 },
{ 1029.1395, 224.3155, 53.5 },
{ 1029.1395, 228.8254, 107 },
{ 1029.1395, 234.1745, 160.5 },
{ 1029.1395, 239.8842, 214 },
{ 1051.8234, 219.5175, 0 },
{ 1051.8234, 222.695, 53.5 },
{ 1051.8234, 227.1192, 107 },
{ 1051.8234, 232.3627, 160.5 },
{ 1051.8234, 237.9545, 214 },
{ 1074.5072, 217.9565, 0 },
{ 1074.5072, 221.0745, 53.5 },
{ 1074.5072, 225.4131, 107 },
{ 1074.5072, 230.551, 160.5 },
{ 1074.5072, 236.0248, 214 },
{ 1097.191, 216.3955, 0 },
{ 1097.191, 219.4539, 53.5 },
{ 1097.191, 223.7069, 107 },
{ 1097.191, 228.7392, 160.5 },
{ 1097.191, 234.095, 214 },
{ 1119.8748, 214.8345, 0 },
{ 1119.8748, 217.8334, 53.5 },
{ 1119.8748, 222.0007, 107 },
{ 1119.8748, 226.9274, 160.5 },
{ 1119.8748, 232.1653, 214 },
{ 1142.5586, 213.2736, 0 },
{ 1142.5586, 216.2129, 53.5 },
{ 1142.5586, 220.2945, 107 },
{ 1142.5586, 225.1157, 160.5 },
{ 1142.5586, 230.2356, 214 },
{ 1165.2424, 211.7126, 0 },
{ 1165.2424, 214.5923, 53.5 },
{ 1165.2424, 218.5884, 107 },
{ 1165.2424, 223.3039, 160.5 },
{ 1165.2424, 228.3058, 214 },
{ 1187.9263, 210.1516, 0 },
{ 1187.9263, 212.9718, 53.5 },
{ 1187.9263, 216.8822, 107 },
{ 1187.9263, 221.4921, 160.5 },
{ 1187.9263, 226.3761, 214 },
{ 1210.6101, 208.5906, 0 },
{ 1210.6101, 211.3513, 53.5 },
{ 1210.6101, 215.176, 107 },
{ 1210.6101, 219.6804, 160.5 },
{ 1210.6101, 224.4464, 214 },
{ 1233.2939, 207.0296, 0 },
{ 1233.2939, 209.7308, 53.5 },
{ 1233.2939, 213.4698, 107 },
{ 1233.2939, 217.8686, 160.5 },
{ 1233.2939, 222.5167, 214 },
{ 1255.9778, 205.4687, 0 },
{ 1255.9778, 208.1102, 53.5 },
{ 1255.9778, 211.7637, 107 },
{ 1255.9778, 216.0568, 160.5 },
{ 1255.9778, 220.5869, 214 },
{ 1278.6616, 203.9077, 0 },
{ 1278.6616, 206.4897, 53.5 },
{ 1278.6616, 210.0575, 107 },
{ 1278.6616, 214.245, 160.5 },
{ 1278.6616, 218.6572, 214 },
{ 1301.3455, 202.3467, 0 },
{ 1301.3455, 204.8692, 53.5 },
{ 1301.3455, 208.3513, 107 },
{ 1301.3455, 212.4333, 160.5 },
{ 1301.3455, 216.7275, 214 },
{ 1324.0293, 200.7857, 0 },
{ 1324.0293, 203.2486, 53.5 },
{ 1324.0293, 206.6452, 107 },
{ 1324.0293, 210.6215, 160.5 },
{ 1324.0293, 214.7977, 214 },
{ 1346.7131, 199.2247, 0 },
{ 1346.7131, 201.6281, 53.5 },
{ 1346.7131, 204.939, 107 },
{ 1346.7131, 208.8097, 160.5 },
{ 1346.7131, 212.868, 214 },
{ 1369.397, 197.6638, 0 },
{ 1369.397, 200.0076, 53.5 },
{ 1369.397, 203.2328, 107 },
{ 1369.397, 206.998, 160.5 },
{ 1369.397, 210.9383, 214 },
{ 1392.0808, 196.1028, 0 },
{ 1392.0808, 198.3871, 53.5 },
{ 1392.0808, 201.5266, 107 },
{ 1392.0808, 205.1862, 160.5 },
{ 1392.0808, 209.0085, 214 },
{ 1414.7646, 194.5418, 0 },
{ 1414.7646, 196.7665, 53.5 },
{ 1414.7646, 199.8205, 107 },
{ 1414.7646, 203.3744, 160.5 },
{ 1414.7646, 207.078, 214 },
{ 1437.4484, 192.9808, 0 },
{ 1437.4484, 195.146, 53.5 },
{ 1437.4484, 198.1143, 107 },
{ 1437.4484, 201.5315, 160.5 },
{ 1437.4484, 205.1471, 214 },
{ 1460.1322, 191.4199, 0 },
{ 1460.1322, 193.4955, 53.5 },
{ 1460.1322, 196.3372, 107 },
{ 1460.1322, 199.6798, 160.5 },
{ 1460.1322, 203.2162, 214 },
{ 1482.816, 189.766, 0 },
{ 1482.816, 191.7785, 53.5 },
{ 1482.816, 194.5589, 107 },
{ 1482.816, 197.8281, 160.5 },
{ 1482.816, 201.2852, 214 },
{ 1505.4999, 188.0926, 0 },
{ 1505.4999, 190.0614, 53.5 },
{ 1505.4999, 192.7805, 107 },
{ 1505.4999, 195.9763, 160.5 },
{ 1505.4999, 199.3543, 214 },
{ 1528.1837, 186.4192, 0 },
{ 1528.1837, 188.3444, 53.5 },
{ 1528.1837, 191.0022, 107 },
{ 1528.1837, 194.1246, 160.5 },
{ 1528.1837, 197.4233, 214 },
{ 1550.8674, 184.7458, 0 },
{ 1550.8674, 186.6274, 53.5 },
{ 1550.8674, 189.2239, 107 },
{ 1550.8674, 192.2729, 160.5 },
{ 1550.8674, 195.4924, 214 },
{ 1573.5513, 183.0723, 0 },
{ 1573.5513, 184.9103, 53.5 },
{ 1573.5513, 187.4456, 107 },
{ 1573.5513, 190.4212, 160.5 },
{ 1573.5513, 193.5615, 214 },
{ 1596.2351, 181.3989, 0 },
{ 1596.2351, 183.1933, 53.5 },
{ 1596.2351, 185.6673, 107 },
{ 1596.2351, 188.5695, 160.5 },
{ 1596.2351, 191.6305, 214 },
{ 1618.9189, 179.7255, 0 },
{ 1618.9189, 181.4763, 53.5 },
{ 1618.9189, 183.8889, 107 },
{ 1618.9189, 186.7177, 160.5 },
{ 1618.9189, 189.6996, 214 },
{ 1641.6028, 178.0521, 0 },
{ 1641.6028, 179.7592, 53.5 },
{ 1641.6028, 182.1106, 107 },
{ 1641.6028, 184.866, 160.5 },
{ 1641.6028, 187.7687, 214 },
{ 1664.2866, 176.3786, 0 },
{ 1664.2866, 178.0422, 53.5 },
{ 1664.2866, 180.3323, 107 },
{ 1664.2866, 183.0143, 160.5 },
{ 1664.2866, 185.8377, 214 },
{ 1686.9705, 174.7052, 0 },
{ 1686.9705, 176.3252, 53.5 },
{ 1686.9705, 178.554, 107 },
{ 1686.9705, 181.1626, 160.5 },
{ 1686.9705, 183.9068, 214 },
{ 1709.6543, 173.0318, 0 },
{ 1709.6543, 174.6082, 53.5 },
{ 1709.6543, 176.7756, 107 },
{ 1709.6543, 179.3108, 160.5 },
{ 1709.6543, 181.9758, 214 },
{ 1732.3381, 171.3584, 0 },
{ 1732.3381, 172.8911, 53.5 },
{ 1732.3381, 174.9973, 107 },
{ 1732.3381, 177.4591, 160.5 },
{ 1732.3381, 180.0449, 214 },
{ 1755.022, 169.685, 0 },
{ 1755.022, 171.1741, 53.5 },
{ 1755.022, 173.219, 107 },
{ 1755.022, 175.6074, 160.5 },
{ 1755.022, 178.114, 214 },
{ 1777.7058, 168.0115, 0 },
{ 1777.7058, 169.4571, 53.5 },
{ 1777.7058, 171.4406, 107 },
{ 1777.7058, 173.7557, 160.5 },
{ 1777.7058, 176.183, 214 },
{ 1800.3896, 166.3381, 0 },
{ 1800.3896, 167.74, 53.5 },
{ 1800.3896, 169.6623, 107 },
{ 1800.3896, 171.9039, 160.5 },
{ 1800.3896, 174.2521, 214 },
{ 1823.0735, 164.6647, 0 },
{ 1823.0735, 166.023, 53.5 },
{ 1823.0735, 167.884, 107 },
{ 1823.0735, 170.0522, 160.5 },
{ 1823.0735, 172.3211, 214 },
{ 1845.7572, 162.9913, 0 },
{ 1845.7572, 164.306, 53.5 },
{ 1845.7572, 166.1057, 107 },
{ 1845.7572, 168.2005, 160.5 },
{ 1845.7572, 170.3902, 214 },
{ 1868.4412, 161.3178, 0 },
{ 1868.4412, 162.5889, 53.5 },
{ 1868.4412, 164.3273, 107 },
{ 1868.4412, 166.3488, 160.5 },
{ 1868.4412, 168.4592, 214 },
{ 1891.1249, 159.6444, 0 },
{ 1891.1249, 160.8719, 53.5 },
{ 1891.1249, 162.5249, 107 },
{ 1891.1249, 164.418, 160.5 },
{ 1891.1249, 166.4102, 214 },
{ 1913.8087, 157.8601, 0 },
{ 1913.8087, 159.0055, 53.5 },
{ 1913.8087, 160.5785, 107 },
{ 1913.8087, 162.4188, 160.5 },
{ 1913.8087, 164.355, 214 },
{ 1936.4926, 155.9908, 0 },
{ 1936.4926, 157.1039, 53.5 },
{ 1936.4926, 158.6321, 107 },
{ 1936.4926, 160.4196, 160.5 },
{ 1936.4926, 162.2999, 214 },
{ 1959.1764, 154.1215, 0 },
{ 1959.1764, 155.2023, 53.5 },
{ 1959.1764, 156.6858, 107 },
{ 1959.1764, 158.4204, 160.5 },
{ 1959.1764, 160.2447, 214 },
{ 1981.8602, 152.2523, 0 },
{ 1981.8602, 153.3007, 53.5 },
{ 1981.8602, 154.7394, 107 },
{ 1981.8602, 156.4212, 160.5 },
{ 1981.8602, 158.1895, 214 },
{ 2004.5441, 150.383, 0 },
{ 2004.5441, 151.3991, 53.5 },
{ 2004.5441, 152.793, 107 },
{ 2004.5441, 154.422, 160.5 },
{ 2004.5441, 156.1343, 214 },
{ 2027.2279, 148.5137, 0 },
{ 2027.2279, 149.4975, 53.5 },
{ 2027.2279, 150.8467, 107 },
{ 2027.2279, 152.4228, 160.5 },
{ 2027.2279, 154.0792, 214 },
{ 2049.9116, 146.6444, 0 },
{ 2049.9116, 147.5959, 53.5 },
{ 2049.9116, 148.9003, 107 },
{ 2049.9116, 150.4236, 160.5 },
{ 2049.9116, 152.024, 214 },
{ 2072.5955, 144.7751, 0 },
{ 2072.5955, 145.6944, 53.5 },
{ 2072.5955, 146.9539, 107 },
{ 2072.5955, 148.4245, 160.5 },
{ 2072.5955, 149.9688, 214 },
{ 2095.2793, 142.9058, 0 },
{ 2095.2793, 143.7928, 53.5 },
{ 2095.2793, 145.0076, 107 },
{ 2095.2793, 146.4252, 160.5 },
{ 2095.2793, 147.9137, 214 },
{ 2117.9631, 141.0365, 0 },
{ 2117.9631, 141.8912, 53.5 },
{ 2117.9631, 143.0612, 107 },
{ 2117.9631, 144.4261, 160.5 },
{ 2117.9631, 145.8585, 214 },
{ 2140.647, 139.1673, 0 },
{ 2140.647, 139.9896, 53.5 },
{ 2140.647, 141.1148, 107 },
{ 2140.647, 142.4269, 160.5 },
{ 2140.647, 143.8033, 214 },
{ 2163.3308, 137.298, 0 },
{ 2163.3308, 138.088, 53.5 },
{ 2163.3308, 139.1684, 107 },
{ 2163.3308, 140.4277, 160.5 },
{ 2163.3308, 141.7482, 214 },
{ 2186.0146, 135.4287, 0 },
{ 2186.0146, 136.1864, 53.5 },
{ 2186.0146, 137.2221, 107 },
{ 2186.0146, 138.4285, 160.5 },
{ 2186.0146, 139.693, 214 },
{ 2208.6985, 133.5594, 0 },
{ 2208.6985, 134.2848, 53.5 },
{ 2208.6985, 135.2757, 107 },
{ 2208.6985, 136.4293, 160.5 },
{ 2208.6985, 137.6378, 214 },
{ 2231.3823, 131.6901, 0 },
{ 2231.3823, 132.3832, 53.5 },
{ 2231.3823, 133.3293, 107 },
{ 2231.3823, 134.4301, 160.5 },
{ 2231.3823, 135.5826, 214 },
{ 2254.0662, 129.8208, 0 },
{ 2254.0662, 130.4816, 53.5 },
{ 2254.0662, 131.383, 107 },
{ 2254.0662, 132.3887, 160.5 },
{ 2254.0662, 133.4366, 214 },
{ 2276.75, 127.7253, 0 },
{ 2276.75, 128.3251, 53.5 },
{ 2276.75, 129.1457, 107 },
{ 2276.75, 130.1032, 160.5 },
{ 2276.75, 131.1093, 214 },
{ 2299.4336, 125.5365, 0 },
{ 2299.4336, 126.1123, 53.5 },
{ 2299.4336, 126.8996, 107 },
{ 2299.4336, 127.8178, 160.5 },
{ 2299.4336, 128.7819, 214 },
{ 2322.1177, 123.3476, 0 },
{ 2322.1177, 123.8993, 53.5 },
{ 2322.1177, 124.6534, 107 },
{ 2322.1177, 125.5323, 160.5 },
{ 2322.1177, 126.4545, 214 },
{ 2344.8013, 121.1588, 0 },
{ 2344.8013, 121.6865, 53.5 },
{ 2344.8013, 122.4073, 107 },
{ 2344.8013, 123.2468, 160.5 },
{ 2344.8013, 124.1272, 214 },
{ 2367.4854, 118.97, 0 },
{ 2367.4854, 119.4735, 53.5 },
{ 2367.4854, 120.1611, 107 },
{ 2367.4854, 120.9613, 160.5 },
{ 2367.4854, 121.7998, 214 },
{ 2390.1689, 116.7812, 0 },
{ 2390.1689, 117.2607, 53.5 },
{ 2390.1689, 117.915, 107 },
{ 2390.1689, 118.6759, 160.5 },
{ 2390.1689, 119.4725, 214 },
{ 2412.853, 114.5923, 0 },
{ 2412.853, 115.0477, 53.5 },
{ 2412.853, 115.6688, 107 },
{ 2412.853, 116.3904, 160.5 },
{ 2412.853, 117.1451, 214 },
{ 2435.5366, 112.4035, 0 },
{ 2435.5366, 112.8349, 53.5 },
{ 2435.5366, 113.4226, 107 },
{ 2435.5366, 114.1049, 160.5 },
{ 2435.5366, 114.8178, 214 },
{ 2458.2205, 110.2147, 0 },
{ 2458.2205, 110.6219, 53.5 },
{ 2458.2205, 111.1765, 107 },
{ 2458.2205, 111.8195, 160.5 },
{ 2458.2205, 112.4904, 214 },
{ 2480.9043, 108.0258, 0 },
{ 2480.9043, 108.409, 53.5 },
{ 2480.9043, 108.9303, 107 },
{ 2480.9043, 109.534, 160.5 },
{ 2480.9043, 110.1631, 214 },
{ 2503.5884, 105.837, 0 },
{ 2503.5884, 106.1961, 53.5 },
{ 2503.5884, 106.6841, 107 },
{ 2503.5884, 107.2485, 160.5 },
{ 2503.5884, 107.8357, 214 },
{ 2526.272, 103.6481, 0 },
{ 2526.272, 103.9832, 53.5 },
{ 2526.272, 104.438, 107 },
{ 2526.272, 104.963, 160.5 },
{ 2526.272, 105.5084, 214 },
{ 2548.9558, 101.4572, 0 },
{ 2548.9558, 101.7488, 53.5 },
{ 2548.9558, 102.1448, 107 },
{ 2548.9558, 102.6025, 160.5 },
{ 2548.9558, 103.0786, 214 },
{ 2571.6396, 98.8024, 0 },
{ 2571.6396, 99.0765, 53.5 },
{ 2571.6396, 99.4486, 107 },
{ 2571.6396, 99.8786, 160.5 },
{ 2571.6396, 100.3259, 214 },
{ 2594.3235, 96.1475, 0 },
{ 2594.3235, 96.4041, 53.5 },
{ 2594.3235, 96.7525, 107 },
{ 2594.3235, 97.1548, 160.5 },
{ 2594.3235, 97.5731, 214 },
{ 2617.0073, 93.4926, 0 },
{ 2617.0073, 93.7318, 53.5 },
{ 2617.0073, 94.0563, 107 },
{ 2617.0073, 94.4309, 160.5 },
{ 2617.0073, 94.8204, 214 },
{ 2639.6912, 90.8378, 0 },
{ 2639.6912, 91.0595, 53.5 },
{ 2639.6912, 91.3601, 107 },
{ 2639.6912, 91.7071, 160.5 },
{ 2639.6912, 92.0677, 214 },
{ 2662.375, 88.1829, 0 },
{ 2662.375, 88.3871, 53.5 },
{ 2662.375, 88.664, 107 },
{ 2662.375, 88.9833, 160.5 },
{ 2662.375, 89.3149, 214 },
{ 2685.0588, 85.5281, 0 },
{ 2685.0588, 85.7148, 53.5 },
{ 2685.0588, 85.9678, 107 },
{ 2685.0588, 86.2594, 160.5 },
{ 2685.0588, 86.5622, 214 },
{ 2707.7427, 82.8732, 0 },
{ 2707.7427, 83.0425, 53.5 },
{ 2707.7427, 83.2716, 107 },
{ 2707.7427, 83.5356, 160.5 },
{ 2707.7427, 83.8095, 214 },
{ 2730.4263, 80.2184, 0 },
{ 2730.4263, 80.3596, 53.5 },
{ 2730.4263, 80.5498, 107 },
{ 2730.4263, 80.7689, 160.5 },
{ 2730.4263, 80.9965, 214 },
{ 2753.1104, 76.8748, 0 },
{ 2753.1104, 77.0025, 53.5 },
{ 2753.1104, 77.1753, 107 },
{ 2753.1104, 77.3745, 160.5 },
{ 2753.1104, 77.5813, 214 },
{ 2775.7942, 73.5304, 0 },
{ 2775.7942, 73.6453, 53.5 },
{ 2775.7942, 73.8009, 107 },
{ 2775.7942, 73.9801, 160.5 },
{ 2775.7942, 74.1662, 214 },
{ 2798.478, 70.186, 0 },
{ 2798.478, 70.2882, 53.5 },
{ 2798.478, 70.4265, 107 },
{ 2798.478, 70.5857, 160.5 },
{ 2798.478, 70.7511, 214 },
{ 2821.1616, 66.8417, 0 },
{ 2821.1616, 66.9311, 53.5 },
{ 2821.1616, 67.0521, 107 },
{ 2821.1616, 67.1914, 160.5 },
{ 2821.1616, 67.336, 214 },
{ 2843.8457, 63.4973, 0 },
{ 2843.8457, 63.574, 53.5 },
{ 2843.8457, 63.6777, 107 },
{ 2843.8457, 63.797, 160.5 },
{ 2843.8457, 63.9208, 214 },
{ 2866.5293, 60.1529, 0 },
{ 2866.5293, 60.2169, 53.5 },
{ 2866.5293, 60.3033, 107 },
{ 2866.5293, 60.4026, 160.5 },
{ 2866.5293, 60.5057, 214 },
{ 2889.2131, 55.7471, 0 },
{ 2889.2131, 55.7953, 53.5 },
{ 2889.2131, 55.8606, 107 },
{ 2889.2131, 55.9356, 160.5 },
{ 2889.2131, 56.0135, 214 },
{ 2911.897, 51.1355, 0 },
{ 2911.897, 51.1751, 53.5 },
{ 2911.897, 51.2287, 107 },
{ 2911.897, 51.2903, 160.5 },
{ 2911.897, 51.3544, 214 },
{ 2934.5811, 46.5239, 0 },
{ 2934.5811, 46.5549, 53.5 },
{ 2934.5811, 46.5968, 107 },
{ 2934.5811, 46.6451, 160.5 },
{ 2934.5811, 46.6952, 214 },
{ 2957.2646, 41.9123, 0 },
{ 2957.2646, 41.9347, 53.5 },
{ 2957.2646, 41.965, 107 },
{ 2957.2646, 41.9999, 160.5 },
{ 2957.2646, 42.0361, 214 },
{ 2979.9485, 35.8881, 0 },
{ 2979.9485, 35.9007, 53.5 },
{ 2979.9485, 35.9176, 107 },
{ 2979.9485, 35.9371, 160.5 },
{ 2979.9485, 35.9573, 214 },
{ 3002.6323, 28.281, 0 },
{ 3002.6323, 28.2887, 53.5 },
{ 3002.6323, 28.2991, 107 },
{ 3002.6323, 28.311, 160.5 },
{ 3002.6323, 28.3235, 214 },
{ 3025.3162, 20.6739, 0 },
{ 3025.3162, 20.6767, 53.5 },
{ 3025.3162, 20.6806, 107 },
{ 3025.3162, 20.685, 160.5 },
{ 3025.3162, 20.6896, 214 },
{ 3048, 0, 0 },
{ 3048, 0, 53.5 },
{ 3048, 0, 107 },
{ 3048, 0, 160.5 },
{ 3048, 0, 214 },
};
#endif