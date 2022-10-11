import CreateSubkey as cs
import F_function as f
#十六进制转二进制比特串
def Hex2bin(text):
    result = []
    for i in range(len(text)):
        result.extend(f.int2bit(int(text[i],16)))
    return result
#二进制比特串转十六进制
def bin2Hex(text):
    result = []
    q = len(text)//4
    for i in range(q):
        dec = int(text[4*i])*8 + int(text[4*i+1])*4 + int(text[4*i+2])*2 + int(text[4*i+3])*1
        x = hex(dec)[2:].upper()
        result.extend(x)
    rs = ''.join(result)
    return rs
#按照DES算法的流程图进行运算
def Encryption(text, key):
    keylist = cs.Subkey(keybit)
    text1 = f.IP(text, 0)  #IP置换
    L = [text1[i] for i in range(32)]
    R = [text1[i] for i in range(32,64)]
    for i in range(16):
        tmp = R
        tmp = f.Extend(tmp)
        tmp = f.Xor(tmp, keylist[i])
        tmp = f.S_replace(tmp)
        tmp = f.P_replace(tmp)
        tmp = f.Xor(tmp, L)
        L = R
        R = tmp
    L,R = R,L
    ctext = L
    ctext.extend(R)
    ctext = f.IP(ctext, 1)
    return bin2Hex(ctext)

if __name__ == '__main__':
    with open('明文.txt','r',encoding='utf-8') as f1:
        plaintext=f1.readline()
    with open('key.txt','r',encoding='utf-8') as f2:
        key=f2.readline()
    ptext = Hex2bin(plaintext)
    keybit = Hex2bin(key)
    with open('密文.txt','w',encoding='utf-8') as f3:
        f3.write(Encryption(ptext, keybit))
