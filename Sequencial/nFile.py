import random

min = 0
max = 36000

file_ref = 'RefFrom' + str(min) + 'to' + str(max) + '.txt'
file_test = 'TestFrom' + str(min) + 'to' + str(max) + '.txt'


with open(file_ref, 'w') as file:
    useful = 0
    while( useful < max):
        useful += 1
        file.write(str(random.randint( int(min) , int(max) )) + '\n')
        
with open(file_test, 'w') as file:
    useful = 0
    while( useful < max):
        useful += 1
        file.write(str(random.randint( int(min) , int(max) )) + '\n')

    



