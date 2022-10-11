import requests
import re
import os
import time
headers={
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}
r=requests.get("https://www.vmgirls.com/13487.html",headers=headers)

demo=r.text
urls=re.findall('<a href="(.*?)".*?alt=""',demo)
dirname=re.findall('alt="(.*?)" title="你与星河,皆可收藏">',demo)[-1]
if not os.path.exists(dirname):
    os.mkdir(dirname)
print(dirname)
for url in urls:
    time.sleep(1)
    with open(dirname+'/'+url.split('/')[-1],'wb') as f:
        r1=requests.get(url)
        f.write(r1.content)