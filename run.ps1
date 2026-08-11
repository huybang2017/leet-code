param(
    [string]$file = "",
    [switch]$clean,
    [switch]$Debug
)

# ============================================================
# Find source file
# ============================================================

if (-not $file) {
    # No file specified -> use the most recently modified .cpp
    $latest = Get-ChildItem "*.cpp" -File |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1

    if (-not $latest) {
        Write-Host "Khong tim thay file .cpp nao." -ForegroundColor Red
        exit 1
    }

    $file = $latest.Name
}

# Support:
#   .\run.ps1 7
#   .\run.ps1 7_reverse_integer
#   .\run.ps1 7_reverse_integer.cpp

if ($file -match '^\d+$') {
    $found = Get-ChildItem "${file}_*.cpp" -File |
        Select-Object -First 1

    if ($found) {
        $file = $found.Name
    }
    else {
        $file = "${file}.cpp"
    }
}

# Add .cpp extension if missing
if (-not $file.EndsWith(".cpp", [System.StringComparison]::OrdinalIgnoreCase)) {
    $file += ".cpp"
}

# ============================================================
# Validate source file
# ============================================================

if (-not (Test-Path -LiteralPath $file -PathType Leaf)) {
    Write-Host "Khong tim thay: $file" -ForegroundColor Red
    exit 1
}

$file = (Resolve-Path -LiteralPath $file).Path
$exe = [System.IO.Path]::ChangeExtension($file, ".exe")

# ============================================================
# Build
# ============================================================

if ($Debug) {
    $buildFlags = @(
        "-std=c++17"
        "-g"
        "-O0"
        "-Wall"
        "-Wextra"
    )

    Write-Host "Building DEBUG: $([System.IO.Path]::GetFileName($file))" -ForegroundColor Cyan
}
else {
    $buildFlags = @(
        "-std=c++17"
        "-O2"
        "-Wall"
        "-Wextra"
    )

    Write-Host "Building: $([System.IO.Path]::GetFileName($file))" -ForegroundColor Cyan
}

Write-Host ""

& g++ @buildFlags -o $exe $file

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Compile that bai!" -ForegroundColor Red
    exit $LASTEXITCODE
}

# ============================================================
# Run
# ============================================================

Write-Host ""
Write-Host "Running $([System.IO.Path]::GetFileName($exe)) ..." -ForegroundColor Cyan
Write-Host ""

& $exe
$exitCode = $LASTEXITCODE

# ============================================================
# Cleanup
# ============================================================

if ($clean) {
    Remove-Item -LiteralPath $exe -Force -ErrorAction SilentlyContinue
    Write-Host ""
    Write-Host "Da xoa $([System.IO.Path]::GetFileName($exe))" -ForegroundColor DarkGray
}

exit $exitCode