
from django.http import HttpResponse
from django.shortcuts import render
import json
 
import jieba.posseg as pseg

# 表单
def show(request):
    return render(request, 'fenci.html')


def test(request):
    print('request', request, request.GET)
    text = request.GET.get('text',1) 
    print(text)
    words = pseg.cut(text)
    mess = ""
    for w in words:
        print("%s %s" %(w.word, w.flag))
        mess +=w.word + '/' + w.flag + '\t'
    data = {
        'result' : mess,
    }
    return HttpResponse(json.dumps(data), content_type="application/json")