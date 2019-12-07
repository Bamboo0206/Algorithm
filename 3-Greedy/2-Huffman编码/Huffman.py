code_dict=dict([])
def letter_count(data):
    data=data.lower()
    letter_dict=dict([])
    for c in data:
        if((c in letter_dict)==False):
            letter_dict[c]=1
        else:
            letter_dict[c]=letter_dict[c]+1
    return letter_dict


class node:
    def __init__(self,name=None,value=0):
        self.name=name
        self.value=value
        self.left=None
        self.right=None

def huffman(letter_dict):
    H=[node(name=i,value=letter_dict[i]) for i in letter_dict] # H保存所有树的树根，是小顶堆
    while len(H) != 1: #H= 1 则只有一棵树
        H.sort(key=lambda node:node.value) #用节点权重排序,升序
        # T=node(value=H[0].value + H[1].value) ###？？？？？？？？
        T = node()
        T.left=H.pop(0)
        T.right=H.pop(0)
        T.value = T.left.value + T.right.value
        H.append(T)
    return H[0] #返回树的根节点，是node对象

def coding(root,code):
    if (not root): #none 叶节点
        return
    elif (root.name): #叶节点
        print(root.name+'的编码为：',code)
        code_dict[root.name]=code[:] #不能直接=code，否则list是浅拷贝
    # else: #非叶节点
    code.append(0)
    coding(root.left,code)
    code.pop()
    code.append(1)
    coding(root.right,code)
    code.pop()

def encode(text,code_dict,fout):
    text = text.lower()
    BYTE_SIZE=8
    cur = 0  # 待输出的一个字节的编码串
    size = 0  # 当前待输出的比特数
    for c in text:
        code=code_dict[c]
        for i in code:
            if i == 0:
                cur = cur << 1
            else:
                cur = (cur << 1 ) | 1
            size +=1
            if (size==BYTE_SIZE): #写一个字节
                fout.write(cur.to_bytes(1, 'little'))
                size = 0
                cur = 0
    if size:
        # 不足一个字节
        cur = cur << (BYTE_SIZE-size)
        fout.write(cur.to_bytes(1, 'little'))

def compress(text,code_dict):
    fout=open("Huffman_output.huffman",'wb')
    encode(text,code_dict,fout)
    fout.close()

def main():
    file = open('HuffmanData.txt', 'r')
    data = file.read()
    file.close()
    letter_dict=letter_count(data)
    Tree=huffman(letter_dict)
    coding(Tree,[])
    compress(data,code_dict)

if __name__=='__main__':
    main()