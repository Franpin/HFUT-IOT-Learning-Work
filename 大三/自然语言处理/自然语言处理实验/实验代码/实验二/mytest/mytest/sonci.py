 
from django.http import HttpResponse
from django.shortcuts import render
import json
 
# 表单
def show(request):
    return render(request, 'show.html')


def hello(request):
    print('test')
    data = {
        'successful': 'true',
        'data' : {
            'message': 'test'
        }
    }
    return HttpResponse(json.dumps(data), content_type="application/json")