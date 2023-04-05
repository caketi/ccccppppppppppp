 param(
[string]$location="e:\ww",
[int]$quality,
[switch]$allscreen,
[switch]$long
)
Add-Type -AssemblyName System.Windows.Forms
if($long.IsPresent){
    while($true){
        if($allscreen.IsPresent)
{

$Capture = [System.Windows.Forms.Screen]::AllScreens 
}
else
{
$Capture = [System.Windows.Forms.Screen]::PrimaryScreen
}
if ($AllScreens)
{
    $Capture = [System.Windows.Forms.Screen]::AllScreens 
}
else
{
    $Capture = [System.Windows.Forms.Screen]::PrimaryScreen
}
foreach ($C in $Capture)
{
    $filename=$location+(get-date).ToString("yyyy-MM-dd-HH-mm-ss")+".jpg"
    $Bitmap = New-Object System.Drawing.Bitmap($C.Bounds.Width, $C.Bounds.Height)
    $G = [System.Drawing.Graphics]::FromImage($Bitmap)
    $G.CopyFromScreen($C.Bounds.Location, (New-Object System.Drawing.Point(0,0)), $C.Bounds.Size)
    $g.Dispose()
    $EncoderParam = [System.Drawing.Imaging.Encoder]::Quality
    $EncoderParamSet = New-Object System.Drawing.Imaging.EncoderParameters(1) 
    $EncoderParamSet.Param[0] = New-Object System.Drawing.Imaging.EncoderParameter($EncoderParam, $Quality) 
    $JPGCodec = [System.Drawing.Imaging.ImageCodecInfo]::GetImageEncoders() | Where{$_.MimeType -eq 'image/jpeg'}
    $Bitmap.Save($FileName ,$JPGCodec, $EncoderParamSet)
}
 }
 sleep(5)
}

else{
     if($allscreen.IsPresent)
{

$Capture = [System.Windows.Forms.Screen]::AllScreens 
}
else
{
$Capture = [System.Windows.Forms.Screen]::PrimaryScreen
}
if ($AllScreens)
{
    $Capture = [System.Windows.Forms.Screen]::AllScreens 
}
else
{
    $Capture = [System.Windows.Forms.Screen]::PrimaryScreen
}
foreach ($C in $Capture)
{
    $filename=$location+(get-date).ToString("yyyy-MM-dd-HH-mm-ss")+".jpg"
    $Bitmap = New-Object System.Drawing.Bitmap($C.Bounds.Width, $C.Bounds.Height)
    $G = [System.Drawing.Graphics]::FromImage($Bitmap)
    $G.CopyFromScreen($C.Bounds.Location, (New-Object System.Drawing.Point(0,0)), $C.Bounds.Size)
    $g.Dispose()
    $EncoderParam = [System.Drawing.Imaging.Encoder]::Quality
    $EncoderParamSet = New-Object System.Drawing.Imaging.EncoderParameters(1) 
    $EncoderParamSet.Param[0] = New-Object System.Drawing.Imaging.EncoderParameter($EncoderParam, $Quality) 
    $JPGCodec = [System.Drawing.Imaging.ImageCodecInfo]::GetImageEncoders() | Where{$_.MimeType -eq 'image/jpeg'}
    $Bitmap.Save($FileName ,$JPGCodec, $EncoderParamSet)
}}