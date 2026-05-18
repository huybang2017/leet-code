param(
    [string]$file = "",
    [switch]$clean
)

# Nếu không truyền file, lấy file .cpp mới nhất trong thư mục hiện tại
if (-not $file) {
    $latest = Get-ChildItem "*.cpp" -File | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $latest) { Write-Host "Khong tim thay file .cpp nao." -ForegroundColor Red; exit 1 }
    $file = $latest.Name
}

# Hỗ trợ truyền số bài: ./run.ps1 1 -> tìm 1_*.cpp
if ($file -match '^\d+$') {
    $found = Get-ChildItem "${file}_*.cpp" -File | Select-Object -First 1
    if ($found) { $file = $found.Name }
    else { $file = "${file}.cpp" }
}

if (-not $file.EndsWith('.cpp')) { $file += '.cpp' }

if (-not (Test-Path $file)) {
    Write-Host "Khong tim thay: $file" -ForegroundColor Red
    exit 1
}

$exe = $file -replace '\.cpp$', '.exe'

Write-Host "Compiling $file ..." -ForegroundColor Cyan
g++ -std=c++17 -O2 -Wall -Wextra -o $exe $file 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compile that bai!" -ForegroundColor Red
    exit 1
}

Write-Host "Running..." -ForegroundColor Cyan
Write-Host ""
& ".\$exe"
$exitCode = $LASTEXITCODE

if ($clean) { Remove-Item $exe -ErrorAction SilentlyContinue }

exit $exitCode
