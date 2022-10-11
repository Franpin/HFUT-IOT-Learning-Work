"""mytest URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
 
from . import sonci
from . import newCi
from . import fenci
from . import hmm
 
urlpatterns = [
    url(r'^hello$', sonci.hello),
    url(r'^show$', sonci.show),
    url(r'^fenci$', fenci.show),
    url(r'^xijiangyue$', newCi.xijiangyue),
    url(r'^sumuzhe$', newCi.sumuzhe),
    url(r'^jiuquanzi$', newCi.jiuquanzi),
    url(r'^gancaozi$', newCi.gancaozi),
    url(r'^shengchazi$', newCi.shengchazi),
    url(r'^fenci$', fenci.test),
    url(r'^hmm$', hmm.fenci),

]