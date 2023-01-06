import hashlib


door = 'ffykfhsq'
index = 0 
res1 = ''
res2 = ['@'] * 8
rem2 = 8
while len(res1) < 8 or rem2 > 0:
    md5 = hashlib.md5(f'{door}{index}'.encode('utf-8')).hexdigest()
    if md5[:5] == '00000':
        if len(res1) < 8:
            res1 += md5[5]
        position = ord(md5[5]) - ord('0')
        if 0 <= position <= 7 and res2[position] == '@':
            res2[position] = md5[6]
            rem2 -= 1
    index += 1
print('Part 1: ', res1)
print('Part 1: ', ''.join(res2))
