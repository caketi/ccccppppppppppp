print(_VERSION)
a = 0
while a ~= 5 do 
    a= a+1
    io.write(a.." ")
end

for a = 1, 4, 2 do io.write(a) end

function printf(fmt, ...)
    io.write(string.format(fmt, ...))
end
printf("cc %s from %s on %s \n", os.getenv"USER" or "there", _VERSION, os.date())