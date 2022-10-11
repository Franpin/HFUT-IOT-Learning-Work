import secrets
from PIL import Image
import re

from sympy import sec


def LstBit(source, target):
    '''替换最后一位的数据'''
    replace_reg = re.compile(r'[1|0]$')  # 匹配二进制最后一位
    return replace_reg.sub(target, source)


def StringtoBin(string):
    '''将字符串转换成二进制,不够8位补齐8位'''
    return ''.join(bin(ord(c)).replace('0b', '').rjust(8, '0') for c in string)


def encode(path, new_path, data):
    '''
    LSB加密
    path: 原图路径
    new_path: 为加密后图片的路径
    data: 为需要加密的数据
    '''
    # 初始化、定义
    data = StringtoBin(data)
    im = Image.open(path)
    width = im.size[0]  # 宽度
    height = im.size[1]  # 高度
    count = 0
    if width * height * 3 < len(data):
        print("数据过大")
        return
    # 遍历图片所有像素点
    for w in range(width):
        for h in range(height):
            # 获取像素点
            pixel = im.getpixel((w, h))
            # 取三通道值（十进制）
            R = pixel[0]
            G = pixel[1]
            B = pixel[2]
            # 十进制转二进制
            R_bit = bin(R).replace("0b", "")
            G_bit = bin(G).replace("0b", "")
            B_bit = bin(B).replace("0b", "")
            # 在R通道的末位存数据
            R_bit = LstBit(R_bit, data[count])
            count += 1
            if count == len(data):  # 存完数据时
                # 二进制转十进制
                R_bit = int(R_bit, 2)
                G_bit = int(G_bit, 2)
                B_bit = int(B_bit, 2)
                # 写回像素点
                im.putpixel((w, h), (R_bit, G_bit, B_bit))
                break
            # 在G通道的末位存数据
            G_bit = LstBit(G_bit, data[count])
            count += 1
            if count == len(data):  # 存完数据时
                # 二进制转十进制
                R_bit = int(R_bit, 2)
                G_bit = int(G_bit, 2)
                B_bit = int(B_bit, 2)
                # 写回像素点
                im.putpixel((w, h), (R_bit, G_bit, B_bit))
                break
            # 在B通道的末位存数据
            B_bit = LstBit(R_bit, data[count])
            count += 1
            if count == len(data):  # 存完数据时
                # 二进制转十进制
                R_bit = int(R_bit, 2)
                G_bit = int(G_bit, 2)
                B_bit = int(B_bit, 2)
                # 写回像素点
                im.putpixel((w, h), (R_bit, G_bit, B_bit))
                break
            R_bit = int(R_bit, 2)
            G_bit = int(G_bit, 2)
            B_bit = int(B_bit, 2)
            # 写回像素点
            im.putpixel((w, h), (R_bit, G_bit, B_bit))            
        if count == len(data):  # 存完数据时
                break
    im.save(new_path)


def decode(path,length):
    '''
    LSB解密
    path:需要解密的图片路径
    '''
    length = length*8
    data_bit = ""
    im = Image.open(path)
    width = im.size[0]  # 宽度
    height = im.size[1]  # 高度
    count = 0
    # 遍历图片所有像素点
    for w in range(width):
        for h in range(height):
            # 获取像素点
            pixel = im.getpixel((w, h))
            # 取三通道值（十进制）
            R = pixel[0]
            G = pixel[1]
            B = pixel[2]
            # 十进制转二进制
            R_bit = bin(R).replace("0b", "")
            G_bit = bin(G).replace("0b", "")
            B_bit = bin(B).replace("0b", "")
            # 在RGB通道的末位取数据
            data_bit += R_bit[-1:]
            count = count + 1
            if count == length:
                break  

            data_bit += G_bit[-1:]
            count = count + 1
            if count == length:
                break

            data_bit += B_bit[-1:]
            count = count + 1
            if count == length:
                break
        if count == length:
                break
    # 二进制转字符
    data = ""
    i = 0
    try: #有时候会出现报错，一报错就输出结果
        while i <= len(data_bit):  # 步长为8
            data += chr(int(data_bit[i:i + 8],2))
            i += 8
    except:
        return data
    return data
if __name__ == "__main__":
    secret = "hello world I Love You"
    encode("pic.png","new.png",secret)
    print('解码后：',decode("new.png",len(secret)))
