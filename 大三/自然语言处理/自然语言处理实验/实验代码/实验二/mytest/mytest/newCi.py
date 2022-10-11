
import os
import re
import random
 
from django.http import HttpResponse
from django.shortcuts import render
import json


resultOne = open('./mytest/static/1.txt', encoding='utf-8').read()
resultOne = resultOne.split('\n')
resultOne = [one.split(' ')[0] for one in resultOne if int(one.split(' ')[2]) > 10]
# print(resultOne)


resultTwo = open('./mytest/static/2.txt', encoding='utf-8').read()
resultTwo = resultTwo.split('\n')
resultTwo = [one.split(' ')[0] for one in resultTwo if int(one.split(' ')[2]) > 10]

# print(resultTwo)

resultThree = open('./mytest/static/3.txt', encoding='utf-8').read()
resultThree = resultThree.split('\n')
resultThree = [one.split(' ')[0] for one in resultThree if int(one.split(' ')[2]) > 10]
# print(resultThree)

def one():
    return resultOne[random.randint(0,len(resultOne) -1)]

def two():
    return resultTwo[random.randint(0,len(resultTwo) -1)]

def three():
    return resultThree[random.randint(0,len(resultThree) -1)]

def jiuquanzi(request):
    # 长忆 观潮，满郭 人争 江上望。来疑 沧海 尽成空。万面 鼓声中。弄涛 儿向 涛头立。手把 红旗 旗不湿。别来 几向 梦中看。梦觉 尚心寒。 
    allText = '长忆%s，\n%s%s%s。\n%s%s%s。\n%s%s。\n%s%s%s。\n%s%s%s。\n%s%s%s。\n%s%s'
    message = allText%(two(), two(),two(),three(), two(),two(),three(), two(),three(), two(),two(),three(),two(),two(),three(),two(),two(),three(), two(),three())
    data = {
        'successful': 'true',
        'title': '酒泉子',
        'data': message
    };
    return HttpResponse(json.dumps(data), content_type="application/json")

def sumuzhe(request):
    # 碧云天，黄叶地。秋色 连波，波上 寒烟翠。山映 斜阳 天接水。芳草 无情，更在 斜阳外。黯乡魂，追旅思。夜夜 除非，好梦 留人睡。明月 楼高 休独倚。酒入 愁肠，化作 相思泪。
    allText = '%s，%s。\n%s%s，%s%s。\n%s%s%s。\n%s%s，%s%s。\n%s，%s。\n%s%s，%s%s。\n%s%s%s。\n%s%s，%s%s。'
    message = allText%(three(),three(),two(),two(), two(), three(),  two(),two(),three(), two(),two(), two(), three(),three(),three(),two(),two(), two(), three(),  two(),two(),three(), two(),two(), two(), three())
    data = {
        'successful': 'true',
        'title': '苏幕遮',
        'data': message
    };
    return HttpResponse(json.dumps(data), content_type="application/json")

def xijiangyue(request):
    # 凤额 绣帘 高卷，兽钚 朱户 频摇。两竿 红日 上花梢。春睡 厌厌 难觉。好梦 狂随 飞絮，闲愁 浓胜 香醪。不成 雨暮 与 云朝。又是 韶光 过 了。
    allText = '%s%s%s，%s%s%s。\n%s%s%s。\n%s%s%s。\n%s%s%s，%s%s%s。\n%s%s%s%s。\n%s%s%s。'
    message = allText%(two(), two(), two(),two(),two(), two(),two(),two(), three(),two(), two(), two(),two(), two(), two(),two(), two(), two(),two(), two(),one(), two(),two(), two(), two())
    data = {
        'successful': 'true',
        'title': '西江月',
        'data': message
    };
    return HttpResponse(json.dumps(data), content_type="application/json")


def gancaozi(request):
    # 秋 暮。乱洒 衰荷，颗颗 真珠雨。雨过 月华生，冷彻 鸳鸯浦。池上 凭阑 愁无侣。奈此个、单栖 情绪。却傍  金笼 共鹦鹉。念 粉郎 言语。
    allText = '秋%s。\n%s%s，%s%s。\n%s%s，%s%s。\n%s%s%s。\n%s%s%s。\n%s%s%s。\n%s%s%s。'
    message = allText%(one(), two(), two(),two(),three(), two(),three(),two(), three(),two(), two(), three(),three(), two(), two(),two(),two(), three(),one(), two(),two())
    data = {
        'successful': 'true',
        'title': '甘草子',
        'data': message
    };
    return HttpResponse(json.dumps(data), content_type="application/json")

def shengchazi(request):
    # 浪荡 去未来，踯躅 花频换。可惜 石榴裙，兰麝 香销半。琵琶 闲抱 理相思，必拨 朱弦断。拟续 断朱弦，待这 冤家看。
    allText = '%s%s，%s%s。\n%s%s，%s%s。 \n%s%s%s，%s%s。\n%s%s，%s%s。'
    message = allText%(two(), three(), two(), three(),two(), three(),two(), three(),two(),two(), three(),two(), three(),two(), three(),two(), three())
    data = {
        'successful': 'true',
        'title': '生查子',
        'data': message
    };
    return HttpResponse(json.dumps(data), content_type="application/json")
