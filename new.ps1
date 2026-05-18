param([string]$name)

if (-not $name) {
    Write-Host "Usage: ./new.ps1 <ten_bai>" -ForegroundColor Yellow
    Write-Host "  VD:  ./new.ps1 1_two_sum" -ForegroundColor Yellow
    Write-Host "  VD:  ./new.ps1 146_lru_cache" -ForegroundColor Yellow
    exit 1
}

if (-not $name.EndsWith('.cpp')) { $name += '.cpp' }

if (Test-Path $name) {
    Write-Host "File da ton tai: $name" -ForegroundColor Red
    exit 1
}

Copy-Item template.cpp $name
Write-Host "Tao file: $name" -ForegroundColor Green

# Mở file nếu có editor
$editors = @("code", "nvim", "vim", "notepad")
foreach ($ed in $editors) {
    if (Get-Command $ed -ErrorAction SilentlyContinue) {
        & $ed $name
        break
    }
}
