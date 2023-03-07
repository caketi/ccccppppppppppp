# Get-ChildItem .\*.md | ForEach-Object {Get-content $_ -Head 1; Get-content $_ -Tail 1}

function DF {
    # DF -mf $true -fn t.txt -fdir E:\ww\ -desDir E:\ww\test
    [cmdletbinding()]param (
        #newfile
        [Parameter(Mandatory, ParameterSetName = "nf")]
        [bool]
        $nf,
        [Parameter(Mandatory, ParameterSetName = "df")]
        [bool]
        $df,
        [Parameter(Mandatory, ParameterSetName = "mf")]
        [bool]
        $mf,
        [Parameter(ValueFromPipelineByPropertyName)]
        [string]
        $fn,
        [Parameter(ValueFromPipelineByPropertyName)]
        [string]
        $fdir,
        [Parameter(Mandatory, ParameterSetName = "mf")]
        [string]
        $desDir
    )
    process {
        if ($nf -eq $true) {
            if (!(Test-Path $fdir)) {
                New-Item -ItemType Directory -Path $fdir
                Write-Verbose -Verbose "creating dir...."
            }
            $newfilepath = $fdir + "\" + $fn
            New-Item -Path $newfilepath
            Write-Verbose -Verbose "creating file..."
        }
        if ($df -eq $true) {
            $dfpath = $fdir + "\" + $fn     
            Remove-Item -Path $dfpath
            Write-Verbose -Verbose "deleting file ...."   
        }
        if($mf -eq $true){
            $srcfPath = $fdir +"\" +$fn
            Write-Verbose -Verbose "src path building ..."
            if(!(Test-Path $desDir)){
                new-item -ItemType Directory -path $desDir
                Write-Verbose -Verbose "creating desDir ..."
            }
            $desPath = $desDir + "\" + $fn
            Write-Verbose -Verbose "des path building..."
            Move-Item -path $srcfPath -Destination $desPath
            Write-Verbose -Verbose "moving file ..."
        }
    }
}




$allevent = Get-EventLog -LogName Application | where { $_.TimeGenerated -gt (Get-Date).AddDays(-5) }
$alleventcount = ($allevent | Measure-Object).Count
$allerroreventcount = (Get-EventLog -LogName Application | where { ($_.TimeGenerated -gt (get-date).AddDays(-5)) -and ($_.EntryType -eq "
error") }).count
foreach ($event in $allevent) {
    if ($event.Message -match "软件保护") {
        Write-Host $event.Message
    }
}

$LIST = @(1, "ss")
foreach ($b in $LIST) {
    if ($b -isnot [int]) {
        Write-Host $b "is not int"
    }
}

$a = Import-Csv xxx.txt
$name = @{expression = "name"; width = 5; label = "username"; alignment = "left" }
$street = @{expression = "street"; width = 5; label = "username"; alignment = "left" }

$a | ft $name, $street


$session = New-PSSession -ComputerName testSession

Invoke-Command -ComputerName $session -ScriptBlock { Start-Job -name newdir

    -ScriptBlock { New-Item -ItemType Directory -Path E:\111111 } }

Enter-PSSession xxxx

$day = get-date
$day.tostring("yyyy-MM-dd-HH-mm-ss")
$day.AddDays(12111)

"caketi".Length
"caketi".Contains("f")
"caketi".Split("")
"caketi".Replace("c", "C")
"caketi".Trim()
"caketi".Substring(0, 2)

