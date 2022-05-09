# %%
arr = [] 
flag = True
for l in open("insurance.csv","rt"):
    if flag:
        flag = False
        continue
    arr.append(int(l.split(",")[0]))

# %%
sum(arr)/len(arr)

