

$files = Get-ChildItem 

foreach ($file in $files) {
    $content = Get-Content -Path $file.FullName 
    $updatedContent = $content -replace 'data-nodeid="(\d+)"', ''
    $updatedContent | Set-Content -Path $file.FullName 
}



# # 读取文本文件内容
# $content = Get-Content -Path "1.md"

# # 定义正则表达式模�?
# $pattern = 'data-nodeid="(\d+)"'

# # 循环处理每一行文�?
# foreach ($line in $content) {
#     # 使用正则表达式替换匹配结果为�?
#     $line = $line -replace $pattern, ''

#     # 输出处理后的文本
#     Write-Output $line
# }

# # 读取文本文件内容
# $text = Get-Content -Path "2.md" -Encoding UTF8

# # 使用正则表达式进行替�?
# $newText = $text -replace 'data-nodeid="(\d+)"', ''

# # 将替换后的文本写回原文件
# $newText | Set-Content -Path "2.md" -Encoding UTF8
