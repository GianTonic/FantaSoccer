import csv
import os
import requests
import re
import json

class file_csv(object):
    append_csv_header = False
    header = ['squad', 'day', 'point']
    def __init__(self,file):
        self.LOG_FILE = file+".csv"
        self.file_name = file+".csv"		
        if not os.path.exists(self.LOG_FILE):
                self.append_csv_header = True

    def get_points_squad(self,squad):
        url_token_1="http://localhost:8030/GET?squad="
        url_token_2="&day_point="
        i=1
        while i <= 38:
            url = url_token_1+squad+url_token_2+str(i)
            r =requests.get(url)
            s = str(r.json())
            list=re.findall(r'\b\d+\b',s)
            print(list)
            self.write(squad,list)
            i= i+1      
        
    def write(self,name_squad,list):
        with open(self.file_name, mode="a", newline='', encoding='utf-8') as f:
                csv_writer = csv.writer(f, delimiter=";")
                if self.append_csv_header:
                    self.append_csv_header = False
                    csv_writer.writerow(self.header)
                csv_writer.writerow([name_squad,list[0],list[1]])

            
def main():
    name_file ="file"
    name_squad = "Triestina"
    file = file_csv(name_file)
    file.get_points_squad(name_squad)
    

if __name__ == "__main__":
    main()
