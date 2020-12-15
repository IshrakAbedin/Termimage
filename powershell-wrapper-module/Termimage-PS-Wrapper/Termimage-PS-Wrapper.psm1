<#
.Synopsis
Displays an image on terminal.

.Description
Displays an image in the VT100 emulated terminal.
This function supports width and height-weight ratio manipulation.
Uses Termimage (https://www.github.com/ishrakabedin/termimage) for core printing purpose.

.Parameter ImagePath
Path to the image to be displayed.

.Parameter Width
Width of the image to be printed. Represents number of horizontal character blocks.
Default value is the current width of the terminal.

.Parameter Ratio
Height/Width ratio of the image. Since terminal character blocks are not perfect squares generally,
a ratio is required. Default value is 2.2.

.Example
# Show a default display of image fit to the terminal width.
Show-Image .\path-to-image

.Example
# Show a default display of image with fixed width of 100 character blocks.
Show-Image .\path-to-image -Width 100

.Example
# Show a default display of image with width 124 and ratio of 2.5.
Show-Image .\path-to-image -Width 124 -Ratio 2.5
#>

function Show-Image
{
    param (
        [string]$ImagePath,
        [int]$Width = $Host.UI.RawUI.WindowSize.Width,
        [double]$Ratio = 2.2
    )
    Termimage.exe $ImagePath -w $Width -r $Ratio
}

Export-ModuleMember -Function Show-Image