param([switch]$ConfigureOnly)
$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$projectShort = (New-Object -ComObject Scripting.FileSystemObject).GetFolder($projectRoot).ShortPath
$registry = Join-Path $projectRoot '.tools/eim_idf.json'
if (!(Test-Path $registry)) { throw 'Registro local ausente. Consulte a secao de compilacao do README.' }
$installation = (Get-Content $registry -Raw | ConvertFrom-Json).idfInstalled |
    Where-Object { $_.name -eq 'v5.4.2' } | Select-Object -First 1
if (!$installation) { throw 'ESP-IDF v5.4.2 nao encontrado no registro local.' }
# Ler as variaveis evita executar o perfil que altera a politica do PowerShell.
$env:PYTHONDONTWRITEBYTECODE = '1'
$variables = & $installation.activationScript -e 6>&1
foreach ($line in $variables) {
    if ("$line" -match '^([A-Z_]+)=(.*)$' -and $Matches[1] -ne 'SYSTEM_PATH') {
        if ($Matches[1] -eq 'PATH') { $env:PATH = $Matches[2] + ';' + $env:PATH }
        else { Set-Item -Path "Env:$($Matches[1])" -Value $Matches[2] }
    }
}
$env:TEMP = "$projectShort\.tools\tmp"
$env:TMP = $env:TEMP
$env:CCACHE_DIR = "$projectShort\.tools\cache\ccache"
$env:IDF_COMPONENT_CACHE_PATH = "$projectShort\.tools\cache\components"
$env:IDF_TARGET = 'esp32s3'
$localCompiler = "$projectShort\.tools\toolchain\xtensa-esp-elf\bin"
if (Test-Path $localCompiler) { $env:PATH = $localCompiler + ';' + $env:PATH }
$env:SENSOR_COMPILER_DIR = $localCompiler
New-Item -ItemType Directory -Force $env:TEMP,"$projectRoot/evidencias" | Out-Null
Push-Location $projectShort
try {
    $action = if ($ConfigureOnly) { 'reconfigure' } else { 'build' }
    $ErrorActionPreference = 'Continue'
    & $installation.python "$env:IDF_PATH/tools/idf.py" -C $projectShort -B "$projectShort\build" -D "CMAKE_PROJECT_INCLUDE_BEFORE=$projectShort/scripts/select-toolchain.cmake" $action 2>&1 |
        Tee-Object -FilePath "$projectRoot/evidencias/build.log"
    $buildExitCode = $LASTEXITCODE
    $logPath = "$projectRoot/evidencias/build.log"
    $logText = Get-Content -LiteralPath $logPath -Raw
    [System.IO.File]::WriteAllText($logPath, $logText, (New-Object System.Text.UTF8Encoding($false)))
    if ($buildExitCode -ne 0) { throw "Compilacao falhou: $buildExitCode" }
} finally { Pop-Location }
