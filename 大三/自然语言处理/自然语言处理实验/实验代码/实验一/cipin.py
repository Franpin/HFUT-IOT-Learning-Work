
import os
import re
import collections

file = open('Ci.txt', encoding='utf-8').read()
# print(file)
word = []
twoWords = []
threeWords = []

# file = re.findall('[\u4e00-\u9fa5]', file)
sentences = re.split('（|）|。|，|\n|、|？| ',file)
sentences = [one for one in sentences if len(one) > 1]
# print(sentences)

for sentence in sentences:
    print(sentence)
    sentence = ''.join(re.findall('[\u4e00-\u9fa5]', sentence))
    for i in range(len(sentence)):
        # print(i)
        if i + 1 < len(sentence):
            twoWord = sentence[i: i+2]
            twoWords.append(twoWord)
        if i + 2 < len(sentence):
            threeWord = sentence[i: i+3]
            threeWords.append(threeWord)
        one = sentence[i]
        word.append(one)

one_counter_list = collections.Counter(word).most_common()
two_counter_list = collections.Counter(twoWords).most_common()
three_counter_list = collections.Counter(threeWords).most_common()

writeOne = [one[0] + '  ' + str(one[1]) for one in one_counter_list]
writeTwo = [one[0] + '  ' + str(one[1]) for one in two_counter_list]
writeThree = [one[0] + '  ' + str(one[1]) for one in three_counter_list]


resultOne = open('1.txt','w', encoding='utf-8')
resultOne.write('\n'.join(writeOne))
resultOne.close()

resultOne = open('2.txt','w', encoding='utf-8')
resultOne.write('\n'.join(writeTwo))
resultOne.close()

resultOne = open('3.txt','w', encoding='utf-8')
resultOne.write('\n'.join(writeThree))
resultOne.close()