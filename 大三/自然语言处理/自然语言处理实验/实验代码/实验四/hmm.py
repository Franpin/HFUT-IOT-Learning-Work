'''
语料库：1998-01-2003版-带音.txt
要求：根据构建的单词词典和双词词典，用n-gram模型，或者前向最长匹配，或者后向最长匹配等算法，鼓励用更复杂一些的方法来进行，包括隐马尔科夫模型和条件随机场模型。

使用hmm
'''

import os
import re
import numpy as np
import math
import json

minest = float('-inf')
enums = ['B', 'M', 'E', 'S']
words = []
chars = []
dic = {}

count_trans = {'B':{'B':0, 'E':0, 'M':0, 'S':0}, 'M':{'B':0, 'E':0, 'M':0, 'S':0}, 'E':{'B':0, 'E':0, 'M':0, 'S':0}, 'S':{'B':0, 'E':0, 'M':0, 'S':0}}
trans = {'B':{'B':0, 'E':0, 'M':0, 'S':0}, 'M':{'B':0, 'E':0, 'M':0, 'S':0}, 'E':{'B':0, 'E':0, 'M':0, 'S':0}, 'S':{'B':0, 'E':0, 'M':0, 'S':0}}
count_mixed =  {'B':{}, 'M':{}, 'E':{}, 'S':{}}
mixed = {'B':{}, 'M':{}, 'E':{}, 'S':{}}

pi_init = [0, 0, 0, 0]

# file = open('test.txt', encoding='utf-8').read()
file = open('1998-01-2003版-带音.txt', encoding='utf-8').read()
file = '\n'.join(re.split('\n', file)[1:])
text = re.split('\n|。|！|？', file)
# print(text)
newText = []
newCharacter = []
for line in text:
    line = line.split('  ')
    # line = [1:]
    # print(line)
    newLine = []
    newchar = []
    for word in line:
        if word == '':
            continue
        index = word.index('/')
        char = word[index+1:]
        # print(word[:index])
        fil = re.compile(r"\{.*?\}|\[.*?\]")
        word = fil.sub('', word[:index])
        # print(word)
        if not word == '':
            newLine.append(word)
            newchar.append(char)
        if not len(newLine) == len(newchar):
            print('----------------------------------')
    # print(newLine)
    if len(newLine) > 0:
        newText.append(newLine)
        newCharacter.append(newchar)

for line in newText:
    for word in line:
        words.extend(word.strip())
words = list(set(words))

for line in newCharacter:
    for char in line:
        # print(char)
        chars.append(char)
chars = list(set(chars))
# print(chars)
char_count_trans = {}
char_trans = {}
char_mixed = {}
char_count_mixed = {}
char_pi_init = {}
for char in chars:
    char_mixed[char] = {}
    char_count_mixed[char] = {}
    char_count_trans[char] = {}
    char_trans[char] = {}
    char_pi_init[char] = 0
    for char2 in chars:
        char_count_trans[char][char2] = 0
        char_trans[char][char2] = 0

# print(char_count_trans)
# print(newText)

def initChar(allText, newCharacter):
    text = []
    character = []
    print(len(newCharacter))
    for i in range(len(allText)):
        line = allText[i]
        char_line = newCharacter[i]
        text += line
        character += char_line
        char_pi_init[char_line[0]] +=1
        for j in range(len(line) - 1):
            char_count_trans[char_line[j]][char_line[j+1]] += 1
            if line[j] not in char_count_mixed[char_line[j]].keys():
                char_count_mixed[char_line[j]][line[j]] = 1
            else:
                char_count_mixed[char_line[j]][line[j]] += 1

    print('init')
    # print(char_pi_init)
    for i in char_pi_init:
        char_pi_init[i] = char_pi_init[i] / sum(char_pi_init.values())
    for i in char_pi_init:
        if char_pi_init[i] == 0:
            char_pi_init[i] = minest
        else:
            char_pi_init[i] = math.log(char_pi_init[i])

    print('char_pi_init')
    # print(count_mixed)
    for (key, value) in char_count_trans.items():
        count = sum(value.values())
        # print(key, value)
        for (in_key, in_value) in value.items():
            if count == 0:
                char_trans[key][in_key] = 0
            else:
                char_trans[key][in_key] = in_value / count
            if char_trans[key][in_key] == 0:
                char_trans[key][in_key] = minest
            else:
                char_trans[key][in_key] = math.log(char_trans[key][in_key])

    print('char_trans')

    for (key, value) in char_count_mixed.items():
        for item in text:
            if item not in value.keys():
                char_count_mixed[key][item] = 1

    print('trans')

    for (key, value) in char_count_mixed.items():
        count = sum(value.values())
        for (in_key, in_value) in value.items():
            # 平滑
            char_mixed[key][in_key] = math.log((in_value + 1) / count)

    print('char_mixed')
    trans_save = open('char_trans.json', 'w')
    json.dump(char_trans, trans_save)
    mixed_save = open('char_mixed.json', 'w')
    json.dump(char_mixed, mixed_save)
    text_save = open('char_text.json', 'w')
    char_text = {'text': text}
    json.dump(char_text, text_save)


def initTrain(allText):
    word_label = []
    newText = []
    print(len(allText))
    for line in allText:
        # print(line)
        newText +=line
        if len(line[0]) == 1:
            pi_init[3] += 1
        else:
            pi_init[0] +=1

        for i in range(len(line)):
            if len(line[i]) == 1:
                word_label += 'S'
            else:
                for j in range(len(line[i])):
                    if j == 0:
                        word_label += 'B'
                    elif j == len(line[i]) - 1:
                        word_label += 'E'
                    else:
                        word_label += 'M'
    # print(allText)
    # print(word_label)
    for i in range(len(pi_init)):
        pi_init[i] = pi_init[i] / sum(pi_init)
    for i in range(len(pi_init)):
        if pi_init[i] == 0:
            pi_init[i] = minest
        else:
            pi_init[i] = math.log(pi_init[i])
    print('pi_init', pi_init)

    # print(newText)
    print("change to %d<-------->%d" %(len(newText),len(word_label)));
    newText = ''.join(newText)

    for i in range(len(word_label)-1):
        # for calc trans matrix P[I][J]
        count_trans[word_label[i]][word_label[i+1]] += 1
    for i in range(len(word_label)-1):
        # for calc mixed_matrix 
        if newText[i] not in count_mixed[word_label[i]].keys():
            count_mixed[word_label[i]][newText[i]] = 1
        else:
            count_mixed[word_label[i]][newText[i]] += 1

    print('count_trans')
    # print(count_mixed)
    for (key, value) in count_trans.items():
        count = sum(value.values())
        print(key, value)
        for (in_key, in_value) in value.items():
            trans[key][in_key] = in_value / count
            if trans[key][in_key] == 0:
                trans[key][in_key] = minest
            else:
                trans[key][in_key] = math.log(trans[key][in_key])
    
    for (key, value) in count_mixed.items():
        for item in words:
            if item not in value.keys():
                count_mixed[key][item] = 1

    for (key, value) in count_mixed.items():
        count = sum(value.values())
        for (in_key, in_value) in value.items():
            # 平滑
            mixed[key][in_key] = math.log((in_value + 1) / count)

    trans_save = open('trans.json', 'w')
    json.dump(trans, trans_save)
    mixed_save = open('mixed.json', 'w')
    json.dump(mixed, mixed_save)

    return 



def viterbi(sents,init=pi_init):
    trans_save = open('trans.json')
    trans = json.load(trans_save)
    mixed_save = open('mixed.json')
    mixed = json.load(mixed_save)

    length = len(sents)
    weight = [[0 for col in range(length)] for row in range(4)]
    path = [[0 for col in range(length)] for row in range(4)] 
    inx = [0 for row in range(length)]
    # print(init)
    print(trans)
    # print(dic)
    # init
    for i in range(4):
        weight[i][0] = init[i] + mixed[enums[i]][sents[0]]

    print('init', init)
    print(weight)

    for i in list(range(length))[1:]:
        print(length, i, sents[i])
        for j in range(4):
            # print(trans[enums[0]])
            tmp = [weight[k][i-1] + trans[enums[k]][enums[j]] + mixed[enums[j]][sents[i]] for k in range(4)]
            # print('tmp', tmp)
            # print(weight[0][i-1])
            weight[j][i] = max(tmp)
            path[j][i] = tmp.index(weight[j][i])
    print(path)


    # end
    print(weight)
    if weight[2][-1] > weight[3][-1]:
        inx[-1] = 2
    else:
        inx[-1] = 3
    # print(inx)

    # back
    for i in list(range(length - 1))[::-1]:
        # print(i,inx[i+1])
        inx[i] = path[inx[i + 1]][i + 1]
    print(inx)
    label = [enums[i] for i in inx]
    print(label)

    change_sents = []
    word = ''
    for i in range(length):
        word += sents[i]
        if inx[i] == 3 or inx[i] == 2:
            change_sents.append(word)
            word = ''
    print(change_sents)

    return change_sents



def char_viterbi(sents,init=char_pi_init):
    # try:
    trans_save = open('char_trans.json')
    char_trans = json.load(trans_save)
    mixed_save = open('char_mixed.json')
    char_mixed = json.load(mixed_save)
    text_save = open('char_text.json')
    char_text = json.load(text_save)
    text = char_text['text']
    # print(text)
    for word in sents:
        if not word in text:
            print(word)
            print('no')
            raise Exception("no word")

    length = len(sents)
    allChar = len(chars)
    weight = [[0 for col in range(length)] for row in range(allChar)]
    path = [[0 for col in range(length)] for row in range(allChar)] 
    inx = [0 for row in range(length)]
    # print(init)
    print(trans)
    # print(dic)
    # init
    for i in range(allChar):
        weight[i][0] = init[chars[i]] + char_mixed[chars[i]][sents[0]]

    print('init', init)
    print(weight)

    for i in list(range(length))[1:]:
        print(length, i, sents[i])
        for j in range(allChar):
            # print(trans[chars[0]])
            tmp = [weight[k][i-1] + char_trans[chars[k]][chars[j]] + char_mixed[chars[j]][sents[i]] for k in range(allChar)]
            # print('tmp', tmp)
            # print(weight[0][i-1])
            weight[j][i] = max(tmp)
            path[j][i] = tmp.index(weight[j][i])
    print(path)


    # end
    print(weight)
    tmp = [one[-1] for one in weight]
    inx[-1] = tmp.index(max(tmp))
    # print(inx)

    # back
    for i in list(range(length - 1))[::-1]:
        # print(i,inx[i+1])
        inx[i] = path[inx[i + 1]][i + 1]
    print(inx)
    label = [chars[i] for i in inx]
    print(label)

    change_sents = ""
    for i in range(length):
        change_sents += sents[i] + "/" + label[i] + "\t"
    print(change_sents)
    # except:
    #     print('---------------------')
    return

# initTrain(newText)
# initChar(newText, newCharacter)
change_sents = viterbi('我是合肥工业大学计算机科学与技术15-3班的学生')
char_viterbi(change_sents)