class Node:
    def __init__(self,val):
        self.val=val
        self.child=[]
        self.parent=None


n=int(input())
parents=[]
dixt={}
for i in range(n):
    dixt[i]=Node(i)
    parents.append(int(input()))
q=int(input())
query=[]
for _ in range(q):
    query.append(list(map(int,input().split())))

for i in range(len(parents)):
    dixt[i].parent=dixt[parents[i]]
    dixt[parents[i]].child.append(dixt[i])
    
for ele in query:
    node=dixt[ele[0]]
    up=ele[1]
    while up!=0:
        node=node.parent
        up-=1
    
    print(node.val)
    
    



