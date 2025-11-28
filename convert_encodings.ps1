$extensions = @('.cpp', '.h', '.cs', '.idl', '.xaml')
$excludeDirs = @('AppPackages', 'ARM64', 'Debug', 'Release', 'packages', 'x64', 'node_modules', '.git', '.vs', 'bin', 'obj')

Write-Host "Scanning for source files..."
$files = Get-ChildItem -Path . -Recurse -File | Where-Object {
    $file = $_
    if ($extensions -notcontains $file.Extension) { return $false }
    
    $pathParts = $file.FullName.Split([System.IO.Path]::DirectorySeparatorChar)
    foreach ($dir in $excludeDirs) {
        if ($pathParts -contains $dir) { return $false }
    }
    return $true
}

Write-Host "Found $($files.Count) files. Starting conversion..."

foreach ($file in $files) {
    try {
        $content = Get-Content -LiteralPath $file.FullName -Raw
        # Use -NoNewline to prevent Set-Content from adding an extra newline at the end
        $content | Set-Content -LiteralPath $file.FullName -Encoding utf8BOM -NoNewline
    }
    catch {
        Write-Error "Failed to process $($file.Name): $_"
    }
}

Write-Host "All done. Converted $($files.Count) files to UTF-8 BOM."
