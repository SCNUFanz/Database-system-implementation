import re
import random
import time, os
import csv, math
import numpy as np
import pandas as pd

a_class = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
b_class = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
c_class = a_class + b_class
num_class = [0,1,2,3,4,5,6,7,8,9]

#数据集1
id = 1
for i in range(2000):
    ans = ""
    ans = ans + str(id) + "\t"
    id += 1
    ans = ans + random.choice(a_class) + random.choice(b_class) + "\t"
    for j in range(random.randint(2,5)):
        ans = ans + str(random.choice(num_class))
    ans += "\t"
    for j in range(random.randint(7,12)):
        ans = ans + str(random.choice(c_class))
    ans = ans + "\n"
    with open('data1.txt', 'a', encoding='utf-8') as f:
        f.write(ans)

#数据集2
id = 1
for i in range(999):
    ans = ""
    ans = ans + str(id) + "\t"
    id += 1
    ans = ans + random.choice(a_class) + str(random.choice(num_class)) + "\t"
    ans = ans + random.choice(a_class) + str(random.choice(num_class)) + "\t"
    ans = ans + random.choice(a_class) + random.choice(b_class) + "\t"
    ans = ans + random.choice(a_class) + random.choice(a_class) + str(random.choice(num_class)) + random.choice(b_class) + random.choice(b_class) + "\t"
    ans = ans + random.choice(a_class) + random.choice(a_class)+ str(random.choice(num_class)) + random.choice(b_class) + random.choice(b_class) + "\t"
    ans = ans + random.choice(a_class) + random.choice(a_class) + str(random.choice(num_class)) + random.choice(b_class) + random.choice(b_class)+ "\n"
    with open('data2.txt', 'a', encoding='utf-8') as f:
        f.write(ans)

print("数据集构造完成！")