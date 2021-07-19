import os, json

def load_file():
    if os.path.isfile('data.json'):
        f = open('data.json','r')
        data = json.loads(f.read())
        print(data['name'])
    else: 
        print('file non presente')

load_file()