y=0
s=int(input("enter the 1st digit"))
op = input("enter your operation to carry")
while(op == '+' or op == '-' or op == '*' or op == '/' or op == '='):
    
    y=int(input("enter the next digit"))
    
    if op == '+':
        s=s + y
        print(s)
    elif op == '-':
        s=s-y
        print(s)
    elif op == '*':
        s=s*y
        print(s)
    elif op == '/':
        s=s/y
        print(s)
    elif op == '=':
        print(s)
    op = input("enter your operation to carry")
