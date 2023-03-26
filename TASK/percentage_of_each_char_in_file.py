lis=('a','b','c','d','e','f')
with open("file.txt") as f:
    var=f.read()
##    print(var)
def counts(let):
    count=0;
    for i in var:
        if(let==i):
            count=count+1
    return (count/len(var)*100)

for i in lis:
    print(i,":",counts(i),"%")
