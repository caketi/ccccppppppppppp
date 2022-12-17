import inspect

frame = None 
def foo():
    bar()
def bar():
    global frame
    frame = inspect.currentframe()


foo()
print(frame.f_code.co_name)
caller_frame = frame.f_back
print(caller_frame.f_code.co_name)