# dex文件格式

string_list 绝对指针-》String_data_item
type_list 相对指针-》string_list的结构体索引
jadx-gui 
**结构体面向**
DexClassLoader加载时会验证checksum
magic
checksum
SHA1 signature[20]
uint file_size
uint header_size
uint endian_tag