class e(object):
    def __abs__(self):
        pass
        # return abs(self.num)
    def __init__(self, e_list):
        self.e = e_list

    def __getitem__(self, item):
        return self.e[item]

    def __len__(self):
        return len(self.e)
    def __str__(self):
        return ",".join(self.e)

    def __repr__(self):
        return ",".join(self.e)


e1 = e(["a", "b"])
for item in e1:
    print(item)
print(len(e1))
e2 = e1[:4]
print(len(e2))

a = 1
b = "abc"
print(type(1))
print(type(int))
print(type(b))
print(type(str))
# type->int->1
# type->class->obj
# class st:
#     pass
# class stt(st):
#     pass
# st = st()
# stt = stt()
# print(type(st))
# print(type(stt))
print(int.__bases__)
print(str.__bases__)
# print(st.__bases__)
# print(stt.__bases__)
print(type.__bases__)
print(object.__bases__)
print(type.__bases__)

a = None
b = None
print(id(a) == id(b))
