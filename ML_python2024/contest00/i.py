st = []
str = input()

res = True

for sym in str:
    if sym in '([{<':
        st.append(sym)
    elif sym == ')':
        if len(st) == 0 or st[-1] != '(':
            res = False
            break
        else:
            st.pop()
    elif sym == ']':
        if len(st) == 0 or st[-1] != '[':
            res = False
            break
        else:
            st.pop()
    elif sym == '}':
        if len(st) == 0 or st[-1] != '{':
            res = False
            break
        else:
            st.pop()
    elif sym == '>':
        if len(st) == 0 or st[-1] != '<':
            res = False
            break
        else:
            st.pop()

if len(st) > 0:
    res = False

print("YES") if res else print("NO")