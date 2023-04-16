ise

## yaml

## 文件夹稽核 文件监控脚本 PowerBI数据可视化
新建 修改 删除
设置监听目录
定义监听属性 行为
注册监听行为
写入日志
## write-progress
write-progress -activity "xxx" -PercentComplete -Status 
-id -parentid

```ps1
for($i=0; $i -le 100; $i++){
    Write-progress -Status $i -Activity "轮询i" -PercentComplete $i -Id 1
    for($j=0; $j -le 100; $j++){
        Write-progress -Status $j -Activity "轮询j" -PercentComplete $i -ParentId 1
    }
}
```

## Cim common interface model
避免使用rpc135 
wswan 限制 无法通过额外账户登录

get-cimclass win32_share

notepad
get-ciminstance -class win32_process  -filter "name='notepad.exe'" | invoke-cimmethod -name terminate

## wmi wbemtest 基于rpc（135） dcom（445）进行沟通
Root\cimv2
Root\webadministrator -- IIS相关命名空间
Root\MicrosoftDNS 
win32_perfFormattedData_Perfdisk_logicaldisk 
get-wmiobject -class win32_operatingsystem -computername
              -namespace root -class __namespace 

## QRCODE 词云 
pswordcloud 仅支持英文
$poem = get-content -path xx.txt
$poem | new-wordcloud -Path .\test.svg -Imagesize 800 -Typeface "Segoe Print" -FocusWord Caketi -AllowRotation none

## HTML

convertTo-Html
 -property
 -body   
 -head
 -Title
 -cssuri

## webrequest
.parsedhtml.getElementsByTagName

## export to xml

```powershell
$dataall = import-csv xxx.txt -Delimiter " "
$fileloc = "xxx.xml"
$xmlwriter = new-object system.xml.xmltextwriter($filedoc, $null)
$xmlwriter.formatting="indented"
$xmlwriter.indentchar="`t"
$xmlwriter.writestartdocument()
$xmlwriter.writestartelement("sensordata")
$xmlwriter.writecomment("1000 rows sensor data")
$n=0
foreach($data in $dataall){
    $xmlwriter.writestartelement("data")
    $xmlwriter.writeAttributeString("type", "alldata")
    $xmlwriter.writeelementString("date", $data.date)
    $xmlwriter.writeelementString("date", $data.time)
    $xmlwriter.writeelementString("date", $data.temperature)
    $xmlwriter.writeelementString("date", $data.shidu)
    $xmlwriter.writeelementString("date", $data.light)
    $xmlwriter.writeEndElement()
}

$xmlwriter.writeEndElement()
$xmlwriter.writeEndDocument()
$xmlwriter.flush()
$xmlwriter.close()

```

ft format-table
export-clixml
convertto-xml

&gt &lt &amp   &quot

## big(Oracle) mid(MySQL) small(SQLite)


## 数据导入
get-content set-content
import-csv  export-csv 格式化数据提取
select-string out-file

-Delimeter 
-Encoding 

## winRM & WSMan 
service.msc 

- 远程执行
$createfilename = @("c:\log\c", "c:\log\cc")
invoke-command -computername xxx -scriptblock { foreach($fi in $using:createfilename)(new-item -itemtype directory -path $fi)}

get-process | out-gridview -PassThru | get-member 输出表格形式
write-eventlog -logname xxx -source "xxx" -eventid 1111 -entrytype information -message "xxx"

export-csv 

add-content

SET-CONTENT -path E:\test-setcontent.txt 

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