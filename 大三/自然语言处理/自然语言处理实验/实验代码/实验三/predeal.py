'''
中文词频统计
语料库：1998-01-2003版-带音.txt
要求：输入txt文件，统计1元模型和2元模型，输出单词和词频文件，双词和词频文件。设计相应的接口，能够快速载入文件，并检索单词和双词。

'''
import os
import re
import collections

file = open('1998-01-2003版-带音.txt', encoding='utf-8').read()
# file = open('test.txt', encoding='utf-8').read()
line = file.split('\n')
text = []
oneWords = []
twoWords = []


for one in line:
    fil= re.compile("(/[a-z]*\\s{0,})")
    one = fil.split(one)
    # one = [word for word in one]
    one = one[1:]
    one = one[1::2]
    # print(one)
    test = []
    test.append('<b>')
    one = one[1:]
    for i in range(len(one)):
        word = one[i]
        # print(word)
        # word = word.split('/')[0]
        fil = re.compile(r"\{.*?\}|\[.*?\]")
        word = fil.sub('', word)
        # tmp_find = re.findall('[\u4e00-\u9fa5]|，|、|\d+',word)
        word = ''.join(word)
        # print(word)
        if len(word) < 1:
            continue
        test.append(word)
    test.append('<e>')
    if len(test) > 2:
        text.append(test)

# print(text)

for line in text:
    for i in range(len(line)):
        if not line[i] == '<b>' and not line[i] == '<e>':
            oneWords.append(line[i])
        if i + 1 < len(line):
            twoWords.append(line[i] + line[i+1])

# print (twoWords)
one_counter_list = collections.Counter(oneWords)
two_counter_list = collections.Counter(twoWords)
# print(one_counter_list['谆谆教诲'])

one_counter = dict(one_counter_list)
two_counter = dict(two_counter_list)



resultOne = open('1.txt','w', encoding='utf-8')
resultOne.write(str(one_counter))
resultOne.close()

resultOne = open('2.txt','w', encoding='utf-8')
resultOne.write(str(two_counter))
resultOne.close()