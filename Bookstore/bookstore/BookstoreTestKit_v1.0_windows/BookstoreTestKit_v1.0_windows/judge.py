#coding=utf-8
import os
import time

print("Bookstore test kit --WINDOWS-- //somehow slower than linux's")

temp_dir = 'temp'

test_name = [
    'user test 1',
    'user test 2',
    'user test 3',
    'book test 1',
    'book test 2',
    'book test 3',
    'file test 1',
    'performance test 1',
    'file test 2',
    'performance test 2',
]
test_loc = list(map(lambda x: 'testcase'+str(x),range(1,11)))

exe = 'bookstore.exe'
for i in range(6):
    nw = time.time()
    k = test_name[i]
    loc = test_loc[i]
    os.system('mkdir '+temp_dir+' > log.txt 2> log2.txt')
    os.system('copy '+exe+' '+temp_dir+'\\bookstore.exe > log.txt 2> log2.txt')
    command = 'copy '+'test_data\\'+loc+'.txt '+temp_dir+'\\command.txt > log.txt 2> log2.txt &&cd '+\
        temp_dir+'  &&'+'.\\bookstore.exe > ans.txt 2> cerr.txt;cd ..'
    os.system(command)
    result = os.system('fc test_data\\'+loc+'_ans.txt '+temp_dir+'\\ans.txt > log.txt 2> log2.txt')
    if result != 0:
        print("Stopped at case: "+ str(i))
        exit(1)
    os.system('del '+temp_dir+' /f /s /q /a > log.txt')
    print('case '+str(i+1)+': '+str(k)+"\t-\033[1;32mACCEPT\033[0m-  time:"+str(round(time.time()-nw,3))+'s')

for i in range(6,8):
    nw = time.time()
    k = test_name[i]
    loc = test_loc[i]
    os.system('mkdir '+temp_dir+' > log.txt 2> log2.txt')
    os.system('copy '+exe+' '+temp_dir+'\\bookstore.exe > log.txt 2> log2.txt')
    with open("test_data\\"+loc+"\\config.txt",'r') as f:
        s = int(f.readline())
        for j in range(s):
            command = 'copy '+'test_data\\'+loc+'\\'+str(j+1)+'.txt '+temp_dir+'\\command.txt > log.txt 2> log2.txt && cd '+\
                temp_dir+' && .\\'+'bookstore.exe >> ans.txt 2>> cerr.txt && cd ..'
            os.system(command)
    result = os.system('fc test_data\\'+loc+'\\ans.txt '+temp_dir+'\\ans.txt > log.txt 2> log2.txt')
    if result != 0:
        print("Stopped at case: "+ str(i))
        exit(1)
    os.system('del '+temp_dir+' /f /s /q /a > log.txt')
    print('case '+str(i+1)+': '+str(k)+"\t-\033[1;32mACCEPT\033[0m-  time:"+str(round(time.time()-nw,3))+'s')

print("Congratulations~    --lxy")