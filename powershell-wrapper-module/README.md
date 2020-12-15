# A Powershell Module wrapper around Termimage

This module wrapper works to ease the use of Termimage from Powershell. When any optional `Width` parameter is not passed, is takes the window width of terminal as the width, fitting the image properly with the console. Works best with *emulated terminals* like **Windows Terminal**.

> Requires *Termimage.exe* path to be under *system environment variables*. Alternatively, the module can be edited to set a hardcoded path to *Termimage.exe*.
---
## Importing the Module
---
Keep the module in one of the powershell module directories such as `C:\Users\UserName\Documents\PowerShell\Modules` or navigate to the directory where the module is located.

Import module using,
```powershell
# Exports function Show-Image
Import-Module Termimage-PS-Wrapper
```

Tested with **PSCORE**. *The module importing can be put in the profile script of Powershell, directory of which is accessible using the ENVIRONMENT VARIABLE* `$PROFILE`.

---
## Using Show-Image Function
---
Show a default display of image fit to the terminal width.

```powershell
Show-Image .\PathToImage
```

Show a default display of image with fixed width of 100 character blocks.

```powershell
Show-Image .\PathToImage -Width 100
```

Show a default display of image with width 124 and ratio of 2.5.

```powershell
Show-Image .\PathToImage -Width 124 -Ratio 2.5
```

### Parameters

* `-ImagePath` *Path to the image to be displayed.*

* `-Width` *Width of the image to be printed. Represents number of horizontal character blocks. Default value is the current width of the terminal.*

* `-Ratio` *Height/Width ratio of the image. Since terminal character blocks are not perfect squares generally, a non-one ratio is required. Default value is 2.2.*