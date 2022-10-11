MaxTime = 16
     #生成子密钥的置换表1，将64位的密钥转换为56位
key_table1=[ 57, 49, 41, 33, 25, 17,  9,
               1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12,  4 ]
     #生成子密钥的置换表2，将56位的密钥转换为48位
key_table2=[ 14, 17, 11, 24,  1,  5,
               3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 ]
 
def Listmove(l, step):    #将列表中的元素循环左移
     return l[step:] + l[:step]
 
def Subkey(key):    #生成子密钥
     keyresult = []
     key0 = [0 for i in range(56)] 
     for i in range(len(key_table1)):
         key0[i] = key[key_table1[i]-1]
 
     #生成16个密钥
     for i in range(MaxTime):
         key1 = [0 for i in range(48)]
         #确定每次左移的步数
         if (i == 0 or i == 1 or i == 8 or i == 15):
             step = 1
         else:
             step = 2
         #分成两组
         tmp1 = key0[0:28]
         tmp2 = key0[28:56]
         #循环左移
         tmp1 = Listmove(tmp1, step)
         tmp2 = Listmove(tmp2, step)
         #左右连接
         key0 = tmp1 + tmp2
         #置换选择
         for i in range(len(key_table2)):
             key1[i] = key0[key_table2[i]-1]
         #生成密钥
         keyresult.append(key1)
     #返回的是一个集合包含了每次的密钥
     return keyresult