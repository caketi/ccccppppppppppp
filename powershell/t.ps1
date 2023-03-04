# Get-ChildItem .\*.md | ForEach-Object {Get-content $_ -Head 1; Get-content $_ -Tail 1}

$session = New-PSSession -ComputerName testSession

Invoke-Command -ComputerName testSession -ScriptBlock {Start-Job -name newdir

-ScriptBlock { New-Item -ItemType Directory -Path E:\111111}}

Enter-PSSession testSession