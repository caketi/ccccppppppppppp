ise

dir .\*.md | ForEach {Get-content $_ -Head 1; Get-content $_ -Tail 1}

(get-content LICENSE).Split(@(" ", "."))
Get-Credential

```PowerShell
$list=@()

for($i = 0; $i -le 100; $i++){
    $randomnum = get-random -Maximum 100 -Minimum 50
    $list += $randomnum
}

$list | group-object | sort -Property count


```



-in -notin -match -contains -like
$a="1"
$b=@("1","2")
if ($a -in $b){
    $a 
}
get-content xx | measure -Character -Word -Line
get-childitem | sort -CaseSensitive -Property Length
Measure-Object -Character  -

## com 弹窗
12.4 -as [int] 
         [datetime]\
$wsh =  new-object -com wscript.shell
$wsh.popup('d')

## pipe 
get-process | select name, id, @{name="up-time"; expression={((get-date)-$_.startTime).Totaldays}} 
.createTime

get-commmand -verb update
get-aduser -filter xxx

$DebugPreference 
errorAction
verbose
warning       
stop|inquire|continue|sliently continue 

1,2,3 | %{$_ + 1}

import-csv xxx.txt | foreach{New-Item -Name $_.oldname}
xxx.txt 内容    oldname
                zzzz
                xxxx

get-help 


write-host & write-output
stop-service  xxxx - 


## PowerShell Snapin 
get-pssnapin  使用场景少 未来模块化
add-pssnapin xxxx
publish-module -Name xxx PackagfeManagement -Repository xxxx

## alias & $profile 
set-alias cha get-process
$profile
get-childItem
New-Item -ItemType Directory -Path c:\cdefg

get-help  -online -window
Get-PSProvider
Get-PSDrive
PowerShell Provider     文件系统
                        注册表
                        函数
                        变量
                        别名
                        环境变量
                        证书
                        WSMan
```PowerShell
$docPath = "test.pdf"
$pdfPath = "test.docx"
$wordApp = New-Object -ComObject Word.application
$document = $wordApp.Documents.Open($docPath)
$document.SaveAs([ref] $pdfPath, [ref] 17)
$document.Close()
$document.Quit()
```